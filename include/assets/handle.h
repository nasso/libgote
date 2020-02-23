/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Asset handle type
*/

#ifndef LIBGOTE_ASSETS_HANDLE_H
#define LIBGOTE_ASSETS_HANDLE_H

//! \file include/assets/handle.h

#include "my/types.h"
#include "my/rc.h"
#include "gote/assets/format.h"

//! \brief Structure holding properties of an asset handle: its ID and the
//! storage containing the asset.
struct gt_asset_handle_data;

//! \brief Callback function called when the last handle to an asset is dropped.
//!
//! DO NOT CALL THIS FUNCTION.
//! \param data The asset handle data.
void gt_asset_handle_free(struct gt_asset_handle_data *data);

RC_DEFINE(struct gt_asset_handle_data, gt_asset_handle, gt_asset_handle_free)

typedef RC(gt_asset_handle) gt_handle_t;

#include "gote/assets/storage.h"

struct gt_asset_handle_data {
    u64_t id;
    gt_asset_storage_t *storage;
};

//! \brief Create a new \c gt_handle_t to an asset.
//! \param id The ID of the asset in the storage.
//! \param storage The storage containing the asset.
//! \return A new \c gt_handle_t.
gt_handle_t gt_handle_create(u64_t id, gt_asset_storage_t *storage);

//! \brief Clone a \c gt_handle_t (increment the reference count).
//! \param self The \c gt_handle_t to clone.
//! \return \c self.
static inline gt_handle_t gt_handle_clone(gt_handle_t self)
{
    return (RC_INC(gt_asset_handle)(self));
}

//! \brief Drop a \c gt_handle_t (decrement the reference count).
//! \param self The \c gt_handle_t to drop.
static inline void gt_handle_drop(gt_handle_t self)
{
    RC_DROP(gt_asset_handle)(self);
}

//! \brief Get the \c u64_t ID of a \c gt_handle_t.
//! \param self The \c gt_handle_t.
//! \return The \c u64_t ID of the handle.
static inline u64_t gt_handle_id(gt_handle_t self)
{
    return (self->v->id);
}

#endif /* LIBGOTE_ASSETS_HANDLE_H */
