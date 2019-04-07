# Topssed

`topssed` is a Linux network _daemon_ that streams [system information](/doc/data.out.md) over [server-sent events](https://html.spec.whatwg.org/multipage/server-sent-events.html).

```
$❯ ./topssed &
[1] 31586
Listening at http://127.0.0.1:53001

$❯ curl -sm 1 http://127.0.0.1:53001
event: config
data: 100 2009681 4 4096

event: hello
data: world


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

$❯ curl -svm 1 http://127.0.0.1:53001 | cat
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
{ [53 bytes data]
* Operation timed out after 1000 milliseconds with 66 bytes received
* Closing connection 0
event: config
data: 100 2009681 4 4096

event: hello
data: world


$❯ systemctl --user stop topssed-dev
```

> `cat` is used here to get the exact same output as [Bats](https://github.com/bats-core/bats-core) tests will get.
