pub struct BloomFilter{
    data: Vec<u8>,
}

impl BloomFilter{
    pub fn new(len: usize)->Self{
        BloomFilter{
            data: vec![0;(len/8) + 1],
        }
    }
    pub fn insert(&mut self, input: usize){
        for hash in self.hash(input){
            self.data[hash / 8] |= 0x80 >> (hash % 8);
        }
    }
    pub fn is_in(&self, input: usize)->bool{
        for hash in self.hash(input){
            if (self.data[hash / 8] & (0x80 >> (hash % 8))) == 0{
                return false;
            }
        }
        return true;
    }
    pub fn hash(&self, input: usize)-> [usize; 3]{
        let len = self.data.len() * 8;
        return [(input * 123) % len, (input * 456) % len, (input * 789) % len];
    }
}
