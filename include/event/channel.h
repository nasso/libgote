/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_t
*/

#ifndef LIBGOTE_EVENT_CHANNEL_H
#define LIBGOTE_EVENT_CHANNEL_H

//! \file include/event/channel.h

#include "my/types.h"

typedef struct gt_event_channel gt_event_channel_t;

//! \brief Create a new event channel.
//! \param event_type_size The size of the event type of this channel.
//! \return A new instance of \ref gt_event_channel_t.
gt_event_channel_t *gt_event_channel_create(usize_t event_type_size);

//! \brief Destroy an event channel.
//! \param self The event channel to destroy.
void gt_event_channel_destroy(gt_event_channel_t *self);

//! \brief Subscribe to an event channel.
//! \param self The event channel to subscribe to.
//! \return A new channel subscribtion handle, \c 0 on failure.
u64_t gt_event_channel_sub(gt_event_channel_t *self);

//! \brief Unsubscribe from an event channel.
//! \param self The event channel.
//! \param handle The channel subscribtion handle.
void gt_event_channel_unsub(gt_event_channel_t *self, u64_t handle);

//! \brief Poll an event from an event channel.
//!
//! All subscribers MUST absolutely call this method, even if they don't care
//! about the events, otherwise the event channel's internal buffer will keep
//! growing! Consider unsubscribing from the channel with
//! \ref gt_event_channel_unsub or calling \ref gt_event_channel_discard_all if
//! you don't care about the events in the channel.
//! \param self The event channel.
//! \param handle The channel subscribtion handle.
//! \param event A pointer to a memory zone on which to copy the event data.
//! \return \c true if an event was read, \c false if there isn't any new event.
bool gt_event_channel_poll(gt_event_channel_t *self, u64_t handle, void *event);

//! \brief Discard all events from the channel.
//!
//! Calling this method has the same effect as calling
//! \ref gt_event_channel_poll until it returns false.
//! \param self The event channel.
//! \param handle The channel subscribtion handle.
void gt_event_channel_discard_all(gt_event_channel_t *self, u64_t handle);

//! \brief Push an event to the channel.
//! \param self The event channel.
//! \param event A pointer from which to copy the event data.
//! \return \c true in case of error, \c false otherwise.
bool gt_event_channel_push(gt_event_channel_t *self, const void *event);

#endif /* LIBGOTE_EVENT_CHANNEL_H */
