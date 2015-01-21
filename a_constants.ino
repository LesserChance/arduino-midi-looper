/**
 * @var {Int} the midi channel to listen on
 */
const int MIDI_CHANNEL = 10;

/**
 * @var {Int} the buffer in which loop lengths should be trimmed to match
 */
const int TARGET_LENGTH_MARGIN = 300;

/**
 * @var {byte} the note on instruction
 */
const byte MIDI_NOTE_ON = 0;

/**
 * @var {byte} the note on instruction
 */
const byte MIDI_NOTE_OFF = 1;

/**
 * @var {byte} the maximum number of concurrent loops
 *      its possible to loop around while loops are still playing, if so the lower loop will be overwritten
 */
const byte MAX_LOOPS = 4;

/**
 * @var {byte} the maximum number of instructions
 *      its possible to loop around while loops are still playing, if so instructions in the lower loop will be overwritten
 */
const byte MAX_INSTRUCTIONS = 100;

/**
 * @var {byte} the maximum number of arguments for an instruction
 */
const byte MAX_INSTRUCTION_ARGUMENTS = 4;

/**
 * @var {byte} a reference value for not having a previous loop
 */
const byte NO_PREVIOUS_LOOP = 255;

/**
 * @var {byte} 
 */
const byte COMMAND_RECORD_ONE = 102;

/**
 * @var {byte} 
 */
const byte COMMAND_DELETE_ONE = 103;

/**
 * @var {byte} 
 */
const byte COMMAND_RECORD_TWO = 104;

/**
 * @var {byte} 
 */
const byte COMMAND_DELETE_TWO = 105;

/**
 * @var {byte} 
 */
const byte COMMAND_CONTROL = 106;

/**
 * @var {byte} 
 */
const byte COMMAND_VALUE_OFF = 0;

/**
 * @var {byte} 
 */
const byte COMMAND_VALUE_ON = 127;

/**
 * @var {byte} the number of pads
 */
const byte PAD_COUNT = 8;

/**
 * @var {byte} the maximum number of pitches a single pad can have
 */
const byte MAX_PITCHES_PER_PAD = 2;

/**
 * @var {byte} pad indicies
 */
const byte SNARE = 0;
const byte TOM_ONE = 1;
const byte TOM_TWO = 2;
const byte FLOOR_TOM = 4;
const byte HI_HAT = 5;
const byte CRASH = 6;
const byte RIDE = 7;
const byte BASS_DRUM = 8;
