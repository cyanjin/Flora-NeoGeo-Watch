#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   10
#define PIXEL_PIN    6
#define PIXEL_COUNT 16
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;   // active low button
int showType = 0;       // show number
// the setup routine runs once when you press reset:
void setup() {                
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'  
  Serial.begin(9600);  
}
 
// the loop routine runs over and over again forever:
void loop() {
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      showType++;
      for (int i=0;i<16;i++){
        strip.setPixelColor(i, strip.Color(showType*5, showType*5, showType*5) );
      }
      strip.show();
      Serial.println(showType);

      if (showType > 10)
        showType=0;
      //startShow(showType);
    }
  }

  // Set the last button state to the old state.
  oldState = newState;
}


