#include <stddef.h>
#include <stdbool.h>

typedef unsigned int uint_t;

typedef void *(voidPtr__voidPtr_voidPtr__func)(void *be_ret, void *args);
typedef struct test_result_t test_result_t;
typedef struct test_t
{
    voidPtr__voidPtr_voidPtr__func *test;
    void *args;
} test_t;

void assertEqual_i(long long i1, long long i2, const char *msg);
void assertEqual_u(unsigned long long i1, unsigned long long i2, const char *msg);
void assertEqual_p(void *p1, void *p2, const char *msg);
void assertAlmostEqual_f(long double f1, long double f2, const char *msg);
void assertEquals_s(void *p1, void *p2, size_t size, const char *msg);

void assertNotEqual_i(long long i1, long long i2, const char *msg);
void assertNotEqual_u(unsigned long long i1, unsigned long long i2, const char *msg);
void assertNotEqual_p(void *p1, void *p2, const char *msg);
void assertNotAlmostEqual_f(long double f1, long double f2, const char *msg);
void assertNotEquals_s(void *p1, void *p2, size_t size, const char *msg);

void assertGreater_i(long long i1, long long i2, const char *msg);
void assertGreater_u(unsigned long long i1, unsigned long long i2, const char *msg);
void assertGreater_f(long double f1, long double f2, const char *msg);
void assertGreater_p(void *p1, void *p2, const char *msg);

void assertGreaterEqual_i(long long i1, long long i2, const char *msg);
void assertGreaterEqual_u(unsigned long long i1, unsigned long long i2, const char *msg);
void assertGreaterEqual_f(long double f1, long double f2, const char *msg);
void assertGreaterEqual_p(void *p1, void *p2, const char *msg);

void assertLess_i(long long i1, long long i2, const char *msg);
void assertLess_u(unsigned long long i1, unsigned long long i2, const char *msg);
void assertLess_f(long double f1, long double f2, const char *msg);
void assertLess_p(void *p1, void *p2, const char *msg);

void assertLessEqual_i(long long i1, long long i2, const char *msg);
void assertLessEqual_u(unsigned long long i1, unsigned long long i2, const char *msg);
void assertLessEqual_f(long double f1, long double f2, const char *msg);
void assertLessEqual_p(void *p1, void *p2, const char *msg);

void assertTrue_b(bool b, const char *msg);
void assertFalse_b(bool b, const char *msg);

test_result_t **runTests(test_t *tests, size_t numTests, void *(*before_each)(void *be_args), void *be_args, void (*after_each)(void *be_ret));
void printTests(test_result_t **results, size_t numTests);
