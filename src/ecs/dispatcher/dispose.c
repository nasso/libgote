/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_dispatcher_dispose
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/ecs/system.h"
#include "gote/ecs/world.h"
#include "gote/ecs/dispatcher.h"

static int dispose_system_callback(void *user_data, void *ptr)
{
    gt_world_t *wld = user_data;
    gt_system_t *sys = ptr;

    if (sys->dispose == NULL)
        return (0);
    return (sys->dispose(sys->self, wld));
}

bool gt_dispatcher_dispose(gt_dispatcher_t *self, gt_world_t *world)
{
    return (list_for_each(self->systems, &dispose_system_callback, world));
}
