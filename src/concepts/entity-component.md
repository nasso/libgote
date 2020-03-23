# Entity and Resource

## Entity

An entity represents any object of your game. Examples of entities include the
player, NPCs, an item, a button or a map. An entity doesn't hold any data (other
than its existence)! Essentially, entities can be thought of as elements in a
big array containing all the objects that make up a scene of your game:

| player | villager | sword | play_button |
|--------|----------|-------|-------------|

## Component

A component is what gives _properties_ to an entity. Without components,
entities are... Well, useless! They don't do anything! They don't even have a
_position_, a _color_, a _sprite_... All this information comes from components.

At any given point, an entity either _has_ or _doesn't have_ a component. It
cannot have, say, the same component twice. Keeping the example from above, it's
as if each component type added one new line to the following table:

|             |   entity    |
|:-----------:|:-----------:|
| Component A |   value 1   |
| Component B |   value 2   |
| Component C |   value 3   |

Entities are not required to have a value for all component types. For example,
we could say that the player only needs a position and a sprite:

|          |   player   |
|:--------:|:----------:|
| Position |   (3, 4)   |
|   Sprite | player.png |
|    Color |      -     |

The player doesn't have a "color", so the value for the "color" component line
is just left empty.

Adding an entity adds a column to the table!

|          |   player   |   villager   |    sword  | play_button |
|:--------:|:----------:|:------------:|:---------:|:-----------:|
| Position |   (3, 4)   |   (17, 12)   |   (-4, 1) |  (40, 160)  |
|   Sprite | player.png | villager.png | sword.png |      -      |
|    Color |      -     |       -      |      -    |   #88FF00   |

Even if only one entity requires a "color" component the line for the "color"
component spans all the table. That can create "holes" in the table, but it's
okay because there are ways to eliminate that problem we will see very shortly.

## Usage with the `libgote`

### Creating a component class

Say you want to create a new kind of component. For this example, we will create
a "position" component class.

The first step is to declare a new [`gt_component_class_t`] global constant.
Usually, you will want to declare it in a header file with the `extern` keyword:

```c
extern const gt_component_class_t POSITION_COMP;
```

And then, define it in your source file:

```c
const gt_component_class_t POSITION_COMP = {
  .name = "position_component",
  .destroyer = &my_free,
};
```

There are two important fields here:

- `name` - a static, ***unique*** character string that will be used as the key
  for the storage resource in the world. It **must be unique** and must **not
  be used as the key for any other resource in the world**.
- `destroyer` - a pointer to the function to be called when the component data
  is to be destroyed.

Speaking about the component data: it can be anything you want! It is common to
have a constructor for your component data (declared in the same header file as
the [`gt_component_class_t`] it corresponds to):

```c
typedef struct {
  f64_t x;
  f64_t y;
} position_comp_t;

position_comp_t *position_component(f64_t x, f64_t y);
```

An example implementation could be:

```c
position_comp_t *position_component(f64_t x, f64_t y)
{
  position_comp_t *self = my_calloc(1, sizeof(position_comp_t));

  self->x = x;
  self->y = y;
  return (self);
}
```

### Registering components

Components are stored in _"storages"_ kept as a [Resource] in the [World]. Think
of a storage as a simple array (that's basically what they are anyway).  Keeping
the table example from earlier, each component "storage" corresponds to a line
of the table. That means there's one storage per component type.

|          |   player   |   villager   |    sword  | play_button |
|:--------:|:----------:|:------------:|:---------:|:-----------:|
| Position |   (3, 4)   |   (17, 12)   |   (-4, 1) |  (40, 160)  |
|   Sprite | player.png | villager.png | sword.png |      -      |
|    Color |      -     |       -      |      -    |   #88FF00   |

In this example, there are 3 storages: one for `Position` components, one for
`Sprite` components and another for `Color` components. Each line is a storage.

There are two implementations of storage in the `libgote`:

- [`gt_vec_storage`] - literally just a vector: better when most entities will
  have this component (there's very few "holes").
- [`gt_map_storage`] - uses a hash map: better when few entities will have this
  component (there are many, big "holes"). **Not implemented as of writing this.
  Do not use.**

As a component storage is just a resource in the world, you add them just like
any other resource:

```c
// create the storage (here it's just a vector/array!)
gt_storage_t *strg = gt_vec_storage();

gt_world_insert(
  world,
  POSITION_COMP.name,
  strg,
  (void (*)(void*)) &gt_storage_destroy
);
```

Though, having to do that for every component type would be kinda annoying. This
is why the [`gt_world_register`] function exists! It takes care of the last
argument (the destroyer):

```c
gt_storage_t *strg = gt_vec_storage();

gt_world_register(world, POSITION_COMP.name, strg);
```

But there's even better than this! The [`gt_world_register_component`] function!

```c
gt_world_register_component(world, &POSITION_COMP, &gt_vec_storage);
```

Here, all you have to give is a pointer to the [`gt_component_class_t`] and a
pointer to the constructor for the storage implementation to use. It does the
exact same thing as the code snippets above!

### Creating an entity

You cannot create an entity from nothing (there's no "`gt_entity_create`"
function). The reason for this is that an entity only makes sense when it is
part of a world, with the appropriate storages available.

You can create entities with the [`gt_world_create_entity`] function:

The arguments are:
- The world
- How many components to initialize the entity with
- For each initial component:
  - A pointer to the [`gt_component_class_t`]
  - The component data

For example, to create an entity using our `position_comp_t`:

```c
gt_entity_t *ent = gt_world_create_entity(world, 1,
  &POSITION_COMP, position_component(2.0, 6.0)
);
```

Or with more components you've created (don't forget to change the component
count!):

```c
gt_entity_t *player = gt_world_create_entity(world, 3,
  &POSITION_COMP, position_component(2.0, 6.0),
  &SPRITE_COMP, sprite_component("player.png"),
  &INVENTORY_COMP, inventory_component()
);
```

Of course, if you want to create an entity without any component:

```c
gt_entity_t *ent = gt_world_create_entity(world, 0);
```

### Removing the entity

When you're done using an entity, you have to manually remove it from the world!
[State]s do not know about the entities you've created, so they are not removed
automatically!

To remove entities, use the [`gt_world_remove_entity`] function:

```c
/* Remove the player entity when the state stops */
static void combat_state_on_stop(void *ptr, gt_world_t *world)
{
  struct combat_state *self = ptr;

  gt_world_remove_entity(world, self->player);
}
```

[`gt_component_class_t`]: https://nasso.io/libgote/doc/component_8h.html#a6739e0f3cea04059f731821731848abf
[`gt_vec_storage`]: https://nasso.io/libgote/doc/storage_8h.html#a840ee612a9d9f0e18173aa76a5c00157
[`gt_map_storage`]: https://nasso.io/libgote/doc/storage_8h.html#a1734e440a07ce6d8bc21b053a2f2cc7d
[`gt_world_register`]: https://nasso.io/libgote/doc/world_8h.html#a38a9c2aac83d56af536247b9b195c26a
[`gt_world_register_component`]: https://nasso.io/libgote/doc/world_8h.html#ac219c2fa113e399980f9f05391fef06e
[`gt_world_create_entity`]: https://nasso.io/libgote/doc/world_8h.html#ad152d8ee4d09746e01e3610507ffcb18
[`gt_world_remove_entity`]: https://nasso.io/libgote/doc/world_8h.html#a1cdb28dd5c3b8de2a578aaf832abdebe
[World]: world-resource.md#world
[Resource]: world-resource.md#resource
[State]: state.md
