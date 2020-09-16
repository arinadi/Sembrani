//Buzzer Tone
#include "pitches.h" // NOTE to INT

//Deep Sleep
const int KEEP_ALIVE_TIMER = 15 * (1000 * 60); // minutes
unsigned long KEEP_ALIVE_TIMENOW = 0;
unsigned long KEEP_ALIVE_LASTACTION = millis();


//Default BT
#define BT_NAME "Sembrani Smart Moto"

//Default buzzer
#define BUZZER_PIN 13
#define BUZZER_CHANNEL 0 // PWM CHANNEL


// RF
#define RF_VT_PIN 12 // Input Detector
#define RF_D0_PIN 14 // Input A
#define RF_D1_PIN 27 // Input B
#define RF_D2_PIN 26 // Input C
#define RF_D3_PIN 25 // Input D

bool RF_VT_STATE = 0;
bool RF_D0_STATE = 0;
bool RF_D1_STATE = 0;
bool RF_D2_STATE = 0;
bool RF_D3_STATE = 0;

short int RF_CLICK = 0;
short int RF_CLICK_TYPE = 0;
const int RF_CLICK_TIMER = 1 * 1000; // s
unsigned long RF_CLICK_TIMESTART = 0;
unsigned long RF_CLICK_TIMELIMIT = 0;
