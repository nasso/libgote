/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Storage data type
*/

#ifndef LIBGOTE_ECS_STORAGE_H
#define LIBGOTE_ECS_STORAGE_H

//! \file include/ecs/storage.h

#include "my/types.h"

//! \brief An abstract collection of elements identified by a \c u64_t.
//!
//! Examples of storage implementations include \ref gt_vec_storage_t,
//! \ref gt_map_storage_t or \ref gt_dense_vec_storage_t.
typedef struct gt_storage {
    void (*destroy)(void *self);
    bool (*insert)(void *self, u64_t id, void *data);
    void *(*get)(void *self, u64_t id);
    void *(*remove)(void *self, u64_t id);
    void *self;
} gt_storage_t;

#endif /* LIBGOTE_ECS_STORAGE_H */
