/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_machine_trans
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/state/state.h"
#include "gote/state/trans.h"
#include "gote/state/machine.h"
#include "priv.h"

static bool trans_pop(gt_state_machine_t *self, gt_world_t *world)
{
    gt_state_t *state = self->stack->head->val;

    gt_state_on_stop(state, world);
    gt_state_destroy(list_pop_front(self->stack).v);
    state = list_get(self->stack, 0).v;
    self->running = state != NULL;
    if (state)
        gt_state_on_resume(state, world);
    else
        self->running = false;
    return (false);
}

static bool trans_push(gt_state_machine_t *self, gt_state_t *state,
    gt_world_t *world)
{
    gt_state_t *old_top = self->stack->head->val;

    if (list_push_front(self->stack, state))
        return (true);
    gt_state_on_pause(old_top, world);
    gt_state_on_start(state, world);
    return (false);
}

static bool trans_switch(gt_state_machine_t *self, gt_state_t *state,
    gt_world_t *world)
{
    gt_state_t *old_top = self->stack->head->val;

    gt_state_on_stop(old_top, world);
    gt_state_destroy(old_top);
    self->stack->head->val = state;
    gt_state_on_start(state, world);
    return (false);
}

static bool trans_stop(gt_state_machine_t *self, gt_world_t *world)
{
    gt_state_t *state = list_pop_front(self->stack).v;

    self->running = false;
    while (state) {
        gt_state_on_stop(state, world);
        gt_state_destroy(state);
        state = list_pop_front(self->stack).v;
    }
    return (false);
}

bool gt_state_machine_trans(gt_state_machine_t *self,
    const gt_state_trans_t *trans, gt_world_t *world)
{
    if (!self->running)
        return (false);
    switch (trans->type) {
    case GT_STATE_TRANS_POP:
        return (trans_pop(self, world));
    case GT_STATE_TRANS_PUSH:
        return (trans_push(self, trans->state, world));
    case GT_STATE_TRANS_SWITCH:
        return (trans_switch(self, trans->state, world));
    case GT_STATE_TRANS_QUIT:
        return (trans_stop(self, world));
    default:
        return (false);
    }
}
