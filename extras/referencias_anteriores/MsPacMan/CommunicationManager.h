#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

class DirectionController;

enum MESSAGE{
	SYNC_ATTEMP,
	SYNC,
	LINE_TRACKER_INITIALIZED,
	GYROSCOPE_INITIALIZED,
	MOTORS_INITIALIZED,
	DIRECCTION_INITIALIZED,

	START,


	RED_LED,
	GREEN_LED,
	BLUE_LED,
	YELLOW_LED,
	CIAN_LED,
	MAGENTA_LED,
	WHITE_LED,
	OK
};


class CommunicationManager{
private:
	SoftwareSerial miBT;

	int8_t id;
	bool start = false;

	DirectionController* directionController;
public:
	CommunicationManager();

	void Init();
	void Sync();
	void Update();

	void SetDirectionController(DirectionController* d);

	void SendMsg(MESSAGE msg);
	MESSAGE ReadMsg();
	bool MsgAvailable();

	void WaitApproval();
	void WaitForMsg(MESSAGE msg);
};