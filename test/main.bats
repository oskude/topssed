@test "program starts" {
	run systemd-run --user --unit="topssed-test" ./topssed
	[ "$status" -eq 0 ]
	[ "$output" = "Running as unit: topssed-test.service" ]
}

@test "program is running" {
	run systemctl --user is-active topssed-test
	[ "$status" -eq 0 ]
	[ "$output" = "active" ]
}

@test "program sends sse header" {
	run curl -sv http://127.0.0.1:53001
	[ "$status" -eq 56 ]
	[ "${lines[8]}" = "< HTTP/1.1 200 OK" ]
	[ "${lines[9]}" = "< Access-Control-Allow-Origin: *" ]
	[ "${lines[10]}" = "< Content-Type: text/event-stream;charset=utf-8" ]
	[ "${lines[11]}" = "* Recv failure: Connection reset by peer" ]
	[ "${lines[12]}" = "* Closing connection 0" ]
}

@test "program is still running" {
	run systemctl --user is-active topssed-test
	[ "$status" -eq 0 ]
	[ "$output" = "active" ]
}

@test "program stops" {
	run systemctl --user stop topssed-test
	[ "$status" -eq 0 ]
}

@test "program is stopped" {
	run systemctl --user is-active topssed-test
	[ "$status" -eq 3 ]
	[ "$output" = "inactive" ]
}
