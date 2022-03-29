/*
-----------------------------------------------------------------------------
 
SoilMoistureSensor

Version: version 0.1 (30/03/2020)
Author: Murray Buchanan
Resources: http://gardenbot.org/

UPDATES:
  - [29/03/2020]  Programme creation
  - [29/03/2020]  Display logo and 'intro' screensaver
  - [30/03/2020]  Tuned resistor values
  - [30/03/2020]  Corrected polarity of senor such that no connection amounts to a zero value probe measurement
  - [30/03/2020]  Changed LED behaviour to reflect sensitivity level
TO FIX:
  -

-----------------------------------------------------------------------------
*/

// 'light_icon1', 64x64px
const unsigned char MoistureLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 
  0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x3f, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x00, 0x7e, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x01, 0xfc, 0x47, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0xf8, 0xc7, 0xff, 0xff, 0xff, 0xff, 0x80, 
  0x03, 0xf1, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xf1, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x07, 0xe3, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xe3, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0x0f, 0xc7, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xcf, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xf8, 
  0x1f, 0xcf, 0xf4, 0x7f, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0x8f, 0xe6, 0x7f, 0xff, 0xff, 0xff, 0xfc, 
  0x3f, 0x8f, 0xe6, 0x7f, 0xff, 0x00, 0x03, 0xfc, 0x3f, 0x8f, 0xc6, 0x7f, 0xf0, 0x00, 0x03, 0xfc, 
  0x7f, 0xcf, 0x84, 0x7f, 0x00, 0x1f, 0xc7, 0xfe, 0x7f, 0xc7, 0x8c, 0xfc, 0x07, 0xff, 0x8f, 0xfe, 
  0x7f, 0xc3, 0xf8, 0xf0, 0x3f, 0xff, 0x8f, 0xfe, 0x7f, 0xe0, 0xe1, 0xe0, 0xff, 0xff, 0x1f, 0xfe, 
  0x7f, 0xf0, 0x03, 0x83, 0xff, 0xfe, 0x3f, 0xfe, 0x7f, 0xfc, 0x0f, 0x0f, 0xff, 0x3e, 0x3f, 0xfe, 
  0x7f, 0xff, 0xff, 0x1f, 0xfc, 0x3c, 0x7f, 0xfe, 0xff, 0xff, 0xfe, 0x3f, 0xf8, 0x7c, 0x7f, 0xff, 
  0xff, 0xff, 0xfc, 0x7f, 0xe0, 0xfc, 0xff, 0xff, 0x7f, 0xff, 0xfc, 0x7f, 0xc3, 0xf8, 0xff, 0xfe, 
  0x7f, 0xff, 0xf8, 0xff, 0x87, 0xf9, 0xff, 0xfe, 0x7f, 0xff, 0xf8, 0xff, 0x1f, 0xf9, 0xff, 0xfe, 
  0x7f, 0xff, 0xf9, 0xfe, 0x3f, 0xf1, 0xff, 0xfe, 0x7f, 0xff, 0xf9, 0xfc, 0x7f, 0xf1, 0xff, 0xfe, 
  0x7f, 0xff, 0xf9, 0xf8, 0xff, 0xf3, 0xff, 0xfe, 0x7f, 0xff, 0xf9, 0xf1, 0xff, 0xf3, 0xff, 0xfe, 
  0x3f, 0xff, 0xf9, 0xe3, 0xff, 0xe3, 0xff, 0xfc, 0x3f, 0xff, 0xf9, 0xc3, 0xff, 0xe3, 0xff, 0xfc, 
  0x3f, 0xff, 0xf8, 0xc7, 0xff, 0xe7, 0xff, 0xfc, 0x1f, 0xff, 0xf8, 0x8f, 0xff, 0xc7, 0xff, 0xf8, 
  0x1f, 0xff, 0xfc, 0x1f, 0xff, 0x8f, 0xff, 0xf8, 0x0f, 0xff, 0xfc, 0x1f, 0xff, 0x8f, 0xff, 0xf0, 
  0x0f, 0xff, 0xfe, 0x1f, 0xff, 0x1f, 0xff, 0xf0, 0x07, 0xff, 0xfe, 0x07, 0xfc, 0x3f, 0xff, 0xe0, 
  0x07, 0xff, 0xfc, 0x00, 0x40, 0x7f, 0xff, 0xe0, 0x03, 0xff, 0xfc, 0xe0, 0x00, 0xff, 0xff, 0xc0, 
  0x01, 0xff, 0xf8, 0xfc, 0x07, 0xff, 0xff, 0x80, 0x01, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x80, 
  0x00, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xf9, 0xff, 0xff, 0xff, 0xfe, 0x00, 
  0x00, 0x3f, 0xf9, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00
};


// 'drop_light', 40x40px
const unsigned char DropLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x01, 0xe7, 0x80, 0x00, 0x00, 0x01, 0xe3, 
  0x80, 0x00, 0x00, 0x03, 0xc3, 0xc0, 0x00, 0x00, 0x07, 0x81, 0xe0, 0x00, 0x00, 0x07, 0x80, 0xe0, 
  0x00, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0x00, 0x0e, 0x00, 0x78, 0x00, 0x00, 0x1e, 0x00, 0x38, 0x00, 
  0x00, 0x3c, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x1c, 0x00, 0x00, 0x78, 0x00, 0x1e, 0x00, 0x00, 
  0x78, 0x00, 0x0e, 0x00, 0x00, 0x70, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x07, 0x00, 0x00, 0xe0, 
  0x00, 0x07, 0x00, 0x00, 0xe0, 0x00, 0xe7, 0x80, 0x00, 0xe0, 0x00, 0xe7, 0x80, 0x00, 0xe0, 0x00, 
  0xe7, 0x80, 0x00, 0xe0, 0x01, 0xe7, 0x80, 0x00, 0xe0, 0x03, 0xc7, 0x00, 0x00, 0xf0, 0x07, 0xc7, 
  0x00, 0x00, 0x70, 0x0f, 0x8f, 0x00, 0x00, 0x78, 0x07, 0x1e, 0x00, 0x00, 0x3c, 0x00, 0x1e, 0x00, 
  0x00, 0x3e, 0x00, 0x7c, 0x00, 0x00, 0x1f, 0x81, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 
  0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char DropIcon [] PROGMEM = {
  // 'drop_dark, 24x24px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 
  0x7e, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x01, 0xff, 0x80, 0x01, 0xff, 0x80, 0x03, 0xff, 
  0xc0, 0x03, 0xff, 0xc0, 0x07, 0xff, 0xe0, 0x07, 0xff, 0xe0, 0x07, 0xfe, 0x20, 0x07, 0xfc, 0x20, 
  0x07, 0xfc, 0x60, 0x07, 0xf8, 0x60, 0x07, 0xf0, 0xe0, 0x03, 0xe1, 0xc0, 0x01, 0xe7, 0x80, 0x00, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#define NUMICONS      8 // Number of falling icons in the animation example
#define LOGO_HEIGHT   40
#define LOGO_WIDTH    40
#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2
#define INTRO_TIME 25  

#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdio.h>
#define LEN 10      // This value sets how many elements are captured into the MoistureArray

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(128, 64, &Wire, 8);

// Version number
String version_number = "Version: 0.1"; 

// Values
int debounce_time = 50;
//int switch_hold_time = 75;
int sensitivity = 0;        // HIGH sensitivity (default)
int MoistureArray[LEN];
float SmoothedMoisture;
int MoistureReading;
int MoistureLevel;
const int sampleSize = LEN;

// TIME VARIABLES
unsigned long sample_time = 75;
unsigned long last_sample_start;
unsigned long last_interrupt_time_SW1;
unsigned long last_interrupt_time_SW2;
unsigned long last_interrupt_time_SW3;;

// Switches
const int SW1 = 0;            // [TX0] BLUE switch
const int SW2 = 1;            // [RX1] RED switch
const int SW3 = 7;            // [D7]  BLACK switch
const int SW4 = 4;            // [D4]  WHITE switch

// Probe pins
const int probe_static = 6;   // probe static resistance pin
const int probe_high = 10;    // high sensitivity: probe dynamic resistance pin
const int probe_med = 9;      // med sensitivity: probe dynamic resistance pin
const int probe_low= 8;       // low sensitivity: probe dynamic resistance pin
const int probe_sense = A1;   // pin for analogue reading of probe

// LED RED/GREEN
const int LED_R = 16;           // Red LED (TX1)
const int LED_G = 14;           // Green LED (RX0)

//-----------------------------------------------------------------------------------------
// SETUP
//-----------------------------------------------------------------------------------------
void setup() {
  // Pull-up switches
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);

  // Probe analogue sensor
  pinMode(probe_sense, INPUT);
  // Probe outputs
  pinMode(probe_static, OUTPUT);
  pinMode(probe_low, OUTPUT);
  pinMode(probe_med, OUTPUT);
  pinMode(probe_high, OUTPUT);

  // LED
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);

  Serial.begin(9600);
  while (!Serial) {}
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)  
  delay(100);
  //screensaver(DropLogo, LOGO_WIDTH, LOGO_HEIGHT, INTRO_TIME); // Animate bitmaps
  
  display.clearDisplay();
  display.drawBitmap(32, 0,  MoistureLogo, 64, 64, SSD1306_WHITE);
  display.display();
  
  // Invert and restore display, pausing in-between
  delay(250);
  display.invertDisplay(true);
  delay(250);
  display.invertDisplay(false);
  delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40,0);
  display.println("Plant");
  display.setCursor(50,18);
  display.println("Pot");
  display.setCursor(50,36);
  display.println("Bot");
  display.setTextSize(1);
  display.setCursor(25,55);
  display.print(version_number);
  display.display();
  //Serial.println("Starting probe sensing...");
  
  //attachInterrupt(digitalPinToInterrupt(SW1), SW1_press, FALLING);
  //attachInterrupt(digitalPinToInterrupt(SW2), SW2_press, FALLING);
  //attachInterrupt(digitalPinToInterrupt(SW3), SW3_press, FALLING);
  //attachInterrupt(digitalPinToInterrupt(SW4), SW4_press, FALLING);
  
}

//-----------------------------------------------------------------------------------------
// MAIN LOOP
//-----------------------------------------------------------------------------------------
void loop() {
  // change probe sensitivity
  if (button_press(SW1))  {
    sensitivity += 1;
    Serial.println("SW1 pressed");
    if (sensitivity > 2)  {
      sensitivity = 0;
    }
  }
  else if (button_press(SW2))  {
    Serial.println("SW2 pressed");
  }
  else if (button_press(SW3))  {
    Serial.println("SW3 pressed");
  }
  else if (button_press(SW4))  {
    Serial.println("SW4 pressed");
  }
  
  if (millis() - last_sample_start >  sample_time)  {
    enable_probe();
    sample_probe();
    disable_probe();
    last_sample_start = millis();
    Serial.println("---------------------------------------------");
  }
  display_information();
}


//-----------------------------------------------------------------------------------------
// PERIPHERAL FUNCTIONS
//-----------------------------------------------------------------------------------------

bool button_press(int Switch) {
  unsigned long press_start = millis();
  // ensure Switch is held for switch_hold_time
  while (!digitalRead(Switch))  {
    if (millis() - press_start > debounce_time) {
      // wait for Switch release
      while(!digitalRead(Switch));
      return true;
    }
  }
  return false;
}


//-----------------------------------------------------------------------------------------

void enable_probe() {
  /*
  // indicate probe ON
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_R, LOW);
  */
  // block dynamic pins (LOW - HIGH)
  digitalWrite(probe_low, HIGH);
  digitalWrite(probe_med, HIGH);
  digitalWrite(probe_high, HIGH);
  
  // apply forward bias to sensor
  digitalWrite(probe_static, HIGH);
  // probe_sensitivity exists between 0 and 2 (inclusive)
  digitalWrite(probe_low + sensitivity, LOW);
}

//-----------------------------------------------------------------------------------------

void disable_probe()  {
  /*
  // reverse electrolysis/oxidisation (reverse bias sensor)
  digitalWrite(probe_static, LOW);
  digitalWrite(probe_low + sensitivity, HIGH);
  delay(100);
  */

  // disable probe
  digitalWrite(probe_static, LOW);
  digitalWrite(probe_low, LOW);
  digitalWrite(probe_med, LOW);
  digitalWrite(probe_high, LOW);
  
  /*
  // indicate probe OFF
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, HIGH);
  */
  }

//-----------------------------------------------------------------------------------------

void sample_probe() {
  //Serial.println("SAMPLING MOISTURE SENSOR");
  // This function adds a new smaple to the MoistureReading value which effectively smoothes
  // the calculation of the mean for aesthetic effect.
  SmoothedMoisture = 0;
  // Shift MoistureArray values down by 1 address
  for (int arrayItem = 0; arrayItem < sampleSize - 1; arrayItem++)  {
    Serial.print("MoistureArray[");Serial.print(arrayItem);Serial.print("] = ");Serial.println(MoistureArray[arrayItem + 1]);
    MoistureArray[arrayItem] = MoistureArray[arrayItem + 1];
    SmoothedMoisture += (MoistureArray[arrayItem]);
  }
  // Take new measurement with the probe
  MoistureReading = analogRead(probe_sense);
  // Add new probe measurement to MoistureArray
  MoistureArray[sampleSize-1] = MoistureReading;
  Serial.print("MoistureArray[");Serial.print(sampleSize);Serial.print("] = ");Serial.println(MoistureArray[sampleSize-1]);
  // Add new probe measurement to SmoothedMoisture value
  SmoothedMoisture += MoistureArray[sampleSize-1];
  SmoothedMoisture = SmoothedMoisture/sampleSize;
  // Print: "MoistureReading = [MoistureReading] ([SmoothedMoisture])"
  Serial.print("MoistureReading = ");Serial.print(MoistureReading);
  Serial.print("\t(");Serial.print(SmoothedMoisture);Serial.println(")");
  // Convert SmoothedMoisture to MoistureLevel
  MoistureLevel = constrain(SmoothedMoisture/168,0,6);
  Serial.print("sensitivity = ");Serial.println(sensitivity);
  disable_probe();
}

//-----------------------------------------------------------------------------------------

void display_information() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("");
  char MoistureReadingBuffer[6];
  char MoistureString[20];
  dtostrf(MoistureReading, 4, 1, MoistureReadingBuffer);
  sprintf(MoistureString, "Moisture Meter:%s", MoistureReadingBuffer);
  display.println(MoistureString);
  // draw Moisture Meter box
  display.drawRoundRect(4, 12, display.width()-4, 30, display.height()/4, SSD1306_WHITE);
  // fill Moisture Meter with proportional number of DropLogo's
  for (int i = 0; i < MoistureLevel; i++) {
    display.drawBitmap(8+18*i, 15,  DropIcon, 24, 24, SSD1306_WHITE);
  }
  
  display.setCursor(0, 55);
  display.print("Sensitivity: ");
  display.setCursor(95, 55);
  digitalWrite(LED_R,LOW);
  digitalWrite(LED_G,LOW);
  if (sensitivity == 0) {
    digitalWrite(LED_R, HIGH);
    display.println("LOW");
  }
  else if (sensitivity == 1)  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    display.println("MED");
  }
  else if (sensitivity == 2)  {
    digitalWrite(LED_G, HIGH);
    display.println("HIGH");
  }
  display.display();
}

//-----------------------------------------------------------------------------------------

void screensaver(const uint8_t *bitmap, uint8_t w, uint8_t h, uint16_t SCREEN_SAVER_TIME) {
    int8_t f, icons[NUMICONS][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMICONS; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
  }

  for(int frame = 0; frame < SCREEN_SAVER_TIME; frame++) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMICONS; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(30);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMICONS; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}

//---------------------------------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//---------------------------------------------------------------------------------
void SW1_press() {
  unsigned long interrupt_time_SW1 = millis();
  unsigned long duration_SW1 = interrupt_time_SW1 - last_interrupt_time_SW1;
  // software debounce
  if (duration_SW1 > debounce_time) {
    sensitivity += 1;
    Serial.println("SW1 pressed");
    if (sensitivity > 2)  {
      sensitivity = 0;
    }
    last_interrupt_time_SW1 = interrupt_time_SW1;
  }
}

void SW2_press() {
  unsigned long interrupt_time_SW2 = millis();
  unsigned long duration_SW2 = interrupt_time_SW2 - last_interrupt_time_SW2;
  // software debounce
  if (duration_SW2 > debounce_time) {
    Serial.println("SW2 pressed");
    last_interrupt_time_SW2 = interrupt_time_SW2;
  }
}

void SW3_press() {
  unsigned long interrupt_time_SW3 = millis();
  unsigned long duration_SW3 = interrupt_time_SW3 - last_interrupt_time_SW3;
  // software debounce
  if (duration_SW3 > debounce_time) {
    Serial.println("SW3 pressed");
    last_interrupt_time_SW3 = interrupt_time_SW3;
  }
}
