/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_data_t
*/

#ifndef LIBGOTE_STATE_DATA_H
#define LIBGOTE_STATE_DATA_H

//! \file include/state/data.h

#include "gote/ecs/world.h"

//! \brief The data shared by all states of a state machine.
typedef struct gt_state_data {
    gt_world_t *world;
    void *data;
} gt_state_data_t;

//! \brief Create a new \ref gt_state_data_t instance.
//! \param world The associated \ref gt_world_t.
//! \param data User data pointer.
//! \return A new \ref gt_state_data_t.
gt_state_data_t *gt_state_data_create(gt_world_t *world, void *data);

//! \brief Destroy a \ref gt_state_data_t instance.
//! \param self The instance.
void gt_state_data_destroy(gt_state_data_t *self);

#endif /* LIBGOTE_STATE_DATA_H */
