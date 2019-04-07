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
	run curl -svm 2 http://127.0.0.1:53001
	[ "${lines[8]}" = "< HTTP/1.1 200 OK" ]
	[ "${lines[9]}" = "< Access-Control-Allow-Origin: *" ]
	[ "${lines[10]}" = "< Content-Type: text/event-stream;charset=utf-8" ]
}

@test "program sends config event and data" {
	run curl -svm 2 http://127.0.0.1:53001
	[ "${lines[16]}" = "event: config" ]
	# TODO: hmm, why cant we use "[0-9]+"? is there a substitute?
	[ $(expr "${lines[17]}" : "data: [0-9]* [0-9]* [0-9]* [0-9]*") -ne 0 ]
}

@test "program sends hello event and data" {
	run curl -svm 2 http://127.0.0.1:53001
	[ "${lines[18]}" = "event: hello" ]
	[ "${lines[19]}" = "data: world" ]
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
