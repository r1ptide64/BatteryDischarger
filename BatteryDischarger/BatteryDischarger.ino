#include "ScreenHelper.h"
#include "PBHelper.h"

#define TRANSISTOR_PIN D5
#define MAX_LIPO_VOLTAGE 4.3
#define STORAGE_VOLTAGE 3.8
#define R1_OHMS 10220
#define R2_OHMS 2200
#define R_TOT (R1_OHMS + R2_OHMS)
#define ADC_RES 10230.0
#define SWITCH_DELAY 5
#define MIN_PB_RUN_TIME 30

PBHelper pbHelper;

ulong dischargeTime;
ulong runtime;
ulong lastSwitched;
int raw;
float voltage;
byte numCells;
byte transistorState;
byte ledState;
bool sentPush;
bool pbConnected;

void setup() {
	pinMode(TRANSISTOR_PIN, OUTPUT);
	digitalWrite(TRANSISTOR_PIN, LOW);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	pinMode(A0, INPUT);
	display.init();
	display.setFont(ArialMT_Plain_24);
	display.flipScreenVertically();
}

void loop() {
	ulong now = millis() / 1000;
	if (now <= runtime) {
		return;
	}
	runtime = now;
	updateDisplay();
	updateStates(voltage > numCells * STORAGE_VOLTAGE);
}

void updateStates(byte aboveStorageVoltage) {
	//bool recentlySwitched = lastSwitched > 0 && lastSwitched + SWITCH_DELAY < runtime;
	if (!aboveStorageVoltage) {
		if (!sentPush && WiFi.isConnected() && dischargeTime > MIN_PB_RUN_TIME) {
			pb.sendNotePush("Battery is done discharging!", "D-U-N done!");
			sentPush = true;
		}
		//if (transistorState) {
		//	if (recentlySwitched) {
		//		return;
		//	}
		//	lastSwitched = runtime;
		//
		//}
		transistorState = LOW;
		ledState = HIGH;
	}
	else {
		//if (!transistorState) {
		//	if (recentlySwitched) {
		//		newTransistorState = LOW;
		//	}
		//	else {
		//		lastSwitched = runtime;
		//	}
		//}
		//else {
		//	dischargeTime++;
		//}
		dischargeTime++;
		transistorState = HIGH;
		ledState = !ledState;
	}
	digitalWrite(LED_BUILTIN, ledState);
	digitalWrite(TRANSISTOR_PIN, transistorState);
}

float getVoltage(void) {
	raw = analogRead(A0);
	return ((ADC_TOUT * raw * R_TOT) / R2_OHMS) / ADC_RES;
}

int getNumCells(void) {
	return (int)((voltage / MAX_LIPO_VOLTAGE) + 1);
}

void drawVoltageString(void) {
	voltage = getVoltage();
	numCells = getNumCells();
	String voltageString = String(String(voltage, 2) + "V  " + String(numCells) + "S");
	display.drawString(0, 0, voltageString);
}

void drawTimeString(void) {
	int seconds = dischargeTime;
	int hours = seconds / 3600;
	seconds %= 3600;
	int minutes = seconds / 60;
	seconds %= 60;
	char timeString[9];
	snprintf(timeString, 9, "%01d:%02d:%02d", hours, minutes, seconds);
	display.drawString(0, 26, timeString);
}

void drawWifiIndicator(void) {
	if (!WiFi.isConnected()) {
		return;
	}
	display.drawCircle(124, 28, 4);
}

void updateDisplay() {
	display.clear();
	drawVoltageString();
	drawTimeString();
	drawWifiIndicator();
	display.display();
}