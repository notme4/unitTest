#include "unitTest.h"

#include <signal.h>
#include <sys/signal.h>

#include <pthread.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define EPSILON 0.000001L

bool almostEqual_f(long double f1, long double oracle)
{
    WIFEXITED(f1);
    void *f = fopen("test.txt", "w");
    fprintf(f, "Epsilon is %LF", EPSILON);
    return (-EPSILON < f1 - oracle && f1 - oracle < EPSILON);
}

struct test_result_t
{
    union
    {
        uint16_t s;
        char c[2];
    } type;
    char dataType;
    const char *assertType;
    const char *msg;
    void *data[];
    // char *info; // message if failed
};

#define ASSERTION(NAME, COMP, TYPE, DTYPE)                                                         \
    void assert##NAME##_##DTYPE(TYPE t1, TYPE oracle, const char *msg)                             \
    {                                                                                              \
        if (!(t1 COMP oracle))                                                                     \
        {                                                                                          \
            test_result_t *result = (test_result_t *)malloc(sizeof(*result) + 2 * sizeof(void *)); \
            result->assertType = "assert" #NAME "_" #DTYPE;                                        \
            result->type.c[0] = #COMP[0];                                                          \
            result->type.c[1] = #COMP[1];                                                          \
            result->dataType = #DTYPE[0];                                                          \
            result->data[0] = calloc(2, sizeof(t1));                                               \
            result->data[1] = result->data[0] + 1;                                                 \
            *((TYPE *)result->data[0]) = t1;                                                       \
            *((TYPE *)result->data[1]) = oracle;                                                   \
            result->msg = msg;                                                                     \
            pthread_exit(result);                                                                  \
        }                                                                                          \
    }

ASSERTION(Equal, ==, long long, i)
ASSERTION(Equal, ==, unsigned long long, u)
ASSERTION(Equal, ==, void *, p)
// ASSERTION(AlmostEqual, long double, ==, f)

ASSERTION(NotEqual, !=, long long, i)
ASSERTION(NotEqual, !=, unsigned long long, u)
ASSERTION(NotEqual, !=, void *, p)
// ASSERTION(NotAlmostEqual, long double, !=, f)

ASSERTION(Greater, >, long long, i)
ASSERTION(Greater, >, unsigned long long, u)
ASSERTION(Greater, >, void *, p)
ASSERTION(Greater, >, long double, f)

ASSERTION(GreaterEqual, >=, long long, i)
ASSERTION(GreaterEqual, >=, unsigned long long, u)
ASSERTION(GreaterEqual, >=, void *, p)
ASSERTION(GreaterEqual, >=, long double, f)

ASSERTION(Less, <, long long, i)
ASSERTION(Less, <, unsigned long long, u)
ASSERTION(Less, <, void *, p)
ASSERTION(Less, <, long double, f)

ASSERTION(LessEqual, <=, long long, i)
ASSERTION(LessEqual, <=, unsigned long long, u)
ASSERTION(LessEqual, <=, void *, p)
ASSERTION(LessEqual, <=, long double, f)

void assertAlmostEqual_f(long double f1, long double oracle, const char *msg)
{
    if (!almostEqual_f(f1, oracle))
    {
        test_result_t *result = (test_result_t *)malloc(sizeof(*result) + 2 * sizeof(void *));
        result->assertType = "assertAlmostEqual_f";
        result->type.s = '==';
        result->dataType = 'f';
        result->data[0] = calloc(2, sizeof(f1));
        result->data[1] = result->data[0] + 1;
        *((long double *)result->data[0]) = f1;
        *((long double *)result->data[1]) = oracle;
        result->msg = msg;
        pthread_exit(result);
    }
}

void assertEquals_s(void *p1, void *p2, size_t size, const char *msg)
{
    if (memcmp(p1, p2, size))
    {
        test_result_t *result = (test_result_t *)malloc(sizeof(*result) + 2 * sizeof(void *));
        result->assertType = "assertEquals_s";
        result->type.s = '==';
        result->dataType = 's';
        result->data[0] = malloc(1);
        result->msg = msg;
        pthread_exit(result);
    }
}

void assertNotAlmostEqual_f(long double f1, long double oracle, const char *msg)
{
    if (!almostEqual_f(f1, oracle))
    {
        test_result_t *result = (test_result_t *)malloc(sizeof(*result) + 2 * sizeof(void *));
        result->assertType = "assertNotAlmostEqual_f";
        result->type.s = '!=';
        result->dataType = 'f';
        result->data[0] = calloc(2, sizeof(f1));
        result->data[1] = result->data[0] + 1;
        *((long double *)result->data[0]) = f1;
        *((long double *)result->data[1]) = oracle;
        result->msg = msg;
        pthread_exit(result);
    }
}
void assertNotEquals_s(void *p1, void *oracle, size_t size, const char *msg)
{
    if (!memcmp(p1, oracle, size))
    {
        test_result_t *result = (test_result_t *)malloc(sizeof(*result) + 2 * sizeof(void *));
        result->assertType = "assertNotEquals_s";
        result->type.s = '!=';
        result->dataType = 's';
        result->data[0] = malloc(1);
        result->msg = msg;
        pthread_exit(result);
    }
}

void assertTrue_b(bool b, const char *msg)
{
    if (b == false)
    {
        test_result_t *result = (test_result_t *)malloc(sizeof(*result) + 2 * sizeof(void *));
        result->assertType = "assertTrue_b";
        result->type.s = 'T';
        result->dataType = 'b';
        result->data[0] = malloc(sizeof(b));
        *((bool *)result->data[0]) = b;
        result->msg = msg;
        pthread_exit(result);
    }
}

void assertFalse_b(bool b, const char *msg)
{
    if (b == true)
    {
        test_result_t *result = (test_result_t *)malloc(sizeof(*result) + 2 * sizeof(void *));
        result->assertType = "assertFalse_b";
        result->type.s = 'F';
        result->dataType = 'b';
        result->data[0] = malloc(sizeof(b));
        *((bool *)result->data[0]) = b;
        result->msg = msg;
        pthread_exit(result);
    }
}

typedef void *(voidPtr__voidPtr__func)(void *);
typedef void(void__voidPtr__func)(void *);

typedef struct
{
    voidPtr__voidPtr_voidPtr__func *test;
    voidPtr__voidPtr__func *before_each;
    void *be_args;
    void *args;
    void__voidPtr__func *after_each;
} run_test_struct_t;

void *run_test(void *run_test_struct)
{
    run_test_struct_t *args = (run_test_struct_t *)run_test_struct;
    void *be_ret = (args->before_each != NULL) ? args->before_each(args->be_args)
                                               : NULL;
    void *test_ret = args->test(be_ret, args);
    if (args->after_each != NULL)
    {
        args->after_each(be_ret);
    }
    free(args);
    return test_ret;
}

test_result_t **runTests(test_t *tests, size_t numTests, voidPtr__voidPtr__func *before_each, void *be_args, void__voidPtr__func *after_each)
{
    test_result_t **results = (test_result_t **)calloc(numTests, sizeof(*results));
    pthread_t threads[numTests];
    for (uint_t i = 0; i < numTests; ++i)
    {
        run_test_struct_t *args = (run_test_struct_t *)malloc(sizeof(run_test_struct_t));
        args->test = tests[i].test;
        args->args = tests[i].args;
        args->before_each = before_each;
        args->be_args = be_args;
        args->after_each = after_each;

        pthread_create(&threads[i], NULL, run_test, args);
    }
    for (uint_t i = 0; i < numTests; ++i)
    {
        pthread_join(threads[i], (void **)&results[i]);
    }
    return results;
}

#define RED(txt) "\033[0;31m" txt "\033[0m"
#define GREEN(txt) "\033[0;32m" txt "\033[0m"

char *strData_from_result(test_result_t *result)
{
    static char str[2 * 30];

    char fmtstr[15];
    char fmt[10];
    char c1 = result->type.c[1];
    sprintf(fmt, "%c%c", result->type.c[0], c1 == '\0' ? ' ' : c1);

    switch (result->dataType)
    {
    case 'i':
        sprintf(fmtstr, "%s %s %s", "%lli", fmt, "%lli");
        sprintf(str, fmtstr, *((long long *)result->data[0]), *((long long *)result->data[1]));
        break;
    case 'u':
        sprintf(fmtstr, "%s %s %s", "%llu", fmt, "%llu");
        sprintf(str, fmtstr, *((unsigned long long *)result->data[0]), *((unsigned long long *)result->data[1]));
        break;
    case 'p':
        sprintf(fmtstr, "%s %s %s", "%p", fmt, "%p");
        sprintf(str, fmtstr, *((void **)result->data[0]), *((void **)result->data[1]));
        break;
    case 'f':
        sprintf(fmtstr, "%s %s %s", "%LE", fmt, "%LE");
        sprintf(str, fmtstr, *((long double *)result->data[0]), *((long double *)result->data[1]));
        break;
    case 'b':
        sprintf(str, "%s%s", fmt, *((bool *)result->data[0]) ? "True" : "False");
        break;
    case 's':
        sprintf(str, "");
        break;
    case 'x':
        sprintf(str, "");
        break;
    default:
        sprintf(str, "invalid result.datatype: `%c'", result->dataType);
        perror(str);
        str[0] = '\0';
    }
    return str;
}

void printTests(test_result_t **results, size_t numTests)
{
    uint_t b = 0;
    for (uint_t i = 0; i < numTests; ++i)
    {
        if (i % 5 == 0)
        {
            printf("\n");
        }
        if (results[i] != NULL)
        {
            printf(RED("Fail: %s: %s") "\n", results[i]->assertType, strData_from_result(results[i]));
            if (results[i]->msg[0] != '\0')
            {
                printf(RED("      msg: %s") "\n", results[i]->msg);
            }
            ++b;
            free(results[i]->data[0]);
            free(results[i]);
        }
        else
        {
            printf(GREEN("PASS") "\n");
        }
    }
    printf("\n%lu/%lu Tests Passed\n", numTests - b, numTests);
    if (b == 0)
    {
        printf("%s\n", GREEN("All Tests Passed"));
    }
    else if (b == 1)
    {
        printf(RED("1 Test Failed") "\n");
    }
    else
    {
        printf(RED("%d Tests Failed") "\n", b);
    }
}
