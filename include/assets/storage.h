/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_asset_storage_t
*/

#ifndef LIBGOTE_ASSETS_STORAGE_H
#define LIBGOTE_ASSETS_STORAGE_H

//! \file include/assets/storage.h

#include "gote/ecs.h"
#include "gote/assets/format.h"

//! \brief A wrapper of \c gt_storage_t that generates the IDs.
typedef struct gt_asset_storage {
    gt_storage_t *storage;
    u64_t last_id;
    const gt_format_t *format;
} gt_asset_storage_t;

//! \brief Create a new \c gt_asset_storage_t.
//!
//! This function "takes ownership" of the <code>gt_storage_t</code>! That means
//! you should \b NOT attempt to use it after calling this function.
//! \param storage The wrapped storage.
//! \param start The starting ID.
//! \return A new \c gt_asset_storage_t.
gt_asset_storage_t *gt_asset_storage_create(gt_storage_t *storage,
    const gt_format_t *format, u64_t start);

//! \brief Destroy a \c gt_asset_storage_t.
//!
//! This function destroys the wrapped \c gt_storage_t as well!
//! \param self The \c gt_asset_storage_t to destroy.
void gt_asset_storage_destroy(gt_asset_storage_t *self);

#include "gote/assets/handle.h"

//! \brief Add an asset to a \c gt_asset_storage_t.
//! \param self The \c gt_asset_storage_t.
//! \param asset_data The asset data.
//! \return A \c gt_handle_t to the asset; \c NULL if an error occured.
gt_handle_t gt_asset_storage_push(gt_asset_storage_t *self, void *asset_data);

//! \brief Get an asset from a storage.
//! \param self The \c gt_asset_storage_t.
//! \param handle A \c gt_handle_t to the asset.
//! \return The asset data.
void *gt_asset_storage_get(gt_asset_storage_t *self, const gt_handle_t handle);

#endif /* LIBGOTE_ASSETS_STORAGE_H */
