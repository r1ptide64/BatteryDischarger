#include "VoltageHelper.h"

VoltageHelper::VoltageHelper()
{
	VTot = 0.0f;
	VpC = 0.0f;
	NumCells = 1;
}

void VoltageHelper::Update(int raw)
{
	VTot = ((ADC_TOUT * raw * R_TOT) / R2_OHMS) / ADC_RES;
	NumCells = (byte)((VTot / MAX_LIPO_VOLTAGE) + 1);
	VpC = VTot / (float)NumCells;
}