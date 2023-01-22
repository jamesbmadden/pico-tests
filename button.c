#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

// built for a raspberry pi pico!

// the builtin light to indicate it's running
const uint BUILTIN_PIN = 25;

// the pins that output to LEDs
const uint BLUE_PIN = 17;
const uint GREEN_PIN = 14;

// the pin getting input from the button
const uint BUTTON_PIN = 13;

int main() {

  // this boolean tracks which light is on (true = green, false = blue)
  bool green = true;
  // whether the button is currently pressed
  bool buttonPressed = false;

  bi_decl(bi_program_description("This is a test binary."));
  bi_decl(bi_1pin_with_name(BLUE_PIN, "Connected Blue LED"));
  bi_decl(bi_1pin_with_name(GREEN_PIN, "Connected Green LED"));
  bi_decl(bi_1pin_with_name(BUTTON_PIN, "Button to toggle LED"));

  stdio_init_all();

  gpio_init(BUILTIN_PIN);
  gpio_set_dir(BUILTIN_PIN, GPIO_OUT);
  gpio_init(BLUE_PIN);
  gpio_set_dir(BLUE_PIN, GPIO_OUT);
  gpio_init(GREEN_PIN);
  gpio_set_dir(GREEN_PIN, GPIO_OUT);
  gpio_init(BUTTON_PIN);
  gpio_set_dir(BUTTON_PIN, GPIO_IN);

  // turn on the builtin LED to show it's on
  gpio_put(BUILTIN_PIN, 1);

  // green LED should start on
  gpio_put(GREEN_PIN, 1);

  while (1) {

    // get the input from the button
    int buttonVal = gpio_get(BUTTON_PIN);

    if (buttonVal != 0 && !buttonPressed) {
      // the button is pressed but it has not been processed yet. Switch the light colour!
      if (green) {
        // turn green off, and blue on
        gpio_put(GREEN_PIN, 0);
        gpio_put(BLUE_PIN, 1);
        green = false;
      } else {
        gpio_put(BLUE_PIN, 0);
        gpio_put(GREEN_PIN, 1);
        green = true;
      }
      // we have now processed the button press, so set the boolean to true
      buttonPressed = true;
    }
    // if the button is not pressed, make sure buttonPress is false
    if (buttonVal == 0 && buttonPressed) {
      buttonPressed = false;
    }

  }

  /*while (1) {
    gpio_put(BLUE_PIN, 0);
    gpio_put(GREEN_PIN, 1);
    sleep_ms(1000);
    gpio_put(BLUE_PIN, 1);
    gpio_put(GREEN_PIN, 0);
    sleep_ms(1000);
  }*/

}