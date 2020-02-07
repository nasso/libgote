/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Storage data type
*/

#ifndef LIBGOTE_ECS_STORAGE_H
#define LIBGOTE_ECS_STORAGE_H

#include "my/types.h"
#include "gote/ecs/entity.h"

//! \file include/ecs/storage.h
//! \typedef gt_storage_t
//! \brief A structure of function pointers for a particular type of
//! \ref gt_storage_t.
//!
//! Examples of storage type implementations include \ref gt_vec_storage_t,
//! \ref gt_map_storage_t or \ref gt_dense_vec_storage_t.
typedef struct gt_storage {
    void *data;
    void (*destroy)(void*);
    bool (*insert)(void*, gt_entity_t*, void*);
    void *(*get)(void*, gt_entity_t*);
    void *(*remove)(void*, gt_entity_t*);
} gt_storage_t;

#endif /* LIBGOTE_ECS_STORAGE_H */
