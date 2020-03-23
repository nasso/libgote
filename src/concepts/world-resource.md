# World and Resource

## World

All the data global to your game is stored in what is called a "World". That
includes, for instance, all the entities of your game. Entities are covered in
[their own chapter](entity.md).

The world really is just a [hash table][hash-table-wiki] mapping keys (character
strings) to _resources_.

## Resource

What is a resource? Anything you want! The only requirement is that it must be
a pointer. Other than that, you can have anything you want except for function
pointers, because of the C language specification forbidding it. If you really
need to store a function pointer in your World, wrap them in a heap-allocated
structure and it will be fine!

## Usage in the `libgote`

### Creating a new world

You will rarely ever need to create or destroy a world directly (`libgote` does
it for you when you create a [`gt_app_t`][gt_app_t]). Though, here's how you
would do it:

```c
// create a world this way:
gt_world_t *world = gt_world_create();

// destroy it when you're done!
gt_world_destroy(world);
```

### Resource insertion

When inserting a resource in the world, you can optionally specify a destructor
to be called when the resource is removed or the world destroyed:

```c
list_t *cool_stuff = list_from(3, "furries", "undertale", "you");

// the destroyer must be explicitly cast because C cannot implicitly cast
// function pointers, even when they are compatible.
gt_world_insert(world, "cool_stuff", data, (void (*)(void*)) &list_destroy);
```

For resources which do not need to be destroyed (i.e. static value), just set
the destroyer to `NULL`:

```c
gt_world_insert(world, "some_string", "Hey! This is a resource!", NULL);
```

### Resource retrieval

Getting a resource from the world is straightforward:

```c
const char *my_resource = gt_world_get(world, "some_string");

my_printf("%s", my_resource); // "Hey! This is a resource!"
```

### Resource removal

Removing a resource from the world is, also, straightforward:

```c
gt_world_remove(world, "some_string");
```

Note that `gt_world_remove` does _NOT_ return anything! The resource is
destroyed as soon as you remove it from the world.

[hash-table-wiki]: https://en.wikipedia.org/wiki/Hash_table
[gt_app_t]: https://nasso.io/libgote/doc/app_8h.html
