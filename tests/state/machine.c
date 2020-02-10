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
    static void shout_##name(void *self, gt_state_data_t *data) \
    { \
        my_printf(#name " %d %d;", *((i32_t*) self), *((i32_t*) data->data)); \
    }

MAKE_SHOUTER(start)
MAKE_SHOUTER(stop)
MAKE_SHOUTER(pause)
MAKE_SHOUTER(resume)
MAKE_SHOUTER(shadow_update)

static gt_state_trans_t shout_update(void *self, gt_state_data_t *data)
{
    my_printf("update %d %d;", *((i32_t*) self), *((i32_t*) data->data));
    return (gt_state_trans_none());
}

static void shout_destroy(void *self)
{
    my_printf("destroy %d;", *((i32_t*) self));
}

static gt_state_t *loud_state(i32_t *val)
{
    gt_state_t *self = my_malloc(sizeof(gt_state_t));

    self->self = val;
    self->on_start = &shout_start;
    self->on_stop = &shout_stop;
    self->on_pause = &shout_pause;
    self->on_resume = &shout_resume;
    self->shadow_update = &shout_shadow_update;
    self->update = &shout_update;
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
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));

    cr_assert_not_null(mach);
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("destroy 4;");
}

Test(state_machine, is_running)
{
    i32_t val = 4;
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));

    cr_assert_not(gt_state_machine_is_running(mach));
    gt_state_machine_destroy(mach);
}

Test(state_machine, trans_on_machine_not_running)
{
    i32_t data_val = 2;
    i32_t val = 4;
    gt_state_data_t *data = gt_state_data_create(NULL, &data_val);
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));
    gt_state_trans_t trans = gt_state_trans_none();

    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    trans = gt_state_trans_pop();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    gt_state_machine_destroy(mach);
    my_putchar('\n');
    cr_assert_stdout_eq_str("destroy 4;\n");
}

Test(state_machine, start_machine)
{
    i32_t data_val = 8;
    i32_t val = 4;
    gt_state_data_t *data = gt_state_data_create(NULL, &data_val);
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));

    cr_assert_not(gt_state_machine_start(mach, data));
    cr_assert(gt_state_machine_is_running(mach));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("start 4 8;destroy 4;");
}

Test(state_machine, start_already_started)
{
    i32_t data_val = 8;
    i32_t val = 4;
    gt_state_data_t *data = gt_state_data_create(NULL, &data_val);
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));

    gt_state_machine_start(mach, data);
    cr_assert_not(gt_state_machine_start(mach, data));
    cr_assert(gt_state_machine_is_running(mach));
    cr_assert_not(gt_state_machine_start(mach, data));
    cr_assert(gt_state_machine_is_running(mach));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("start 4 8;destroy 4;");
}

Test(state_machine, trans_on_machine_running)
{
    i32_t data_val = 8;
    i32_t val = 4;
    gt_state_data_t *data = gt_state_data_create(NULL, &data_val);
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));
    gt_state_trans_t trans = gt_state_trans_none();

    gt_state_machine_start(mach, data);
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    trans = gt_state_trans_pop();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    cr_assert_not(gt_state_machine_is_running(mach));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("start 4 8;stop 4 8;destroy 4;");
}

Test(state_machine, trans_push)
{
    i32_t data_val = 8;
    i32_t val = 4;
    i32_t val2 = 2;
    gt_state_data_t *data = gt_state_data_create(NULL, &data_val);
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));
    gt_state_trans_t trans = gt_state_trans_push(loud_state(&val2));

    gt_state_machine_start(mach, data);
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str(
        "start 4 8;pause 4 8;start 2 8;stop 2 8;destroy 2;stop 4 8;destroy 4;"
    );
}

Test(state_machine, trans_pop)
{
    i32_t data_val = 8;
    i32_t val = 4;
    i32_t val2 = 2;
    gt_state_data_t *data = gt_state_data_create(NULL, &data_val);
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));
    gt_state_trans_t trans = gt_state_trans_push(loud_state(&val2));

    gt_state_machine_start(mach, data);
    gt_state_machine_trans(mach, &trans, data);
    trans = gt_state_trans_pop();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str(
        "start 4 8;pause 4 8;start 2 8;stop 2 8;destroy 2;resume 4 8;stop 4 8;"
        "destroy 4;"
    );
}

Test(state_machine, trans_none)
{
    i32_t data_val = 8;
    i32_t val = 4;
    gt_state_data_t *data = gt_state_data_create(NULL, &data_val);
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));
    gt_state_trans_t trans = gt_state_trans_none();

    gt_state_machine_start(mach, data);
    gt_state_machine_trans(mach, &trans, data);
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str("start 4 8;stop 4 8;destroy 4;");
}

Test(state_machine, trans_switch)
{
    i32_t data_val = 8;
    i32_t val = 4;
    i32_t val2 = 2;
    gt_state_data_t *data = gt_state_data_create(NULL, &data_val);
    gt_state_machine_t *mach = gt_state_machine_create(loud_state(&val));
    gt_state_trans_t trans = gt_state_trans_switch(loud_state(&val2));

    gt_state_machine_start(mach, data);
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    trans = gt_state_trans_quit();
    cr_assert_not(gt_state_machine_trans(mach, &trans, data));
    gt_state_machine_destroy(mach);
    cr_assert_stdout_eq_str(
        "start 4 8;stop 4 8;destroy 4;start 2 8;stop 2 8;destroy 2;"
    );
}
