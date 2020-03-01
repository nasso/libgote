/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_register
*/

#include "my/my.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/storage.h"
#include "gote/ecs/component.h"
#include "gote/ecs/world.h"

static void destroy_storage_callback(void *ptr)
{
    gt_storage_t *storage = ptr;

    gt_storage_destroy(storage);
}

bool gt_world_register(gt_world_t *self, const char *key, gt_storage_t *storage)
{
    return (gt_world_insert(self, key, storage, &destroy_storage_callback));
}

bool gt_world_register_component(gt_world_t *self,
    const gt_component_class_t *class,
    gt_storage_t *(*storage_ctor)(void (*)(void*)))
{
    return (gt_world_register(self, class->name,
        storage_ctor(class->destroyer)));
}
