# Introduction

## Presentation

This book will teach you everything you need to know about building video games
with the `libgote`. I'll try to add information about the various aspects of the
library and how you can link them together to make a complete video game.

Refer to the [API documentation][docs] for an in-depth detail of all the
functions provided by the library.

## Building from source

### Cloning the repository

#### Using SSH

Make sure your SSH key is linked to your GitHub account.

```sh
git clone git@github.com:nasso/libgote.git
```

#### Using HTTPS

```sh
git clone https://github.com/nasso/libgote.git
```

### Building `libgote`

Just navigate in the root directory of the repository and call make:

```sh
cd libgote
make
```

If you want to build it with debug flag (`-g3`), add `DEBUG=1` to the `make`
command:

```sh
make DEBUG=1
```

## Generating the documentation

The library documentation is generated using Doxygen. A online version is
available [here][doc].
 
First, make sure the `./target` directory exists at the root of the repository.
It is automatically created when building the library, but you can also use
`mkdir`.

[docs]: https://nasso.io/libgote/doc/
