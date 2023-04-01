#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <stdint.h>

#define SETTINGS_VER_NONE		(0x00000000)
#define SETTINGS_VER_1			(0x00000001)

struct SettingsHeader {
	uint32_t magic;
	uint64_t revision;
	uint8_t structVersion;
	uint8_t structSize;			//incl this header
};

enum SettingsThingType {
	SettingsThingTypeNone,
	SettingsThingTypeImage,
	SettingsThingTypeUpdate,
};

struct Settings { //V3, limited to 255b by code
	struct SettingsHeader hdr;
	uint8_t initialized;
	
	//master address
	uint8_t masterMac[8];
	uint16_t panId;
	
	//encryption things
	uint32_t encrKey[4];
	uint32_t nextIV;
	
	//checkin tracking
	uint32_t checkinDelay;					//space between checkins, in msec
	uint32_t retryDelay;
	uint16_t failedCheckinsTillBlank;		//how many fails till we go blank
	uint16_t failedCheckinsTillDissoc;		//how many fails till we dissociate
	uint16_t numFailedCheckins;
	uint16_t prevDlProgress;
	
	
	//state
	uint8_t lastRxedLQI;
	int8_t lastRxedRSSI;
	uint8_t isPaired				: 1;
	uint8_t channel					: 4;
	uint8_t reserved				: 3;
	
	//these two are for picture frame mode only
	uint8_t checkinsToFlipCtr;
	uint16_t lastShownImgSlotIdx;

	uint32_t helperInit;
};

#define SETTINGS_CURRENT		SETTINGS_VER_1


void settingsRead(struct Settings __xdata *settings);
void settingsWrite(struct Settings __xdata *settings);


void settingsTest(void);



#endif
