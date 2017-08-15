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
	int8_t delta;
	if (_lastChange > 0 && _lastChange + MIN_STATE_TIME > now && _state == FULL) {
		delta = 0;
	}
	else if (vpc > STORAGE_VOLTAGE) {
		delta = 1;
	}
	else {
		delta = -1;
	}
	Serial.println(String("ph: delta = " + String(delta) + ", vpc = " + String(vpc)));
	_state = ChangeState(delta, now);
	Serial.println(String("ph: new _state = " + String(_state)));
	ApplyState();
}

dcstate PinHelper::State(void)
{
	return _state;
}

int8_t PinHelper::GetStateInt()
{
	return (int8_t)_state;
}

dcstate PinHelper::ChangeState(int8_t delta, ulong now)
{
	int8_t newEnumVal = GetStateInt() + delta;
	newEnumVal = max(min(newEnumVal, 4), 0);
	dcstate retVal = (delta >= 0) ? FULL : OFF; //(dcstate)newEnumVal;
	if (retVal != _state) {
		_lastChange = now;
	}
	return retVal;
}

void PinHelper::ApplyState(void)
{
	uint16_t ledVal, transVal;
	Serial.println(String("ph.ApplyState: _state = " + String(_state)));
	switch (_state)
	{
	case QUARTER:
		ledVal = 765;
		transVal = 255;
		break;
	case HALF:
		ledVal = 511;
		transVal = 511;
		break;
	case THREEQUARTER:
		ledVal = 255;
		transVal = 765;
		break;
	case FULL:
		ledVal = LOW;
		transVal = HIGH;
		break;
	default: // OFF
		ledVal = HIGH;
		transVal = LOW;
		break;
	}
	Serial.println(String("ph.ApplyState: transVal = " + String(transVal)));
	if (1) { //ledVal == LOW || ledVal == HIGH) {
		digitalWrite(TRANSISTOR_PIN, transVal);
		digitalWrite(BUILTIN_LED, ledVal);
	}
	//else {
	//	analogWrite(TRANSISTOR_PIN, transVal);
	//	analogWrite(BUILTIN_LED, ledVal);
	//}
	if (GetStateInt() > 0) {
		DcTime += 1000;
	}
}