/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_create
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/state/state.h"
#include "gote/state/machine.h"
#include "gote/state/machine_priv.h"

gt_state_machine_t *gt_state_machine_create(gt_state_t *initial_state)
{
    gt_state_machine_t *self = my_calloc(1, sizeof(gt_state_machine_t));

    if (self == NULL)
        return (NULL);
    self->stack = list_from(initial_state ? 1 : 0, initial_state);
    if (self->stack == NULL) {
        my_free(self);
        return (NULL);
    }
    return (self);
}
