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
#include "gote/state/machine_priv.h"

static int destroy_stack_callback(void *user_data, void *element)
{
    (void)(user_data);
    gt_state_destroy(element);
    return (0);
}

void gt_state_machine_destroy(gt_state_machine_t *self)
{
    if (self != NULL)
        list_destroy_with(self->stack, &destroy_stack_callback, NULL);
    my_free(self);
}
