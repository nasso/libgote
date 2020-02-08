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

//! \brief An abstract collection where each item is identified by a \c u64_t.
//! \see gt_vec_storage
//! \see gt_map_storage
typedef struct gt_storage {
    void (*destroy)(void *self);
    bool (*set)(void *self, u64_t id, void *data);
    void *(*get)(const void *self, u64_t id);
    void (*delete)(void *self, u64_t id);
    void *self;
} gt_storage_t;

//! \brief Create a \ref gt_storage_t that stores items in a vector.
//!
//! Items are indexed directly using their \c u64_t identifier. This is very
//! efficient when most identifiers are close to zero and leave very few to no
//! gaps between them.
//! \param destroy_item A function to be called to free items when removed.
//! \return A new \ref gt_storage_t.
gt_storage_t *gt_vec_storage(void (*destroy_item)(void *item));

//! \brief Create a \ref gt_storage_t that stores items in a map.
//!
//! Items are stored in a hash map where the keys are the identifiers and the
//! values are the items. Useful when there isn't many items with small
//! identifiers or when they are very rare.
//! \param destroy_item A function to be called to free items when removed.
//! \return A new \ref gt_storage_t.
gt_storage_t *gt_map_storage(void (*destroy_item)(void *item));

//! \brief Destroy the storage.
//! \param self The \ref gt_storage_t.
void gt_storage_destroy(gt_storage_t *self);

//! \brief Set the value of an item.
//! \param self The \ref gt_storage_t.
//! \param id The identifier of the item.
//! \param data The value of the item.
//! \return \c true in case of error, \c false otherwise.
bool gt_storage_set(gt_storage_t *self, u64_t id, void *data);

//! \brief Retrieve an item from the storage.
//! \param self The \ref gt_storage_t.
//! \param id The identifier of the item.
//! \return The value of the item; \c NULL if there isn't any.
void *gt_storage_get(const gt_storage_t *self, u64_t id);

//! \brief Destroy an item from the storage.
//! \param self The \ref gt_storage_t.
//! \param id The identifier of the item.
void gt_storage_delete(gt_storage_t *self, u64_t id);

#endif /* LIBGOTE_ECS_STORAGE_H */
