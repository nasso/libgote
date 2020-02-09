/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_t
*/

#ifndef LIBGOTE_STATE_MACHINE_H
#define LIBGOTE_STATE_MACHINE_H

//! \file include/state/machine.h

#include "my/my.h"
#include "gote/state/data.h"
#include "gote/state/state.h"
#include "gote/state/trans.h"

//! \brief A simple state machine.
//!
//! The machine is automatically destroyed when all the states have been popped.
typedef struct gt_state_machine gt_state_machine_t;

//! \brief Create a new state machine with the given initial state.
//! \param initial_state The initial state.
//! \return A new state machine.
gt_state_machine_t *gt_state_machine_create(gt_state_t *initial_state);

//! \brief Destroy a state machine.
//!
//! Any remaining state is forcefully destroyed.
//! \note In most cases, you don't need to call this method, as it is called
//! automatically when the root state is popped out of the machine.
//! \param self The state machine to be destroyed.
void gt_state_machine_destroy(gt_state_machine_t *self);

//! \brief Check if a state machine is still running.
//! \param self The state machine.
//! \return \c true if the machine has any state left on its stack, \c false
//! otherwise.
bool gt_state_machine_is_alive(gt_state_machine_t *self);

//! \brief Start the state machine.
//! \param self The state machine.
//! \param state_data The state data structure.
//! \return \c true if an error occured, \c false otherwise.
bool gt_state_machine_start(gt_state_machine_t *self, gt_state_data_t *data);

//! \brief Update the state machine.
//! \param self The state machine.
//! \param state_data The state data structure.
//! \return \c true if an error occured, \c false otherwise.
bool gt_state_machine_update(gt_state_machine_t *self, gt_state_data_t *data);

//! \brief Perform a state transition.
//! \param self The state machine.
//! \param trans The transition to perform.
//! \param state_data The state data structure.
//! \return \c true if an error occured, \c false otherwise.
bool gt_state_machine_trans(gt_state_machine_t *self,
    const gt_state_trans_t *trans, gt_state_data_t *data);

#endif /* LIBGOTE_STATE_MACHINE_H */
