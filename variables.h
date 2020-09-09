//Deep Sleep
int STAY_ALIVE_STATE = 0;


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

int RF_VT_STATE = 0;
int RF_D0_STATE = 0;
int RF_D1_STATE = 0;
int RF_D2_STATE = 0;
int RF_D3_STATE = 0;

int RF_CLICK = 0;
String RF_CLICK_TYPE = "";
const int RF_CLICK_TIMER = 1000; // ms
unsigned long RF_CLICK_TIMESTART = 0;
unsigned long RF_CLICK_TIMELIMIT = 0;
