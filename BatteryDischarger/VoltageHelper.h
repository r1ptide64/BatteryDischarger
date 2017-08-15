#pragma once

#include <Arduino.h>

#define MAX_LIPO_VOLTAGE 4.3f
#define STORAGE_VOLTAGE 3.8f
#define R1_OHMS 10220
#define R2_OHMS 2200
#define R_TOT (R1_OHMS + R2_OHMS)
#define ADC_RES 10230.0f

class VoltageHelper
{
public:
	VoltageHelper();
	void Update(int raw);
private:

public:
	byte NumCells;
	float VTot;
	float VpC;
};
