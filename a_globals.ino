/***************************
 * GLOBAL LOOP DATA        *
 ***************************/
/**
 * @var {Byte} the position the next recorded loop will go in
 */
byte current_loop = 0;

/**
 * @var {Byte} the position of the of the loop before the current loop
 */
byte previous_loop = NO_PREVIOUS_LOOP;

/**
 * @var {Byte} the position of the loop at the bottom of the stack
 */
byte bottom_loop = 0;

/**
 * @var {Boolean[]} the loops to be played back
 *                 run_loops[loop_index] = boolean run
 */
boolean run_loops[MAX_LOOPS];


/***************************
 * LOOP DATA               *
 ***************************/
/**
 * @var {Long[]} the beginning time for each loop
 *                 loop_start[loop_index] = unsigned long time
 */
unsigned long loop_start[MAX_LOOPS];

/**
 * @var {Long[]} the length for each loop
 *                 loop_length[loop_index] = unsigned long length
 */
unsigned long loop_length[MAX_LOOPS];

/**
 * @var {Byte[]} the first instruction for each loop
 *                 loop_instruction_index_start[loop_index] = byte instruction index
 */
byte loop_instruction_index_start[MAX_LOOPS];

/**
 * @var {Byte[]} the last instruction for each loop
 *                 loop_instruction_index_end[loop_index] = byte instruction index
 */
byte loop_instruction_index_end[MAX_LOOPS];


/***************************
 * LOOP INSTRUCTION DATA   *
 ***************************/
/**
 * @var {Byte[][]} the instructions for each loop 
 *                 loop_instructions[instruction_index] = byte args[]
 */
byte loop_instructions[MAX_INSTRUCTIONS][MAX_INSTRUCTION_ARGUMENTS];

/**
 * @var {Int[]} the time of each instruction in a loop (starting from 0 as start of loop)
 *                 loop_instruction_times[instruction_index] = unsigned int time
 */
unsigned int loop_instruction_times[MAX_INSTRUCTIONS];


/***************************
 * RECORDING STATE         *
 ***************************/
/**
 * @var {Boolean} true if currently recording
 */
boolean recording = false;

/**
 * @var {Boolean} true if recording is waiting on a loop to begin
 */
boolean record_on_loop_start = false;

/**
 * @var {Int} the position the next recorded instruction will go in
 */
unsigned int loop_record_instruction_position = 0;


/***************************
 * PLAYBACK STATE          *
 ***************************/
/**
 * @var {Long[]} the last time marker the playback happened at for each loop
 *                 loop_playback_position[loop_index] = unsigned int time
 */
unsigned int loop_playback_position[MAX_LOOPS];


/***************************
 * EFFECTS                 *
 ***************************/
/**
 * @var {Boolean[]} true if the effect should be running
 */
boolean effect_running[PAD_COUNT];

/**
 * @var {Long[]} the timestmp the effect started
 */
unsigned long effect_start[PAD_COUNT];

/**
 * @var {Int[]} length of the effect
 */
unsigned int effect_length[PAD_COUNT];

/**
 * @var {byte[]} the initial value of the effect
 */
byte effect_inital_value[PAD_COUNT];


/***************************
 * PAD DATA                *
 ***************************/
/**
 * @var {byte[][]} the possible pitches each pad can produce
 *                 pad_pitches[pad] = array of pitche
 */
byte pad_pitches[PAD_COUNT][MAX_PITCHES_PER_PAD] = {
    {38},
    {48},
    {45},
    {41},
    {46},
    {49},
    {51},
    {36}
};


Adafruit_NeoPixel pad_strips_SNARE     = Adafruit_NeoPixel(19, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pad_strips_TOM_ONE   = Adafruit_NeoPixel(19, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pad_strips_TOM_TWO   = Adafruit_NeoPixel(19, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pad_strips_FLOOR_TOM = Adafruit_NeoPixel(19, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pad_strips_HI_HAT    = Adafruit_NeoPixel(19, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pad_strips_CRASH     = Adafruit_NeoPixel(19, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pad_strips_RIDE      = Adafruit_NeoPixel(19, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pad_strips_BASS_DRUM = Adafruit_NeoPixel(19, 9, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel * pad_strips[PAD_COUNT] = {
    &pad_strips_SNARE,
    &pad_strips_TOM_ONE,
    &pad_strips_TOM_TWO,
    &pad_strips_FLOOR_TOM,
    &pad_strips_HI_HAT,
    &pad_strips_CRASH,
    &pad_strips_RIDE,
    &pad_strips_BASS_DRUM
};
