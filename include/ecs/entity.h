/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Entity data type
*/

#ifndef LIBGOTE_ECS_ENTITY_H
#define LIBGOTE_ECS_ENTITY_H

#include "my/types.h"

//! \file include/ecs/entity.h
//! \typedef gt_entity_t
//! \brief An entity is just an identifier that has corresponding components.
typedef struct gt_entity {
    u32_t id;
} gt_entity_t;

#endif /* LIBGOTE_ECS_ENTITY_H */
