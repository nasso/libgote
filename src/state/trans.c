/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_trans_t
*/

#include "my/my.h"
#include "gote/state/state.h"
#include "gote/state/trans.h"

gt_state_trans_t gt_state_trans_none(void)
{
    return ((gt_state_trans_t) {
        .type = GT_STATE_TRANS_NONE,
        .state = NULL,
    });
}

gt_state_trans_t gt_state_trans_pop(void)
{
    return ((gt_state_trans_t) {
        .type = GT_STATE_TRANS_POP,
        .state = NULL,
    });
}

gt_state_trans_t gt_state_trans_push(gt_state_t *state)
{
    return ((gt_state_trans_t) {
        .type = GT_STATE_TRANS_PUSH,
        .state = state,
    });
}

gt_state_trans_t gt_state_trans_switch(gt_state_t *state)
{
    return ((gt_state_trans_t) {
        .type = GT_STATE_TRANS_SWITCH,
        .state = state,
    });
}

gt_state_trans_t gt_state_trans_quit(void)
{
    return ((gt_state_trans_t) {
        .type = GT_STATE_TRANS_QUIT,
        .state = NULL,
    });
}
