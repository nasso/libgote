/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** System data type
*/

#ifndef LIBGOTE_ECS_SYSTEM_H
#define LIBGOTE_ECS_SYSTEM_H

//! \file include/ecs/system.h

#include "gote/ecs/world.h"

//! \brief Systems are executed every frame to process components.
typedef struct gt_system {
    void (*destroy)(void *self);
    bool (*setup)(void *self, gt_world_t *world);
    bool (*run)(void *self, gt_world_t *world);
    bool (*dispose)(void *self, gt_world_t *world);
    void *self;
} gt_system_t;

//! \brief Destroy a system, freeing up all allocated resources.
//! \param self The system to destroy.
void gt_system_destroy(gt_system_t *self);

//! \brief Setup a system; called once at initialization.
//! \param self The system.
//! \param world The \ref gt_world_t associated with the event.
//! \return \c true if an error occured, \c false otherwise.
bool gt_system_setup(gt_system_t *self, gt_world_t *world);

//! \brief Run the system; called once per frame.
//! \param self The system.
//! \param world The \ref gt_world_t associated with the event.
//! \return \c true if an error occured, \c false otherwise.
bool gt_system_run(gt_system_t *self, gt_world_t *world);

//! \brief Dispose a system; called once when the world is ending (muhahah).
//! \param self The system.
//! \param world The \ref gt_world_t associated with the event.
//! \return \c true if an error occured, \c false otherwise.
bool gt_system_dispose(gt_system_t *self, gt_world_t *world);

#endif /* LIBGOTE_ECS_SYSTEM_H */
