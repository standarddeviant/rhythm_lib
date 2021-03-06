
#include <rhythm.h>
//  Compile
//  gcc test.c ../src/*.c -I ../include -o rhythm_test && ./rhythm_test
int main(void) {
    rhythm_t *r = rhythm_create(0);
    r->bits = chsequl(1, 8, 5, 0);

    // create Cuban Cinquillo
    rhythm_print("Cuban Cinquillo: ", r);
    bit_array_free(r->bits);
    printf("\n");

    // create Cuban Tresillo
    r->bits = chsequl(1, 8, 3, 0);
    printf("Cuban Tresillo, rotated 2, then 3\n");
    rhythm_print("\0", r);
    rhythm_rotate(r, 2);
    rhythm_print("\0", r);
    rhythm_rotate(r, 3);
    rhythm_print("\0", r);
    bit_array_free(r->bits);
    printf("\n");

    // create Cuban Tresillo
    r->bits = chsequl(1, 8, 3, 0);
    printf("Cuban Tresillo, rotated next onset twice\n");
    rhythm_print("\0", r);
    rhythm_rotate_next_onset(r);
    rhythm_print("\0", r);
    rhythm_rotate_next_onset(r);
    rhythm_print("\0", r);
    bit_array_free(r->bits);
    printf("\n");

    // create Folding Algo(s)
    r->bits = pfold(16, 1, 1);
    printf("Folding(16,1,1) rotated next onset twice\n");
    rhythm_print("\0", r);
    rhythm_rotate_next_onset(r);
    rhythm_print("\0", r);
    rhythm_rotate_next_onset(r);
    rhythm_print("\0", r);
    bit_array_free(r->bits);
    printf("\n");

}