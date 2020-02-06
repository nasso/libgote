/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** ECS data structure definitions
*/

#ifndef LIBGOTE_ECS_H
#define LIBGOTE_ECS_H

#include "my/types.h"

typedef struct gt_world gt_world_t;
typedef struct gt_entity gt_entity_t;
typedef struct gt_component gt_component_t;
typedef struct gt_system gt_system_t;

typedef struct gt_storage_impl {
    void *(*create)(void (*destroyer)(void*));
    void (*destroy)(void*);
    bool (*set)(void*, gt_entity_t*, void*);
    void *(*get)(void*, gt_entity_t*);
    void *(*del)(void*, gt_entity_t*);
    void (*clear)(void*);
} gt_storage_impl_t;

typedef struct gt_storage {
    const gt_storage_impl_t *impl;
    void *data;
} gt_storage_t;

//! \fn gt_world_t *gt_world_create(void);
//! \brief create a new world
//! \return a new, empty world
gt_world_t *gt_world_create(void);

//! \fn void gt_world_destroy(gt_world_t *self);
//! \brief destroy a world, freeing up all resources
//! \param self the world to destroy
void gt_world_destroy(gt_world_t*);

//! \fn bool gt_world_insert(gt_world_t *self, const char *key, void *res);
//! \brief insert a resource
//! \param self the world
//! \param key the resource type ID
//! \param res the resource itself
//! \return false in case of error, true otherwise
bool gt_world_insert(gt_world_t*, const char*, void*);

//! \fn void *gt_world_get(gt_world_t *self, const char *key);
//! \brief retrieve a resource
//! \param self the world
//! \param key the resource type ID
//! \return the resource (NULL is returned if it wasn't found)
void *gt_world_get(const gt_world_t*, const char*);

//! \fn void *gt_world_remove(gt_world_t *self, const char *key);
//! \brief remove a resource from the world
//! \param self the world
//! \param key the resource type ID
//! \return the resource (NULL is returned if it wasn't found)
void *gt_world_remove(gt_world_t*, const char*);

//! \fn bool gt_world_register(gt_world_t *self, const char *type,
//! gt_storage_impl_t *impl);
//! \brief register a component type with the specified storage
//! \param self the world
//! \param type the component type
//! \param impl the storage implementation to use
//! \return false in case of error, true otherwise
bool gt_world_register(gt_world_t*, const char*, gt_storage_impl_t*);

//! \fn bool gt_world_unregister(gt_world_t *self, const char *type);
//! \brief remove a component storage
//! \param self the world
//! \param type the component type
void gt_world_unregister(gt_world_t*, const char*);

#endif /* LIBGOTE_ECS_H */
