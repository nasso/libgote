/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_create_entity implementation
*/

#include <stdarg.h>
#include "my/my.h"
#include "gote/gote.h"

static list_node_t *assign_slot(gt_world_t *self, gt_entity_t *ent)
{
    list_node_t *n = self->entities->head;

    if (ent == NULL)
        return (NULL);
    ent->id = 0;
    while (ent->id < self->entities->len) {
        if (n->val == NULL)
            return (n);
        n = n->next;
        ent->id++;
    }
    if (list_push_back(self->entities, NULL))
        return (NULL);
    return (self->entities->head->previous);
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
    list_node_t *slot = assign_slot(self, ent);
    const gt_component_class_t *class = NULL;
    void *component_data = NULL;

    if (ent == NULL || slot == NULL) {
        my_free(ent);
        return (NULL);
    }
    slot->val = ent;
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
