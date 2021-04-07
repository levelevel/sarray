#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sarray.h"

#define ARRAY_INIT_SIZE     16
#define ARRAY_GROW_FACTOR   2

//アレイをアロケートする。
//init_capacityには初期最大データサイズを指定する。0の場合はデフォルト値が使用される。
//長さ(array->num)は常に0となる。
sarray_t *new_sarray(const sarray_char_t *str) {
    size_t len = 0;
    if (str) len = strlen(str);
    sarray_t *sarray = calloc(1, sizeof(sarray_t));
    assert(sarray);
    sarray->capacity = len?len+1:ARRAY_INIT_SIZE;
    sarray->str_buf = calloc(sarray->capacity, sizeof(sarray_char_t));
    assert(sarray->str_buf);
    if (str) strcpy(sarray->str_buf, str);
    return sarray;
}

//アレイを解放する。
void free_sarray(sarray_t *sarray) {
    if (sarray) free(sarray->str_buf);
    free(sarray);
}

//アレイの長さ（文字列の長さ）を取得する。
size_t len_sarray(const sarray_t *sarray) {
    assert(sarray);
    return strlen(sarray->str_buf);
}

//アレイに指定された文字列を格納し、格納された文字列のポインタを返す。
//アレイの長さは指定された文字列を格納するのに十分なサイズに自動的に拡張される。
sarray_char_t *set_sarray(sarray_t *sarray, const sarray_char_t *str) {
    assert(sarray);
    if (str) {
        size_t len = strlen(str);
        if (len>=sarray->capacity) {
            while (len>=sarray->capacity) sarray->capacity *= ARRAY_GROW_FACTOR;
            sarray->str_buf = realloc(sarray->str_buf, sarray->capacity*sizeof(sarray_char_t));
            assert(sarray->str_buf);
        }
        strcpy(sarray->str_buf, str);
    } else {
        *sarray->str_buf = '\0';
    }
    return sarray->str_buf;
}

//アレイの最後に文字列を連結（追加）し、格納された文字列のポインタを返す。
//アレイの長さは指定された文字列を格納するのに十分なサイズに自動的に拡張される。
sarray_char_t *concat_sarray(sarray_t *sarray, const sarray_char_t *str) {
    assert(sarray);
    if (str) {
        size_t old_len = strlen(sarray->str_buf);
        size_t new_len = old_len + strlen(str);
        if (new_len>=sarray->capacity) {
            while (new_len>=sarray->capacity) sarray->capacity *= ARRAY_GROW_FACTOR;
            sarray->str_buf = realloc(sarray->str_buf, sarray->capacity*sizeof(sarray_char_t));
            assert(sarray->str_buf);
        }
        strcpy(sarray->str_buf+old_len, str);
    }
    return sarray->str_buf;
}

//アレイのサイズを必要最低限にシュリンクし、格納された文字列のポインタを返す。
sarray_char_t *shrink_sarray(sarray_t *sarray) {
    assert(sarray);
    sarray->capacity = strlen(sarray->str_buf)+1;
    sarray->str_buf = realloc(sarray->str_buf, sarray->capacity*sizeof(sarray_char_t));
    return sarray->str_buf;
}
