/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** World data type
*/

#ifndef LIBGOTE_ECS_WORLD_H
#define LIBGOTE_ECS_WORLD_H

//! \file include/ecs/world.h

#include "my/types.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/storage.h"

//! \brief A container for resources.
typedef struct gt_world {
    hash_map_t *resources;
} gt_world_t;

//! \brief Create a new world.
//! \return A new, empty world.
gt_world_t *gt_world_create(void);

//! \brief Destroy a world, freeing up all resources.
//! \param self The world to destroy.
void gt_world_destroy(gt_world_t *self);

//! \brief Insert a resource.
//! \param self The world.
//! \param key The resource type ID.
//! \param res The resource itself.
//! \param destroyer A function to be called when freeing the resource.
//! \return \c true in case of error, \c false otherwise.
bool gt_world_insert(gt_world_t *self, const char *key, void *data,
    void (*destroyer)(void*));

//! \brief Retrieve a resource.
//! \param self The world.
//! \param key The resource type ID.
//! \return The resource (NULL is returned if it wasn't found).
void *gt_world_get(const gt_world_t *self, const char *key);

//! \brief Remove a resource from the world.
//! \param self The world.
//! \param key The resource type ID.
void gt_world_remove(gt_world_t *self, const char *key);

//! \brief Shorthand to insert a storage resource.
//!
//! Equivalent to a call to \ref gt_world_insert with the \c destroyer argument
//! set to a function that calls \c storage->destroy approriately.
//! \note This function <strong>makes a copy of \c storage</strong>.
//! \param self The world.
//! \param type The component type.
//! \param storage The storage implementation to use.
//! \return \c true in case of error, \c false otherwise.
bool gt_world_register(gt_world_t *self, const char *type,
    const gt_storage_t *storage);

#endif /* LIBGOTE_ECS_WORLD_H */
