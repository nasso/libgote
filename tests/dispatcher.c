/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_dispatcher_t tests
*/

#include <criterion/criterion.h>
#include "gote/gote.h"

static bool dummy_system_setup(void *self, gt_world_t *world)
{
    u32_t *counter = NULL;

    (void)(self);
    counter = gt_world_get(world, "counter");
    if (counter == NULL) {
        counter = my_malloc(sizeof(u32_t));
        *counter = 0;
        gt_world_insert(world, "counter", counter, &my_free);
    }
    return (false);
}

static bool dummy_system_run(void *self, gt_world_t *world)
{
    u32_t *counter = gt_world_get(world, "counter");

    (void)(self);
    *counter += 2;
    return (false);
}

static bool dummy_system_dispose(void *self, gt_world_t *world)
{
    (void)(self);
    gt_world_remove(world, "counter");
    return (false);
}

static gt_system_t *dummy_system(void)
{
    gt_system_t *self = my_calloc(1, sizeof(gt_system_t));

    self->setup = &dummy_system_setup;
    self->run = &dummy_system_run;
    self->dispose = &dummy_system_dispose;
    return (self);
}

Test(dispatcher, create_and_destroy_empty, .timeout = 1.0)
{
    gt_dispatcher_t *dp = gt_dispatcher_create(0);

    cr_assert_not_null(dp);
    gt_dispatcher_destroy(dp);
}

Test(dispatcher, create_and_destroy_not_empty, .timeout = 1.0)
{
    gt_dispatcher_t *dp = gt_dispatcher_create(1, dummy_system());

    cr_assert_not_null(dp);
    gt_dispatcher_destroy(dp);
}

Test(dispatcher, common_system_lifecycle, .timeout = 1.0)
{
    gt_world_t *wld = gt_world_create();
    gt_dispatcher_t *dp = gt_dispatcher_create(1, dummy_system());

    cr_assert_null(gt_world_get(wld, "counter"));
    gt_dispatcher_setup(dp, wld);
    cr_assert_eq(*((u32_t*) gt_world_get(wld, "counter")), 0);
    gt_dispatcher_run(dp, wld);
    cr_assert_eq(*((u32_t*) gt_world_get(wld, "counter")), 2);
    gt_dispatcher_run(dp, wld);
    cr_assert_eq(*((u32_t*) gt_world_get(wld, "counter")), 4);
    gt_dispatcher_dispose(dp, wld);
    cr_assert_null(gt_world_get(wld, "counter"));
    gt_dispatcher_destroy(dp);
    gt_world_destroy(wld);
}

Test(dispatcher, complex_system_lifecycle, .timeout = 1.0)
{
    gt_world_t *wld = gt_world_create();
    gt_dispatcher_t *dp = gt_dispatcher_create(2, dummy_system(),
        dummy_system());

    cr_assert_null(gt_world_get(wld, "counter"));
    gt_dispatcher_setup(dp, wld);
    cr_assert_eq(*((u32_t*) gt_world_get(wld, "counter")), 0);
    gt_dispatcher_run(dp, wld);
    cr_assert_eq(*((u32_t*) gt_world_get(wld, "counter")), 4);
    gt_dispatcher_run(dp, wld);
    cr_assert_eq(*((u32_t*) gt_world_get(wld, "counter")), 8);
    gt_dispatcher_dispose(dp, wld);
    cr_assert_null(gt_world_get(wld, "counter"));
    gt_dispatcher_destroy(dp);
    gt_world_destroy(wld);
}
