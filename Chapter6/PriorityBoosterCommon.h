#pragma once

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