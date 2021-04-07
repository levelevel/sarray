#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sarray.h"

//CPU時間とメモリを表示
#include <sys/time.h>
#include <sys/resource.h>
void print_usage(void) {
#ifdef __linux__
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    printf("User:   %ld.%03ld sec\n", ru.ru_utime.tv_sec, ru.ru_utime.tv_usec/1000);
    printf("Sys:    %ld.%03ld sec\n", ru.ru_stime.tv_sec, ru.ru_stime.tv_usec/1000);
    printf("Memory: %.1f MB\n", ru.ru_maxrss/1024.0);
#endif
}
void print_memory(void) {
#ifdef __linux__
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    printf("Memory: %.1f MB\n", ru.ru_maxrss/1024.0);
#endif
}

//機能テスト
void test_array(void) {
    sarray_t *sarray;//
    sarray_char_t *str;

    sarray = new_sarray(NULL);
    assert(sarray->capacity==16);
    assert(len_sarray(sarray)==0);
    free_sarray(sarray);

    sarray = new_sarray("1234567890");
    assert(sarray->capacity==10+1);
    assert(len_sarray(sarray)==10);
    assert(strcmp(sarray->str_buf, "1234567890")==0);
    free_sarray(sarray);

    sarray = new_sarray(NULL);
    str = set_sarray(sarray, NULL);
    assert(len_sarray(sarray)==0);
    str = set_sarray(sarray, "");
    assert(len_sarray(sarray)==0);
    str = set_sarray(sarray, "abc");
    assert(sarray->capacity==16);
    assert(len_sarray(sarray)==3);
    assert(strlen(str)==3);

    str = concat_sarray(sarray, NULL);
    assert(len_sarray(sarray)==3);
    assert(strlen(str)==3);
    str = concat_sarray(sarray, "xyz");
    assert(len_sarray(sarray)==6);
    assert(strlen(str)==6);
    str = concat_sarray(sarray, "123456789");
    assert(len_sarray(sarray)==15);
    assert(strlen(str)==15);
    assert(sarray->capacity==16);
    str = concat_sarray(sarray, "0");
    assert(len_sarray(sarray)==16);
    assert(strlen(str)==16);
    assert(sarray->capacity==32);
    free_sarray(sarray);

    sarray = new_sarray("abc");
    sarray_t *dup = dup_sarray(sarray);
    assert(strcmp(dup->str_buf, sarray->str_buf)==0);
    assert(dup->capacity==len_sarray(dup)+1);
    free_sarray(sarray);

    printf("== Functional Test: OK\n");
}

//性能テスト
void test_array_speed(int num) {
    static const char str[] = "1234567890abcde";
    size_t len = strlen(str);
    printf("== Speed Test: n=%d (%ldMB)\n", num, len*(1<<num)/(1024*1024));

    sarray_t *sarray = new_sarray(str);

    for (int i=0; i<num; i++) {
        sarray_t *dup = dup_sarray(sarray);
        concat_sarray(sarray, dup->str_buf);
        free_sarray(dup);
        len *= 2;
        //printf("%2d: ", i); print_memory();
    }
    assert(len_sarray(sarray)==len);

    free_sarray(sarray);

    //結果表示
    print_usage();
}

int main(void) {
    printf("Start Test\n");
    test_array();
    test_array_speed(25);
}
