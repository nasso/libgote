/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_format_t
*/

#ifndef LIBGOTE_ASSETS_FORMAT_H
#define LIBGOTE_ASSETS_FORMAT_H

//! \file include/assets/format.h

#include "my/types.h"
#include "gote/ecs.h"

//! \brief A format defines how assets are to be loaded.
typedef struct gt_format {
    const char *name;
    void *(*load)(const char *path, gt_world_t *world);
    void (*destroy)(void *data);
} gt_format_t;

#endif /* LIBGOTE_ASSETS_FORMAT_H */
