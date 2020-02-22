/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Asset handle type
*/

#ifndef LIBGOTE_ASSETS_HANDLE_H
#define LIBGOTE_ASSETS_HANDLE_H

#include "my/my.h"

RC_DEFINE(u64_t, gt_asset_handle, my_free)

typedef RC(gt_asset_handle) gt_handle_t;

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
    return (*self->v);
}

#endif /* LIBGOTE_ASSETS_HANDLE_H */
