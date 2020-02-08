/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_dispatcher_create
*/

#include <stdarg.h>
#include "my/my.h"
#include "my/collections/list.h"
#include "gote/ecs/dispatcher.h"

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

    if (self == NULL)
        return (NULL);
    self->systems = list_from_var(n, ap);
    if (self->systems == NULL) {
        gt_dispatcher_destroy(self);
        return (NULL);
    }
    return (self);
}
