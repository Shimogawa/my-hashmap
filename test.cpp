extern "C" {
#include "table.h"
}
#include <unordered_map>
#include <chrono>

void test() {
    Table *table = Table_new();
    Table_set(table, 3, 114);
    Table_set(table, 11, 514);
    Table_set(table, 19, 514);
    Table_set(table, 7, 514);
    Table_set(table, 6, 514);
    Table_set(table, 5, 514);
    Table_set(table, 4, 514);
    Table_del(table, 6);
    Table_del(table, 5);
    Table_del(table, 4);
    Table_set(table, 5, 114);
    Table_set(table, 6, 114);
    Table_set(table, 7, 114);
    Table_set(table, 8, 114);
    Table_set(table, 9, 114);
    Table_set(table, 10, 114);
    Table_debugprint(table);
    printf("%p\n", Table_find(table, 2));
    printf("%p\n", Table_find(table, 3));
    printf("%p\n", Table_find(table, 11));
    printf("%zd", table->size);
    Table_free(table);
}

int test0() {
    srand(114514);
    for (int i = 0; i < 20000; i++) {
        int key = rand();
        int value = rand();
    }
    for (int i = 0; i < 20000; i++) {
        int key = rand();
    }
    return 0;
}

int test1() {
    Table *table = Table_new();
    srand(114514);
    int count = 0;
    for (int i = 0; i < 20000; i++) {
        int key = rand();
        int value = rand();
        Table_set(table, key, value);
    }
    for (int i = 0; i < 20000; i++) {
        int key = rand();
        if (Table_find(table, key)) count++;
    }
    // printf("len = %zd\n", table->size);
    // printf("count = %d\n", count);
    Table_free(table);
    return count;
}

int test2() {
    std::unordered_map<int, int> table;
    srand(114514);
    int count = 0;
    for (int i = 0; i < 20000; i++) {
        int key = rand();
        int value = rand();
        table[key] = value;
    }
    for (int i = 0; i < 20000; i++) {
        int key = rand();
        if (table.find(key) != table.end()) count++;
    }
    // printf("len = %zd\n", table.size());
    // printf("count = %d\n", count);
    return count;
}

void timeit(int (*f)()) {
    auto start = std::chrono::high_resolution_clock::now();
    int count;
    for (int j = 0; j < 100; j++) count = f();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printf("count = %d, time = %lf\n", count, duration);
}

int main() {
    timeit(test0);
    timeit(test1);
    timeit(test2);
    // test1();
    // test2();
    return 0;
}
