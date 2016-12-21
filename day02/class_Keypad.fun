test_suite class_Keypad

setup
end setup

teardown
end teardown

test test_default_key_is_5
    type(Keypad) :: k
    k = Keypad()
    assert_equal('5', get_current_key(k))
end test 

test test_basic_change_key
    type(Keypad) :: k
    k = Keypad()
    call change_key(k, 'U')
    assert_equal('2', get_current_key(k))
    call change_key(k, 'R')
    assert_equal('3', get_current_key(k))
end test 

test test_bounds_checking
    type(Keypad) :: k
    k = Keypad()
    call change_key(k, 'U')
    assert_equal('2', get_current_key(k))
    call change_key(k, 'U')
    assert_equal('2', get_current_key(k))
end test 

test test_parse_line
    type(Keypad) :: k
    k = Keypad()
    call parse_line(k, "ULLLLLLLL")
    assert_equal('1', get_current_key(k))
    call parse_line(k, "RRDDD")
    assert_equal('9', get_current_key(k))
end test

test test_example
    type(Keypad) :: k
    k = Keypad()
    call parse_line(k, "ULL")
    assert_equal('1', get_current_key(k))
    call parse_line(k, "RRDDD")
    assert_equal('9', get_current_key(k))
    call parse_line(k, "LURDL")
    assert_equal('8', get_current_key(k))
    call parse_line(k, "UUUUD")
    assert_equal('5', get_current_key(k))
end test

test test_part2
    type(Keypad) :: k
    k = Keypad(0, 2, keys2)
    call parse_line(k, "U")
    assert_equal('5', get_current_key(k))
end test

end test_suite 


