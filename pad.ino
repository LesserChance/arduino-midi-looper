void setupPads() {
    uint32_t color = pad_strips[SNARE]->Color(0, 0, 0);
    
    for(int i = 0; i < PAD_COUNT; i++) {
        pad_strips[i]->begin();
        resetPadEffect(i);
    }
}

/***************************
 * OUTGOING INSTRUCTIONS   *
 ***************************/
/**
 * Handle the note on instruction on the proper pad
 * @arg {Byte} channel
 * @arg {Byte} pitch
 * @arg {Byte} velocity
 */
void sendPadNoteOn(byte channel, byte pitch, byte velocity) {
    int pad = -1;
    for(int i = 0; i < PAD_COUNT && pad == -1; i++) {
        for(int j = 0; j < MAX_PITCHES_PER_PAD && pad == -1; j++) {
            if (pad_pitches[i][j] == pitch) {
                pad = i;
            }
        }
    }
    
    if (pad != -1) {
        startEffect(pad, velocity);
    }
}

/**
 * Handle the note of instruction on the proper pad
 * @arg {Byte} channel
 * @arg {Byte} pitch
 * @arg {Byte} velocity
 */
void sendPadNoteOff(byte channel, byte pitch, byte velocity) {
    
}
