/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** Asset storage tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my/my.h"
#include "my/io.h"
#include "my/cstr.h"
#include "gote/gote.h"

static void *loud_load(const char *path, gt_world_t *world)
{
    (void)(world);
    my_printf("load %s;", path);
    return (my_cstrdup(path));
}

static void loud_destroy(void *ptr)
{
    my_printf("destroy %s;", ptr ? ptr : "(nil)");
    my_free(ptr);
}

static const gt_format_t LOUD_FORMAT = {
    .name = "asset_loud",
    .load = &loud_load,
    .destroy = &loud_destroy,
};

TestSuite(asset_storage, .timeout = 1.0, .init = cr_redirect_stdout);

Test(asset_storage, create_and_destroy_empty)
{
    gt_asset_storage_t *astrg = gt_asset_storage_create(&gt_vec_storage,
        &LOUD_FORMAT, 1);

    cr_assert_not_null(astrg);
    gt_asset_storage_destroy(astrg);
}

Test(asset_storage, load_and_drop_asset)
{
    gt_asset_storage_t *astrg = gt_asset_storage_create(&gt_vec_storage,
        &LOUD_FORMAT, 1);
    gt_handle_t hdl = NULL;

    hdl = gt_asset_storage_push(astrg, LOUD_FORMAT.load("hello", NULL));
    gt_handle_drop(hdl);
    gt_asset_storage_destroy(astrg);
    my_printf("end;");
    cr_assert_stdout_eq_str("load hello;destroy hello;end;");
}

Test(asset_storage, get_asset)
{
    gt_asset_storage_t *astrg = gt_asset_storage_create(&gt_vec_storage,
        &LOUD_FORMAT, 1);
    gt_handle_t hdl = NULL;

    hdl = gt_asset_storage_push(astrg, LOUD_FORMAT.load("hello", NULL));
    cr_assert_eq(my_cstrcmp(gt_asset_storage_get(astrg, hdl), "hello"), 0);
    gt_asset_storage_destroy(astrg);
    my_printf("end;");
    cr_assert_stdout_eq_str("load hello;destroy hello;end;");
}

Test(asset_storage, drop_asset_after_storage_is_destroyed)
{
    gt_asset_storage_t *astrg = gt_asset_storage_create(&gt_vec_storage,
        &LOUD_FORMAT, 1);
    gt_handle_t hdl = NULL;

    hdl = gt_asset_storage_push(astrg, LOUD_FORMAT.load("hello", NULL));
    gt_asset_storage_destroy(astrg);
    my_printf("destroyed;");
    gt_handle_drop(hdl);
    my_printf("end;");
    cr_assert_stdout_eq_str("load hello;destroyed;destroy hello;end;");
}
