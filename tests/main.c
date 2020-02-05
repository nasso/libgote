/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Unit tests
*/

#include <criterion/criterion.h>
#include "gote/gote.h"

Test(libgote, it_works)
{
    cr_assert_eq(gt_add(2, 2), 4);
}
