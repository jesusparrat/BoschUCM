#include "Simple_MPU6050.h"          // incluye libreria Simple_MPU6050
#define MPU6050_ADDRESS_AD0_LOW     0x68      // direccion I2C con AD0 en LOW o sin conexion
#define MPU6050_ADDRESS_AD0_HIGH    0x69      // direccion I2C con AD0 en HIGH
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW // por defecto AD0 en LOW


#define DRIFT 6
float currentYaw = 0;
float previousYaw = 0;
float driftedYaw = 0;
float generaloffset = 0;

int aux = 0;
bool initialized = false;

Simple_MPU6050 mpu;       // crea objeto con nombre mpu
// ENABLE_MPU_OVERFLOW_PROTECTION();    // activa proteccion, ya no se requiere

//#define OFFSETS  -667, -3921, 979, 61, 11, -1  // Colocar valores personalizados
#define OFFSETS  -667, -3921, 979, 61, 11, -1  // Colocar valores personalizados

#define spamtimer(t) for (static uint32_t SpamTimer; (uint32_t)(millis() - SpamTimer) >= (t); SpamTimer = millis())
// spamtimer funcion para generar demora al escribir en monitor serie sin usar delay()

#define printfloatx(Name,Variable,Spaces,Precision,EndTxt) print(Name); {char S[(Spaces + Precision + 3)];Serial.print(F(" ")); Serial.print(dtostrf((float)Variable,Spaces,Precision ,S));}Serial.print(EndTxt);
// printfloatx funcion para mostrar en monitor serie datos para evitar el uso se multiples print()

// mostrar_valores funcion que es llamada cada vez que hay datos disponibles desde el sensor
void mostrar_valores (int16_t *gyro, int16_t *accel, int32_t *quat, uint32_t *timestamp) {  
  uint8_t SpamDelay = 100;      // demora para escribir en monitor serie de 100 mseg
  Quaternion q;         // variable necesaria para calculos posteriores
  VectorFloat gravity;        // variable necesaria para calculos posteriores
  float ypr[3] = { 0, 0, 0 };     // array para almacenar valores de yaw, pitch, roll
  float xyz[3] = { 0, 0, 0 };     // array para almacenar valores convertidos a grados de yaw, pitch, roll
  spamtimer(SpamDelay) {      // si han transcurrido al menos 100 mseg entonces proceder
    mpu.GetQuaternion(&q, quat);    // funcion para obtener valor para calculo posterior
    mpu.GetGravity(&gravity, &q);   // funcion para obtener valor para calculo posterior
    mpu.GetYawPitchRoll(ypr, &q, &gravity); // funcion obtiene valores de yaw, ptich, roll
    mpu.ConvertToDegrees(ypr, xyz);   // funcion convierte a grados sexagesimales

    driftedYaw = 0;
    if(xyz[0] < 0)
      driftedYaw = 360 + xyz[0];
    else 
      driftedYaw = xyz[0];

    anguloReal(driftedYaw);

    //Serial.printfloatx(F("Yaw")  , xyz[0] , 9, 4, F(",   "));  // muestra en monitor serie rotacion de eje Z, yaw
    //Serial.printfloatx(F("Pitch"), xyz[1], 9, 4, F(",   "));  // muestra en monitor serie rotacion de eje Y, pitch
    //Serial.printfloatx(F("Roll") , xyz[2], 9, 4, F(",   "));  // muestra en monitor serie rotacion de eje X, roll

    if(aux < 150){
      aux++;
      Serial.print(".");
      if(aux == 150){
        generaloffset = driftedYaw;
        previousYaw = 0;
        currentYaw = 0;
        initialized = true;
        Serial.println("\nInicializado");
      }
    }
  }
}


void anguloReal(float driftedYaw){
    if(initialized)
      driftedYaw -= generaloffset;
    
    //Serial.printfloatx(F("Yaw")  , driftedYaw, 9, 4, F(",   "));
    float delta = getDelta(driftedYaw);

    currentYaw += delta;

    //currentYaw = fmod(currentYaw, 360.0);
    if(currentYaw < -180.0)
      currentYaw = 360 + currentYaw;
    else if(currentYaw > 180)
      currentYaw = currentYaw - 360;
      
    if(initialized)
      Serial.println(currentYaw);

    previousYaw = driftedYaw;
}

float getDelta(float driftedYaw){
    //drifed delta
    float delta = (driftedYaw - previousYaw);
    if(delta > 300) delta -= 360;
    else if (delta < -300) delta += 360;

    //undrif delta
    float aux = (delta * DRIFT) / 360.0;
    delta -= aux;

    return delta;
}




void setup() {
  uint8_t val;
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE  // activacion de bus I2C a 400 Khz
  Wire.begin();
  Wire.setClock(400000);
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  
  Serial.begin(115200);     // inicializacion de monitor serie a 115200 bps
  while (!Serial);      // espera a enumeracion en caso de modelos con USB nativo
  Serial.println(F("Inicio:"));   // muestra texto estatico
#ifdef OFFSETS                // si existen OFFSETS
  Serial.println(F("Usando Offsets predefinidos"));     // texto estatico
  mpu.SetAddress(MPU6050_ADDRESS_AD0_LOW).load_DMP_Image(OFFSETS);  // inicializacion de sensor

#else                   // sin no existen OFFSETS
  Serial.println(F(" No se establecieron Offsets, haremos unos nuevos.\n" // muestra texto estatico
                   " Colocar el sensor en un superficie plana y esperar unos segundos\n"
                   " Colocar los nuevos Offsets en #define OFFSETS\n"
                   " para saltar la calibracion inicial \n"));
  mpu.SetAddress(MPU6050_ADDRESS_AD0_LOW).CalibrateMPU().load_DMP_Image();  // inicializacion de sensor
#endif
  mpu.on_FIFO(mostrar_valores);   // llamado a funcion mostrar_valores si memoria FIFO tiene valores

  Serial.println("\nVamos a proceder a inicializar el giroscopio");
  while(!initialized)
    mpu.dmp_read_fifo();
}



void loop() {
   mpu.dmp_read_fifo();    // funcion que evalua si existen datos nuevos en el sensor y llama
} 
