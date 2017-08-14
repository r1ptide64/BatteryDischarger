#include "PBHelper.h"

PBHelper::PBHelper(void)
{
	WiFi.begin("GLaDOS", WIFI_PASSWORD);
}

bool PBHelper::ConnectIfNecessary(void)
{
	if (!this->_connected && WiFi.isConnected()) {
		this->_connected = this->_pb.openConnection();
	}
	return this->_connected;
}

bool PBHelper::Push(const String message, const String title)
{
	if (!this->_connected || _pushSent) {
		return false;
	}
	_pb.sendNotePush(message, title);
	return true;
}