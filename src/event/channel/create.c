/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_create
*/

#include "my/my.h"
#include "gote/event/channel.h"
#include "gote/event/channel_priv.h"

static const usize_t INITIAL_SIZE = 4;

gt_event_channel_t *gt_event_channel_create(usize_t event_type_size)
{
    gt_event_channel_t *self = my_calloc(1, sizeof(gt_event_channel_t));

    if (self == NULL)
        return (NULL);
    self->type_size = event_type_size;
    self->buf_size = INITIAL_SIZE;
    self->buffer = my_calloc(self->buf_size, self->type_size);
    if (self->buffer == NULL) {
        my_free(self);
        return (NULL);
    }
    return (self);
}
