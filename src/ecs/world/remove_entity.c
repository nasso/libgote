/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_remove_entity implementation
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/gote.h"

struct remove_component_data {
    gt_world_t *world;
    gt_entity_t *entity;
};

static int remove_component(void *user_data, void *ptr)
{
    struct remove_component_data *data = user_data;
    const gt_component_class_t *class = ptr;
    gt_storage_t *storage = gt_world_get(data->world, class->name);

    if (storage == NULL)
        return (1);
    gt_storage_delete(storage, data->entity->id);
    return (0);
}

void gt_world_remove_entity(gt_world_t *self, gt_entity_t *entity)
{
    struct remove_component_data data = {self, entity};

    if (list_remove_element(self->entities, entity, NULL) == NULL)
        return;
    list_for_each(self->component_classes, &remove_component, &data);
    my_free(entity);
}
