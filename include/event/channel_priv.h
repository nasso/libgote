/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_t
*/

#ifndef LIBGOTE_EVENT_CHANNEL_PRIV_H
#define LIBGOTE_EVENT_CHANNEL_PRIV_H

#include "my/types.h"

//! \private
struct gt_event_channel {
    usize_t type_size;
    void *buffer;
    usize_t cursor;
    usize_t buf_size;
    opt_usize_t *subs;
    usize_t sub_count;
};

#endif /* LIBGOTE_EVENT_CHANNEL_PRIV_H */
