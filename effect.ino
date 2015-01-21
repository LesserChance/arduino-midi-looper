void startEffect(int pad_index, byte velocity) {
    byte brightness = expScale(velocity);
    uint32_t color = getPadColor(pad_index, brightness);
    
    effect_running[pad_index] = true;
    effect_start[pad_index] = millis();
    effect_length[pad_index] = 200;
    effect_inital_value[pad_index] = brightness;
    
    for(int i = 0; i < pad_strips[pad_index]->numPixels(); i++) {
        pad_strips[pad_index]->setPixelColor(i, color);
    }
    pad_strips[pad_index]->show();
    effect_running[pad_index] = true;
}

/**
 * run the current step in all running effects
 */
void playEffects() {
    for (int i = 0; i < PAD_COUNT; i++) {
        if (effect_running[i]) {
            playEffect(i);
        }
    }
}

/**
 * run the current step in the given effect
 */
void playEffect(int pad_index) {
    unsigned long clock = millis();
    int effect_step = clock - effect_start[pad_index];

    if (effect_step <= effect_length[pad_index]) {
        //fade out
        float fade_by = effect_inital_value[pad_index] / (float) effect_length[pad_index];
        int brightness = effect_inital_value[pad_index] - (effect_step * fade_by);
        
        uint32_t color = getPadColor(pad_index, brightness);
    
        for(int i = 0; i < pad_strips[pad_index]->numPixels(); i++) {
            pad_strips[pad_index]->setPixelColor(i, color);
        }
        pad_strips[pad_index]->show();
    } else if (effect_step <= effect_length[pad_index] + 10) {
        resetPadEffect(pad_index);
    }
}

/**
 * get a pad color
 * @param {int} pad_index
 * @param {byte} brightness
 */
uint32_t getPadColor(int pad_index, byte brightness) {
    byte red;
    byte green;
    byte blue;
    
    switch (pad_index) {        
        case SNARE:
            red = 255;
            green = 0;
            blue = 0;
            break;
        case TOM_ONE:
            red = 255;
            green = 128;
            blue = 0;
            break;
        case TOM_TWO:
            red = 0;
            green = 255;
            blue = 0;
            break;
        case FLOOR_TOM:
            red = 0;
            green = 128;
            blue = 255;
            break;
        case HI_HAT:
            red = 0;
            green = 0;
            blue = 255;
            break;
        case CRASH:
            red = 255;
            green = 255;
            blue = 0;
            break;
        case RIDE:
            red = 255;
            green = 128;
            blue = 128;
            break;
        case BASS_DRUM:
            red = 255;
            green = 0;
            blue = 255;
            break;
    }
    
    //scale each color by a factor of the brightness
    // brightness of 255 = a full start value
    // brightness of 127 = half start value
    return pad_strips[pad_index]->Color(
        ((red)   ? brightness * (float(red)   / 255) : 0),
        ((green) ? brightness * (float(green) / 255) : 0),
        ((blue)  ? brightness * (float(blue)  / 255) : 0)
    );
}

void resetPadEffect(int pad_index) {
    effect_running[pad_index] = false;
    uint32_t color = pad_strips[pad_index]->Color(0, 0, 0);
    
    for(int i = 0; i < pad_strips[pad_index]->numPixels(); i++) {
        pad_strips[pad_index]->setPixelColor(i, color);
    }
    pad_strips[pad_index]->show();
}

/**
 * The scale at which velocity corresponds to brightness, return a value between 0 and 255
 */
unsigned long expScale(float val) {
    float a = 3.351;
    float b = 1.034;
    return a * (pow(b, val));
}
