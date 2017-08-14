#include "ScreenHelper.h"

ScreenHelper::ScreenHelper(void)
{
	_display = new SSD1306Brzo(0x3c, D2, D3);
	_display->init();
	_display->flipScreenVertically();
	_display->setFont(ArialMT_Plain_16);
	_lastUpdate = 0;
}

void ScreenHelper::Update(VoltageHelper * vh, PinHelper * ph, ulong now)
{
	if (_lastUpdate > 0 && _lastUpdate + SCREEN_PERIOD < now) {
		return;
	}
	_lastUpdate = now;
	String voltageString = GetVoltageString(vh->VTot);
	String cellsString = GetCellsString(vh->NumCells);
	String dcTimeString = GetTimeString(ph->DcTime / 1000);
	String onTimeString = GetTimeString(now / 1000);
	_display->clear();
	_display->setTextAlignment(TEXT_ALIGN_LEFT);
	_display->drawString(0, 0, voltageString);
	_display->drawString(0, 12, dcTimeString);
	_display->setTextAlignment(TEXT_ALIGN_RIGHT);
	_display->drawString(0, 0, cellsString);
	_display->drawString(0, 12, onTimeString);
	_display->display();
}

void ScreenHelper::Update(float voltage, byte numCells, ulong dcTime, ulong onTime)
{
	String voltageString = GetVoltageString(voltage);
	String cellsString = GetCellsString(numCells);
	String dcTimeString = GetTimeString(dcTime);
	String onTimeString = GetTimeString(onTime);
	_display->clear();
	_display->setTextAlignment(TEXT_ALIGN_LEFT);
	_display->drawString(0, 0, voltageString);
	_display->drawString(0, 12, dcTimeString);
	_display->setTextAlignment(TEXT_ALIGN_RIGHT);
	_display->drawString(0, 0, cellsString);
	_display->drawString(0, 12, onTimeString);
	_display->display();
}

String ScreenHelper::GetVoltageString(float voltage)
{
	return String(String(voltage, 2) + "V");
}

String ScreenHelper::GetCellsString(byte numCells)
{
	return String(String(numCells) + "S");
}

String ScreenHelper::GetTimeString(ulong time)
{
	uint seconds = time / 1000;
	uint minutes = seconds / 60;
	seconds %= 60;
	char buf[6];
	snprintf(buf, 6, "%02d:%02d");
	return String(buf);
}