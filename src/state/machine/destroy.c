/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_destroy
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/state/state.h"
#include "gote/state/machine.h"
#include "priv.h"

void gt_state_machine_destroy(gt_state_machine_t *self)
{
    if (self == NULL)
        return;
    LIST_FOR_EACH(self->stack, iter)
        gt_state_destroy(iter.v);
    list_destroy(self->stack);
    my_free(self);
}
