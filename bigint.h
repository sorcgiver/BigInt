//=================================== FLAGS ====================================
#define BGN_PRINTF
//==============================================================================

#ifndef BIGINT_H
#define BIGINT_H

#include "bgn_list.h"

typedef struct bigint {
    BGN_LIST data;
    unsigned int num_byte; // Number of digits actually in the number.
    unsigned int num_allocated_byte; // digits array has space for this many digits
    unsigned char is_negative; // Nonzero if this BigInt is negative, zero otherwise.
} *BIGINT;

//============================== CREATE / FREE =================================
//BIGINT bgn_create_int(int val);
//BIGINT bgn_create_str(char *val);
//void bgn_copy(BIGINT *bgn, BIGINT val);

//void bgn_free(BIGINT bgn);

//================================= PRINTF =====================================
#ifdef BGN_PRINTF
//void bgn_printf_bit(BIGINT bgn);
#endif

//================================ ADDITION ====================================
//void bgn_add(BIGINT bgn, BIGINT add);

//================================= MALLOC =====================================
//void bgn_malloc_cpy(BIGINT bgn, unsigned int new_num_byte);

#endif /* BIGINT_H */
