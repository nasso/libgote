/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_game_data_t tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/io.h"
#include "gote/gote.h"

static void shout_destroy(void *self)
{
    (void)(self);
    my_printf("DESTROY!\n");
}

static gt_system_t *dummy_system(void)
{
    gt_system_t *sys = my_calloc(1, sizeof(gt_system_t));

    sys->destroy = &shout_destroy;
    return (sys);
}

TestSuite(game_data, .timeout = 1.0, .init = cr_redirect_stdout);

Test(game_data, create_and_destroy_empty)
{
    gt_game_data_t *gd = gt_game_data_with(0);

    cr_assert_not_null(gd);
    gt_game_data_destroy(gd);
}

Test(game_data, create_and_destory_not_empty)
{
    gt_game_data_t *gd = gt_game_data_with(2, dummy_system(), dummy_system());

    cr_assert_not_null(gd);
    gt_game_data_destroy(gd);
    cr_assert_stdout_eq_str("DESTROY!\nDESTROY!\n");
}

Test(game_data, create_with_failed)
{
    gt_game_data_t *gd = gt_game_data_with(3, dummy_system(), NULL,
        dummy_system());

    cr_assert_null(gd);
    cr_assert_stdout_eq_str("DESTROY!\nDESTROY!\n");
}
