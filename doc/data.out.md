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

x | type | info
-|-|-
0 | int | Number of clock ticks per second. [sysconf _SC_CLK_TCK]()
1 | int | Number of pages of physical memory. [sysconf _SC_PHYS_PAGES]()
2 | int | Number of processors currently online. [sysconf _SC_NPROCESSORS_ONLN]()
3 | int | Size of a page in bytes. [sysconf _SC_PAGESIZE]()
