#include "PBHelper.h"

PBHelper::PBHelper(void)
{
	WiFi.begin("GLaDOS", WIFI_PASSWORD);
}

void PBHelper::Update(PinHelper * pinHelper)
{
	ConnectIfNecessary();
	if (pinHelper->DcTime < MIN_NOTIFICATION_TIME || pinHelper->State() != OFF) {
		return;
	}
	Push("Battery is done discharging!", "Battery Done");
}

bool PBHelper::ConnectIfNecessary(void)
{
	if (!_connected && WiFi.isConnected()) {
		_connected = _pb.openConnection();
	}
	return _connected;
}

bool PBHelper::Push(const String message, const String title)
{
	if (!_connected || _pushSent) {
		return false;
	}
	_pb.sendNotePush(message, title);
	_pushSent = true;
	return true;
}