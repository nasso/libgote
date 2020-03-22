/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_on_pause
*/

#include "my/my.h"
#include "gote/state/state.h"

void gt_state_on_pause(gt_state_t *state, gt_world_t *world)
{
    if (state->on_pause)
        state->on_pause(state->self, world);
}
