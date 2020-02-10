/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_start
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/state/machine.h"
#include "gote/state/machine_priv.h"

static int start_state_callback(void *user_data, void *element)
{
    gt_state_on_start(element, user_data);
    return (0);
}

bool gt_state_machine_start(gt_state_machine_t *self, gt_state_data_t *data)
{
    if (self->running)
        return (false);
    self->running = true;
    list_for_each(self->stack, &start_state_callback, data);
    return (false);
}
