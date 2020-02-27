/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_app_t tests
*/

#include <criterion/criterion.h>
#include "gote/gote.h"

static gt_state_t *test_state(void)
{
    gt_state_t *state = my_malloc(sizeof(gt_state_t));

    state->self = NULL;
    state->destroy = NULL;
    state->on_stop = NULL;
    state->on_pause = NULL;
    state->on_start = NULL;
    state->on_resume = NULL;
    state->shadow_update = NULL;
    state->update = NULL;
    return (state);
}

Test(app, create_and_destroy_empty)
{
    gt_app_t *app = gt_app_create(test_state(), 0);

    gt_app_destroy(app);
}
