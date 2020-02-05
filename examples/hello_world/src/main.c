/*
** EPITECH PROJECT, 2020
** libgote-example-hello_world
** File description:
** Program entry point
*/

#include "my/my.h"
#include "my/io.h"
#include "gote/gote.h"

int main(void)
{
    my_printf("Hello gote!\n");
    my_printf("%d + %d = %d\n", 3, 5, gt_add(3, 5));
    return (0);
}
