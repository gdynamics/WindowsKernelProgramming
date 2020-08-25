#include <ntddk.h>

void Chapter2Unload(_In_ PDRIVER_OBJECT DriverObject);

extern "C"
NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	DriverObject->DriverUnload = Chapter2Unload;

	return STATUS_SUCCESS;
}

void Chapter2Unload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
}