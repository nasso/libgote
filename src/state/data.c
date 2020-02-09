/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_state_data_t
*/

#include "my/my.h"
#include "gote/ecs/world.h"
#include "gote/state/data.h"

gt_state_data_t *gt_state_data_create(gt_world_t *world, void *data)
{
    gt_state_data_t *self = my_malloc(sizeof(gt_state_data_t));

    if (self == NULL)
        return (NULL);
    self->world = world;
    self->data = data;
    return (self);
}

void gt_state_data_destroy(gt_state_data_t *self)
{
    my_free(self);
}
