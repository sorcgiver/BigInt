
#ifndef BGN_LIST_H
#define BGN_LIST_H

//=============================== FLAGS ========================================
#define BGNL_SIZE_TYPE unsigned long

#define BGNL_RELOCATE_BEGIN 0xFFFFFFFF
#define BGNL_RELOCATE_END 0xFFFFFFFE

#define BGNL_CREATE_FORWARD 1
#define BGNL_CREATE_BACK 0

#define BGNL_PRINTF
//==============================================================================

typedef union bgn_list_data {
    unsigned short data_sh;
    unsigned char data_ch[2];
} *BGN_LIST_DATA;

typedef struct bgn_list {
    union bgn_list_data data;
    BGNL_SIZE_TYPE *size;
    struct bgn_list *next;
    struct bgn_list *previous;
} *BGN_LIST;

//============================ CREATE / FREE ===================================
BGN_LIST bgnl_create(union bgn_list_data data);

BGN_LIST bgnl_free(BGN_LIST bgnl);
BGN_LIST bgnl_free_next(BGN_LIST bgnl);
BGN_LIST bgnl_free_all(BGN_LIST bgnl);

//============================== ADD / REMOVE ==================================
BGN_LIST bgnl_add(BGN_LIST bgnl, union bgn_list_data data, unsigned char flag_create);
BGN_LIST bgnl_add_ptr(BGN_LIST bgnl, union bgn_list_data *data, unsigned char flag_create);

//================================ RELOCATE ====================================
BGN_LIST bgnl_relocate(const BGN_LIST bgnl, const long pos);

//================================== DATA ======================================
void bgnl_bit_shift_begin(BGN_LIST bgnl, unsigned int shift);
void bgnl_bit_shift_end(BGN_LIST bgnl, unsigned int shift);

//================================= PRINTF =====================================
#ifdef BGNL_PRINTF
void bgnl_printf(BGN_LIST bgnl);
#endif

//================================ OPERATION ===================================
void bgnl_operation_add(BGN_LIST bgnl, BGN_LIST add);
void bgnl_operation_sub(BGN_LIST bgnl, BGN_LIST sub);
void bgnl_operation_mul(BGN_LIST bgnl, BGN_LIST mul);
void bgnl_operation_div(BGN_LIST bgnl, BGN_LIST div);


//============================= HELP FUNCTION ==================================
BGN_LIST __bgnl_create_connect(BGN_LIST fd_bgnl, BGN_LIST_DATA data_cpy, unsigned char flag_crete);
//======================== !!! FINALIZE FREE !!! ===============================
BGN_LIST __bgnl_free(BGN_LIST bgnl);

#endif /* BGN_LIST_H */
