# Topssed

`topssed` is a "_hello world_" program for Linux.

```
$ topssed
Hello World!
```
# Requirements

&nbsp; | [Build](#Build) | [Test](#Test) | [Run](#Run)
-|-|-|-
[Linux](https://www.kernel.org/) | ◉ | ◉ | ◉
[GCC](https://www.gnu.org/software/gcc/) | ◉ | ○ | ○
[make](https://www.gnu.org/software/make/) | ◉ | ◉ | ○
[Bats](https://github.com/bats-core/bats-core) | ○ | ◉ | ○

# Files

Path | Description
-|-
`.editorconfig` | Formatting information. [⌘](https://editorconfig.org/)
`makefile` | Automation instructions. [⌘](https://www.gnu.org/software/make/manual/make.html)
`readme.md` | Developer information. [⌘](https://github.github.com/gfm/)
`src/main.c` | Main source code. [⌘](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html)
`test/*` | Test instructions. [⌘](https://github.com/bats-core/bats-core#writing-tests)

# Build

```
$ make
```

# Test

```
$ make test
```

# Run

```
$ ./topssed
```
