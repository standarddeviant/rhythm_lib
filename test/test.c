
#include <rhythm.h>

int main(void) {
    rhythm_t rkick;

    // BIT_ARRAY *chsequl(uint8_t upper, unsigned long p, unsigned long q, unsigned long _n)
    rkick.bits = chsequl(1, 8, 5, 0);
    print_rhythm(&rkick);


}