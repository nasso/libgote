/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_shadow_update
*/

#include "my/my.h"
#include "gote/state/state.h"

void gt_state_shadow_update(gt_state_t *state, gt_world_t *world)
{
    if (state->shadow_update)
        state->shadow_update(state->self, world);
}
