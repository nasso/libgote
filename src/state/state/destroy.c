/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_destroy
*/

#include "my/my.h"
#include "gote/state/state.h"

void gt_state_destroy(gt_state_t *state)
{
    if (state->destroy)
        state->destroy(state->self);
    my_free(state);
}
