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
    gt_dispatcher_t *disp = NULL;
    va_list ap;

    va_start(ap, system_count);
    disp = gt_dispatcher_create_v(system_count, ap);
    va_end(ap);
    if (disp == NULL)
        return (NULL);
    return (gt_game_data_create(disp));
}

void gt_game_data_destroy(gt_game_data_t *self)
{
    if (self)
        gt_dispatcher_destroy(self->dispatcher);
    my_free(self);
}
