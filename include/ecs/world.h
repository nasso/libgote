/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** World data type
*/

#ifndef LIBGOTE_ECS_WORLD_H
#define LIBGOTE_ECS_WORLD_H

//! \file include/ecs/world.h

#include <stdarg.h>
#include "my/types.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/storage.h"
#include "gote/ecs/entity.h"
#include "gote/ecs/component.h"

//! \brief A container for resources.
typedef struct gt_world {
    hash_map_t *resources;
    list_t *entities;
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
//! \param self The world.
//! \param type The component type.
//! \param storage The storage to use.
//! \return \c true in case of error, \c false otherwise.
bool gt_world_register(gt_world_t *self, const char *key,
    gt_storage_t *storage);

//! \brief Shorthand to insert a storage resource for a component class.
//!
//! The storage is created by calling the given constructor. It takes one
//! argument which is the destructor (called to destroy components when they are
//! removed).
//! Equivalent to the following:
//! ```c
//! gt_world_register(self, class->name, storage_ctor(class->destroyer));
//! ```
//! \param self The world.
//! \param class The \ref gt_component_class_t to create the storage for.
//! \param storage_ctor The constructor of the storage.
bool gt_world_register_component(gt_world_t *self,
    const gt_component_class_t *class,
    gt_storage_t *(*storage_ctor)(void (*)(void*)));

//! \brief Create a new entity in this world.
//!
//! If any of the given component instance is a NULL pointer, all the components
//! are destroyed.
//! The variadic arguments must be a list of \c const \ref gt_component_class_t*
//! and \c void* pairs. The \c gt_component_class_t is needed to know which
//! storage to use and how to destroy entities.
//! ```c
//! static const gt_component_class_t HEALTH_COMPONENT = { ... };
//! static const gt_component_class_t POS_COMPONENT = { ... };
//!
//! // ...
//!
//! gt_entity_t *entity = gt_world_create_entity(
//!     world,
//!     2,
//!     &HEALTH_COMPONENT, create_health_component(4.0),
//!     &POS_COMPONENT, create_pos_component(1.0, 3.0)
//! );
//!
//! if (entity == NULL)
//!     my_printf("Couldn't create the entity!");
//! ```
//! \param self The world.
//! \param component_count How many components are described in the varargs.
//! \param ... The components to be attached to the new entity.
//! \return The newly created entity; \c NULL if an error occured.
gt_entity_t *gt_world_create_entity(gt_world_t *self, usize_t component_count,
    ...);

//! \brief \c va_list version of \ref gt_world_create_entity.
//! \param self The world.
//! \param component_count How many components are described in the varargs.
//! \param ... The components to be attached to the new entity.
//! \return The newly created entity; \c NULL if an error occured.
gt_entity_t *gt_world_create_entity_va(gt_world_t *self,
    usize_t component_count, va_list ap);

#endif /* LIBGOTE_ECS_WORLD_H */
