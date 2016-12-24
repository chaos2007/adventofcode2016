extern crate crypto;
use crypto::md5::*;
use crypto::digest::Digest;


pub fn calculate_md5(x: &str) -> String {
    let mut sh = Md5::new();
    sh.input_str(x);
    sh.result_str()
}

pub fn return_character(x: &str) -> Option<(char, char)> {
    if x.starts_with("00000") {
        let y: Vec<char> = x.chars().collect();
        Some((y[5], y[6]))
    } else {
        None 
    }
}

pub fn map_number_to_letter(x: char) -> char {
    match x {
        '0' => 'z',
        '1' => 'y',
        '2' => 'x',
        '3' => 'w',
        '4' => 'v',
        '5' => 'u',
        '6' => 't',
        '7' => 's',
        _ => 'r',
    }
}

pub fn generate_password_2(door_id: &str) -> String {
    let mut index: u32 = 0;
    let mut password: String = String::from("zyxwvuts");

    while password.find('z').is_some() || password.find('y').is_some() ||
          password.find('x').is_some() || password.find('w').is_some() ||
          password.find('v').is_some() || password.find('u').is_some() ||
          password.find('t').is_some() || password.find('s').is_some() {
        let test_string = door_id.to_string() + &index.to_string();
        let checksum = calculate_md5(test_string.as_str());
        let result = return_character(checksum.as_str());
        match result {
            Some((index, character)) => {
                let index = map_number_to_letter(index);
                let character = character.to_string();
                let character = character.as_str();
                password = password.replace(index, character);
            }
            None => {}
        }
        index = index + 1;
    }
    password
}

pub fn generate_password_1(door_id: &str) -> String {
    let mut index: u32 = 0;
    let mut password: String = String::from("");
    while password.len() < 8 {
        let test_string = door_id.to_string() + &index.to_string();
        let checksum = calculate_md5(test_string.as_str());
        let result = return_character(checksum.as_str());
        match result {
            Some((character,_)) => {
                password.push(character);
            }
            None => {}
        }
        index = index + 1;
    }
    password
}

#[test]
fn basic_test_1() {
    let number = "abc3231929";
    let digest = calculate_md5(number);
    let control_val = "00000155f8105dff7f56ee10fa9b9abd";
    assert_eq!(control_val, digest);
    assert_eq!(Some(('1', '5')), return_character(control_val));
}

#[test]
fn basic_test_2() {
    let number = "abc5017308";
    let digest = calculate_md5(number);
    let control_val = "000008f82c5b3924a1ecbebf60344e00";
    assert_eq!(control_val, digest);
    assert_eq!(Some(('8', 'f')), return_character(control_val));
}

#[test]
fn basic_test_3() {
    let number = "abc5278568";
    let digest = calculate_md5(number);
    let control_val = "00000f9a2c309875e05c5a5d09f1b8c4";
    assert_eq!(control_val, digest);
    assert_eq!(Some(('f', '9')), return_character(control_val));
}

#[test]
fn basic_test_4() {
    let door_id = "abc";
    let expected_password = "18f47a30";
    let generated_password = generate_password_1(door_id);
    assert_eq!(expected_password, generated_password);
}

#[test]
fn test_part_1() {
    let door_id = "ojvtpuvg";
    let expected_password = "4543c154";
    let generated_password = generate_password_1(door_id);
    assert_eq!(expected_password, generated_password);
}

#[test]
fn basic_test_5() {
    let door_id = "abc";
    let expected_password = "05ace8e3";
    let generated_password = generate_password_2(door_id);
    assert_eq!(expected_password, generated_password);
}

#[test]
fn test_part_2() {
    let door_id = "ojvtpuvg";
    let expected_password = "1050cbbd";
    let generated_password = generate_password_2(door_id);
    assert_eq!(expected_password, generated_password);
}


