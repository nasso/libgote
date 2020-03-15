/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_asset_storage
*/

#include "my/my.h"
#include "gote/ecs/storage.h"
#include "gote/assets/storage.h"

gt_asset_storage_t *gt_asset_storage_create(
    gt_storage_t *(*storage_ctor)(void (*)(void*)),
    const gt_format_t *format, u64_t start)
{
    gt_asset_storage_t *self = my_calloc(1, sizeof(gt_asset_storage_t));

    if (self == NULL)
        return (NULL);
    self->format = format;
    self->last_id = start - 1;
    self->storage = storage_ctor(format->destroy);
    if (self->storage == NULL) {
        my_free(self);
        return (NULL);
    }
    return (self);
}

void gt_asset_storage_destroy(gt_asset_storage_t *self)
{
    gt_storage_destroy(self->storage);
    my_free(self);
}

gt_handle_t gt_asset_storage_push(gt_asset_storage_t *self, void *asset_data)
{
    gt_handle_t handle = gt_handle_create(self->last_id + 1, self);

    if (handle == NULL)
        return (NULL);
    else if (gt_storage_set(self->storage, self->last_id + 1, asset_data))
        return (NULL);
    self->last_id++;
    return (handle);
}

void *gt_asset_storage_get(gt_asset_storage_t *self, const gt_handle_t handle)
{
    return (gt_storage_get(self->storage, handle->v->id));
}
