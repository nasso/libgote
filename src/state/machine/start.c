/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_start
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/state/machine.h"
#include "priv.h"

bool gt_state_machine_start(gt_state_machine_t *self, gt_state_data_t *data)
{
    if (self->running)
        return (false);
    self->running = true;
    LIST_FOR_EACH(self->stack, iter)
        gt_state_on_start(iter.v, data);
    return (false);
}
