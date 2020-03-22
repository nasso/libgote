/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_t
*/

#ifndef LIBGOTE_STATE_MACHINE_H
#define LIBGOTE_STATE_MACHINE_H

//! \file include/state/machine.h

//! \brief A simple state machine.
//!
//! The machine is automatically destroyed when all the states have been popped.
typedef struct gt_state_machine gt_state_machine_t;

#include "my/my.h"
#include "gote/ecs.h"
#include "gote/state/state.h"
#include "gote/state/trans.h"

//! \brief Create a new state machine with the given initial state.
//! \param initial_state The initial state.
//! \return A new state machine.
gt_state_machine_t *gt_state_machine_create(gt_state_t *initial_state);

//! \brief Destroy a state machine.
//!
//! Any remaining state is forcefully destroyed (\c on_stop is \b NOT called).
//! \param self The state machine to be destroyed.
void gt_state_machine_destroy(gt_state_machine_t *self);

//! \brief Check if a state machine is still running.
//! \param self The state machine.
//! \return \c true if the machine is currently running, \c false otherwise.
bool gt_state_machine_is_running(gt_state_machine_t *self);

//! \brief Start the state machine.
//! \param self The state machine.
//! \param world The world.
//! \return \c true if an error occured, \c false otherwise.
bool gt_state_machine_start(gt_state_machine_t *self, gt_world_t *world);

//! \brief Update the state machine.
//! \param self The state machine.
//! \param world The world.
//! \return \c true if an error occured, \c false otherwise.
bool gt_state_machine_update(gt_state_machine_t *self, gt_world_t *world);

//! \brief Perform a state transition.
//! \param self The state machine.
//! \param trans The transition to perform.
//! \param world The world.
//! \return \c true if an error occured, \c false otherwise.
bool gt_state_machine_trans(gt_state_machine_t *self,
    const gt_state_trans_t *trans, gt_world_t *world);

#endif /* LIBGOTE_STATE_MACHINE_H */
