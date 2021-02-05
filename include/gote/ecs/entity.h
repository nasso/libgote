/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Entity data type
*/

#ifndef LIBGOTE_ECS_ENTITY_H
#define LIBGOTE_ECS_ENTITY_H

//! \file include/ecs/entity.h

#include "my/types.h"

//! \brief An entity is just an identifier (that can be used to index storages).
//! \see gt_storage_t
typedef struct gt_entity {
    u64_t id;
} gt_entity_t;

#endif /* LIBGOTE_ECS_ENTITY_H */
