/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_dispatcher_run
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/ecs/system.h"
#include "gote/ecs/world.h"
#include "gote/ecs/dispatcher.h"

bool gt_dispatcher_run(gt_dispatcher_t *self, gt_world_t *world)
{
    LIST_FOR_EACH(self->systems, iter) {
        if (gt_system_run(iter.v, world))
            return (true);
    }
    return (false);
}
