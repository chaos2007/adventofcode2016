use std::io::prelude::*;
use std::io::Error;
use std::fs::File;
//#[macro_use] extern crate log;

pub fn validate_triangle(a: &str) -> bool {
    let vec: Vec<u32> = a.split_whitespace().map(|n| n.parse::<u32>().unwrap()).collect();
    if vec[0] + vec[1] <= vec[2] {
        false
    } else if vec[1] + vec[2] <= vec[0] {
        false
    } else if vec[0] + vec[2] <= vec[1] {
        false
    } else {
        true
    }
}

pub fn count_valid_triangle(filename: &str) -> Result<(usize), Error>{
    let mut f = try!(File::open(filename));
    let mut s = String::new();
    try!(f.read_to_string(&mut s));
    let number = s.lines().filter(|n| validate_triangle(n)).count();
    Ok(number)
}

#[test]
fn basic_triangle() {
    let x = "1 1 1";
    assert_eq!(true, validate_triangle(x));
}

#[test]
fn basic_invalid_triangle() {
    let x = "5 10 25";
    assert_eq!(false, validate_triangle(x));
}

#[test]
fn basic_triangles_example() {
    let x = "  606  465   97  ";
    assert_eq!(false, validate_triangle(x));
    let y = "  724  441  760  ";
    assert_eq!(true, validate_triangle(y));
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
fn test_new_triangle() {

}

#[test]
fn test_part2() {
    let x = count_valid_triangle("src/part1.txt");
    assert_eq!(982, x.unwrap());
}

