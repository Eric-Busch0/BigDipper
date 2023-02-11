#include <Arduino.h>
#include <time.h>
#include <stdint.h>


#define ALKAID 11
#define ALCOR_MIZAR 10
#define ALIOTH 9
#define MEGREZ 7 // MEGREZ is not on a PWM pin
#define DUBHE 6
#define MERAK 5
#define PHECDA 3

static uint8_t stars[] = {ALKAID, ALCOR_MIZAR, ALIOTH, MEGREZ, DUBHE, MERAK, PHECDA};
#define NUM_STARS sizeof(stars)
static uint8_t current_brightness[NUM_STARS] = {0};
#define MIN_BRIGHTNESS 32

#define TICK_RATE 15 // 15ms update rate 
#define NON_PWM_TIME_ON 200
#define NON_PWM_PERIOD 500

void fade_random()
{

static uint8_t count = 0;


for(uint8_t i = 0; i < NUM_STARS; i++)
{
    if(digitalPinHasPWM(stars[i]))
    {

      //if we have PWM available we can just use some functions to randomly fade in and out.
      uint8_t sign = rand() % 64;

      if(sign < 32)
      {
        current_brightness[i] -= rand() % 8;
      }
      else
      {
        current_brightness[i] += rand() % 8;
      }

      if(current_brightness[i] < MIN_BRIGHTNESS)
      {
        current_brightness[i] = MIN_BRIGHTNESS;
      }

      analogWrite(stars[i], current_brightness[i]);
    }  
    else
    {
      uint16_t time_passed = ++count * TICK_RATE;

      if(time_passed > NON_PWM_TIME_ON)
      {
        digitalWrite(stars[i], 0);

      }
      else
      {
        digitalWrite(stars[i], 1);
      }


      if(time_passed > NON_PWM_PERIOD)
      {
        count = 0;
      }
    }

  }

}

void setup() {
  // put your setup code here, to run once:

  pinMode(ALKAID, OUTPUT);
  pinMode(ALCOR_MIZAR, OUTPUT);
  pinMode(ALIOTH, OUTPUT);
  pinMode(MEGREZ, OUTPUT);
  pinMode(PHECDA, OUTPUT);
  pinMode(DUBHE, OUTPUT);
  pinMode(MERAK, OUTPUT);

  Serial.begin(115200);

  


  Serial.println("Fuck you");

}

void loop() {

  
  fade_random();
  delay(TICK_RATE);


}