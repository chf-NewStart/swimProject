#include "dataArray.h"

#include <Adafruit_NeoPixel.h>
#include <Arduino_LSM9DS1.h>

#define NUM_LEDS 21
#define DATA_PIN 11

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void displayPattern(){

  for (int j=0; j<NUM_LEDS; j++){
    for (int i=0; i<23; i++){
      // strip.setPixelColor(i,strip.Color((255-fullimg[j][i][0])/5, (255-fullimg[j][i][1])/5, (255-fullimg[j][i][2])/5));
      
      strip.setPixelColor(i,strip.Color((fullimg[j][i][0])/10, (fullimg[j][i][1])/10, (fullimg[j][i][2])/10));
      
      // strip.setPixelColor(i,strip.Color((fullimg[j][i][0]), (fullimg[j][i][1]), (fullimg[j][i][2])));
      
      // Serial.print(fullimg[i][j][0], fullimg[i][j][1], fullimg[i][j][2]));
      strip.show(); // Update the strip with new pixel colors
    }
    delay(30); // Delay for each row
  }
} 
void lightdown(){

  for (int j=0; j<NUM_LEDS; j++){
    for (int i=0; i<23; i++){
      // strip.setPixelColor(i,strip.Color((255-fullimg[j][i][0])/5, (255-fullimg[j][i][1])/5, (255-fullimg[j][i][2])/5));
      
      strip.setPixelColor(i,strip.Color(0, 0, 0));
      
      // strip.setPixelColor(i,strip.Color((fullimg[j][i][0]), (fullimg[j][i][1]), (fullimg[j][i][2])));
      
      // Serial.print(fullimg[i][j][0], fullimg[i][j][1], fullimg[i][j][2]));
      strip.show(); // Update the strip with new pixel colors
    }
    delay(80); // Delay for each row
  }

}


void setup() 
{

  strip.begin(); // Initialize the NeoPixel strip
  strip.show(); // Initialize all pixels to 'off'

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() 
{
  float x, y, z;
  // Read acceleration data
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Check for significant movement - adjust threshold as needed
    if (abs(x) > 1.2 || abs(y) > 1.2 || abs(z) > 1.2) {
      displayPattern();
      lightdown();
    }
  }

}
