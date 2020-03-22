/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_get
*/

#include "my/my.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/world.h"
#include "gote/ecs/world_priv.h"

void *gt_world_get(const gt_world_t *self, const char *key)
{
    OPT(ptr) opt_res = hash_map_get(self->resources, key);
    gt_resource_t *res = opt_res.is_some ? opt_res.v : NULL;

    if (res == NULL)
        return (NULL);
    return (res->self);
}
