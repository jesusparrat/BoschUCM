#pragma once
#include <Arduino.h>




#define BLACK 1
#define WHITE 0

class LineTracker{
private:
	int START_SENSOR = 9;

    bool leftLine = false;

    bool previousLeftLine = false;

public:

    LineTracker();

    void Init();
    void Update();

    bool StartTurn();
    bool EndTurn();
};