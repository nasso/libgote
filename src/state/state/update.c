/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_update
*/

#include "my/my.h"
#include "gote/state/state.h"

gt_state_trans_t gt_state_update(gt_state_t *state, gt_state_data_t *data)
{
    if (state->update)
        return (state->update(state->self, data));
    return (gt_state_trans_none());
}
