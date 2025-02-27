use::std::collections::HashSet;
use::std::time::Instant;

fn main() {
    let arrdict = vec!["youtube", "youtube-music", "soundcloud", "bandcamp","piped"];
    let hashset: HashSet<&str> = HashSet::from_iter(arrdict.iter().cloned());
    let tests: Vec<String> = (0..100000)
        .map(|x| arrdict[x % arrdict
            .len()]
            .to_string())
        .collect();

    let mut start = Instant::now();
    let _: Vec<bool> = tests
        .iter()
        .map(|x| arrdict
            .iter()
            .any(|y| x == y))
        .collect();
    let mut end = Instant::now();
    let mut elasped = end - start;
    println!("Linear Check:{}", elasped.as_micros());

    start = Instant::now();
    let _: Vec<bool> = tests
        .iter()
        .map(|x| hashset
            .contains(x.as_str()))
        .collect();
    end = Instant::now();
    elasped = end - start;
    println!("Hashset Check:{}", elasped.as_micros());
}

