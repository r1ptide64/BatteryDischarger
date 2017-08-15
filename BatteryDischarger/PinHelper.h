#pragma once

#include <Arduino.h>

#define MIN_STATE_TIME 12500
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
	dcstate State(void);
private:
	ulong _lastChange;
	dcstate _state;
	int8_t GetStateInt();
	dcstate ChangeState(int8_t delta, ulong now);
	void ApplyState(void);
};
