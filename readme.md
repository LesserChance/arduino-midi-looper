##Arduino MIDI Looper

This MIDI looper was built to be used in conjunction with an electronic drum set. The idea is that each pad has a ring of Adafruit NeoPixel lights around it that trigger both on the initial hit and on the loop.

It is limited in looping capabilities in that it will not loop any MIDI events besides ``note on`` and ``note off`` and their associated pitch and velocity.

###General Architecture
The top level object is a [loop](https://github.com/LesserChance/arduino-midi-looper/blob/master/loop.ino). Loops contain [instructions](https://github.com/LesserChance/arduino-midi-looper/blob/master/instruction.ino). An instruction is basically just a midi event that can be replayed.

[Globals](https://github.com/LesserChance/arduino-midi-looper/blob/master/a_globals.ino) are used to keep track of which loop is currently being recorded. [Constants](https://github.com/LesserChance/arduino-midi-looper/blob/master/a_constants.ino) are used to limit the maximum number of loops and instructions per loop, so you hopefully don't run out of memory.

A maximum of 4 loops means that you have a max of 4 concurrent loops, when one is deleted it frees up allocation for the next loop to be recorded.

###Execution Loop
The main execution loop runs through the following sequence:

- Read in MIDI state (save any instructions if recording.)
- Check to see if recording has started.
- Play any loop instructions for existing loops that occur at the current time signature.
- Set the state of the pad lights.

###Controlling MIDI Loops
Loops are controlled by sending MIDI control change commands. Currently the commands are mapped as follows


    Command 102 (Toggle)
    - Value 127 - Immediately Start Recording Loop
    - Value 0   - Stop Recording

    Command 104 (Toggle)
    - Value 127 - Start Recording Loop at the same 
                  time the previous loop starts
    - Value 0   - Stop Recording

    Command 103 (Momentary)
    - Delete the bottom-most loop

    Command 105 (Momentary)
    - Delete the top-most loop

###Pad Events
Every time the command to send a MIDI note is triggered the effect to start the pad effect is also triggered. Currently the only pad effect is a quick fade out. See [pad.ino](https://github.com/LesserChance/arduino-midi-looper/blob/master/pad.ino) and [effect.ino](https://github.com/LesserChance/arduino-midi-looper/blob/master/effect.ino) to understand how effects are triggered.

###Libraries
I utilized the following libraries while creating this project. I used older version than whats currently available, so some references may need to be updated.

- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit\_NeoPixel)
- [Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library/)

##

Thanks and enjoy!