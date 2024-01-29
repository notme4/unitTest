#include "unitTest.h"
#include <stdio.h>
#include <signal.h>

void *test__pass_assertTrue(void *, void *)
{
    assertTrue_b(true, "should pass");
    return 0;
}

void *test__fail_assertTrue(void *, void *)
{
    assertTrue_b(false, "");
    return 0;
}

void *test__pass_assertFalse(void *, void *)
{
    assertFalse_b(false, "should pass");
    return 0;
}

void *test__fail_assertFalse(void *, void *)
{
    assertFalse_b(true, "");
    return 0;
}

void *test__pass_assertSegFault(void *, void *)
{
    assertSegFault_x(
        ^{
          raise(SIGSEGV);
        },
        "should pass");
    return 0;
}

void *test__fail_assertSegFault(void *, void *)
{
    assertSegFault_x(
        ^{
          // raise(SIGSEGV);
          return;
        },
        "");
    return 0;
}

void *test__pass_assertAlmostEqual_f(void *, void *)
{
    assertAlmostEqual_f(0.L, 0.L, "should pass");
    return 0;
}

void *test__fail_assertAlmostEqual_f(void *, void *)
{
    assertAlmostEqual_f(0.L, 1.L, "");
    return 0;
}

void *test__pass_assertEqual_i(void *, void *)
{
    assertEqual_i(1, 1, "should pass");
    return 0;
}

void *test__fail_assertEqual_i(void *, void *)
{
    assertEqual_i(0, 1, "");
    return 0;
}

void *test__pass_assertEqual_u(void *, void *)
{
    assertEqual_u(1, 1, "should pass");
    return 0;
}

void *test__fail_assertEqual_u(void *, void *)
{
    assertEqual_u(0, 1, "");
    return 0;
}

void *test__unitTest(void *, void *)
{
    test_t tests[] =
        {
            {.test = test__pass_assertTrue, .args = NULL},
            {.test = test__fail_assertTrue, .args = NULL},
            {.test = test__pass_assertFalse, .args = NULL},
            {.test = test__fail_assertFalse, .args = NULL},
            {.test = test__pass_assertSegFault, .args = NULL},

            {.test = test__fail_assertSegFault, .args = NULL},
            {.test = test__pass_assertAlmostEqual_f, .args = NULL},
            {.test = test__fail_assertAlmostEqual_f, .args = NULL},
            {.test = test__pass_assertEqual_i, .args = NULL},
            {.test = test__fail_assertEqual_i, .args = NULL},

            {.test = test__pass_assertEqual_u, .args = NULL},
            {.test = test__fail_assertEqual_u, .args = NULL},
        };

    bool oracle[] = {
        1,
        0,
        1,
        0,
        1,

        0,
        1,
        0,
        1,
        0,

        1,
        0,
    };

    size_t numTests = sizeof(tests) / sizeof(tests[0]);
    void *results = runTests(tests, numTests, NULL, NULL, NULL);
    printTests(results, numTests);

    printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

    assertEqual_u(sizeof(oracle) / sizeof(oracle[0]), numTests, "size of testOracles != numTests");
    assertLess_u(numTests, 100, "too many tests for buffer, increase it");
    for (uint_t i = 0; i < numTests; ++i)
    {
        static char msg[27];

        if (oracle[i] == 1)
        {
            sprintf(msg, "test %d should have passed", i);
            assertEqual_p(((void **)results)[i], NULL, msg);
        }
        else if (oracle[i] == 0)
        {
            sprintf(msg, "test %d should have failed", i);
            assertNotEqual_p(((void **)results)[i], NULL, msg);
        }
    }
    return 0;
}

int main()
{
    test_t tests[] =
        {
            {.test = test__unitTest, .args = NULL},
        };
    size_t numTests = sizeof(tests) / sizeof(tests[0]);
    void *results = runTests(tests, numTests, NULL, NULL, NULL);
    printTests(results, numTests);
}
