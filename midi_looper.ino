#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

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
