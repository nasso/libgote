/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_t tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/my.h"
#include "my/io.h"
#include "gote/gote.h"

static void loud_i32_free(void *ptr)
{
    my_printf("FREE %d\n", *((i32_t*) ptr));
    my_free(ptr);
}

TestSuite(world, .timeout = 1.0, .init = cr_redirect_stdout);

Test(world, create_and_destroy_empty)
{
    gt_world_t *wld = gt_world_create();

    cr_assert_not_null(wld);
    gt_world_destroy(wld);
}

Test(world, destroy_null)
{
    gt_world_destroy(NULL);
}

Test(world, add_resource)
{
    i32_t value = 84;
    gt_world_t *wld = gt_world_create();

    gt_world_insert(wld, "foo", &value, NULL);
    cr_assert_eq(gt_world_get(wld, "foo"), &value);
    gt_world_destroy(wld);
}

Test(world, add_resource_with_destroyer)
{
    i32_t *value = my_malloc(sizeof(i32_t));
    gt_world_t *wld = gt_world_create();

    *value = 1;
    gt_world_insert(wld, "foo", value, &loud_i32_free);
    gt_world_destroy(wld);
    cr_assert_stdout_eq_str("FREE 1\n");
}

Test(world, remove_resource)
{
    i32_t *value = my_malloc(sizeof(i32_t));
    gt_world_t *wld = gt_world_create();

    *value = 1;
    gt_world_insert(wld, "foo", value, &loud_i32_free);
    gt_world_remove(wld, "foo");
    cr_assert_stdout_eq_str("FREE 1\n");
    gt_world_destroy(wld);
}

Test(world, get_absent_resource)
{
    gt_world_t *wld = gt_world_create();

    cr_assert_null(gt_world_get(wld, "foo"));
    gt_world_destroy(wld);
}

Test(world, remove_absent_resource)
{
    gt_world_t *wld = gt_world_create();

    gt_world_remove(wld, "foo");
    gt_world_destroy(wld);
}

Test(world, register_storage)
{
    gt_world_t *wld = gt_world_create();
    gt_storage_t dummy;

    dummy.self = my_malloc(sizeof(i32_t));
    *((i32_t*) dummy.self) = 1;
    dummy.destroy = &loud_i32_free;
    dummy.set = NULL;
    dummy.get = NULL;
    dummy.delete = NULL;
    gt_world_register(wld, "foo", &dummy);
    gt_world_destroy(wld);
    cr_assert_stdout_eq_str("FREE 1\n");
}
