/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_t tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/my.h"
#include "my/io.h"
#include "gote/gote.h"

#define MAKE_SHOUTER(name, ret_type, ret_val) \
    static ret_type shout_##name(void *self, gt_state_data_t *data) \
    { \
        my_printf(#name " %d %d;", *((i32_t*) self), *((i32_t*) data->data)); \
        return (ret_val); \
    }

MAKE_SHOUTER(start, bool, false)
MAKE_SHOUTER(stop, bool, false)
MAKE_SHOUTER(pause, bool, false)
MAKE_SHOUTER(resume, bool, false)
MAKE_SHOUTER(shadow_update, bool, false)
MAKE_SHOUTER(update, gt_state_trans_t, gt_state_trans_none())

static void shout_destroy(void *self)
{
    my_printf("destroy %d;", *((i32_t*) self));
}

static gt_state_t *state_that_shouts_very_loud(i32_t *val)
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

TestSuite(state, .timeout = 1.0, .init = cr_redirect_stdout);

Test(state, simple_lifecyle)
{
    i32_t val = 4;
    i32_t val2 = 2;
    gt_state_t *state = state_that_shouts_very_loud(&val);
    gt_state_data_t *data = gt_state_data_create(NULL, &val2);

    cr_assert_not(gt_state_on_start(state, data));
    cr_assert_eq(gt_state_update(state, data).type, GT_STATE_TRANS_NONE);
    cr_assert_not(gt_state_shadow_update(state, data));
    cr_assert_not(gt_state_on_pause(state, data));
    cr_assert_not(gt_state_shadow_update(state, data));
    cr_assert_not(gt_state_on_resume(state, data));
    cr_assert_not(gt_state_on_stop(state, data));
    gt_state_data_destroy(data);
    gt_state_destroy(state);
    my_putchar('\n');
    cr_assert_stdout_eq_str(
        "start 4 2;update 4 2;shadow_update 4 2;pause 4 2;shadow_update 4 2;"
        "resume 4 2;stop 4 2;destroy 4;\n"
    );
}
