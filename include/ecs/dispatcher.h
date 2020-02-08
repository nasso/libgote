/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Dispatcher
*/

#ifndef LIBGOTE_ECS_DISPATCHER_H
#define LIBGOTE_ECS_DISPATCHER_H

//! \file include/ecs/dispatcher.h

#include <stdarg.h>
#include "my/types.h"
#include "my/collections/list.h"
#include "gote/ecs/world.h"

//! \brief Helper object to run a list of \ref gt_system_t on a \ref gt_world_t.
typedef struct gt_dispatcher {
    list_t *systems;
} gt_dispatcher_t;

//! \brief Create a new \ref gt_dispatcher_t with the given systems.
//! \param n How many systems the variadic argument list contains.
//! \param ... \c n pointers to \ref gt_system_t to be added to the dispatcher.
//! \return A new instance of \ref gt_dispatcher_t.
//! \see gt_dispatcher_create_v
gt_dispatcher_t *gt_dispatcher_create(usize_t n, ...);

//! \brief Same as \ref gt_dispatcher_create but taking a \c va_list directly.
//! \param n How many systems the variadic argument list contains.
//! \param ap A \c va_list of \c n pointers to \ref gt_system_t to be added to
//! the dispatcher.
//! \return A new instance of \ref gt_dispatcher_t.
//! \see gt_dispatcher_create_v
gt_dispatcher_t *gt_dispatcher_create_v(usize_t n, va_list ap);

//! \brief Destroy a \ref gt_dispatcher_t.
//! \param self The \ref gt_dispatcher_t instance to destroy.
void gt_dispatcher_destroy(gt_dispatcher_t *self);

//! \brief Call \c setup with the given \ref gt_world_t on all the systems.
//! \param self The \ref gt_dispatcher_t.
//! \param world The \ref gt_world_t.
//! \return \c true if any error occured when calling the systems, or \c false.
bool gt_dispatcher_setup(gt_dispatcher_t *self, gt_world_t *world);

//! \brief Call \c run with the given \ref gt_world_t on all the systems.
//! \param self The \ref gt_dispatcher_t.
//! \param world The \ref gt_world_t.
//! \return \c true if any error occured when calling the systems, or \c false.
bool gt_dispatcher_run(gt_dispatcher_t *self, gt_world_t *world);

//! \brief Call \c dispose with the given \ref gt_world_t on all the systems.
//! \param self The \ref gt_dispatcher_t.
//! \param world The \ref gt_world_t.
//! \return \c true if any error occured when calling the systems, or \c false.
bool gt_dispatcher_dispose(gt_dispatcher_t *self, gt_world_t *world);

#endif /* LIBGOTE_ECS_DISPATCHER_H */
