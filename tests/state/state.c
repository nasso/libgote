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
MAKE_SHOUTER(shadow_update)

static gt_state_trans_t shout_update(void *self, gt_world_t *world)
{
    my_printf("update %d %zu;", *((i32_t*) self), (usize_t) world);
    return (gt_state_trans_none());
}

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
    gt_world_t *world = (gt_world_t*) 2;
    gt_state_t *state = state_that_shouts_very_loud(&val);

    gt_state_on_start(state, world);
    cr_assert_eq(gt_state_update(state, world).type, GT_STATE_TRANS_NONE);
    gt_state_shadow_update(state, world);
    gt_state_on_pause(state, world);
    gt_state_shadow_update(state, world);
    gt_state_on_resume(state, world);
    gt_state_on_stop(state, world);
    gt_state_destroy(state);
    my_putchar('\n');
    cr_assert_stdout_eq_str(
        "start 4 2;update 4 2;shadow_update 4 2;pause 4 2;shadow_update 4 2;"
        "resume 4 2;stop 4 2;destroy 4;\n"
    );
}
