/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_destroy
*/

#include "my/my.h"
#include "gote/event/channel.h"
#include "priv.h"

void gt_event_channel_destroy(gt_event_channel_t *self)
{
    if (self == NULL)
        return;
    my_free(self->buffer);
    my_free(self->subs);
    my_free(self);
}
