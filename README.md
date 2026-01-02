# Optimization found
1. Use `stat <filename>` for fast O(1) `wc -c` instead of scan the whole file
2. Use a lookup table to check for spaces
3. Use a buffer `fread()` instead of fgetc(). 2048 * 2048 seems good
4. Remove if branch, check for whitespace using a variable
5. Use two direct pointer for traversing inside the buffer

I chose to implement `wc -w` specifically.

# Clone and build
```bash
git clone https://github.com/cnyegun/fastwc.git
cd fastwc
make
```

# How much faster? 
3 times faster on big ASCII files. Here's the steps I used to benchmark my program.

## 1. Create a really big file
Run this script to create a 10G text file filled with random words
```bash 
dict_size=$(wc -c < /usr/share/dict/words)
repeats=$((10737418240 / dict_size + 1))  # 10GB in bytes

for i in $(seq 1 $repeats); do
    cat /usr/share/dict/words
done | head -c 10G > bigfile.txt
```

## 2. Run tests and result 
I assume you have cloned and built fastwc on your machine.

```bash
time ./fastwc bigfile.txt
time wc -w bigfile.txt
```

## Result on my machine
```bash
cnyegun@smooth:~/fastwc$ time ./wc bigfile.txt
1040078199

real	0m6.582s
user	0m5.818s
sys	0m0.719s
```
```bash
cnyegun@smooth:~/fastwc$ time wc -w bigfile.txt
1040078199 bigfile.txt

real	0m17.061s
user	0m16.201s
sys	0m0.759s
```

That is about 2.6 times faster, with only 50 lines of code.
