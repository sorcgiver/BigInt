
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "bigint.h"
#include "bgn_list.h"

/*
 * 
 */
int main(int argc, char** argv) {
    union bgn_list_data a;
    a.data_sh = 0xff;
    BGN_LIST lst = bgnl_create(a);
    a.data_sh = 0xf0;
    lst = bgnl_add(lst, a, BGNL_CREATE_FORWARD);
    lst = bgnl_add(lst, a, BGNL_CREATE_FORWARD);
    lst = bgnl_relocate(lst, BGNL_RELOCATE_BEGIN);
    for (int i = 0; i < 8; i++) {
        //        printf("%d) ", i);
        bgnl_printf(lst->next->next);
        printf(" ");
        bgnl_printf(lst->next);
        printf(" ");
        bgnl_printf(lst);
        printf("\n");
        bgnl_bit_shift_begin(lst, 1);
    }
    for (int i = 0; i < 8; i++) {
        //        printf("%d) ", i);
        bgnl_printf(lst->next->next);
        printf(" ");
        bgnl_printf(lst->next);
        printf(" ");
        bgnl_printf(lst);
        printf("\n");
        bgnl_bit_shift_end(lst, 1);
    }
    bgnl_printf(lst->next->next);
    printf(" ");
    bgnl_printf(lst->next);
    printf(" ");
    bgnl_printf(lst);
    printf("\n");
    bgnl_free_all(lst);

    //    BIGINT a, b;
    //    a = bgn_create_int(1);
    //    b = bgn_create_int(256);
    ////    bgn_malloc_cpy(a, 10);
    ////    a->data[0].byte2 = 10;
    ////    a->data[1].byte2 = 20;
    ////    a->num_byte = 2;
    //    bgn_add(a, b);
    //    //    bgn_add(a, b);
    ////    bgn_printf_bit(a);
    //    bgn_free(a);
    //    bgn_free(b);
    return (EXIT_SUCCESS);
}

