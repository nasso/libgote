/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_app_create and gt_app_create_var
*/

#include <stdarg.h>
#include "my/my.h"
#include "gote/gote.h"

gt_app_t *gt_app_create(gt_state_t *initial_state, usize_t system_count, ...)
{
    gt_app_t *app = NULL;
    va_list ap;

    va_start(ap, system_count);
    app = gt_app_create_var(initial_state, system_count, ap);
    va_end(ap);
    return (app);
}

gt_app_t *gt_app_create_var(gt_state_t *initial_state, usize_t system_count,
    va_list ap)
{
    gt_app_t *app = my_calloc(1, sizeof(gt_app_t));

    if (app == NULL)
        return (NULL);
    app->world = gt_world_create();
    app->states = gt_state_machine_create(initial_state);
    app->data = gt_game_data_with_var(system_count, ap);
    if (app->world == NULL || app->states == NULL || app->data == NULL) {
        gt_app_destroy(app);
        return (NULL);
    }
    return (app);
}
