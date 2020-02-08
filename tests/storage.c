/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_vec_storage tests
*/

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/redirect.h>
#include "my/cstr.h"
#include "my/io.h"
#include "gote/gote.h"

#define STORAGE_TEST(suite, name) \
    ParameterizedTestParameters(suite, name) \
    { \
        static usize_t params[] = { 0 }; \
        return (cr_make_param_array(usize_t, params, 1)); \
    } \
    ParameterizedTest(usize_t *impl_id, suite, name)

static gt_storage_t *(*const CONSTRUCTORS[])(void (*)(void*)) = {
    &gt_vec_storage,
};

static void shout_i32_ptr(void *ptr)
{
    my_printf("%d;", *((i32_t*) ptr));
}

static char *read_line(FILE *in)
{
    char *line = NULL;
    usize_t n = 0;

    getline(&line, &n, in);
    return (line);
}

TestSuite(storage, .timeout = 1.0, .init = cr_redirect_stdout);

Test(storage, null_methods)
{
    gt_storage_t *st = my_calloc(1, sizeof(gt_storage_t));

    cr_assert_not(gt_storage_set(st, 3, NULL));
    cr_assert_null(gt_storage_get(st, 65));
    gt_storage_delete(st, 86);
    gt_storage_destroy(st);
}

STORAGE_TEST(storage, create_and_destroy_empty)
{
    gt_storage_t *st = CONSTRUCTORS[*impl_id](NULL);

    cr_assert_not_null(st);
    gt_storage_destroy(st);
}

STORAGE_TEST(storage, set_item)
{
    i32_t foo = 5;
    gt_storage_t *st = CONSTRUCTORS[*impl_id](NULL);

    cr_assert_not(gt_storage_set(st, 1, &foo));
    gt_storage_destroy(st);
}

STORAGE_TEST(storage, set_and_get_item)
{
    i32_t foo = 5;
    gt_storage_t *st = CONSTRUCTORS[*impl_id](NULL);

    cr_assert_not(gt_storage_set(st, 1, &foo));
    cr_assert_eq(gt_storage_get(st, 1), &foo);
    gt_storage_destroy(st);
}

STORAGE_TEST(storage, get_absent)
{
    gt_storage_t *st = CONSTRUCTORS[*impl_id](NULL);

    cr_assert_eq(gt_storage_get(st, 2), NULL);
    cr_assert_eq(gt_storage_get(st, 82), NULL);
    cr_assert_eq(gt_storage_get(st, 8217), NULL);
    gt_storage_destroy(st);
}

STORAGE_TEST(storage, destroy_item)
{
    FILE *out = cr_get_redirected_stdout();
    char *line = NULL;
    i32_t foo[3] = { 6, 2, 1 };
    gt_storage_t *st = CONSTRUCTORS[*impl_id](shout_i32_ptr);

    gt_storage_set(st, 5, &foo[0]);
    gt_storage_set(st, 2, &foo[1]);
    gt_storage_set(st, 9, &foo[2]);
    my_printf("a;");
    gt_storage_delete(st, 2);
    my_printf("b;");
    gt_storage_destroy(st);
    my_printf("c;\n");
    line = read_line(out);
    cr_assert(
        !my_cstrcmp(line, "a;2;b;1;6;c;\n") ||
        !my_cstrcmp(line, "a;2;b;6;1;c;\n")
    );
    my_free(line);
}

STORAGE_TEST(storage, destroy_absent)
{
    gt_storage_t *st = CONSTRUCTORS[*impl_id](NULL);

    gt_storage_delete(st, 2);
    gt_storage_delete(st, 82);
    gt_storage_delete(st, 8217);
    gt_storage_destroy(st);
}

STORAGE_TEST(storage, overwrite_item)
{
    i32_t foo[3] = { 6, 2, 1 };
    gt_storage_t *st = CONSTRUCTORS[*impl_id](shout_i32_ptr);

    gt_storage_set(st, 5, &foo[0]);
    gt_storage_set(st, 2, &foo[1]);
    gt_storage_set(st, 2, &foo[2]);
    my_printf("\n");
    cr_assert_stdout_eq_str("2;\n");
}

STORAGE_TEST(storage, lots_of_items)
{
    i32_t foo[256] = {0};
    gt_storage_t *st = CONSTRUCTORS[*impl_id](shout_i32_ptr);

    for (usize_t i = 0; i < 256; i++) {
        foo[i] = i;
        cr_assert_not(gt_storage_set(st, i, &foo[i]));
    }
    for (usize_t i = 0; i < 256; i++)
        cr_assert_eq(gt_storage_get(st, i), &foo[i]);
}
