#include <ntddk.h>

void Chapter2Unload(_In_ PDRIVER_OBJECT DriverObject);
void PrintVersion(void);

extern "C"
NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);

	DriverObject->DriverUnload = Chapter2Unload;

	KdPrint(("Sample driver initialized successfully\n"));

	PrintVersion(); // Exercise 1

	return STATUS_SUCCESS;
}

void Chapter2Unload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);

	KdPrint(("Sample driver unload called"));
}

void PrintVersion() {
	_Out_ RTL_OSVERSIONINFOW WindowsVersion;
	RtlZeroMemory(&WindowsVersion, sizeof(PRTL_OSVERSIONINFOW));
	RtlGetVersion(&WindowsVersion);

	KdPrint(("Windows version %d.%d, build %ul\n",
		WindowsVersion.dwMajorVersion,
		WindowsVersion.dwMinorVersion,
		WindowsVersion.dwBuildNumber));
}
