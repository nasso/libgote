/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_destroy
*/

#include "my/my.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/world.h"
#include "gote/ecs/world_priv.h"

static int destroy_resource_callback(void *user_data, hash_map_pair_t *pair)
{
    gt_resource_t *res = pair->value;

    (void)(user_data);
    if (res && res->destroyer)
        res->destroyer(res->self);
    my_free(res);
    return (0);
}

void gt_world_destroy(gt_world_t *self)
{
    if (self == NULL)
        return;
    hash_map_destroy_with(self->resources, &destroy_resource_callback, NULL);
    list_destroy(self->entities);
    list_destroy(self->component_classes);
    my_free(self);
}
