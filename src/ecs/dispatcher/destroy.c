/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_dispatcher_destroy
*/

#include "my/my.h"
#include "my/collections/list.h"
#include "gote/ecs/system.h"
#include "gote/ecs/dispatcher.h"

static int destroy_system_callback(void *user_data, void *ptr)
{
    gt_system_t *system = ptr;

    (void)(user_data);
    if (system && system->destroy)
        system->destroy(system->self);
    my_free(system);
    return (0);
}

void gt_dispatcher_destroy(gt_dispatcher_t *self)
{
    if (self == NULL)
        return;
    if (self->systems)
        list_destroy_with(self->systems, &destroy_system_callback, NULL);
    my_free(self);
}
