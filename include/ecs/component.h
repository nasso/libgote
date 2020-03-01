/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Component type
*/

#ifndef LIBGOTE_ECS_COMPONENT_H
#define LIBGOTE_ECS_COMPONENT_H

//! \file include/ecs/component.h

//! \brief Defines a type of component.
typedef struct gt_component_class {
    void (*destroyer)(void *self);
    const char *name;
} gt_component_class_t;

#endif /* LIBGOTE_ECS_COMPONENT_H */
