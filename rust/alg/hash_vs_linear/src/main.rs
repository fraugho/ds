use std::collections::HashSet;
use std::time::Instant;
use rand::prelude::*;

fn main() {
    let mut rng = rand::rng();
    let times = 100;
    //let arrdict = vec!["youtube", "youtube-music", "soundcloud", "bandcamp","piped"];
    let arrdict: Vec<String> = (0..5)
        .map(|_| 
            (rng.random::<u64>() % 10000000000).to_string())
        .collect();
    //let arrdict = vec!["youtube", "youtube-music", "soundcloud","bandcamp","piped", "spotify", "thing", "think", "placeholder", "windows"];
    let tests: Vec<String> = (0..100000)
        .map(|x| arrdict[x % arrdict.len()]
            .to_string())
        .collect();

    let mut start = Instant::now();
    for _ in 0..times{
        let _: Vec<bool> = tests
            .iter()
            .map(|x| 
                arrdict
                .iter()
                .any(|y| x == y))
            .collect();
    }
    let mut end = Instant::now();
    let mut elasped = end - start;
    println!("Linear Check:{}", elasped.as_micros() / times);

    let hashset: HashSet<String> = HashSet::from_iter(arrdict.iter().cloned());

    start = Instant::now();
    for _ in 0..times{
        let _: Vec<bool> = tests
            .iter()
            .map(|x| hashset
                .contains(x.as_str()))
            .collect();
    }
    end = Instant::now();

    elasped = end - start;
    println!("Hashset Check:{}", elasped.as_micros() / times);
}
