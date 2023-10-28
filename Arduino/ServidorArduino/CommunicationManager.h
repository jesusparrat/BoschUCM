#pragma once
#include <SoftwareSerial.h>
#include <Arduino.h>

enum MESSAGE{
	SYNC_ATTEMP,
	SYNC,
	LINE_TRACKER_INITIALIZED,

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
	SoftwareSerial miBT;
public:
    CommunicationManager();

    void Init();
    void Sync();
    void WaitForRobotToInitialize();
	void WaitForMsg(MESSAGE msg);

	bool MsgAvailable();

	void SendMsg(MESSAGE msg);
	MESSAGE ReadMsg();

    
};
#ifndef CommunicationManager_h
    void rojo();
    void verde();
    void azul();
    void amarillo();
    void cian();
    void magenta();
    void blanco();    
    void nada();

#endif
