/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Component type
*/

#ifndef LIBGOTE_ECS_COMPONENT_H
#define LIBGOTE_ECS_COMPONENT_H

//! \file include/ecs/component.h
//! \typedef gt_component_def_t
//! \brief Defines a type of component.
typedef struct gt_component_def {
    const char *type;
    void (*const destroyer)(void*);
} gt_component_def_t;

#endif /* LIBGOTE_ECS_COMPONENT_H */
