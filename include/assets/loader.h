/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_loader_t
*/

#ifndef LIBGOTE_ASSETS_LOADER_H
#define LIBGOTE_ASSETS_LOADER_H

//! \file include/assets/loader.h

//! \brief A loader is used to load assets from a resource directory.
typedef struct gt_loader {
    const char *dir;
} gt_loader_t;

//! \brief Create a new \c gt_loader_t.
//! \param dir The assets directory.
//! \return A new \c gt_loader_t.
gt_loader_t *gt_loader_create(const char *dir);

//! \brief Destroy a \c gt_loader_t.
//! \param self The \c gt_loader_t to destroy.
void gt_loader_destroy(gt_loader_t *self);

#endif /* LIBGOTE_ASSETS_LOADER_H */
