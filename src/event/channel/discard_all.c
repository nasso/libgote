/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_discard_all
*/

#include "my/my.h"
#include "gote/event/channel.h"

void gt_event_channel_discard_all(gt_event_channel_t *self, u64_t handle)
{
    while (gt_event_channel_poll(self, handle, NULL)) {}
}
