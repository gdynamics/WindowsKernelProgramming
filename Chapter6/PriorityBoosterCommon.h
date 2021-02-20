#pragma once
#include <wdm.h>

struct ThreadData {
	unsigned long ThreadId;
	int Priority;
};

#define PRIORITY_BOOSTER_DEVICE 0x8000

#define IOCTL_PRIORITY_BOOSTER_SET_PRIORITY CTL_CODE(PRIORITY_BOOSTER_DEVICE, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

template<typename T = void>
class kunique_ptr {
	T* _p;
public:
	kunique_ptr(T* p = nullptr) : _p(p) {}

	~kunique_ptr() {
		if (_p)
			ExFreePool(_p);
	}

	T* operator->() const {
		return _p;
	}

	T& operator*() const {
		return *_p;

	}
};

struct Mutex {
	KMUTEX _mutex;
public:
	void Init() {
		KeInitializeMutex(&_mutex, 0);
	}

	void Lock() {
		KeWaitForSingleObject(&_mutex, Executive, KernelMode, FALSE, nullptr);
	}

	void Unlock() {
		KeReleaseMutex(&_mutex, FALSE);
	}
};

template<typename TLock>
struct AutoLock {
	TLock* _lock;
public:
	AutoLock(TLock& lock) : _lock(lock) {
		lock.Lock();
	}

	~AutoLock() {
		_lock.Unlock();
	}
};

// Utilizes the AutoLock RAII struct
class FastMutex {
	FAST_MUTEX _mutex;
public:
	void Init() {
		ExInitializeFastMutex(&_mutex);
	}

	void Lock() {
		ExAcquireFastMutex(&_mutex);
	}

	void Unlock() {
		ExReleaseFastMutex(&_mutex);
	}
};

struct AutoEResource {
	_ERESOURCE _eresource;
public:
	void Init() {
		ExInitializeResourceLite(&_eresource);
	}

	void Share() {
		ExAcquireResourceSharedLite(&_eresource, TRUE);
	}

	void Exclusive() {
		ExEnterCriticalRegionAndAcquireResourceExclusive(&_eresource);
	}

	void Downgrade() {
		ExConvertExclusiveToSharedLite(&_eresource);
	}

	void Release() {
		ExReleaseResourceLite(&_eresource);
	}

	~AutoEResource() {
		Release();
	}
};