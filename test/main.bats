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

@test "program closes new connection" {
	run curl -sv http://127.0.0.1:53001
	[ "$status" -eq 56 ]
	[ "${lines[2]}" = "* Connected to 127.0.0.1 (127.0.0.1) port 53001 (#0)" ]
	[ "${lines[8]}" = "* Recv failure: Connection reset by peer" ]
	[ "${lines[9]}" = "* Closing connection 0" ]
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
