
#include "bigint.h"

#ifdef BGN_PRINTF
#include <stdio.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

#endif

#include <stdlib.h>
#include <math.h>
#include <string.h>

//BIGINT bgn_create_int(int val) {
//    BIGINT bgn = malloc(sizeof (struct bigint));
//
//    if (val < 0) {
//        bgn->is_negative = 1;
//        val |= 0x80000000;
//    } else {
//        bgn->is_negative = 0;
//    }
//
//    bgn->num_byte = floor(log10(val)) + 1;
//
//    if (bgn->num_byte == 0) {
//        bgn->num_byte = 1;
//    }
//
//    bgn->num_allocated_byte = bgn->num_byte;
//    bgn->data = malloc(bgn->num_allocated_byte * sizeof (union bgn_data));
//
//    int i;
//    for (i = 0; i < bgn->num_byte; i++) {
//        bgn->data[i].data[0] = val & 0xFF;
//        val >>= 8;
//        if (val == 0) {
//            bgn->num_byte = i + 1;
//            break;
//        }
//    }
//
//    return bgn;
//}

//void bgn_free(BIGINT bgn) {
//    free(bgn->data);
//    free(bgn);
//}

#ifdef BGN_PRINTF

void printBits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
}

//void bgn_printf_bit(BIGINT bgn) {
//    //    int val = bgn->data[1].byte2;
//    //    printf("%d", val);
//    for (int i = bgn->num_byte - 1; i >= 0; i--) {
//        printBits(1, bgn->data[i].data);
//        //        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(bgn->DATA[i].data[0]));
//    }
//    printf("\n");
//}
#endif

//void bgn_add(BIGINT bgn, BIGINT add) {
//    if (add->num_byte > bgn->num_allocated_byte) {
//        bgn_malloc_cpy(bgn, add->num_byte);
//    }
//    for (int i = 0; i < add->num_byte; i++) {
//        bgn->data[i].data[1] = 0;
//        bgn->data[i].byte2 += add->data[i].data[0];
//        if (bgn->is_negative == 1 && add->is_negative == 1 || bgn->is_negative == 0 && add->is_negative == 0) {
//            if (i > 0 && bgn->data[i - 1].data[1] > 0) {
//                bgn->data[i].data[0] += bgn->data[i - 1].data[1];
//            }
//        } else if (bgn->is_negative == 1 || add->is_negative == 1) {
//            bgn->data[i].data[0] = bgn->data[i].data[1];
//        }
//        //        if (i > 0 && bgn->data[i - 1].data[1] > 0) {
//        //            if (bgn->is_negative == 1 && add->is_negative == 1) {
//        //
//        //            } else if (bgn->is_negative == 1 || add->is_negative == 1) {
//        //
//        //            } else {
//        //                bgn->data[i].data[0] += bgn->data[i - 1].data[1];
//        //            }
//        //        }
//    }
//    if (add->num_byte > bgn->num_byte) {
//        bgn->num_byte = add->num_byte;
//    }
//    if (bgn->data[bgn->num_byte - 1].data[1] > 0) {
//        if (bgn->num_allocated_byte > bgn->num_byte) {
//            bgn->data[bgn->num_byte].data[0] = bgn->data[bgn->num_byte - 1].data[1];
//            bgn->num_byte++;
//        } else {
//            bgn_malloc_cpy(bgn, bgn->num_byte + 1);
//            bgn->data[bgn->num_byte].data[0] = bgn->data[bgn->num_byte - 1].data[1];
//            bgn->num_byte++;
//
//        }
//    }
//}

//void bgn_malloc_cpy(BIGINT bgn, unsigned int new_num_byte) {
//    static BGNDATA bgn_data_old;
//    bgn_data_old = bgn->data;
//    if (new_num_byte > bgn->num_byte) {
//        bgn->num_allocated_byte = new_num_byte;
//        bgn->data = malloc(bgn->num_allocated_byte * sizeof (union bgn_data));
//    } else {
//        bgn->num_allocated_byte = new_num_byte;
//        bgn->num_byte = new_num_byte;
//        bgn->data = malloc(bgn->num_allocated_byte * sizeof (union bgn_data));
//    }
//    memcpy(bgn->data, bgn_data_old, bgn->num_byte * sizeof (union bgn_data));
//    free(bgn_data_old);
//}
//
