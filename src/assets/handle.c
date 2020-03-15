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

void gt_asset_handle_free(gt_asset_handle_data_t *data)
{
    if (data->format->destroy)
        data->format->destroy(data->data);
    my_free(data);
}

gt_handle_t gt_handle_create(const gt_format_t *format, void *data)
{
    gt_asset_handle_data_t *handle_data =
        my_calloc(1, sizeof(gt_asset_handle_data_t));

    if (handle_data == NULL)
        return (NULL);
    handle_data->format = format;
    handle_data->data = data;
    return (RC_WRAP(gt_asset_handle)(handle_data));
}
