@test "correct output and return value" {
	run ./topssed
	[ "$status" -eq 0 ]
	[ "$output" = "Hello World!" ]
}
