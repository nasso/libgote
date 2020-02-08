/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_push
*/

#include "my/my.h"
#include "gote/event/channel.h"
#include "gote/event/channel_priv.h"

//! \brief Grow the buffer making free space right after the cursor.
//! \return \c true if an error occured, \c false otherwise
static bool grow_buffer(gt_event_channel_t *self)
{
    void *data = my_calloc(self->buf_size + 1, self->type_size);
    usize_t total_size = self->type_size * self->buf_size;
    usize_t left_chunk_size = (self->cursor + 1) * self->type_size;
    usize_t right_chunk_size = total_size - left_chunk_size;
    void *right_chunk = (char*) data + left_chunk_size;
    void *right_chunk_dest = (char*) right_chunk + self->type_size;

    if (data == NULL)
        return (true);
    my_memcpy(data, self->buffer, total_size);
    my_memmove(right_chunk_dest, right_chunk, right_chunk_size);
    return (false);
}

//! \brief Check if the slot at the given index is overwritable.
//!
//! A slot is overwritable if no subscriber would receive on their next call to
//! \ref gt_event_channel_poll.
//! \return \c true if an error occured, \c false otherwise
static bool is_index_free(const gt_event_channel_t *self, usize_t id)
{
    opt_usize_t sub = NONE;

    for (usize_t i = 0; i < self->sub_count; i++) {
        sub = self->subs[i];
        if (sub.is_some && (sub.v + 1) % self->buf_size == id)
            return (false);
    }
    return (true);
}

static bool ensure_next_is_free(gt_event_channel_t *self)
{
    usize_t next = (self->cursor + 1) % self->buf_size;

    if (is_index_free(self, next))
        return (false);
    return (grow_buffer(self));
}

bool gt_event_channel_push(gt_event_channel_t *self, const void *event)
{
    if (ensure_next_is_free(self))
        return (true);
    self->cursor = (self->cursor + 1) % self->buf_size;
    my_memcpy((char*) self->buffer + self->cursor * self->type_size, event,
        self->type_size);
    return (false);
}
