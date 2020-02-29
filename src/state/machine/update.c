/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_update
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/state/machine.h"
#include "gote/state/machine_priv.h"

static int shadow_update_callback(void *user_data, void *element)
{
    gt_state_data_t *data = user_data;
    gt_state_t *state = element;

    gt_state_shadow_update(state, data);
    return (0);
}

bool gt_state_machine_update(gt_state_machine_t *self, gt_state_data_t *data)
{
    gt_state_t *top = list_get(self->stack, 0);
    gt_state_trans_t trans = {0};

    if (!self->running)
        return (false);
    if (top)
        trans = gt_state_update(top, data);
    list_for_each(self->stack, &shadow_update_callback, data);
    return (gt_state_machine_trans(self, &trans, data));
}
