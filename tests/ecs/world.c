/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_world_t tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/my.h"
#include "my/io.h"
#include "gote/gote.h"

// Health component: class definition
static const gt_component_class_t HEALTH_COMPONENT = {
    .name = "health_component",
    .destroyer = &my_free
};

// Health component: component data
typedef struct {
    f64_t health;
} health_comp_t;

// Health component: constructor
static health_comp_t *create_health_component(f64_t health)
{
    health_comp_t *comp = my_malloc(sizeof(health_comp_t));

    comp->health = health;
    return (comp);
}

// Pos component: class definition
static const gt_component_class_t POS_COMPONENT = {
    .name = "pos_component",
    .destroyer = &my_free
};

// Pos component: component data
typedef struct {
    f64_t x;
    f64_t y;
} pos_comp_t;

// Pos component: constructor
static pos_comp_t *create_pos_component(f64_t x, f64_t y)
{
    pos_comp_t *comp = my_malloc(sizeof(pos_comp_t));

    comp->x = x;
    comp->y = y;
    return (comp);
}

static void loud_i32_free(void *ptr)
{
    my_printf("FREE %d\n", *((i32_t*) ptr));
    my_free(ptr);
}

TestSuite(world, .timeout = 1.0, .init = cr_redirect_stdout);

Test(world, create_and_destroy_empty)
{
    gt_world_t *wld = gt_world_create();

    cr_assert_not_null(wld);
    gt_world_destroy(wld);
}

Test(world, destroy_null)
{
    gt_world_destroy(NULL);
}

Test(world, add_resource)
{
    i32_t value = 84;
    gt_world_t *wld = gt_world_create();

    gt_world_insert(wld, "foo", &value, NULL);
    cr_assert_eq(gt_world_get(wld, "foo"), &value);
    gt_world_destroy(wld);
}

Test(world, add_resource_with_destroyer)
{
    i32_t *value = my_malloc(sizeof(i32_t));
    gt_world_t *wld = gt_world_create();

    *value = 1;
    gt_world_insert(wld, "foo", value, &loud_i32_free);
    gt_world_destroy(wld);
    cr_assert_stdout_eq_str("FREE 1\n");
}

Test(world, remove_resource)
{
    i32_t *value = my_malloc(sizeof(i32_t));
    gt_world_t *wld = gt_world_create();

    *value = 1;
    gt_world_insert(wld, "foo", value, &loud_i32_free);
    gt_world_remove(wld, "foo");
    cr_assert_stdout_eq_str("FREE 1\n");
    gt_world_destroy(wld);
}

Test(world, get_absent_resource)
{
    gt_world_t *wld = gt_world_create();

    cr_assert_null(gt_world_get(wld, "foo"));
    gt_world_destroy(wld);
}

Test(world, remove_absent_resource)
{
    gt_world_t *wld = gt_world_create();

    gt_world_remove(wld, "foo");
    gt_world_destroy(wld);
}

Test(world, register_storage)
{
    gt_world_t *wld = gt_world_create();
    gt_storage_t *dummy = my_malloc(sizeof(gt_storage_t));

    dummy->self = my_malloc(sizeof(i32_t));
    *((i32_t*) dummy->self) = 1;
    dummy->destroy = &loud_i32_free;
    dummy->set = NULL;
    dummy->get = NULL;
    dummy->delete = NULL;
    cr_assert_not(gt_world_register(wld, "foo", dummy));
    gt_world_destroy(wld);
    cr_assert_stdout_eq_str("FREE 1\n");
}

Test(world, create_entity_without_components)
{
    gt_world_t *wld = gt_world_create();
    gt_entity_t *ent = gt_world_create_entity(wld, 0);

    cr_assert_not_null(ent);
    cr_assert_eq(wld->entities->len, 1);
    cr_assert_eq(wld->entities->head->val, ent);
    gt_world_destroy(wld);
}

Test(world, create_multiple_entity_without_components)
{
    gt_world_t *wld = gt_world_create();
    gt_entity_t *ent1 = gt_world_create_entity(wld, 0);
    gt_entity_t *ent2 = gt_world_create_entity(wld, 0);
    gt_entity_t *ent3 = gt_world_create_entity(wld, 0);

    cr_assert_not_null(ent1);
    cr_assert_not_null(ent2);
    cr_assert_not_null(ent3);
    cr_assert_eq(wld->entities->len, 3);
    cr_assert_eq(wld->entities->head->val, ent1);
    cr_assert_eq(wld->entities->head->next->val, ent2);
    cr_assert_eq(wld->entities->head->next->next->val, ent3);
    gt_world_destroy(wld);
}

Test(world, create_entity_with_unregistered_components)
{
    gt_world_t *wld = gt_world_create();
    gt_entity_t *ent = gt_world_create_entity(
        wld,
        1,
        &HEALTH_COMPONENT, create_health_component(4.0),
        &POS_COMPONENT, create_pos_component(1.0, 3.0)
    );

    cr_assert_null(ent);
    gt_world_destroy(wld);
}

Test(world, create_entity_with_components)
{
    gt_world_t *wld = gt_world_create();
    gt_entity_t *ent = NULL;
    gt_storage_t *health_storage = NULL;
    gt_storage_t *pos_storage = NULL;
    health_comp_t *health_comp = create_health_component(4.0);
    pos_comp_t *pos_comp = create_pos_component(1.0, 3.0);

    gt_world_register_component(wld, &HEALTH_COMPONENT, &gt_vec_storage);
    gt_world_register_component(wld, &POS_COMPONENT, &gt_vec_storage);
    ent = gt_world_create_entity(wld, 2, &HEALTH_COMPONENT, health_comp,
        &POS_COMPONENT, pos_comp);
    cr_assert_not_null(ent);
    health_storage = gt_world_get(wld, HEALTH_COMPONENT.name);
    pos_storage = gt_world_get(wld, POS_COMPONENT.name);
    cr_assert_eq(gt_storage_get(health_storage, ent->id), health_comp);
    cr_assert_eq(gt_storage_get(pos_storage, ent->id), pos_comp);
    gt_world_destroy(wld);
}
