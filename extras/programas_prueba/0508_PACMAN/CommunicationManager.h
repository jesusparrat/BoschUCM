#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

//class DirectionController;
//class MotorsController;

enum MESSAGE{
	SYNC_ATTEMP,
	SYNC,
	LINE_TRACKER_INITIALIZED,
//	MOTORS_INITIALIZED,
//	DIRECCTION_INITIALIZED,

	START,

  LEFT,
  NONE,
  RIGHT,
  TURN180,
  NOSTOP,


	TURN_ENDED,

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
//	SoftwareSerial miBT;

	int8_t id;
	bool start = false;

//	DirectionController* directionController;
//	MotorsController* motorsController;

public:
	CommunicationManager();

	void Init();
	void Sync();
	void Update();

//	void SetDirectionController(DirectionController* d);	
//	void SetMotorsController(MotorsController* m);

	void SendMsg(MESSAGE msg);
	MESSAGE ReadMsg();
	bool MsgAvailable();

	void WaitApproval();
	void WaitForMsg(MESSAGE msg);
};
