/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_dispatcher_create
*/

#include <stdarg.h>
#include "my/my.h"
#include "my/collections/list.h"
#include "gote/ecs/system.h"
#include "gote/ecs/dispatcher.h"

static void destroy_all(usize_t n, gt_system_t **systems)
{
    if (systems == NULL)
        return;
    for (usize_t i = 0; i < n; i++)
        if (systems[i])
            gt_system_destroy(systems[i]);
    my_free(systems);
}

static bool gather_systems(usize_t n, va_list ap, gt_system_t **systems)
{
    bool is_one_null = false;

    for (usize_t i = 0; i < n; i++) {
        systems[i] = va_arg(ap, gt_system_t*);
        is_one_null |= systems[i] == NULL;
    }
    return (is_one_null);
}

gt_dispatcher_t *gt_dispatcher_create(usize_t n, ...)
{
    gt_dispatcher_t *self = NULL;
    va_list ap;

    va_start(ap, n);
    self = gt_dispatcher_create_v(n, ap);
    va_end(ap);
    return (self);
}

gt_dispatcher_t *gt_dispatcher_create_v(usize_t n, va_list ap)
{
    gt_dispatcher_t *self = my_malloc(sizeof(gt_dispatcher_t));
    gt_system_t **systems = my_malloc(n * sizeof(gt_system_t*));

    if (self == NULL || systems == NULL || gather_systems(n, ap, systems)) {
        destroy_all(n, systems);
        my_free(self);
        return (NULL);
    }
    self->systems = list_from_arr(n, (void**) systems);
    if (self->systems == NULL) {
        destroy_all(n, systems);
        my_free(self);
        return (NULL);
    } else
        my_free(systems);
    return (self);
}
