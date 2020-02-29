/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_app_t
*/

#ifndef LIBGOTE_APP_H
#define LIBGOTE_APP_H

//! \file include/app.h

#include <stdarg.h>
#include "gote/ecs.h"
#include "gote/state.h"
#include "gote/game_data.h"

//! \brief Structure holding all the data needed by a game or application.
typedef struct gt_app {
    gt_world_t *world;
    gt_state_machine_t *states;
    gt_game_data_t *data;
    f64_t dt_ms;
    f64_t time_ms;
    struct {
        u64_t trans_chan_sub;
    } priv;
} gt_app_t;

//! \brief Create an application with the given systems.
//! \param initial_state The initial state of the state machine.
//! \param system_count How many systems are in the variadic argument list.
//! \param ... A variable amount of \ref gt_system_t.
//! \return A new \ref gt_app_t.
gt_app_t *gt_app_create(gt_state_t *initial_state, usize_t system_count, ...);

//! \brief Create an application with the given systems (as a \c va_list).
//! \param initial_state The initial state of the state machine.
//! \param system_count How many systems are in the variadic argument list.
//! \param ap A \c va_list of \ref gt_system_t.
//! \return A new \ref gt_app_t.
gt_app_t *gt_app_create_var(gt_state_t *initial_state, usize_t system_count,
    va_list ap);

//! \brief Destroy a \c gt_app_t.
//! \param self The \ref gt_app_t to destroy.
void gt_app_destroy(gt_app_t *self);

//! \brief Run an application.
//! \param self The \ref gt_app_t to run.
//! \return \c false if the game ran successfully, \c true if an error occured.
bool gt_app_run(gt_app_t *self);

#endif /* LIBGOTE_APP_H */
