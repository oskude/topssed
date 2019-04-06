# Topssed

`topssed` is a Linux network _daemon_ that sends [system information](/doc/data.out.md) to every new connection and closes the connection.

```
$❯ ./topssed &
[1] 31586
Listening at http://127.0.0.1:53001

$❯ curl -s http://127.0.0.1:53001
event: config
data: 100 2009681 4 4096

$❯ kill 31586
[1]+  Terminated              ./topssed
```

# Requirements

&nbsp; | [Build](#Build) | [Test](#Test) | [Run](#Run)
-|-|-|-
[Bats](https://github.com/bats-core/bats-core) | ○ | ◉ | ○
[GCC](https://www.gnu.org/software/gcc/) | ◉ | ○ | ○
[make](https://www.gnu.org/software/make/) | ◉ | ◉ | ○
[systemd](https://freedesktop.org/wiki/Software/systemd/) | ○ | ◉ | ◎

# Files

Path | Description
-|-
`.editorconfig` | Formatting information. [⌘](https://editorconfig.org/)
`.gitignore` | Ignore artifacts. [⌘](https://git-scm.com/docs/gitignore)
`doc/*` | Documentation. [⌘](https://github.github.com/gfm/)
`makefile` | Automation instructions. [⌘](https://www.gnu.org/software/make/manual/make.html)
`readme.md` | Developer information. [⌘](https://github.github.com/gfm/)
`src/main.c` | Main source code. [⌘](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html)
`test/*` | Test instructions. [⌘](https://github.com/bats-core/bats-core#writing-tests)

# Build

```
$❯ make
```

# Test

```
$❯ make test
```

# Run

```
$❯ systemd-run --user --unit="topssed-dev" ./topssed
Running as unit: topssed-dev.service

$❯ curl -sv http://127.0.0.1:53001 | cat
*   Trying 127.0.0.1...
* TCP_NODELAY set
* Connected to 127.0.0.1 (127.0.0.1) port 53001 (#0)
> GET / HTTP/1.1
> Host: 127.0.0.1:53001
> User-Agent: curl/7.64.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Access-Control-Allow-Origin: *
< Content-Type: text/event-stream;charset=utf-8
* no chunk, no close, no size. Assume close to signal end
<
{ [40 bytes data]
* Recv failure: Connection reset by peer
* Closing connection 0
event: config
data: 100 2009681 4 4096

$❯ systemctl --user stop topssed-dev
```

> `cat` is used here to get the exact same output as [Bats](https://github.com/bats-core/bats-core) tests will get.
