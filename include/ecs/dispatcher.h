/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Dispatcher
*/

#ifndef LIBGOTE_ECS_DISPATCHER_H
#define LIBGOTE_ECS_DISPATCHER_H

#include "my/types.h"
#include "my/collections/list.h"
#include "gote/ecs/world.h"

//! \file include/ecs/dispatcher.h
//! \typedef gt_dispatcher_t
//! \brief A dispatcher runs a bunch of a systems on a world.
typedef struct gt_dispatcher {
    list_t *systems;
    gt_world_t *world;
} gt_dispatcher_t;

bool gt_dispatcher(usize_t, ...);

#endif /* LIBGOTE_ECS_DISPATCHER_H */
