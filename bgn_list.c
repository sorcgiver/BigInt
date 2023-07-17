
#include "bgn_list.h"

#ifdef BGNL_PRINTF
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
#include <string.h>

BGN_LIST bgnl_create(union bgn_list_data data) {
    return __bgnl_create_connect(NULL, &data, 0);
}

BGN_LIST bgnl_free(BGN_LIST bgnl) {
    if (bgnl != NULL) {
        if (bgnl->previous != NULL) {
            bgnl->previous->next = bgnl->next;
        }
        if (bgnl->next != NULL) {
            bgnl->next->previous = bgnl->previous;
        }
        free(bgnl);
        (*bgnl->size)--;
    }
    return NULL;
}

BGN_LIST bgnl_free_next(BGN_LIST bgnl) {
    if (bgnl->previous == NULL)
        return bgnl_free_all(bgnl);
    static BGN_LIST lst;
    while (bgnl != NULL) {
        lst = bgnl;
        (*bgnl->size)--;
        bgnl = bgnl->next;
        free(lst);
    }
    return NULL;
}

BGN_LIST bgnl_free_all(BGN_LIST bgnl) {
    static BGN_LIST lst;
    bgnl = bgnl_relocate(bgnl, BGNL_RELOCATE_BEGIN);
    while (bgnl->next != NULL) {
        lst = bgnl;
        bgnl = bgnl->next;
        free(lst);
    }
    return __bgnl_free(bgnl);
}

BGN_LIST bgnl_add(BGN_LIST bgnl, union bgn_list_data data, unsigned char flag_create) {
    return __bgnl_create_connect(bgnl, &data, flag_create);
}

BGN_LIST bgnl_add_ptr(BGN_LIST bgnl, union bgn_list_data *data, unsigned char flag_create){
    return __bgnl_create_connect(bgnl, data, flag_create);
}

BGN_LIST bgnl_relocate(const BGN_LIST bgnl, const long pos) {
    if (bgnl == NULL)
        return NULL;
    static BGN_LIST lst;
    static int i;
    lst = bgnl;
    if (pos == BGNL_RELOCATE_BEGIN) {
        while (lst->previous != NULL) {
            lst = lst->previous;
        }
    } else if (pos == BGNL_RELOCATE_END) {
        while (lst->next != NULL) {
            lst = lst->next;
        }
    } else {
        if (pos > 0) {
            BGN_LIST lst_new = bgnl;
            //            lst_new = bgnl_relocate(bgnl, BGNL_RELOCATE_BEGIN);
            for (i = 0; i < pos && lst_new != NULL; i++) {
                lst_new = lst_new->next;
            }
            lst = lst_new;
        } else if (pos < 0) {
            BGN_LIST lst_new = bgnl;
            //            lst_new = bgnl_relocate(bgnl, BGNL_RELOCATE_END);
            for (i = 0; i > pos && lst_new != NULL; i--) {
                lst_new = lst_new->previous;
            }
            lst = lst_new;
        }
    }
    return lst;
}

void bgnl_bit_shift_begin(BGN_LIST bgnl, unsigned int shift) {
    if (bgnl == NULL)
        return;
    static BGN_LIST lst;
    long div = shift / 8;
    if (div >= *bgnl->size) {
        while (bgnl != NULL) {
            bgnl->data.data_ch[0] = 0;
            bgnl = bgnl->next;
        }
        return;
    }
    unsigned char resbit = shift % 8;
    unsigned char resbitinv = 8 - resbit;
    lst = bgnl_relocate(bgnl, div);
    while (lst != NULL) {
        if (resbit == 0) {
            bgnl->data.data_ch[0] = lst->data.data_ch[0];
        } else {
            bgnl->data.data_ch[0] = lst->data.data_ch[0] >> resbit;
            if (lst->next != NULL)
                bgnl->data.data_ch[0] |= (lst->next->data.data_ch[0] & (unsigned char) (0xFF >> resbitinv)) << resbitinv;
        }
        bgnl = bgnl->next;
        lst = lst->next;
    }
    while (bgnl != NULL) {
        bgnl->data.data_ch[0] = 0;
        bgnl = bgnl->next;
    }
}

void bgnl_bit_shift_end(BGN_LIST bgnl, unsigned int shift) {
    if (bgnl == NULL)
        return;
    static BGN_LIST lst, lst1;
    long div = shift / 8;
    if (div >= *bgnl->size) {
        while (bgnl != NULL) {
            bgnl->data.data_ch[0] = 0;
            bgnl = bgnl->next;
        }
        return;
    }
    unsigned char resbit = shift % 8;
    unsigned char resbitinv = 8 - resbit;
    lst = bgnl_relocate(bgnl, BGNL_RELOCATE_END);
    lst1 = bgnl_relocate(lst, (-1) * div);
    while (lst1 != bgnl->previous) {
        if (resbit == 0) {
            lst->data.data_ch[0] = lst1->data.data_ch[0];
        } else {
            lst->data.data_ch[0] = lst1->data.data_ch[0] << resbit;
            if (lst1->previous != bgnl->previous)
                lst->data.data_ch[0] |= (lst1->previous->data.data_ch[0] & (0xFF << resbitinv)) >> resbitinv;
            }
        lst = lst->previous;
        lst1 = lst1->previous;
    }
    while(lst != bgnl->previous){
        lst->data.data_ch[0] = 0;
        lst = lst->previous;
    }
}

#ifdef BGNL_PRINTF

void bgnl_printf(BGN_LIST bgnl) {
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(bgnl->data.data_ch[0]));
}
#endif

void bgnl_operation_add(BGN_LIST bgnl, BGN_LIST add){
    bgnl->data.data_ch[1] = 0;
    bgnl->data.data_sh += add->data.data_ch[0];
}

void bgnl_operation_sub(BGN_LIST bgnl, BGN_LIST sub){
    bgnl->data.data_ch[0] -= sub->data.data_ch[0];
}

void bgnl_operation_mul(BGN_LIST bgnl, BGN_LIST mul){
    bgnl->data.data_ch[1] = 0;
    bgnl->data.data_sh *= mul->data.data_ch[0];
}

void bgnl_operation_div(BGN_LIST bgnl, BGN_LIST div){
    bgnl->data.data_ch[0] /= div->data.data_ch[0];
}

BGN_LIST __bgnl_create_connect(BGN_LIST fd_bgnl, BGN_LIST_DATA data_cpy, unsigned char flag_crete) {
    static BGN_LIST bgnl;
    if (fd_bgnl == NULL) {
        bgnl = malloc(sizeof (struct bgn_list));
        bgnl->next = NULL;
        bgnl->previous = NULL;
        bgnl->size = malloc(sizeof (BGNL_SIZE_TYPE));
        *bgnl->size = 1;
        if (data_cpy != NULL)
            memcpy(&bgnl->data, data_cpy, sizeof (union bgn_list_data));
    } else {
        if (flag_crete == BGNL_CREATE_FORWARD) {
            bgnl = malloc(sizeof (struct bgn_list));
            bgnl->next = fd_bgnl->next;
            bgnl->previous = fd_bgnl;
            bgnl->size = fd_bgnl->size;
            (*bgnl->size)++;
            if (data_cpy != NULL)
                memcpy(&bgnl->data, data_cpy, sizeof (union bgn_list_data));
            fd_bgnl->next = bgnl;
        } else if (flag_crete == BGNL_CREATE_BACK) {
            bgnl = malloc(sizeof (struct bgn_list));
            bgnl->next = fd_bgnl;
            bgnl->previous = fd_bgnl->previous;
            bgnl->size = fd_bgnl->size;
            (*bgnl->size)++;
            if (data_cpy != NULL)
                memcpy(&bgnl->data, data_cpy, sizeof (union bgn_list_data));
            fd_bgnl->previous = bgnl;
        }
    }
    return bgnl;
}

BGN_LIST __bgnl_free(BGN_LIST bgnl) {
    if (bgnl != NULL) {
        free(bgnl->size);
        free(bgnl);
    }
    return NULL;
}