#ifndef UBWT_H
#define UBWT_H

#include <stdint.h>
#include <stdio.h>

#define _OCC_C 5
#define _BWT_N 4
#define nt_N 4

#define _BWT_NT_K 4        // bits of per bwt_char
#define _BWT_NT_B 2
#define _BWT_NT_M 0x7      // 0/1/2/3/4
#define _BWT_INV 16        // count of bwt_char in one bwt_int; 16=64/4
#define _BWT_INV_B 4
#define _BWT_INV_M 0xf     // 15

#define _OCC_INV 128       // store C[5] for every (_OCC_INV) bwt_char; 128=16*8
#define _OCC_INV_B 7
#define _OCC_INV_M 0x7f    // 127

//#define _BWT_OCC_B 3     // 9=2^3+1
//#define bwt_bwt_occ_a(i) (((i) << _BWT_OCC_B) + (i))
//#define _BWT_OCC_B       // 8+5=13 = 2^3+2^2+1
#define ubwt_bwt_occ_a(i) (((i)<<3) + ((i)<<2) + (i))


#define ubwt_int_t uint64_t
#define ubwt_count_t uint64_t

typedef struct {
    ubwt_count_t ubwt_l;        // length of bwt_str(length of sequence)
    ubwt_count_t ubwt_size;     // size of bwt(bwt_char & OCC)
    ubwt_int_t *ubwt;           // bwt_str & OCC
    ubwt_count_t *ubwt_map, uni_c;     // map of adjacent unipath
    ubwt_int_t ubwt_unit;       // for push bwt
    ubwt_count_t ubwt_i, ubwt_k; // index of bwt_str and bwt

    ubwt_count_t C[_OCC_C];    // cumulative count of 'A/C/G/T/#'
                              // before:      [0]:A, [1]: C, [2]: G, [3]: T, [4]: #;
                              // updated C[]: [0]: 0
                              //              [1]: count of A
                              //              [2]: count of A, C
                              //              [3]: count of A, C, G
                              //              [4]: count of A, C, G, T
    uint8_t bit_table16[65536]; // count of '1'
} ubwt_t; // unipath bwt

uint8_t *ubwt_read_bwt_str(char *fn, int input_b, ubwt_count_t *ubwt_l);
void ubwt_init(ubwt_t *ubwt, ubwt_count_t ubwt_l);
void ubwt_free(ubwt_t *ubwt);
void ubwt_cal_occ(uint8_t ubwt_nt, ubwt_t *ubwt);
int ubwt_cal(ubwt_t *ubwt, uint8_t *ubwt_bstr, ubwt_count_t ubwt_l);
ubwt_count_t ubwt_exact_match(const ubwt_t *ubwt, int qlen, const uint8_t *query, ubwt_count_t *bwt_k, ubwt_count_t *bwt_l);
void ubwt_gen_bit_table16(ubwt_t *ubwt);
void ubwt_update(ubwt_t *ubwt);
void ubwt_gen_map(ubwt_t *ubwt, uint8_t *ubwt_bstr, int uni_c);
ubwt_count_t ubwt_cal_off(ubwt_t *ubwt, ubwt_count_t k, ubwt_count_t *off);
void ubwt_gen_unipath(ubwt_t *ubwt, uint8_t *ubwt_bstr, int uni_c, FILE *out);
void ubwt_gen_unipath1(ubwt_t *ubwt, ubwt_count_t uid, FILE *out);

#endif