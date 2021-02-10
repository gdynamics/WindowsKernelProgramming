#pragma once

struct ThreadData {
	unsigned long ThreadId;
	int Priority;
};

#define PRIORITY_BOOSTER_DEVICE 0x8000

#define IOCTL_PRIORITY_BOOSTER_SET_PRIORITY CTL_CODE(PRIORITY_BOOSTER_DEVICE, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)