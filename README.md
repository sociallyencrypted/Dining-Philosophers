# Dining-Philosophers

This assignment tries to solve two variations of the dining philosophers by using strict ordering and semaphores on each variation.

1. Five Philosophers, Five Forks
2. Five Philosophers, Five Forks, Two Bowls

## Installation

Clone this repo, `cd` into it, and run:

```console
make
```

This will generate the binaries for all variations.

## Usage

You can run the first variation, strictly ordered, by running:

```console
bin/forksA
```

You can run the second variation, strictly ordered, by running:

```console
bin/soupA
```

You can run the first variation, semaphores, by running:

```console
bin/forksB
```

You can run the second variation, semaphores, by running:

```console
bin/soupB
```

## References

[OSTEP Chapter on Semaphores](https://pages.cs.wisc.edu/~remzi/OSTEP/threads-sema.pdf)