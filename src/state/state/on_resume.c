/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_on_resume
*/

#include "my/my.h"
#include "gote/state/state.h"

bool gt_state_on_resume(gt_state_t *state, gt_state_data_t *data)
{
    if (state->on_resume)
        return (state->on_resume(state->self, data));
    return (false);
}
