/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_trans_t
*/

#ifndef LIBGOTE_STATE_TRANS_H
#define LIBGOTE_STATE_TRANS_H

//! \file include/state/trans.h

#include "gote/state/state.h"

//! \brief Type representing transitions between states in a state machine.
typedef struct gt_state_trans {
    enum {
        GT_STATE_TRANS_NONE,
        GT_STATE_TRANS_POP,
        GT_STATE_TRANS_PUSH,
        GT_STATE_TRANS_SWITCH,
        GT_STATE_TRANS_QUIT,
    } type;
    gt_state_t *state;
} gt_state_trans_t;

//! \brief A transition that doesn't do anything.
//! \return A \ref gt_state_trans representing the transition.
gt_state_trans_t gt_state_trans_none(void);

//! \brief Pop the state at the top of the stack.
//! \return A \ref gt_state_trans representing the transition.
gt_state_trans_t gt_state_trans_pop(void);

//! \brief Push a state on top of the stack.
//! \param state The state.
//! \return A \ref gt_state_trans representing the transition.
gt_state_trans_t gt_state_trans_push(gt_state_t *state);

//! \brief Replace the state at the top of the stack with another state.
//! \param state The state to replace the current state with.
//! \return A \ref gt_state_trans representing the transition.
gt_state_trans_t gt_state_trans_switch(gt_state_t *state);

//! \brief Pop all states and quit the state machine.
//! \return A \ref gt_state_trans representing the transition.
gt_state_trans_t gt_state_trans_quit(void);

#endif /* LIBGOTE_STATE_TRANS_H */
