#ifndef APTXDEC_H
#define APTXDEC_H

//Header goes here

/*
Reads from input_buffer of 16-bit ADPCM codewords at 11.025kHz, and writes
16-bit PCM samples at 44.1kHz to output_buffer
*/
void aptX_dec(unsigned short* input_buffer, unsigned short* output_buffer);


#endif