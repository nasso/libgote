/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_storage_destroy
*/

#include "my/my.h"
#include "gote/ecs/storage.h"

void gt_storage_destroy(gt_storage_t *self)
{
    if (self && self->destroy)
        self->destroy(self->self);
    my_free(self);
}

bool gt_storage_set(gt_storage_t *self, u64_t id, void *data)
{
    if (self->set)
        return (self->set(self->self, id, data));
    return (false);
}

void *gt_storage_get(const gt_storage_t *self, u64_t id)
{
    if (self->get)
        return (self->get(self->self, id));
    return (NULL);
}

void gt_storage_delete(gt_storage_t *self, u64_t id)
{
    if (self->delete)
        self->delete(self->self, id);
}
