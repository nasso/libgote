/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_data_t tests
*/

#include <criterion/criterion.h>
#include "gote/gote.h"

Test(state_data, create_and_destroy)
{
    gt_world_t dummy_world = {0};
    i32_t dummy_data = 32;
    gt_state_data_t *data = gt_state_data_create(&dummy_world, &dummy_data);

    cr_assert_not_null(data);
    cr_assert_eq(data->world, &dummy_world);
    cr_assert_eq(data->data, &dummy_data);
    gt_state_data_destroy(data);
}
