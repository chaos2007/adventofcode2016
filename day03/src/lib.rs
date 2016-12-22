use std::io::prelude::*;
use std::io::Error;
use std::fs::File;

pub fn validate_triangle(a: (u32, u32, u32)) -> bool {
    if a.0 + a.1 <= a.2 ||
       a.1 + a.2 <= a.0 ||
       a.0 + a.2 <= a.1 {
        false
    } else {
        true
    }
}

pub fn split_string_and_validate(a: &str) -> bool {
    let vec: Vec<u32> = a.split_whitespace().map(|n| n.parse::<u32>().unwrap()).collect();
    validate_triangle((vec[0], vec[1], vec[2]))
}

pub fn count_valid_triangle(filename: &str) -> Result<(usize), Error>{
    let mut f = try!(File::open(filename));
    let mut s = String::new();
    try!(f.read_to_string(&mut s));
    let number = s.lines().filter(|n| split_string_and_validate(n)).count();
    Ok(number)
}

pub fn count_valid_triangles(filename: &str) -> Result<(usize), Error>{
    let mut count = 0;
    let mut f = try!(File::open(filename));
    let mut s = String::new();
    try!(f.read_to_string(&mut s));
    let s: Vec<_> = s.lines().collect();
    for element in 0..(s.len()/3) {
        let el = element*3;
        let one:Vec<u32> = s[el].split_whitespace().map(|n| n.parse::<u32>().unwrap()).collect();
        let two:Vec<u32> = s[el+1].split_whitespace().map(|n| n.parse::<u32>().unwrap()).collect();
        let three:Vec<u32> = s[el+2].split_whitespace().map(|n| n.parse::<u32>().unwrap()).collect();
        if validate_triangle((one[0], two[0], three[0])) {
            count += 1;
        }
        if validate_triangle((one[1], two[1], three[1])) {
            count += 1;
        }
        if validate_triangle((one[2], two[2], three[2])) {
            count += 1;
        }
    }
    Ok(count)
}

#[test]
fn basic_triangle() {
    let x = "1 1 1";
    assert_eq!(true, split_string_and_validate(x));
}

#[test]
fn basic_invalid_triangle() {
    let x = "5 10 25";
    assert_eq!(false, split_string_and_validate(x));
}

#[test]
fn basic_triangles_example() {
    let x = "  606  465   97  ";
    assert_eq!(false, split_string_and_validate(x));
    let y = "  724  441  760  ";
    assert_eq!(true, split_string_and_validate(y));
}

#[test]
fn basic_read_file() {
    let x = count_valid_triangle("src/test1.txt");
    assert_eq!(1, x.unwrap());
}

#[test]
fn test_part1() {
    let x = count_valid_triangle("src/part1.txt");
    assert_eq!(982, x.unwrap());
}

#[test]
fn test_part2() {
    let x = count_valid_triangles("src/part1.txt");
    assert_eq!(1826, x.unwrap());
}

