/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_app_create and gt_app_create_var
*/

#include <stdarg.h>
#include "my/my.h"
#include "gote/gote.h"

static bool setup_world(gt_app_t *self)
{
    gt_event_channel_t *trans_chan =
        gt_event_channel_create(sizeof(gt_state_trans_t));
    bool err = trans_chan == NULL;

    err = err || gt_world_insert(self->world, "trans_channel", trans_chan,
        (void (*)(void*)) &gt_event_channel_destroy);
    err = err || gt_world_insert(self->world, "time_ms", &self->time_ms, NULL);
    err = err || gt_world_insert(self->world, "dt_ms", &self->dt_ms, NULL);
    if (!err) {
        self->priv.trans_chan_sub = gt_event_channel_sub(trans_chan);
        err |= self->priv.trans_chan_sub == 0;
    }
    return (err);
}

gt_app_t *gt_app_create(gt_state_t *initial_state, usize_t system_count, ...)
{
    gt_app_t *app = NULL;
    va_list ap;

    va_start(ap, system_count);
    app = gt_app_create_var(initial_state, system_count, ap);
    va_end(ap);
    return (app);
}

gt_app_t *gt_app_create_var(gt_state_t *initial_state, usize_t system_count,
    va_list ap)
{
    gt_app_t *app = my_calloc(1, sizeof(gt_app_t));

    if (app == NULL)
        return (NULL);
    app->world = gt_world_create();
    app->states = gt_state_machine_create(initial_state);
    app->data = gt_game_data_with_var(system_count, ap);
    if (app->world == NULL || app->states == NULL || app->data == NULL ||
        setup_world(app)) {
        gt_app_destroy(app);
        return (NULL);
    }
    return (app);
}
