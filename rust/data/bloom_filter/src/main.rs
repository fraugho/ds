mod bloom_filter;
use bloom_filter::*;
fn main() {
    let mut bloom = BloomFilter::new(8);
    bloom.insert(1);
    bloom.insert(2);
    bloom.insert(3);
    println!("1: {}", bloom.is_in(1));
    println!("2: {}", bloom.is_in(2));
    println!("3: {}", bloom.is_in(3));
    println!("4: {}", bloom.is_in(4));
    println!("5: {}", bloom.is_in(5));
}
