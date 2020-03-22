/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_t tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/my.h"
#include "my/io.h"
#include "gote/gote.h"

#define MAKE_SHOUTER(name) \
\
static void shout_##name(void *self, gt_world_t *world) \
{ \
    my_printf(#name " %d %zu;", *((i32_t*) self), (usize_t) world); \
}

MAKE_SHOUTER(start)
MAKE_SHOUTER(stop)
MAKE_SHOUTER(pause)
MAKE_SHOUTER(resume)
MAKE_SHOUTER(shadow)

static gt_state_trans_t shout_update(void *self, gt_world_t *world)
{
    my_printf("update %d %zu;", *((i32_t*) self), (usize_t) world);
    return (gt_state_trans_none());
}

static gt_state_trans_t shout_update_pop(void *self, gt_world_t *world)
{
    my_printf("update %d %zu;", *((i32_t*) self), (usize_t) world);
    return (gt_state_trans_pop());
}

static void shout_destroy(void *self)
{
    my_printf("destroy %d;", *((i32_t*) self));
}

static gt_state_t *loud_state(i32_t *val, bool pop)
{
    gt_state_t *self = my_malloc(sizeof(gt_state_t));

    self->self = val;
    self->on_start = &shout_start;
    self->on_stop = &shout_stop;
    self->on_pause = &shout_pause;
    self->on_resume = &shout_resume;
    self->shadow_update = &shout_shadow;
    self->update = pop ? &shout_update_pop : &shout_update;
    self->destroy = &shout_destroy;
    return (self);
}

TestSuite(state_machine, .timeout = 1.0, .init = cr_redirect_stdout);

Test(state_machine, create_and_destroy_empty)
{
    gt_state_machine_t *mach = gt_state_machine_create(NULL);

    cr_assert_not_null(mach);
    gt_state_machine_destroy(mach);
}

Test(state_machine, create_and_destroy)
{
    i32_t val = 4;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));

    cr_assert_not_null(mach);
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("destroy 4;");
}

Test(state_machine, is_running)
{
    i32_t val = 4;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));

    cr_assert_not(gt_state_machine_is_running(mach));
    gt_state_machine_destroy(mach);
}

Test(state_machine, trans_on_machine_not_running)
{
    i32_t val = 4;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));
    gt_state_trans_t trans = gt_state_trans_none();

    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    trans = gt_state_trans_pop();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    gt_state_machine_destroy(mach);
    my_putchar('\n');
    cr_assert_stdout_eq_str("destroy 4;\n");
}

Test(state_machine, start_machine)
{
    i32_t val = 4;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));

    cr_assert_not(gt_state_machine_start(mach, world));
    cr_assert(gt_state_machine_is_running(mach));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("start 4 8;destroy 4;");
}

Test(state_machine, start_already_started)
{
    i32_t val = 4;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));

    gt_state_machine_start(mach, world);
    cr_assert_not(gt_state_machine_start(mach, world));
    cr_assert(gt_state_machine_is_running(mach));
    cr_assert_not(gt_state_machine_start(mach, world));
    cr_assert(gt_state_machine_is_running(mach));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("start 4 8;destroy 4;");
}

Test(state_machine, trans_on_machine_running)
{
    i32_t val = 4;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));
    gt_state_trans_t trans = gt_state_trans_none();

    gt_state_machine_start(mach, world);
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    trans = gt_state_trans_pop();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    cr_assert_not(gt_state_machine_is_running(mach));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("start 4 8;stop 4 8;destroy 4;");
}

Test(state_machine, trans_push)
{
    i32_t val = 4;
    i32_t val2 = 2;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));
    gt_state_trans_t trans = gt_state_trans_push(loud_state(&val2, false));

    gt_state_machine_start(mach, world);
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str(
        "start 4 8;pause 4 8;start 2 8;stop 2 8;destroy 2;stop 4 8;destroy 4;"
    );
}

Test(state_machine, trans_pop)
{
    i32_t val = 4;
    i32_t val2 = 2;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));
    gt_state_trans_t trans = gt_state_trans_push(loud_state(&val2, false));

    gt_state_machine_start(mach, world);
    gt_state_machine_trans(mach, &trans, world);
    trans = gt_state_trans_pop();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str(
        "start 4 8;pause 4 8;start 2 8;stop 2 8;destroy 2;resume 4 8;stop 4 8;"
        "destroy 4;"
    );
}

Test(state_machine, trans_none)
{
    i32_t val = 4;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));
    gt_state_trans_t trans = gt_state_trans_none();

    gt_state_machine_start(mach, world);
    gt_state_machine_trans(mach, &trans, world);
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("start 4 8;stop 4 8;destroy 4;");
}

Test(state_machine, trans_switch)
{
    i32_t val = 4;
    i32_t val2 = 2;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));
    gt_state_trans_t trans = gt_state_trans_switch(loud_state(&val2, false));

    gt_state_machine_start(mach, world);
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str(
        "start 4 8;stop 4 8;destroy 4;start 2 8;stop 2 8;destroy 2;"
    );
}

Test(state_machine, update_stack)
{
    i32_t val = 4;
    i32_t val2 = 2;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, false));
    gt_state_trans_t trans = gt_state_trans_push(loud_state(&val2, false));

    cr_assert_not(gt_state_machine_update(mach, world));
    cr_assert_not(gt_state_machine_start(mach, world));
    cr_assert_not(gt_state_machine_update(mach, world));
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    cr_assert_not(gt_state_machine_update(mach, world));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, world));
    cr_assert_not(gt_state_machine_update(mach, world));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str(
        "start 4 8;update 4 8;shadow 4 8;pause 4 8;start 2 8;update 2 8;"
        "shadow 2 8;shadow 4 8;stop 2 8;destroy 2;stop 4 8;destroy 4;"
    );
}

Test(state_machine, update_trans)
{
    i32_t val = 4;
    gt_world_t *world = (gt_world_t*) 8;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val, true));

    gt_state_machine_start(mach, world);
    cr_assert_not(gt_state_machine_update(mach, world));
    cr_assert_not(gt_state_machine_is_running(mach));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str(
        "start 4 8;update 4 8;shadow 4 8;stop 4 8;destroy 4;"
    );
}
