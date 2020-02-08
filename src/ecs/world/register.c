/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_register
*/

#include "my/my.h"
#include "my/collections/hash_map.h"
#include "gote/ecs/storage.h"
#include "gote/ecs/world.h"

static void destroy_storage_callback(void *ptr)
{
    gt_storage_t *storage = ptr;

    gt_storage_destroy(storage);
}

bool gt_world_register(gt_world_t *self, const char *key,
    const gt_storage_t *storage)
{
    gt_storage_t *storage_cpy = my_malloc(sizeof(gt_storage_t));

    if (storage_cpy == NULL)
        return (true);
    my_memcpy(storage_cpy, storage, sizeof(gt_storage_t));
    return (gt_world_insert(self, key, storage_cpy, &destroy_storage_callback));
}
