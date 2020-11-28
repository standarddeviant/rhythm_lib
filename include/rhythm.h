// rhythm_types.h

// TODO cpp-extern
#ifndef RHYTHM_HEADER_SEEN
#define RHYTHM_HEADER_SEEN

#include <bar.h> // bit_array short-hand
#include <stdint.h>

typedef struct {
    uint16_t ix;
    uint8_t take_ratio;
    uint8_t take_ratio_count;
    BIT_ARRAY *bits;
} stored_rhythm_t;
typedef stored_rhythm_t rhythm_t;

rhythm_t *rhythm_create(bit_index_t nbits);
void rhythm_free(rhythm_t *r);
uint8_t rhythm_take(rhythm_t *r);
void print_rhythm(rhythm_t *r);
BIT_ARRAY *chsequl(uint8_t upper, unsigned long p, unsigned long q, unsigned long _n);



typedef struct {
    uint16_t reset;
    uint16_t reset_count;
    uint16_t num_rhythms;
    uint16_t _reserved;
    rhythm_t *rhythms[];
} stored_rhythm_set_t;

#endif // RHYTHM_HEADER_SEEN
// TODO cpp-extern