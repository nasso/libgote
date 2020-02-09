/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_trans_t tests
*/

#include <criterion/criterion.h>
#include "gote/gote.h"

Test(state_trans, make_none)
{
    cr_assert_eq(gt_state_trans_none().type, GT_STATE_TRANS_NONE);
}

Test(state_trans, make_pop)
{
    cr_assert_eq(gt_state_trans_pop().type, GT_STATE_TRANS_POP);
}

Test(state_trans, make_push)
{
    gt_state_t nop_state = {0};
    gt_state_trans_t trans = gt_state_trans_push(&nop_state);

    cr_assert_eq(trans.type, GT_STATE_TRANS_PUSH);
    cr_assert_eq(trans.state, &nop_state);
}

Test(state_trans, make_switch)
{
    gt_state_t nop_state = {0};
    gt_state_trans_t trans = gt_state_trans_switch(&nop_state);

    cr_assert_eq(trans.type, GT_STATE_TRANS_SWITCH);
    cr_assert_eq(trans.state, &nop_state);
}

Test(state_trans, make_quit)
{
    cr_assert_eq(gt_state_trans_quit().type, GT_STATE_TRANS_QUIT);
}
