#pragma once

#include <Arduino.h>

#define MIN_STATE_TIME 5000
#define TRANSISTOR_PIN D5
#define STORAGE_VOLTAGE 3.8

enum dcstate {
	OFF,
	QUARTER,
	HALF,
	THREEQUARTER,
	FULL
};

class PinHelper
{
public:
	PinHelper();
	void Update(float vpc, ulong now);
	ulong DcTime;
private:
	ulong _lastChange;
	dcstate _state;
	byte GetStateByte();
	dcstate ChangeState(byte delta, ulong now);
	void ApplyState(void);
	void SetPinsD(uint16_t trans, uint16_t led);
	void SetPinsA(uint16_t trans, uint16_t led);
};
