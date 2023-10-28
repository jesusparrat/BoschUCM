#pragma once
#include <Arduino.h>


enum JAVA_MESSAGE{
	JAVA_SYNC_ATTEMPT = 0,
	JAVA_SYNC = 1,
	PAC_MAN_UP,
	PAC_MAN_RIGHT,
	PAC_MAN_DOWN,
	PAC_MAN_LEFT,
    PAC_MAN_NEUTRAL,

	JAVA_TURN_ENDED,

	JAVA_START,

	JAVA_OK,
	JAVA_NULL
};


class ServerManager{
private:


public:
	ServerManager();

	void SyncToJava();

	void SendMsg(JAVA_MESSAGE msg);
	JAVA_MESSAGE ReadMsg();

	void WaitForMsg(JAVA_MESSAGE msg);
};
