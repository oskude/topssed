# Data Output

`topssed` sends its data over HTTP [Server-sent events](https://html.spec.whatwg.org/multipage/server-sent-events.html).

# Header
```
HTTP/1.1 200 OK
Access-Control-Allow-Origin: *
Content-Type: text/event-stream;charset=utf-8
```

# Events

## `event: config`

initial system configuration, needed for some calculations.

> sent on connection start.

```
data: 100 2009681 4 4096
```

x | type | src | info
-|-|-|-
`0` | `int` | `clock_tick` | Number of clock ticks per second. [⌘](https://linux.die.net/man/3/sysconf)
`1` | `int` | `max_pages` | Number of pages of physical memory. [⌘](https://linux.die.net/man/3/sysconf)
`2` | `int` | `num_cpus` | Number of processors currently online. [⌘](https://linux.die.net/man/3/sysconf)
`3` | `int` | `page_size` | Size of a page in bytes. [⌘](https://linux.die.net/man/3/sysconf)
