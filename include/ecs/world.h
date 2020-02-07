/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** World data type
*/

#ifndef LIBGOTE_ECS_WORLD_H
#define LIBGOTE_ECS_WORLD_H

#include "my/types.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/storage.h"

//! \file include/ecs/world.h
//! \typedef gt_resource_t
//! \brief Structure holding a resource and a pointer to its destructor.
typedef struct gt_resource {
    void (*destroyer)(void*);
    void *data;
} gt_resource_t;

//! \file include/ecs/world.h
//! \typedef gt_world_t
//! \brief A container for resources.
typedef struct gt_world {
    hash_map_t *resources;
} gt_world_t;

//! \file include/ecs/world.h
//! \fn gt_world_t *gt_world_create(void);
//! \brief Create a new world.
//! \return a new, empty world
gt_world_t *gt_world_create(void);

//! \file include/ecs/world.h
//! \fn void gt_world_destroy(gt_world_t *self);
//! \brief Destroy a world, freeing up all resources.
//! \param self the world to destroy
void gt_world_destroy(gt_world_t*);

//! \file include/ecs/world.h
//! \fn bool gt_world_insert(gt_world_t *self, const char *key, void *data,
//! void (*destroyer)(void*));
//! \brief Insert a resource.
//! \param self the world
//! \param key the resource type ID
//! \param res the resource itself
//! \param destroyer a function to be called when freeing the resource
//! \return false in case of error, true otherwise
bool gt_world_insert(gt_world_t*, const char*, void*, void (*)(void*));

//! \file include/ecs/world.h
//! \fn void *gt_world_get(const gt_world_t *self, const char *key);
//! \brief Retrieve a resource.
//! \param self the world
//! \param key the resource type ID
//! \return the resource (NULL is returned if it wasn't found)
void *gt_world_get(const gt_world_t*, const char*);

//! \file include/ecs/world.h
//! \fn void gt_world_remove(gt_world_t *self, const char *key);
//! \brief Remove a resource from the world.
//! \param self the world
//! \param key the resource type ID
void gt_world_remove(gt_world_t*, const char*);

//! \file include/ecs/world.h
//! \fn bool gt_world_register(gt_world_t *self, const char *type,
//! const gt_storage_t *storage);
//! \brief Shorthand to insert a storage resource.
//!
//! Equivalent to a call to \ref gt_world_insert with the \c destroyer argument
//! set to a function that calls \c storage->destroy approriately.
//! \note this function <strong>makes a copy of \c storage</strong>.
//! \param self the world
//! \param type the component type
//! \param storage the storage implementation to use
//! \return false in case of error, true otherwise
bool gt_world_register(gt_world_t*, const char*, const gt_storage_t*);

#endif /* LIBGOTE_ECS_WORLD_H */
