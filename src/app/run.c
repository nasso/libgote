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
    gt_event_channel_t *trans_chan = gt_world_get(self->world, "trans_channel");
    gt_state_trans_t trans;
    gt_state_data_t state_data = {
        .data = self->data,
        .world = self->world,
    };

    err = err || gt_dispatcher_setup(self->data->dispatcher, self->world);
    err = err || gt_state_machine_start(self->states, &state_data);
    while (!err && gt_state_machine_is_running(self->states)) {
        err = err || gt_state_machine_update(self->states, &state_data);
        err = err || gt_dispatcher_run(self->data->dispatcher, self->world);
        while (!err && gt_event_channel_poll(trans_chan,
            self->priv.trans_chan_sub, &trans))
            err = gt_state_machine_trans(self->states, &trans, &state_data);
    }
    err = err || gt_dispatcher_dispose(self->data->dispatcher, self->world);
    return (err);
}
