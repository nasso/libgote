/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_vec_storage
*/

#include "my/my.h"
#include "gote/ecs/storage.h"

static const usize_t INITIAL_LENGTH = 32;

struct gt_vec_storage {
    void **data;
    usize_t len;
    void (*destroy_item)(void *item);
};

static bool gt_vec_storage_set(void *self_ptr, u64_t id, void *value)
{
    struct gt_vec_storage *self = self_ptr;
    void **data = self->data;

    if (self->len <= id) {
        data = my_calloc(id + 1, sizeof(void*));
        if (data == NULL)
            return (true);
        my_memcpy(data, self->data, sizeof(void*) * self->len);
        my_free(self->data);
        self->len = id + 1;
        self->data = data;
    }
    if (self->destroy_item && data[id])
        self->destroy_item(data[id]);
    data[id] = value;
    return (false);
}

static void *gt_vec_storage_get(const void *self_ptr, u64_t id)
{
    const struct gt_vec_storage *self = self_ptr;

    if (id < self->len)
        return (self->data[id]);
    return (NULL);
}

static void gt_vec_storage_delete(void *self_ptr, u64_t id)
{
    struct gt_vec_storage *self = self_ptr;

    if (id >= self->len)
        return;
    else if (self->destroy_item && self->data[id])
        self->destroy_item(self->data[id]);
    self->data[id] = NULL;
}

static void gt_vec_storage_destroy(void *self_ptr)
{
    struct gt_vec_storage *self = self_ptr;

    for (usize_t i = 0; i < self->len; i++) {
        if (self->destroy_item && self->data[i])
            self->destroy_item(self->data[i]);
    }
    my_free(self->data);
    self->data = NULL;
    self->len = 0;
}

gt_storage_t *gt_vec_storage(void (*destroy_item)(void *item))
{
    struct gt_vec_storage self = {NULL, INITIAL_LENGTH, destroy_item};
    gt_storage_t *proto = my_malloc(sizeof(gt_storage_t));

    if (proto == NULL)
        return (NULL);
    self.data = my_calloc(INITIAL_LENGTH, sizeof(void*));
    proto->self = my_malloc(sizeof(struct gt_vec_storage));
    if (proto->self == NULL || self.data == NULL) {
        my_free(proto->self);
        my_free(proto);
        my_free(self.data);
        return (NULL);
    }
    my_memcpy(proto->self, &self, sizeof(struct gt_vec_storage));
    proto->set = &gt_vec_storage_set;
    proto->get = &gt_vec_storage_get;
    proto->delete = &gt_vec_storage_delete;
    proto->destroy = &gt_vec_storage_destroy;
    return (proto);
}
