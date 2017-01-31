#!/usr/bin/env bats

wclip=./`git rev-parse --show-cdup`/dist/Release/wclip

@test "wclip exists" {
  [ -f $wclip ]
}

@test "version outputs 1 lines" {
    result=`$wclip --version | wc -l`
    [ $result = 1 ]
}

@test "help outputs multiple lines" {
    result=`$wclip --help | wc -l`
    [ $result -gt 3 ]
}

@test "when called without filename stdin is copied to clipboard" {
    echo "from_std_in" | $wclip
    [ `cat /dev/clipboard` = "from_std_in" ]
}

@test "when called with filename, file is copied to clipboard" {
    echo "from_file" > from_file
    echo "do not copy" | $wclip from_file
    rm from_file
    [ `cat /dev/clipboard` = "from_file" ]
}

@test "copied content from stdin is not written to stdout by default" {
    output=`echo "not on stdout" | $wclip`
    [ -z $output ]
}

@test "copied content from file is not written to stdout by default" {
    echo "test_not_on_stdout" > test_not_on_stdout
    output=`$wclip test_not_on_stdout`
    rm test_not_on_stdout
    [ -z $output ]
}

@test "copied content from stdin is written to stdout with --out option" {
    output=`echo "on stdout" | $wclip --out`
    [ "$output" = "on stdout" ]
}

@test "copied content from file is written to stdout with --out option" {
    echo "test_on_stdout" > test_on_stdout
    output=`$wclip --out test_on_stdout`
    rm test_on_stdout
    [ "$output" = "test_on_stdout" ]
}

@test "copied content from stdin is written to stdout with -o option" {
    output=`echo "on stdout2" | $wclip -o`
    [ "$output" = "on stdout2" ]
}

@test "copied content from file is written to stdout with -o option" {
    echo "test_on_stdout2" > test_on_stdout
    output=`$wclip test_on_stdout -o`
    rm test_on_stdout
    [ "$output" = "test_on_stdout2" ]
}

@test "stdin is copied to clipboard with --secret option" {
    echo "secret_from_std_in" | $wclip --secret
    [ `cat /dev/clipboard` = "secret_from_std_in" ]
}

@test "stdin is copied to clipboard with -s option" {
    echo "s_from_std_in" | $wclip -s
    [ `cat /dev/clipboard` = "s_from_std_in" ]
}

@test "file content is copied to clipboard with --secret option" {
    echo "secret_from_file" > from_file
    echo "do not copy" | $wclip from_file --secret
    rm from_file
    [ `cat /dev/clipboard` = "secret_from_file" ]
}

@test "file content is copied to clipboard with -s option" {
    echo "s_from_file" > from_file
    echo "do not copy" | $wclip from_file -s
    rm from_file
    [ `cat /dev/clipboard` = "s_from_file" ]
}

@test "short options s and o can be combined" {
    output=`echo "on stdout2" | $wclip -so`
    [ "$output" = "on stdout2" ]
}

@test "short options o and s can be combined" {
    output=`echo "on stdout2" | $wclip -os`
    [ "$output" = "on stdout2" ]
}

@test "when called with unknown option exits with non-zero" {
    run $wclip --unknown
    [ "$status" -ne 0 ]
}

@test "when file does not exists exits with non-zero" {
    run $wclip some_non_existent_file
    [ "$status" -ne 0 ]
}

@test "when called with multiple files exits with non-zero" {
    touch file_a
    touch file_b
    run $wclip file_a file_b
    rm file_a file_b
    [ "$status" -ne 0 ]
}
