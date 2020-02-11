/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_dispatcher_setup
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/ecs/system.h"
#include "gote/ecs/world.h"
#include "gote/ecs/dispatcher.h"

static int setup_system_callback(void *user_data, void *ptr)
{
    gt_world_t *world = user_data;
    gt_system_t *sys = ptr;

    return (gt_system_setup(sys, world));
}

bool gt_dispatcher_setup(gt_dispatcher_t *self, gt_world_t *world)
{
    return (list_for_each(self->systems, &setup_system_callback, world));
}
