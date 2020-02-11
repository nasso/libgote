/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_system_t
*/

#include "my/my.h"
#include "gote/ecs/system.h"

void gt_system_destroy(gt_system_t *self)
{
    if (self && self->destroy)
        self->destroy(self->self);
    my_free(self);
}

bool gt_system_setup(gt_system_t *self, gt_world_t *world)
{
    if (self->setup != NULL)
        return (self->setup(self->self, world));
    return (false);
}

bool gt_system_run(gt_system_t *self, gt_world_t *world)
{
    if (self->run != NULL)
        return (self->run(self->self, world));
    return (false);
}

bool gt_system_dispose(gt_system_t *self, gt_world_t *world)
{
    if (self->dispose != NULL)
        return (self->dispose(self->self, world));
    return (false);
}
