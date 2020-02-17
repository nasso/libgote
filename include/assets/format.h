/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_format_t
*/

#ifndef LIBGOTE_ASSETS_FORMAT_H
#define LIBGOTE_ASSETS_FORMAT_H

#include "my/types.h"

typedef struct gt_format {
    const char *name;
    void *(*import)(u8_t *bytes, usize_t n);
    void *(*destroy)(void *res);
} gt_format_t;

#endif /* LIBGOTE_ASSETS_FORMAT_H */
