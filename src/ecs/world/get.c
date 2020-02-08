/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_get
*/

#include "my/my.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/world.h"

void *gt_world_get(const gt_world_t *self, const char *key)
{
    gt_resource_t *res = hash_map_get(self->resources, key);

    if (res == NULL)
        return (NULL);
    return (res->self);
}
