/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_app_t implementation
*/

#include <stdarg.h>
#include "my/my.h"
#include "gote/gote.h"

void gt_app_destroy(gt_app_t *self)
{
    if (self == NULL)
        return;
    gt_dispatcher_destroy(self->dispatcher);
    gt_state_machine_destroy(self->states);
    gt_world_destroy(self->world);
    my_free(self);
}
