# Topssed

`topssed` is a Linux network _daemon_ that disconnects every new connection.

```
❯ ./topssed &
[1] 31586
Listening at http://127.0.0.1:53001

❯ curl http://127.0.0.1:53001
curl: (56) Recv failure: Connection reset by peer

❯ kill 31586
[1]+  Terminated              ./topssed
```

# Requirements

&nbsp; | [Build](#Build) | [Test](#Test) | [Run](#Run)
-|-|-|-
[Bats](https://github.com/bats-core/bats-core) | ○ | ◉ | ○
[GCC](https://www.gnu.org/software/gcc/) | ◉ | ○ | ○
[Linux](https://www.kernel.org/) | ◉ | ◉ | ◉
[make](https://www.gnu.org/software/make/) | ◉ | ◉ | ○
[systemd](https://freedesktop.org/wiki/Software/systemd/) | ○ | ◉ | ◎

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
❯ systemd-run --user --unit="topssed-dev" ./topssed
Running as unit: topssed-dev.service

❯ curl -v http://127.0.0.1:53001
*   Trying 127.0.0.1...
* TCP_NODELAY set
* Connected to 127.0.0.1 (127.0.0.1) port 53001 (#0)
> GET / HTTP/1.1
> Host: 127.0.0.1:53001
> User-Agent: curl/7.64.1
> Accept: */*
>
* Recv failure: Connection reset by peer
* Closing connection 0
curl: (56) Recv failure: Connection reset by peer

❯ systemctl --user stop topssed-dev
```
