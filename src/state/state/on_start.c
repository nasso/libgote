/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_on_start
*/

#include "my/my.h"
#include "gote/state/state.h"

bool gt_state_on_start(gt_state_t *state, gt_state_data_t *data)
{
    if (state->on_start)
        return (state->on_start(state->self, data));
    return (false);
}
