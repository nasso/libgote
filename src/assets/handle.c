/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Asset handle methods
*/

#include "my/my.h"
#include "gote/ecs/storage.h"
#include "gote/assets/handle.h"
#include "gote/assets/format.h"

void gt_asset_handle_free(struct gt_asset_handle_data *data)
{
    void *asset = gt_storage_get(data->storage->storage, data->id);

    gt_storage_set(data->storage->storage, data->id, NULL);
    data->storage->format->destroy(asset);
}

gt_handle_t gt_handle_create(u64_t id, gt_asset_storage_t *storage)
{
    struct gt_asset_handle_data *handle_data =
        my_malloc(sizeof(struct gt_asset_handle_data));

    if (handle_data == NULL)
        return (NULL);
    handle_data->id = id;
    handle_data->storage = storage;
    return (RC_WRAP(gt_asset_handle)(handle_data));
}
