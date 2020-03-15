/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Asset loader
*/

#include "gote/gote.h"

gt_handle_t gt_load(const char *path, const gt_format_t *format,
    gt_world_t *world)
{
    return (gt_handle_create(format, format->load(path, world)));
}
