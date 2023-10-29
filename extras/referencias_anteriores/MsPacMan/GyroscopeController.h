#pragma once

#include <Arduino.h>
#include "Simple_MPU6050.h"

#define MPU6050_ADDRESS_AD0_LOW     0x68      // direccion I2C con AD0 en LOW o sin conexion
#define MPU6050_ADDRESS_AD0_HIGH    0x69      // direccion I2C con AD0 en HIGH
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW // por defecto AD0 en LOW

#define spamtimer(t) for (static uint32_t SpamTimer; (uint32_t)(millis() - SpamTimer) >= (t); SpamTimer = millis())
// spamtimer funcion para generar una espera al escribir en monitor serie sin usar delay()

#define printfloatx(Name,Variable,Spaces,Precision,EndTxt) print(Name); {char S[(Spaces + Precision + 3)];Serial.print(F(" ")); Serial.print(dtostrf((float)Variable,Spaces,Precision ,S));}Serial.print(EndTxt);
// printfloatx funcion para mostrar en el monitor serie datos para evitar el uso se multiples print()

#define OFFSETS  -667, -3921, 979, 61, 11, -1  // Colocar valores personalizados
#define TIME_TO_CALCULATE_DESVIATION 15000

class GyroscopeController{
private:
	float adverageYaw;
	float acumulatedYaw;
	int numberOfSamples = 0;
	int targetYaw = 0;

public:

	GyroscopeController();

	void Init();
	void Update();

	void UpdateAdverageYaw();
	float GetCurrentYaw();
	float GetAdverageYaw();
	void ResetYaw();
	void SetTargetYaw(int newTargetYaw);
};
