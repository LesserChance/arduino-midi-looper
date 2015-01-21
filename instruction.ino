/**
 * Record the passed instruction in the current position
 */
void recordInstruction(byte instruction_type, byte channel, byte arg0, byte arg1) {
    //store the args in the current position
    loop_instructions[loop_record_instruction_position][0] = instruction_type;
    loop_instructions[loop_record_instruction_position][1] = channel;
    loop_instructions[loop_record_instruction_position][2] = arg0;
    loop_instructions[loop_record_instruction_position][3] = arg1;
    
    //store the time the event occurred
    loop_instruction_times[loop_record_instruction_position] = getRecordingPosition();
    
    //go to the next instruction position
    if (loop_record_instruction_position == MAX_INSTRUCTIONS - 1) {
        loop_record_instruction_position = 0;
    } else {
        loop_record_instruction_position++;
    }
}

/**
 * Playback a specific instruction
 */
void playInstruction(int index) {
    if (loop_instructions[index][0] == MIDI_NOTE_ON) {
        byte channel  = loop_instructions[index][1];
        byte pitch    = loop_instructions[index][2];
        byte velocity = loop_instructions[index][3];
        
        //Send midi instruction
        sendMidiNoteOn(channel, pitch, velocity);
        
        //Send pad instruction
        sendPadNoteOn(channel, pitch, velocity);
    } else if (loop_instructions[index][0] == MIDI_NOTE_OFF) {
        byte channel  = loop_instructions[index][1];
        byte pitch    = loop_instructions[index][2];
        byte velocity = loop_instructions[index][3];
        
        //Send midi instruction
        sendMidiNoteOff(channel, pitch, velocity);
        
        //Send pad instruction
        sendPadNoteOff(channel, pitch, velocity);
    }
}
