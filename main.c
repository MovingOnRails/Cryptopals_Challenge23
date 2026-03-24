#include <stdbool.h>

#define MT19937_MAGIC_A (0x9d2c5680)
#define MT19937_MAGIC_B (0xefc60000)

// This function does not work correctly
unsigned long undo_right_shift(unsigned long y,int shift){
    unsigned long x = 0;
    for(int i=0;i<32;i++){
        bool bit = (y >> (31 - i)) & 1;
        if(i >= shift){
            bit ^= (x >> (32 - shift)) & 1;
        }
        x = (x << 1) | bit;
    }
    return x;
}

// This function does not work correctly
unsigned long undo_left_shift(unsigned long y, int shift, unsigned long mask){
    unsigned long x = 0;
    for(int i=0;i<32;i++){
        bool bit = (y >> i) & 1;
        if(i >= shift){
            bit ^= ((x >> (i - shift)) & 1) & ((mask >> i) & 1);
        }
        x |= bit << i;
    }
    return x;
}

// This function does not work correctly
uint32_t untemper(uint32_t tempered){
    uint32_t y = tempered;
    y = undo_right_shift(y, 18);
    y = undo_left_shift(y, 15, 0xEFC60000);
    y = undo_left_shift(y, 7, 0x9D2C5680);
    y = undo_right_shift(y, 11);
    return y;
}

uint32_t untemper_value(const uint32_t temp_val)
{
	size_t i;
	uint32_t tmp, untempered;

	// Step 4 : x ^= x >> 18
	untempered = temp_val ^ (temp_val >> 18);

	// Step 3 : x ^= (x << 15) ^ b
	untempered	^= ((untempered << 15) & MT19937_MAGIC_B);
    
	// Step 2 : x ^= (x << 7) ^ a
	tmp = ((untempered << 7 ) &  MT19937_MAGIC_A);
    for (i = 0; i < 4; i++)
    {
       untempered ^= tmp;           
       tmp = ((tmp << 7 ) &  MT19937_MAGIC_A);
    }

	// Step 1 : x ^= x >> 11
	untempered ^= (untempered >> 11) ^ (untempered >> 22);

	return untempered;
}