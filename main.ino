// ---------------------------------------------------------------
// Imports
// ---------------------------------------------------------------

#include <Adafruit_NeoPixel.h>

// ---------------------------------------------------------------
// References
// ---------------------------------------------------------------

#define lightPin 9 // Addressable RGB array

// Define RGB pins
int redPin = 6;
int greenPin = 5;
int bluePin = 3;

// ---------------------------------------------------------------
// Variables
// ---------------------------------------------------------------

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(40, lightPin);

int brightness = 40; // 1/3 brightness
int state = 0;

// ---------------------------------------------------------------
// Setup
// ---------------------------------------------------------------

void setup()
{
    pixels.begin();
    pixels.setBrightness(0); // Set lights to off state 
    pixels.show();
    // Set LED output pins
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT); 
    // Set RGB to off state 
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);

    Serial.begin(9600); // Default baud rate of BT module
}

// ---------------------------------------------------------------
// Main loop
// ---------------------------------------------------------------

void loop()
{
    if (Serial.available() > 0) {
        state = Serial.read();
    }

    if (state == '1') {
        showGreen();
        state = 0;
    } 

    if (state == '2') {
        showOrange();
        state = 0;
    } 

    if (state == '3') {
        showRed();
        state = 0;
    } 

    if (state == '4') {
        cleanMode();
        state = 0;
    } 
}

// ---------------------------------------------------------------
// Green light animation
// ---------------------------------------------------------------

void showGreen()
{
    uint16_t r, j;
    pixels.setBrightness(brightness);

    for (j = 0; j < 256 * 1; j++)
    {
        for (r = 0; r < pixels.numPixels(); r++)
        {
            pixels.setPixelColor(r, greenWheel(((r * 256 / pixels.numPixels()) + j) & 255));
        }
        pixels.show();
        delay(5);
    }
    pixels.setBrightness(0);
    pixels.show();
}

uint32_t greenWheel(byte WheelPos)
{
    if (WheelPos < 25)
    {
        return pixels.Color(0, 200, 0);
    }
    else if (WheelPos < 175)
    {
        WheelPos -= 25;
        return pixels.Color(0, WheelPos * 3, 0);
    }
    else
    {
        WheelPos -= 25;
        return pixels.Color(255, 255, 255);
    }
}

// ---------------------------------------------------------------
// Orange light animation
// ---------------------------------------------------------------

void showOrange()
{
    uint16_t r, j;
    pixels.setBrightness(brightness);

    for (j = 0; j < 256 * 1; j++)
    {
        for (r = 0; r < pixels.numPixels(); r++)
        {
            pixels.setPixelColor(r, orangeWheel(((r * 256 / pixels.numPixels()) + j) & 255));
        }
        pixels.show();
        delay(5);
    }
    pixels.setBrightness(0);
    pixels.show();
}

uint32_t orangeWheel(byte WheelPos)
{
    if (WheelPos < 25)
    {
        return pixels.Color(200, 200, 0);
    }
    else if (WheelPos < 175)
    {
        WheelPos -= 25;
        return pixels.Color(200, WheelPos * 3, 0);
    }
    else
    {
        WheelPos -= 25;
        return pixels.Color(255, 255, 255);
    }
}

// ---------------------------------------------------------------
// Red light animation
// ---------------------------------------------------------------

void showRed()
{
    uint16_t r, j;
    pixels.setBrightness(brightness);

    for (j = 0; j < 256 * 1; j++)
    {
        for (r = 0; r < pixels.numPixels(); r++)
        {
            pixels.setPixelColor(r, redWheel(((r * 256 / pixels.numPixels()) + j) & 255));
        }
        pixels.show();
        delay(5);
    }
    pixels.setBrightness(0);
    pixels.show();
}

uint32_t redWheel(byte WheelPos)
{
    if (WheelPos < 25)
    {
        return pixels.Color(200, 0, 0);
    }
    else if (WheelPos < 175)
    {
        WheelPos -= 25;
        return pixels.Color(WheelPos * 3, 0, 0);
    }
    else
    {
        WheelPos -= 25;
        return pixels.Color(255, 255, 255);
    }
}

// ---------------------------------------------------------------
// Clean mode 
// ---------------------------------------------------------------

void cleanMode()
{
    uint16_t r, j;

    // Turn on lights
    pixels.setBrightness(brightness);
    
    // Set lights to purple-blue
    analogWrite(redPin, 120);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);

    // 9 animation cycles
    for (j = 0; j < 256 * 9; j++)
    { 
        for (r = 0; r < pixels.numPixels(); r++)
        {
            pixels.setPixelColor(r, cleanModeWheel(((r * 256 / pixels.numPixels()) + j) & 255));
        }
        pixels.show();
        delay(5);
    }
    // Set RGB to off state 
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
    // Turn lights off
    pixels.setBrightness(0);
    pixels.show();

}

uint32_t cleanModeWheel(byte WheelPos)
{
    if (WheelPos < 40)
    {
        return pixels.Color(255, 255, 255);
    }
    else if (WheelPos < 180)
    {
        WheelPos -= 90;
        return pixels.Color(0, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 65;
        return pixels.Color(0, 0, 255 - WheelPos * 3);
    }
}