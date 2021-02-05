/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** World data type
*/

#ifndef LIBGOTE_ECS_WORLD_PRIV_H
#define LIBGOTE_ECS_WORLD_PRIV_H

#include "my/types.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/storage.h"

//! \private
typedef struct gt_resource {
    void (*destroyer)(void *self);
    void *self;
} gt_resource_t;

#endif /* LIBGOTE_ECS_WORLD_PRIV_H */
