/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** System data type
*/

#ifndef LIBGOTE_ECS_SYSTEM_H
#define LIBGOTE_ECS_SYSTEM_H

//! \file include/ecs/system.h

#include "gote/ecs/world.h"

//! \brief Systems are executed every frame to process components.
typedef struct gt_system {
    bool (*setup)(void *self, gt_world_t *world);
    bool (*run)(void *self, gt_world_t *world);
    bool (*dispose)(void *self, gt_world_t *world);
    void (*destroy)(void *self);
    void *self;
} gt_system_t;

#endif /* LIBGOTE_ECS_SYSTEM_H */
