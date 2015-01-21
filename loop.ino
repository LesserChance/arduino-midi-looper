/**
 * Initialize the Loop variables
 */
void setupLoops() {
    for (int i = 0; i < MAX_LOOPS; i++) {
        run_loops[i] = false;
    }
}

/***************************
 * RECORDING               *
 ***************************/
/**
 * Start recording a new loop
 */
void startRecording() {
    record();
}

/**
 * Start recording a new loop at the same instant the previous loop loops
 */
void prepRecording() {
    //if loops exist before this, start recording at their beginning
    if (previous_loop != NO_PREVIOUS_LOOP) {
        record_on_loop_start = true;
        checkStartRecording();
    } else {
        record();
    }
}

/**
 * Start recording a new loop
 */
void checkStartRecording() {
    if (record_on_loop_start) {
        if (previous_loop != NO_PREVIOUS_LOOP) {
            unsigned int loop_zero_pos = getPlaybackPosition(previous_loop);
            if (loop_zero_pos <= 5 || loop_zero_pos >= loop_length[previous_loop] - 5) {
                //ok to start recording
                record();
            }
        } else {
            record();
        }
    }
}

/**
 * Start recording instructions on the current loop, marking now as the beginning time
 */
void record() {
    record_on_loop_start = false;
    recording = true;
    
    //if this loop is currently running we've looped around to the bottom
    if (run_loops[current_loop]) {
        deleteBottomLoop();
    }
    
    
    //initialize loop state
    loop_start[current_loop] = millis();
    loop_instruction_index_start[current_loop] = loop_record_instruction_position;
    
    digitalWrite(13, HIGH);
}

/**
 * Stop recording instructions on the current loop
 */
void stopRecording() {
    recording = false;
    
    unsigned long current_time = millis();
    unsigned long fixed_loop_length = getFixedLoopLength(current_time - loop_start[current_loop]);
    
    //save the position of the last recorded instruction
    if (loop_record_instruction_position == 0) {
        loop_instruction_index_end[current_loop] = MAX_INSTRUCTIONS - 1;
    } else {
        loop_instruction_index_end[current_loop] = loop_record_instruction_position - 1;
    }
    
    loop_length[current_loop] = fixed_loop_length;
    loop_playback_position[current_loop] = 0;
    run_loops[current_loop] = true;
    
    //mark the current loop as the previous one before readying the next one
    previous_loop = current_loop;
    
    //go to the next loop position
    current_loop++;
    if (current_loop == MAX_LOOPS) {
        current_loop = 0;
    }
    digitalWrite(13, LOW);
    
}

/*
 * Get the current position within the recording loop
 */
unsigned int getRecordingPosition() {
    return (millis() - loop_start[current_loop]);
}

/***************************
 * PLAYBACK                *
 ***************************/
/**
 * Playback all recorded loops
 */
void playLoops() {
    for (int i = 0; i < MAX_LOOPS; i++) {
        if (run_loops[i]) {
            playLoop(i);
        }
    }
}

/**
 * Playback a specific loop
 */
void playLoop(int index) {
    unsigned int last_playback_position = loop_playback_position[index];
    unsigned int playback_position = getPlaybackPosition(index);
    
    //play any commands between the last time this was checked and now
    if (playback_position != last_playback_position) {
        byte i = loop_instruction_index_start[index];
        boolean done_checking = false;
        
        while (!done_checking) {
            unsigned int check_time = loop_instruction_times[i];
            if (check_time >= last_playback_position && check_time < playback_position) {
                playInstruction(i);
            }
            
            if (i == loop_instruction_index_end[index] || check_time >= playback_position) {
                //no need to check any further
                done_checking = true;
            } else {
                //ready the check for the next instruction
                i++;
                if (i == MAX_INSTRUCTIONS) {
                    i = 0;
                }
            }
        }
        
        loop_playback_position[index] = playback_position;
    }

}

/*
 * Get the current position within the playback loop
 * @param {Int} index - the loop index
 */
unsigned int getPlaybackPosition(int index) {
    return (millis() - loop_start[index]) % loop_length[index];
}

/***************************
 * MANIPULATION            *
 ***************************/
/*
 * Delete the loop at the bottom of the stack
 */
 void deleteBottomLoop() {
     if (run_loops[bottom_loop]) {
         run_loops[bottom_loop] = false;
         bottom_loop++;
         
         if (bottom_loop == MAX_LOOPS) {
             bottom_loop = 0;
         }
         
         if (bottom_loop == current_loop) {
             previous_loop = NO_PREVIOUS_LOOP;
         }
     }
 }
 
/*
 * Delete the loop at the bottom of the stack
 */
 void deleteTopLoop() {
     if (run_loops[previous_loop]) {
         run_loops[previous_loop] = false;
         
         //move the current loop back a position
         current_loop = previous_loop;
         
         if (bottom_loop == current_loop) {
             //we're at the bottom, no previous loop
             previous_loop = NO_PREVIOUS_LOOP;
         } else {
             //we can find a previous loop
             if (previous_loop == 0) {
                 previous_loop = MAX_LOOPS - 1;
             } else {
                 previous_loop = previous_loop - 1;
             }
         }
     }
 }

/***************************
 * GETTERS                 *
 ***************************/
/*
 * if the loop length is close to another recorded loop, make them match
 * @param {Long} length - the lengrth to truncate
 */
unsigned long getFixedLoopLength(unsigned long length) {
    if (previous_loop != NO_PREVIOUS_LOOP) {
        unsigned long target_length = loop_length[previous_loop];
        
        if (length >= target_length - TARGET_LENGTH_MARGIN && length <= target_length + TARGET_LENGTH_MARGIN) {
            //exact length
            return target_length;
        } else if (length >= (target_length / 2) - TARGET_LENGTH_MARGIN && length <= (target_length / 2) + TARGET_LENGTH_MARGIN) {
            //half length
            return (target_length / 2);
        } else if (length >= (target_length * 2) - TARGET_LENGTH_MARGIN && length <= (target_length * 2) + TARGET_LENGTH_MARGIN) {
            //double length
            return (target_length * 2);
        }
    }
    
    //no comparisons, sue the passed in length
    return length;
}

