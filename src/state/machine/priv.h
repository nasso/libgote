/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_t private header
*/

#ifndef LIBGOTE_STATE_MACHINE_PRIV_H
#define LIBGOTE_STATE_MACHINE_PRIV_H

#include "my/collections/list.h"
#include "gote/state/machine.h"

struct gt_state_machine {
    bool running;
    list_t *stack;
};

#endif /* LIBGOTE_STATE_MACHINE_PRIV_H */
