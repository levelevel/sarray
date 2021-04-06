#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sarray.h"

//CPU時間とメモリを表示
#include <sys/time.h>
#include <sys/resource.h>
void print_usage() {
#ifdef __linux__
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    printf("User:   %ld.%03ld sec\n", ru.ru_utime.tv_sec, ru.ru_utime.tv_usec/1000);
    printf("Sys:    %ld.%03ld sec\n", ru.ru_stime.tv_sec, ru.ru_stime.tv_usec/1000);
    printf("Memory: %ld MB\n", ru.ru_maxrss/1024);
#endif
}

static sarray_char_t DATA1 = 'A';
static sarray_char_t DATA2 = 'Z';
static sarray_char_t DATA3 = '9';

//機能テスト
void test_array(void) {
    sarray_t *array, *array2;

    array = new_sarray(10);
    assert(array->capacity==10);
    assert(len_array(array)==0);
    free_sarray(array);

    array = new_sarray(0);
    put_sarray(array, 10, DATA1);
    assert(len_array(array)==11);
    assert(get_sarray(array, 10)==DATA1);
    put_sarray(array, 20, DATA2);
    assert(len_array(array)==21);
    assert(get_sarray(array, 20)==DATA2);
    assert(get_sarray(array, 0)=='\0');
    del_sarray(array, 10);
    assert(len_array(array)==20);
    assert(get_sarray(array, 10)=='\0');
    assert(get_sarray(array, 19)==DATA2);
    free_sarray(array);

    array = new_sarray(0);
    push_sarray(array, DATA1);
    assert(len_array(array)==1);
    assert(get_sarray(array, 0)==DATA1);
    push_sarray(array, DATA2);
    assert(len_array(array)==2);
    assert(get_sarray(array, 0)==DATA1);
    assert(get_sarray(array, 1)==DATA2);
    assert(pop_sarray(array)==DATA2);
    assert(len_array(array)==1);
    free_sarray(array);

    array = new_sarray(0);
    put_sarray(array, 100, DATA1);
    put_sarray(array, 200, DATA2);
    array2 = dup_sarray(array);
    assert(len_array(array2)==201);
    assert(get_sarray(array2, 100)==DATA1);
    assert(get_sarray(array2, 199)=='\0');
    assert(get_sarray(array2, 200)==DATA2);
    put_sarray(array2, 300, DATA3);
    assert(len_array(array2)==301);
    assert(get_sarray(array2, 300)==DATA3);
    assert(len_array(array)==201);
    free_sarray(array);
    free_sarray(array2);

    array = new_sarray(0);
    put_sarray(array, 10, DATA1);
    put_sarray(array, 20, DATA2);
    set_sarray_len(array, 50);
    assert(len_array(array)==50);
    assert(get_sarray(array, 49)=='\0');
    set_sarray_len(array, 15);
    assert(len_array(array)==15);
    assert(get_sarray(array, 10)==DATA1);
    //assert(get_sarray(array, 20)==DATA2);//Eror
    free_sarray(array);

    //サイズ固定
    array = new_sarray(0);
    put_sarray(array, 9, '\0');
    assert(array->len==10);
    assert(array->capacity==16);
    fix_sarray_size(array);
    assert(array->size_fixed);
    assert(array->len==array->capacity);
    put_sarray(array, 9, '\0');
    //put_sarray(array, 10, '\0');//Error
    //pop_sarray(array);//Error
    //push_sarray(array, '\0');//Error

    //サイズ固定解除
    unfix_sarray_size(array);
    put_sarray(array, 10, '\0');
    pop_sarray(array);
    push_sarray(array, '\0');
    assert(array->len==11);
    free_sarray(array);

    printf("== Functional Test: OK\n");
}

//性能テスト
void test_array_speed(long size) {
    printf("== Speed Test: n=%ld\n", size);
    int psize = size/2;
    sarray_t *array = new_sarray(0);

    for (int i=0; i<size; i++) {
        put_sarray(array, i, 'A');
    }
    for (int i=0; i<psize; i++) {
        pop_sarray(array);
    }
    for (int i=0; i<psize; i++) {
        push_sarray(array, '0');
    }
    assert(len_array(array)==size);

    free_sarray(array);

    //結果表示
    print_usage();
}

int main(int argc, char **argv) {
    printf("Start Test\n");
    test_array();
    test_array_speed(200*1000*1000);
}
