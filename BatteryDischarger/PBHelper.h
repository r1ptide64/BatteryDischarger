#pragma once

#include <PushBullet.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include "passwords.h"
#include "Arduino.h"

class PBHelper
{
public:
	PBHelper(void);
	bool ConnectIfNecessary(void);
	bool Push(const String message, const String title);

private:
	WiFiClientSecure _client;
	PushBullet _pb = PushBullet(PB_API_KEY, &_client, 443);
	bool _connected;
	bool _pushSent;
};