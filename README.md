# nag-a-ram

**nag-a-ram** is a fast anagram solving algorithm, allowing for extremely fast
and efficient anagram generation. It was originally made as a submission to the
[Trustpilot Anagram Challenge](https://followthewhiterabbit.trustpilot.com/),
but these days I just maintain and improve it for fun in my free time.

If it isn't obvious already, it's called "nag-a-ram" because "nag a ram" is an
anagram of "anagram". How meta...

Initially written in C, this program was later rewritten in C++ with a
drastically more efficient algorithm. It could probably be improved with more
cache-friendly containers, but that's a project for another time.


## Results

Benchmarking setup:

- **CPU:** Core i7 6700K @ 4.6 GHz
- **RAM:** 2x Kingston KHX2400C15D4/8G at 2400 MT/s in dual-channel mode
- **OS:** Pop!_OS 21.04
- **Kernel:** Linux 5.13.0-7614-generic
- **Compiler:** Clang 12.0.0

Using this algorithm I was able to get all 3 anagrams very quickly:

| Benchmark     | CPU Time     |
| ------------- | ------------ |
| Read File     | 1 **ms**     |
| Parsing       | 10 **ms**    |
| Preprocessing | 15 **ms**    |
| **Easy**      | T+0.11**s**  |
| **Medium**    | T+0.12**s**  |
| **Hard**      | T+4.59**s**  |
| Total Runtime | T+10**s**    |

*Times were averaged over 5 runs.*

* **Total Runtime** indicates the amount of time required to iterate through all
possible anagrams up to 4 words, even after the easy, medium and hard solutions
have all been found already. I included it for benchmarking purposes.

* **T+...** indicates the amount of time elapsed since the proprocessing stage
was done.

The original C version solved the easy & medium anagrams in 0.12 seconds, and
the hard anagram in 4.59 seconds.

The closest thing that I could find for comparison was a
[C++ program](https://github.com/simutisernestas/anagram-search) by a former
coworker that takes around 37 seconds on the same hardware to find the hard
anagram only.


## Build Instructions

### Linux

Make sure OpenSSL (used for MD5 hashing) and Clang (generates slightly faster
code than GCC in this case) are installed:
```
sudo apt install clang libssl-dev
```
Then type the following in a terminal window:
```
git clone https://github.com/OverclockedSanic/nag-a-ram.git
cd nag-a-ram
make
```

### Windows

1. Uninstall Windows
2. Install Linux
3. Build


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
