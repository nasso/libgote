/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_create
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/world.h"

gt_world_t *gt_world_create(void)
{
    gt_world_t *self = my_malloc(sizeof(gt_world_t));

    if (self == NULL)
        return (NULL);
    self->resources = hash_map_new();
    self->entities = list_new();
    if (self->resources == NULL || self->entities == NULL) {
        gt_world_destroy(self);
        return (NULL);
    }
    return (self);
}
