/**

 */
#ifndef MeNewRGBLed_h
#define MeNewRGBLed_h
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "MeConfig.h"


#define DEFAULT_MAX_LED_NUMBER  (32)

/// @brief Class for RGB Led Module
struct cNewRGB
{
  uint8_t g;
  uint8_t r;
  uint8_t b;
};

/**
 * Class: MeRGBLed
 *
 * \par Description
 * Declaration of Class MeRGBLed
 */

class MeNewRGBLed
{
public:

/**
 * Alternate Constructor which can call your own function to map the MeRGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. You can
 * set any arduino digital pin for the LED data PIN, The default number of light strips is 32.
 * \param[in]
 *   port - arduino port
 */
  MeNewRGBLed(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the MeRGBLed to arduino port,
 * it will assigned the LED display buffer and initialization the GPIO of LED lights. You can
 * set any arduino digital pin for the LED data PIN, and reset the LED number by this constructor.
 * \param[in]
 *   port - arduino port
 * \param[in]
 *   led_num - The LED number
 */
  MeNewRGBLed(uint8_t port, uint8_t led_num);
/**
 * Destructor which can call your own function, it will release the LED buffer
 */
  ~MeNewRGBLed(void);

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the LED available data PIN by its arduino port.
 * \param[in]
 *   port - arduino port(should digital pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void setpin(uint8_t port);

/**
 * \par Function
 *   getNumber
 * \par Description
 *   Get the LED number you can light it.
 * \par Output
 *   None
 * \return
 *   The total number of LED's
 * \par Others
 *   The index value from 1 to the max
 */
  uint8_t getNumber(void);

/**
 * \par Function
 *   getColorAt
 * \par Description
 *   Get the LED color value from its index
 * \param[in]
 *   index - The LED index number you want to read its value
 * \par Output
 *   None
 * \return
 *   The LED color value, include the R,G,B
 * \par Others
 *   The index value from 1 to the max
 */
  cNewRGB getColorAt(uint8_t index);

/**
 * \par Function
 *   fillPixelsBak
 * \par Description
 *   fill the LED color data to pixels_bak.
 * \param[in]
 *   red - Red values
 * \param[in]
 *   green - green values
 * \param[in]
 *   blue - blue values
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void fillPixelsBak(uint8_t red, uint8_t green, uint8_t blue);

/**
 * \par Function
 *   setColorAt
 * \par Description
 *   Set the LED color for any LED.
 * \param[in]
 *   index - The LED index number you want to set its color
 * \param[in]
 *   red - Red values
 * \param[in]
 *   green - green values
 * \param[in]
 *   blue - blue values
 * \par Output
 *   None
 * \return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * \par Others
 *   The index value from 0 to the max.
 */
bool setColorAt(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

/**
 * \par Function
 *   setColor
 * \par Description
 *   Set the LED color for any LED.
 * \param[in]
 *   index - The LED index number you want to set its color
 * \param[in]
 *   red - Red values
 * \param[in]
 *   green - green values
 * \param[in]
 *   blue - blue values
 * \par Output
 *   None
 * \return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * \par Others
 *   The index value from 1 to the max, if you set the index 0, all the LED will be lit
 */
  bool setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

/**
 * \par Function
 *   setColor
 * \par Description
 *   Set the LED color for all LED.
 * \param[in]
 *   red - Red values
 * \param[in]
 *   green - green values
 * \param[in]
 *   blue - blue values
 * \par Output
 *   None
 * \return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * \par Others
 *   All the LED will be lit.
 */
  bool setColor(uint8_t red, uint8_t green, uint8_t blue);

/**
 * \par Function
 *   setColor
 * \par Description
 *   Set the LED color for any LED.
 * \param[in]
 *   value - the LED color defined as long type, for example (white) = 0xFFFFFF
 * \par Output
 *   None
 * \return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * \par Others
 *   The index value from 1 to the max, if you set the index 0, all the LED will be lit
 */
  bool setColor(uint8_t index, long value);

/**
 * \par Function
 *   setNumber
 * \par Description
 *   Assigned the LED display buffer by the LED number
 * \param[in]
 *   num_leds - The LED number you used
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void setNumber(uint8_t num_led);

/**
 * \par Function
 *   show
 * \par Description
 *   Transmission the data to WS2812
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void show(void);

private:
  uint16_t count_led;
  uint8_t *pixels;
  uint8_t *pixels_bak;

/**
 * \par Function
 *   rgbled_sendarray_mask
 * \par Description
 *   Set the LED color for any LED.
 * \param[in]
 *   *data - the LED color store memory address
 * \param[in]
 *   datlen - the data length need to be transmitted.
 * \param[in]
 *   maskhi - the gpio pin mask
 * \param[in]
 *   *port - the gpio port address
 * \par Output
 *   None
 * \return
 *   TRUE: Successful implementation
 *   FALSE: Wrong execution
 * \par Others
 *   None
 */
  void rgbled_sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask, uint8_t *port);

  const volatile uint8_t *ws2812_port;
  volatile uint8_t *ws2812_port_reg;
  uint8_t pinMask;
};




// aquí va mi código para manipular los LEDs ************************************

const int AZUL[] = {34, 32, 211};
const int AMBAR[] = {128, 55, 0};
const int ROJO[] = {128, 0, 0};
const int VERDE[] = {22, 124, 0};
const int NEGRO[] = {0, 0, 0};

void rgbled_both(int numLeds, const int* color);
void rightBlinker();
void leftBlinker();
void forwardBlinker();
void backwardBlinker();
void Blinker();

#endif
