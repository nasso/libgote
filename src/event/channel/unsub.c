/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_unsub
*/

#include "my/my.h"
#include "gote/event/channel.h"
#include "gote/event/channel_priv.h"

void gt_event_channel_unsub(gt_event_channel_t *self, u64_t handle)
{
    if (handle == 0 || handle > self->sub_count)
        return;
    self->subs[handle - 1] = (opt_usize_t) NONE;
}
