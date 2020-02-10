/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_on_stop
*/

#include "my/my.h"
#include "gote/state/state.h"

void gt_state_on_stop(gt_state_t *state, gt_state_data_t *data)
{
    if (state->on_stop)
        state->on_stop(state->self, data);
}
