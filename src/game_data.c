/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_game_data_t
*/

#include <stdarg.h>
#include "my/my.h"
#include "gote/ecs/dispatcher.h"
#include "gote/game_data.h"

gt_game_data_t *gt_game_data_create(gt_dispatcher_t *dispatcher)
{
    gt_game_data_t *self = my_malloc(sizeof(gt_game_data_t));

    if (self == NULL)
        return (NULL);
    self->dispatcher = dispatcher;
    return (self);
}

gt_game_data_t *gt_game_data_with(usize_t system_count, ...)
{
    gt_game_data_t *gd = NULL;
    va_list ap;

    va_start(ap, system_count);
    gd = gt_game_data_with_var(system_count, ap);
    va_end(ap);
    return (gd);
}

gt_game_data_t *gt_game_data_with_var(usize_t system_count, va_list ap)
{
    gt_dispatcher_t *disp = NULL;
    gt_game_data_t *gd = NULL;

    disp = gt_dispatcher_create_v(system_count, ap);
    if (disp == NULL)
        return (NULL);
    gd = gt_game_data_create(disp);
    if (gd == NULL)
        gt_dispatcher_destroy(disp);
    return (gd);
}

void gt_game_data_destroy(gt_game_data_t *self)
{
    if (self == NULL)
        return;
    gt_dispatcher_destroy(self->dispatcher);
    my_free(self);
}
