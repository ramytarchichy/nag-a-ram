# nag-a-ram

**nag-a-ram** is a fast anagram solving algorithm, allowing for extremely fast and efficient anagram generation. It was made as a submission to the [Trustpilot Anagram Challenge](https://followthewhiterabbit.trustpilot.com/).

If it isn't obvious already, it's called "nag-a-ram" because "nag a ram" is an anagram of "anagram". How meta...


## How it works

### Preprocessing
1. Count the number of each letter's occurrence in the phrase (simplified example: "hello": {'h':1, 'e':1, 'l':2, 'o':1}, total length: 5)
2. Save entire wordlist to memory (calm down, it's under a megabyte, plus it makes processing faster and easier)
3. Split it into words, calculate their lengths, check if they don't have too many/different characters, generate their "fingerprints" (alphabetically sorted list of the word's characters, example: "fast" -> "afst"), and hash the fingerprints (djb2 for hashtable lookup)
4. Iterate through the newly generated wordlist, check if the fingerprint (key) is in the hashtable. If it is, add the word (value) only to the hashtable, allowing us to find the word (and others with the same fingerprint) using the fingerprint. If not, add it to both the hashtable and the fingerprint list
5. Sort the fingerprint list by length (in characters)

### Runtime
1. Generate a combination (unordered, repeating) of n-1 fingerprints, n being the number of words of the resulting anagram
2. Make sure that the length in characters is less than the input's
3. Make sure the combination doesn't have too many of any character
4. Count the remaining characters, use them to generate a fingerprint and hash it
5. Try to find a fingerprint in the hashtable. If found, add it as the last fingerprint in the combination and continue
6. For each combination, generate a permutation (ordered, unrepeating) of n fingerprints
7. For each permutation, iterate through every fingerprint's words (see preprocessing step 4) to generate an anagram
8. MD5, compare, print
9. `goto 1`


## Results

Benchmarking setup:

- **CPU:** Core i7 6700K @ 4.6 GHz
- **RAM:** 2x Kingston KHX2400C15D4/8G at 2400 MT/s in dual-channel mode
- **OS:** Pop!_OS 21.04
- **Kernel:** Linux 5.11.0-7620-generic
- **Compiler:** Clang 12.0.0

Using this algorithm I was able to get all 3 anagrams very quickly:

| Benchmark     | Time         |
| ------------- | ------------ |
| Read File     | 1 **ms**     |
| Preprocessing | 13 **ms**    |
| Easy          | T+0.11**s**  |
| Medium        | T+0.12**s**  |
| Hard          | T+4.59**s**  |
| Total Runtime | T+10**s**    |

*Times were averaged over 5 runs.*

* **Total Runtime** indicates the amount of time required to iterate through all possible anagrams up to 4 words, even after the easy, medium and hard solutions have all been found already. I included it for benchmarking purposes.

* **T+...** indicates the amount of time elapsed since the proprocessing stage was done.

The closest thing that I could find for comparison was a [C++ program by a coworker](https://github.com/simutisernestas/anagram-search) that takes ~37 seconds on the same hardware to find the hard anagram only.


## Build Instructions

### Linux

Make sure OpenSSL (used for MD5 hashing) and clang (generates slightly faster code than gcc in this case) are installed:
```
sudo apt install clang libssl-dev
```
Then type the following in a terminal window:
```
git clone https://github.com/OverclockedSanic/nag-a-ram.git
cd nag-a-ram
make
```

## Usage

### Linux

To try it, just use:
```
$ make run
```
or
```
$ ./nagaram
```

## Conclusion

I *think* I *might* have just found the most efficient single-threaded solution possible. It was very, very fun to solve.
