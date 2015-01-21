/**
 * Initialize the Midi functionality/listeners
 */
void setupMidi() {
    MIDI.begin(MIDI_CHANNEL);
    MIDI.turnThruOn();
    MIDI.setHandleNoteOn(handleMidiNoteOn);
    MIDI.setHandleNoteOff(handleMidiNoteOff);
    MIDI.setHandleControlChange(handleControlChange);
    MIDI.setHandleProgramChange(handleProgramChange);
}

/***************************
 * INCOMING INSTRUCTIONS   *
 ***************************/
/**
 * Handle a midi note on command
 * @arg {Byte} channel
 * @arg {Byte} pitch
 * @arg {Byte} velocity
 */
void handleMidiNoteOn(byte channel, byte pitch, byte velocity) {
    if (channel == MIDI_CHANNEL) {
        if (recording) {
            recordInstruction(MIDI_NOTE_ON, channel, pitch, velocity);
        }
        
        //Send pad instruction
        sendPadNoteOn(channel, pitch, velocity);
    }
}

/**
 * Handle a midi note off command
 * @arg {Byte} channel
 * @arg {Byte} pitch
 * @arg {Byte} velocity
 */
void handleMidiNoteOff(byte channel, byte pitch, byte velocity) {
    if (channel == MIDI_CHANNEL) {
        if (recording) {
            recordInstruction(MIDI_NOTE_OFF, channel, pitch, velocity);
        }
        
        //Send pad instruction
        sendPadNoteOff(channel, pitch, velocity);
    }
}

/**
 * Handle a midi note off command
 * @arg {Byte} channel
 * @arg {Byte} number
 * @arg {Byte} value
 */
void handleControlChange(byte channel, byte number, byte value) {
    if (channel == MIDI_CHANNEL) {
        if (number == COMMAND_RECORD_ONE) {
            //Toggle
            if (value == COMMAND_VALUE_OFF) {
                stopRecording();
            } else if (value == COMMAND_VALUE_ON) {
                startRecording();
            }
        } else if (number == COMMAND_DELETE_ONE) {
            //Momentary
            if (value == COMMAND_VALUE_OFF) {
                deleteBottomLoop();
            }
        } else if (number == COMMAND_RECORD_TWO) {
            //Toggle
            if (value == COMMAND_VALUE_OFF) {
                stopRecording();
            } else if (value == COMMAND_VALUE_ON) {
                prepRecording();
            }
        } else if (number == COMMAND_DELETE_TWO) {
            //Momentary
            if (value == COMMAND_VALUE_OFF) {
                deleteTopLoop();
            }
        } else if (number == COMMAND_CONTROL) {
            //Momentary
            if (value == COMMAND_VALUE_OFF) {
                
            }
        }
    }
}

/**
 * Handle a midi note off command
 * @arg {Byte} channel
 * @arg {Byte} number
 */
void handleProgramChange(byte channel, byte number) {
    if (channel == MIDI_CHANNEL) {
        
    }
}

/***************************
 * OUTGOING INSTRUCTIONS   *
 ***************************/
/**
 * Send the note on command to midi out
 * @arg {Byte} channel
 * @arg {Byte} pitch
 * @arg {Byte} velocity
 */
void sendMidiNoteOn(byte channel, byte pitch, byte velocity) {
    MIDI.sendNoteOn(pitch, velocity, channel);
}

/**
 * Send the note on command to midi out
 * @arg {Byte} channel
 * @arg {Byte} pitch
 * @arg {Byte} velocity
 */
void sendMidiNoteOff(byte channel, byte pitch, byte velocity) {
    MIDI.sendNoteOff(pitch, velocity, channel);
}
