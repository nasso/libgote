/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Asset loading
*/

#ifndef LIBGOTE_ASSETS_LOADER_H
#define LIBGOTE_ASSETS_LOADER_H

//! \file include/assets/loader.h

#include "gote/ecs.h"
#include "gote/assets/handle.h"
#include "gote/assets/format.h"

//! \brief Load an asset and get a \c gt_handle_t to it.
//! \param path The path to the asset file.
//! \param format The file format.
//! \return A new \c gt_handle_t to the asset.
gt_handle_t gt_load(const char *path, const gt_format_t *format,
    gt_world_t *world);

#endif /* LIBGOTE_ASSETS_LOADER_H */
