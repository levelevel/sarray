#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sarray.h"

#define ARRAY_INIT_SIZE     16
#define ARRAY_GROW_FACTOR   2

//アレイをアロケートする。
sarray_t *new_sarray(int len) {
    assert(len>=0);
    sarray_t *sarray = calloc(1, sizeof(sarray_t));
    assert(sarray);
    sarray->capacity = len?len:ARRAY_INIT_SIZE;
    sarray->buckets = calloc(sarray->capacity, sizeof(sarray_char_t));
    assert(sarray->buckets);
    return sarray;
}

//アレイを開放する。
void free_sarray(sarray_t *sarray) {
    if (sarray) free(sarray->buckets);
    free(sarray);
}

//アレイのサイズ(sarray->len)を取得する。
int len_array(const sarray_t *sarray) {
    assert(sarray);
    return sarray->len;
}

//アレイのサイズを設定する。アレイのサイズは自動的に拡張される。
void set_sarray_len(sarray_t *sarray, int len) {
    assert(sarray);
    assert(len>=0);
    sarray->len = len;
    sarray->buckets = realloc(sarray->buckets, len*sizeof(sarray_char_t));
    assert(sarray->buckets);
    if (len>sarray->capacity) {
        memset(sarray->buckets+sarray->capacity, 0x00, len-sarray->capacity);
    }
    sarray->capacity = len;
}

//アレイのidx番目にデータを格納する。アレイのサイズは自動的に拡張される。
//データ未設定の領域にはNULLが設定される。
void put_sarray(sarray_t *sarray, int idx, sarray_char_t chr) {
    assert(sarray);
    assert(idx>=0);
    if (idx>=sarray->capacity) {     //buckets拡張時は拡張分を0クリアする
        assert(!sarray->size_fixed);
        int new_cap = sarray->capacity;
        while (idx>=new_cap) new_cap *= ARRAY_GROW_FACTOR;
        sarray->buckets = realloc(sarray->buckets, new_cap*sizeof(sarray_char_t));
        assert(sarray->buckets);
        memset(sarray->buckets+sarray->capacity, 0x00, (new_cap-sarray->capacity)*sizeof(sarray_char_t));
        sarray->capacity = new_cap;
    }
    sarray->buckets[idx] = chr;
    if (idx>=sarray->len) sarray->len = idx+1;
}

//アレイのidx番目のデータを取得する。アレイのサイズは変わらない。
sarray_char_t get_sarray(const sarray_t *sarray, int idx) {
    assert(sarray);
    assert(idx>=0);
    assert(idx<sarray->len);
    return (sarray->buckets[idx]);
}

//アレイのidx番目のデータを削除する。以降のデータは前に詰められる。アレイのサイズは1減る。
void del_sarray(sarray_t *sarray, int idx) {
    assert(sarray);
    assert(idx>=0);
    assert(idx<sarray->len);
    memcpy(sarray->buckets+idx, sarray->buckets+idx+1, (sarray->len-idx)*sizeof(sarray_char_t));
    sarray->buckets[sarray->len-1] = '\0';
    sarray->len--;
}

//アレイの最後にデータを1個追加する。アレイのサイズは1増える。
void push_sarray(sarray_t *sarray, sarray_char_t chr) {
    assert(sarray);
    assert(!sarray->size_fixed);
    put_sarray(sarray, sarray->len, chr);
}

//アレイの最後のデータを1個取り出す。アレイのサイズは1減る。
sarray_char_t pop_sarray(sarray_t *sarray) {
    assert(sarray);
    assert(sarray->len>0);
    assert(!sarray->size_fixed);
    sarray_char_t chr = sarray->buckets[--sarray->len];
    sarray->buckets[sarray->len] = '\0';
    return chr;
}

//アレイを複製する。
//複製されたアレイの内部データは必要最低限分が確保される。
sarray_t *dup_sarray(sarray_t *sarray) {
    assert(sarray);
    sarray_t *new = new_sarray(sarray->len);
    new->len = sarray->len;
    memcpy(new->buckets, sarray->buckets, sarray->len*sizeof(sarray_char_t));
    return new;
}

//配列サイズを固定する。
//以降、配列サイズを変更するアクセス（push_sarray/pop_sarray等）はエラーとなる。
void fix_sarray_size(sarray_t *sarray) {
    sarray->size_fixed = 1;
    sarray->buckets = realloc(sarray->buckets, sarray->len*sizeof(sarray_char_t));
    sarray->capacity = sarray->len;
}
