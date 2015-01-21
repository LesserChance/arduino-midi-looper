
#include <SoftwareSerial.h>
#include <MIDI.h>
#include <Adafruit_NeoPixel.h>

/**
 * Initialize the Arduino
 */
void setup(){
    setupMidi();
    setupLoops();
    setupPads();
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
}

/**
 * The main execution loop
 * - read all midi commands
 * - play all recorded loops
 */
void loop() {
    MIDI.read();
    checkStartRecording();
    playLoops();
    playEffects();
}
