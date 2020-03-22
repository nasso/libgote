/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_remove
*/

#include "my/my.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/world.h"
#include "gote/ecs/world_priv.h"

void gt_world_remove(gt_world_t *self, const char *key)
{
    OPT(ptr) opt_res = hash_map_remove(self->resources, key);
    gt_resource_t *res = opt_res.is_some ? opt_res.v : NULL;

    if (res != NULL && res->destroyer)
        res->destroyer(res->self);
    my_free(res);
}
