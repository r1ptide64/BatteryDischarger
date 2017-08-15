#include "ScreenHelper.h"
#include "PBHelper.h"
#include "PinHelper.h"
#include "VoltageHelper.h"

ScreenHelper *screenHelper;
PBHelper *pbHelper;
PinHelper *pinHelper;
VoltageHelper *voltageHelper;
//uint testV = 924;

void setup() {
	Serial.begin(9600);
	pinHelper = new PinHelper();
	screenHelper = new ScreenHelper();
	pbHelper = new PBHelper();
	voltageHelper = new VoltageHelper();
}

void loop() {
	ulong now = millis();
	//Serial.println(String("Voltage = " + String(testV--)));
	voltageHelper->Update(analogRead(A0));
	pinHelper->Update(voltageHelper->VpC, now);
	screenHelper->Update(voltageHelper, pinHelper, now);
	//Serial.println("Calling pbHelper...");
	pbHelper->Update(pinHelper);
	//Serial.println("Done calling pbhelper.");
	delay(1000);
}