#include "PinHelper.h"

PinHelper::PinHelper()
{
	_lastChange = 0;
	_state = OFF;
	pinMode(TRANSISTOR_PIN, OUTPUT);
	pinMode(BUILTIN_LED, OUTPUT);
}

void PinHelper::Update(float vpc, ulong now)
{
	byte delta;
	if (_lastChange > 0 && _lastChange + MIN_STATE_TIME < now) {
		delta = 0;
	}
	else if (vpc > STORAGE_VOLTAGE) {
		delta = 1;
	}
	else {
		delta = -1;
	}
	_state = ChangeState(delta, now);
	ApplyState();
}

byte PinHelper::GetStateByte()
{
	return (byte)_state;
}

dcstate PinHelper::ChangeState(byte delta, ulong now)
{
	byte newEnumVal = GetStateByte() + delta;
	newEnumVal = min(max(newEnumVal, 4), 0);
	dcstate retVal = (dcstate)newEnumVal;
	if (retVal != _state) {
		_lastChange = now;
	}
	return retVal;
}

void PinHelper::ApplyState(void)
{
	uint16_t ledVal, transVal;
	void(*fun)(uint16_t, uint16_t);
	switch (_state)
	{
	case QUARTER:
		ledVal = 765;
		transVal = 255;
		fun = &this->SetPinsA;
		break;
	case HALF:
		ledVal = 511;
		transVal = 511;
		fun = &this->SetPinsA;
		break;
	case THREEQUARTER:
		ledVal = 255;
		transVal = 765;
		fun = &this->SetPinsA;
		break;
	case FULL:
		ledVal = LOW;
		transVal = HIGH;
		break;
	default: // OFF
		ledVal = HIGH;
		transVal = LOW;
		fun = &this->SetPinsD;
		break;
	}
	fun(transVal, ledVal);
	if (GetStateByte() > 0) {
		DcTime++;
	}
}

void PinHelper::SetPinsD(uint16_t trans, uint16_t led)
{
	digitalWrite(TRANSISTOR_PIN, trans);
	digitalWrite(BUILTIN_LED, led);
}

void PinHelper::SetPinsA(uint16_t trans, uint16_t led)
{
	analogWrite(TRANSISTOR_PIN, trans);
	analogWrite(BUILTIN_LED, led);
}