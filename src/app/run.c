/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_app_t implementation
*/

#include "my/my.h"
#include "gote/gote.h"

bool gt_app_run(gt_app_t *self)
{
    bool err = false;
    gt_state_data_t state_data = {
        .data = self->data,
        .world = self->world,
    };

    err = gt_state_machine_start(self->states, &state_data);
    err = err || gt_dispatcher_setup(self->data->dispatcher, self->world);
    while (!err && gt_state_machine_is_running(self->states)) {
        err = gt_state_machine_update(self->states, &state_data);
        err = err || gt_dispatcher_run(self->data->dispatcher, self->world);
    }
    err |= gt_dispatcher_dispose(self->data->dispatcher, self->world);
    return (err);
}
