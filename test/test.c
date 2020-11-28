
#include <rhythm.h>
//  Compile
//  gcc test.c ../src/*.c -I ../include -o rhythm_test && ./rhythm_test
int main(void) {
    rhythm_t r;

    // create Cuban Cinquillo
    r.bits = chsequl(1, 8, 5, 0);
    print_rhythm(&r);
    bit_array_free(r.bits);

    // create Cuban Tresillo
    r.bits = chsequl(1, 8, 3, 0);
    print_rhythm(&r);
    bit_array_free(r.bits);

}