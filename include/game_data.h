/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_game_data_t
*/

#ifndef LIBGOTE_GAME_DATA_H
#define LIBGOTE_GAME_DATA_H

//! \file include/game_data.h

#include <stdarg.h>
#include "gote/ecs/dispatcher.h"

//! \brief A general purpose data type for use in \ref gt_state_data_t.
typedef struct gt_game_data {
    gt_dispatcher_t *dispatcher;
} gt_game_data_t;

//! \brief Create a \ref gt_game_data_t from a \ref gt_dispatcher_t.
//! \param dispatcher The dispatcher.
//! \return A new \ref gt_game_data_t.
gt_game_data_t *gt_game_data_create(gt_dispatcher_t *dispatcher);

//! \brief Create a \ref gt_game_data_t from a list of systems.
//!
//! If any system is a \c NULL pointer, this function destroys all the other
//! non-<code>NULL</code> systems and return \c NULL. This allows this function
//! to be safely called with potentially \c NULL data from an allocation
//! failure.
//! \param system_count The count of systems in the variadic argument list.
//! \param ... The systems.
//! \return A new instance of \ref gt_game_data_t.
gt_game_data_t *gt_game_data_with(usize_t system_count, ...);

//! \brief Create a \ref gt_game_data_t from a list of systems.
//!
//! If any system is a \c NULL pointer, this function destroys all the other
//! non-<code>NULL</code> systems and return \c NULL. This allows this function
//! to be safely called with potentially \c NULL data from an allocation
//! failure.
//!
//! This function is the \c va_list version of \ref gt_game_data_with.
//! \param system_count The count of systems in the variadic argument list.
//! \param ap The systems.
//! \return A new instance of \ref gt_game_data_t.
gt_game_data_t *gt_game_data_with_var(usize_t system_count, va_list ap);

//! \brief Destroy a \ref gt_game_data_t.
//! \param self The \ref gt_game_data_t.
void gt_game_data_destroy(gt_game_data_t *self);

#endif /* LIBGOTE_GAME_DATA_H */
