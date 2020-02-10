/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_is_running
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/state/machine.h"
#include "gote/state/machine_priv.h"

bool gt_state_machine_is_running(gt_state_machine_t *self)
{
    return (self->running);
}
