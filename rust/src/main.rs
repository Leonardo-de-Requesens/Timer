use std::io;

// fn transform_time_to_human() -> String {
//     let hours = 
// }

fn transfrom_human_to_time(time: String) -> i32 {
    let mut temp = 0;
    let mut minutes = 0;
    let mut hours = 0;
    let mut seconds = 0;
    let mut multi = 0;

    for char in time.chars() {
        // let char = String::from(char);
        match char.as_str() {
            b"h" => {
                hours = temp;
                temp = 0;
                multi = 1;
            }
            String::from("m") => {
                minutes = temp;
                temp = 0;
                multi = 1;
            }
            String::from("s") => {
                seconds = temp;
                break;
            }
            _ => {
                temp = temp * multi + char.to_digit(10).unwrap();
            }
        }

    }

    0
}

fn main() {
    let stdin = io::stdin();
    let mut human_time = String::new();
    
    match stdin.read_line(&mut human_time) {
        Ok(_) => println!("Input: {}", human_time),
        Err(e) => println!("Error: {}", e)
    }
}
