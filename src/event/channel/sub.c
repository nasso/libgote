/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_sub
*/

#include "my/my.h"
#include "gote/event/channel.h"
#include "gote/event/channel_priv.h"

static bool grow_subs(gt_event_channel_t *self)
{
    opt_usize_t *subs = my_calloc(self->sub_count + 1, sizeof(opt_usize_t));

    if (subs == NULL)
        return (true);
    else if (self->subs) {
        my_memcpy(subs, self->subs, sizeof(opt_usize_t) * self->sub_count);
        my_free(self->subs);
    }
    self->sub_count++;
    self->subs = subs;
    return (false);
}

static u64_t make_handle(gt_event_channel_t *self)
{
    for (usize_t i = 0; i < self->sub_count; i++)
        if (!self->subs[i].is_some)
            return (i + 1);
    if (grow_subs(self))
        return (0);
    return (self->sub_count);
}

u64_t gt_event_channel_sub(gt_event_channel_t *self)
{
    u64_t handle = make_handle(self);

    if (handle != 0)
        self->subs[handle - 1] = (opt_usize_t) SOME(self->cursor);
    return (handle);
}
