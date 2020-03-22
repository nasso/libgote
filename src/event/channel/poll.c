/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_poll
*/

#include "my/my.h"
#include "my/io.h"
#include "gote/event/channel.h"
#include "priv.h"

bool gt_event_channel_poll(gt_event_channel_t *self, u64_t handle, void *event)
{
    OPT(usize) sub = NONE(usize);
    usize_t offset = 0;

    if (handle == 0 || handle > self->sub_count)
        return (false);
    sub = self->subs[handle - 1];
    if (sub.is_some && sub.v != self->cursor) {
        sub.v = (sub.v + 1) % self->buf_size;
        if (event) {
            offset = sub.v * self->type_size;
            my_memcpy(event, (char*) self->buffer + offset, self->type_size);
        }
        self->subs[handle - 1] = sub;
        return (true);
    }
    return (false);
}
