/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Asset loader
*/

#include "gote/gote.h"

static gt_asset_storage_t *get_asset_storage(gt_world_t *world,
    const gt_format_t *format)
{
    gt_storage_t *strg = NULL;
    gt_asset_storage_t *asset_strg = gt_world_get(world, format->name);

    if (asset_strg)
        return (asset_strg);
    strg = gt_vec_storage(format->destroy);
    if (strg == NULL)
        return (NULL);
    asset_strg = gt_asset_storage_create(strg, format, 1);
    if (asset_strg == NULL)
        gt_storage_destroy(strg);
    gt_world_insert(world, format->name, asset_strg,
        (void (*)(void*)) &gt_asset_storage_destroy);
    return (asset_strg);
}

gt_handle_t gt_load(const char *path, const gt_format_t *format,
    gt_world_t *world)
{
    gt_asset_storage_t *strg = get_asset_storage(world, format);

    if (strg == NULL)
        return (NULL);
    return (gt_asset_storage_push(strg, format->load(path)));
}
