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

bool gt_world_register(gt_world_t *self, const char *key, gt_storage_t *storage)
{
    return (gt_world_insert(self, key, storage,
        (void (*)(void*)) &gt_storage_destroy));
}

bool gt_world_register_component(gt_world_t *self,
    const gt_component_class_t *class,
    gt_storage_t *(*storage_ctor)(void (*)(void*)))
{
    gt_storage_t *storage = NULL;

    if (list_find(self->component_classes, (void*) class))
        return (false);
    else if (list_push_back(self->component_classes, (void*) class))
        return (true);
    storage = storage_ctor(class->destroyer);
    if (storage == NULL)
        return (true);
    else if (gt_world_register(self, class->name, storage)) {
        gt_storage_destroy(storage);
        return (true);
    }
    return (false);
}
