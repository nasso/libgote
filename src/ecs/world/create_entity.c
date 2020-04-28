/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_create_entity implementation
*/

#include <stdarg.h>
#include "my/my.h"
#include "my/collections/list.h"
#include "gote/gote.h"

static u64_t get_first_available_id(list_t *entities)
{
    gt_entity_t *ent = NULL;
    u64_t id = 0;

    LIST_FOR_EACH(entities, iter) {
        ent = iter.v;
        if (ent->id != id)
            return (id);
        id++;
    }
    return (id);
}

static bool add_entity(gt_world_t *self, gt_entity_t *ent)
{
    if (ent == NULL)
        return (true);
    ent->id = get_first_available_id(self->entities);
    if (ent->id >= self->entities->len)
        return (list_push_back(self->entities, ent));
    return (list_insert(self->entities, ent->id, ent));
}

static bool put_component(gt_world_t *self, u64_t id,
    const gt_component_class_t *class, void *data)
{
    gt_storage_t *storage = gt_world_get(self, class->name);

    if (storage == NULL)
        return (true);
    return (gt_storage_set(storage, id, data));
}

gt_entity_t *gt_world_create_entity(gt_world_t *self, usize_t component_count,
    ...)
{
    gt_entity_t *ent = NULL;
    va_list ap;

    va_start(ap, component_count);
    ent = gt_world_create_entity_va(self, component_count, ap);
    va_end(ap);
    return (ent);
}

gt_entity_t *gt_world_create_entity_va(gt_world_t *self,
    usize_t component_count, va_list ap)
{
    gt_entity_t *ent = my_malloc(sizeof(gt_entity_t));
    const gt_component_class_t *class = NULL;
    void *component_data = NULL;

    if (ent == NULL || add_entity(self, ent)) {
        my_free(ent);
        return (NULL);
    }
    for (usize_t i = 0; i < component_count; i++) {
        class = va_arg(ap, const gt_component_class_t*);
        component_data = va_arg(ap, void*);
        if (put_component(self, ent->id, class, component_data)) {
            my_free(ent);
            return (NULL);
        }
    }
    return (ent);
}
