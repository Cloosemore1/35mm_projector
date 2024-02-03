#include <stdio.h>
#include "inv_quantizer.h"

short inv_quantize(unsigned char codeword, inv_quantizer *quantizer) {
    short output;
    short output_sign = 1;
    //Checking if the input level is negative
    if (codeword >= ((1 << quantizer->word_size) / 2)) {
        output_sign = -1;
        codeword -= ((1 << quantizer->word_size) / 2);
    }
    //Calculating the output
    output = output_sign * ((codeword + 0.5) * quantizer->step_size);
    //Determining multiplier and max step size values based on number of bits
    float new_step;
    float *multipliers;
    short max_step = 0;
    switch (quantizer->word_size) {
        case 8:
            multipliers = mult_8bit;
            max_step = MAX_STEP_8;
            break;
        case 4:
            multipliers = mult_4bit;
            max_step = MAX_STEP_4;
            break;
        case 2:
            multipliers = mult_2bit;
            max_step = MAX_STEP_2;
            break;
        default:
            fprintf(stderr, "Invalid quantizer level\n");
            break;
    }
    //Setting new step size
    new_step = quantizer->step_size * multipliers[codeword];
    if(new_step > max_step) {
        quantizer->step_size = max_step;
        return output;
    }
    if (new_step < 1) {
        quantizer->step_size = 1;
        return output;
    }
    quantizer->step_size = new_step;
    return output;
} //inv_quantize

int main() {
    char codewords[12] = {0, 7, 7, 5, 6, 6, 5, 4, 2, 0, 9, 12};
    inv_quantizer quantizer;
    quantizer.word_size = 4;
    quantizer.step_size = 512;

    for (int i = 0; i < 12; i++) {
        printf("Output: %d\n", inv_quantize(codewords[i], &quantizer));
    }

    return 0;
}