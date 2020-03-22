/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_t
*/

#ifndef LIBGOTE_STATE_STATE_H
#define LIBGOTE_STATE_STATE_H

//! \file include/state/state.h

//! \brief A game state.
typedef struct gt_state gt_state_t;

#include "gote/ecs.h"
#include "gote/state/trans.h"

//! \brief A game state.
struct gt_state {
    void (*on_start)(void *self, gt_world_t *world);
    void (*on_stop)(void *self, gt_world_t *world);
    void (*on_pause)(void *self, gt_world_t *world);
    void (*on_resume)(void *self, gt_world_t *world);
    gt_state_trans_t (*update)(void *self, gt_world_t *world);
    void (*shadow_update)(void *self, gt_world_t *world);
    void (*destroy)(void *self);
    void *self;
};

//! \brief Executed when the state begins.
//! \param state The state.
//! \param world The world.
void gt_state_on_start(gt_state_t *state, gt_world_t *world);

//! \brief Executed when the state ends.
//! \param state The state.
//! \param world The world.
void gt_state_on_stop(gt_state_t *state, gt_world_t *world);

//! \brief Executed when a state is pushed on top of this state.
//! \param state The state.
//! \param world The world.
void gt_state_on_pause(gt_state_t *state, gt_world_t *world);

//! \brief Executed when the state above this state is popped.
//! \param state The state.
//! \param world The world.
void gt_state_on_resume(gt_state_t *state, gt_world_t *world);

//! \brief Executed repeatedly only on the state at the top of the stack.
//! \param state The state.
//! \param world The world.
//! \return The transition to perform.
gt_state_trans_t gt_state_update(gt_state_t *state, gt_world_t *world);

//! \brief Executed repeatedly on all states in the stack.
//! \param state The state.
//! \param world The world.
void gt_state_shadow_update(gt_state_t *state, gt_world_t *world);

//! \brief Destroy the state.
//! \param state The state.
void gt_state_destroy(gt_state_t *state);

#endif /* LIBGOTE_STATE_STATE_H */
