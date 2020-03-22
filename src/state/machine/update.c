/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_update
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/state/machine.h"
#include "priv.h"

bool gt_state_machine_update(gt_state_machine_t *self, gt_state_data_t *data)
{
    gt_state_t *top = list_get(self->stack, 0).v;
    gt_state_trans_t trans = {0};

    if (!self->running)
        return (false);
    if (top)
        trans = gt_state_update(top, data);
    LIST_FOR_EACH(self->stack, iter)
        gt_state_shadow_update(iter.v, data);
    return (gt_state_machine_trans(self, &trans, data));
}
