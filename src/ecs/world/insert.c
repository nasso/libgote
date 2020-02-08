/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_insert
*/

#include "my/my.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/world.h"
#include "gote/ecs/world_priv.h"

bool gt_world_insert(gt_world_t *self,  const char *key, void *data, void
    (*destroyer)(void*))
{
    gt_resource_t *res = my_malloc(sizeof(gt_resource_t));

    if (res == NULL)
        return (true);
    res->destroyer = destroyer;
    res->self = data;
    hash_map_insert(self->resources, key, res);
    return (false);
}
