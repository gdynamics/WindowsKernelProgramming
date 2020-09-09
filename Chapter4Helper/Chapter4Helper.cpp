#include <windows.h>
#include <stdio.h>
#include "..\Chapter4\PriorityBoosterCommon.h"

int Error(const char* message);

int main(int argc, const char* argv[]) {
	if (argc < 3) {
		printf("Usage: Booster <threadid> <priority>\n");
		return ERROR_BAD_ARGUMENTS;
	}

	HANDLE hDevice = CreateFile(L"\\\\.\\PriorityBooster", GENERIC_WRITE,
		FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hDevice == INVALID_HANDLE_VALUE) {
		return Error("Failed to open device");
	}

	ThreadData data;
	data.ThreadId = atoi(argv[1]);
	data.Priority = atoi(argv[2]);

	DWORD returned;
	BOOL success = DeviceIoControl(hDevice,
		IOCTL_PRIORITY_BOOSTER_SET_PRIORITY,
		&data, sizeof(data),
		nullptr, 0,
		&returned,
		nullptr);
	if (success) {
		printf("Priority change succeeded!\n");
	} else {
		Error("Priority change failed!");
	}

	CloseHandle(hDevice);

}

int Error(const char* message) {
	DWORD LastError = GetLastError();
	printf("%s (error=%d)\n", message, LastError);
	return LastError;
}