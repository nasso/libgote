/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** System data type
*/

#ifndef LIBGOTE_ECS_SYSTEM_H
#define LIBGOTE_ECS_SYSTEM_H

#include "gote/ecs/world.h"

//! \file include/ecs/system.h
//! \typedef gt_system_t
//! \brief Systems are executed every frame to process components.
typedef struct gt_system {
    bool (*const run)(void*, gt_world_t*);
    void (*const destroy)(void*);
    void *data;
} gt_system_t;

#endif /* LIBGOTE_ECS_SYSTEM_H */
