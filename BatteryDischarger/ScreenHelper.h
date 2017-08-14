#pragma once

#include <Arduino.h>
#include <brzo_i2c.h>
#include <SSD1306Brzo.h>
#include "VoltageHelper.h"
#include "PinHelper.h"

#define SCREEN_PERIOD 1000

class ScreenHelper
{
public:
	ScreenHelper(void);
	void Update(VoltageHelper *vh, PinHelper *ph, ulong now);
	void Update(float voltage, byte numCells, ulong dcTime, ulong onTime);

private:
	SSD1306Brzo *_display;
	String GetVoltageString(float voltage);
	String GetCellsString(byte numCells);
	String GetTimeString(ulong time);
	ulong _lastUpdate;
};