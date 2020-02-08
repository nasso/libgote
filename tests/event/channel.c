/*
** EPITECH PROJECT, 2020
** libgote
** File description:
** gt_event_channel_t tests
*/

#include <criterion/criterion.h>
#include "gote/gote.h"

Test(event_channel, create_empty)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(char));

    cr_assert_not_null(chan);
}

Test(event_channel, create_and_destroy_empty)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(char));

    gt_event_channel_destroy(chan);
}

Test(event_channel, sub)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(char));

    cr_assert_neq(gt_event_channel_sub(chan), 0);
    cr_assert_neq(gt_event_channel_sub(chan), 0);
    cr_assert_neq(gt_event_channel_sub(chan), 0);
    gt_event_channel_destroy(chan);
}

Test(event_channel, unsub)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(char));
    u64_t handle = gt_event_channel_sub(chan);

    gt_event_channel_unsub(chan, handle);
    gt_event_channel_destroy(chan);
}

Test(event_channel, unsub_invalid)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(char));

    gt_event_channel_unsub(chan, 0);
    gt_event_channel_unsub(chan, 1);
    gt_event_channel_unsub(chan, 39);
    gt_event_channel_destroy(chan);
}

Test(event_channel, unsub_twice)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(char));
    u64_t handle = gt_event_channel_sub(chan);

    gt_event_channel_unsub(chan, handle);
    gt_event_channel_unsub(chan, handle);
    gt_event_channel_destroy(chan);
}

Test(event_channel, push_without_subs)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(char));

    cr_assert_not(gt_event_channel_push(chan, "A"));
    cr_assert_not(gt_event_channel_push(chan, "B"));
    cr_assert_not(gt_event_channel_push(chan, "C"));
    gt_event_channel_destroy(chan);
}

Test(event_channel, push_with_subs)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(char));

    gt_event_channel_sub(chan);
    cr_assert_not(gt_event_channel_push(chan, "A"));
    gt_event_channel_sub(chan);
    cr_assert_not(gt_event_channel_push(chan, "B"));
    gt_event_channel_sub(chan);
    gt_event_channel_sub(chan);
    cr_assert_not(gt_event_channel_push(chan, "C"));
    gt_event_channel_destroy(chan);
}

Test(event_channel, push_and_poll)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(u16_t));
    u16_t val = 0;
    u64_t first = 0;
    u64_t second = 0;

    first = gt_event_channel_sub(chan);
    gt_event_channel_push(chan, "\xCD");
    gt_event_channel_push(chan, "\xEF");
    cr_assert(gt_event_channel_poll(chan, first, &val));
    cr_assert_eq(val, 0xCD);
    cr_assert(gt_event_channel_poll(chan, first, &val));
    cr_assert_eq(val, 0xEF);
    cr_assert_not(gt_event_channel_poll(chan, first, &val));
    second = gt_event_channel_sub(chan);
    gt_event_channel_push(chan, "\x42");
    cr_assert(gt_event_channel_poll(chan, first, &val));
    cr_assert_eq(val, 0x42);
    cr_assert(gt_event_channel_poll(chan, second, &val));
    cr_assert_eq(val, 0x42);
    gt_event_channel_destroy(chan);
}

Test(event_channel, poll_after_unsub)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(u16_t));
    u64_t handle = gt_event_channel_sub(chan);

    gt_event_channel_push(chan, "\xAB");
    gt_event_channel_unsub(chan, handle);
    gt_event_channel_push(chan, "\xCD");
    cr_expect_not(gt_event_channel_poll(chan, handle, NULL));
    gt_event_channel_destroy(chan);
}

Test(event_channel, discard_all)
{
    gt_event_channel_t *chan = gt_event_channel_create(sizeof(u16_t));
    u64_t handle = gt_event_channel_sub(chan);

    gt_event_channel_push(chan, "\xAB");
    gt_event_channel_push(chan, "\xCD");
    gt_event_channel_discard_all(chan, handle);
    cr_expect_not(gt_event_channel_poll(chan, handle, NULL));
    gt_event_channel_destroy(chan);
}
