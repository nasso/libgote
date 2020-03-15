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

bool gt_world_insert(gt_world_t *self, const char *key, void *data,
    void (*destroyer)(void*))
{
    gt_resource_t *res = hash_map_get(self->resources, key);

    if (res == NULL) {
        res = my_calloc(1, sizeof(gt_resource_t));
        if (res == NULL)
            return (true);
        hash_map_insert(self->resources, key, res);
    } else if (res->destroyer) {
        res->destroyer(res->self);
    }
    res->destroyer = destroyer;
    res->self = data;
    return (false);
}
