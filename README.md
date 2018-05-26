# nag a ram

**nag a ram** is a fast anagram solving algorithm, allowing for extremely efficient wordlist optimization
and blazing fast anagram generation.

It was made in a couple of days as a submission to the
[Trustpilot Anagram Challenge](https://followthewhiterabbit.trustpilot.com/cs/step3.html),
but can be used for pretty much any anagram.

If you didn't guess, it's called "**nag a ram**" because "nag a ram" is an anagram of the word "anagram".'
How meta...

## How it works

It's pretty complicated, so let's go over a very simplified version, step by step:

### Preprocessing

* We compute and save some data, such as "fingerprints". A fingerprint in this context is just a string
that's just a sorted version of a word. This is useful for looking up anagrams for a single word in O(1).
For example, we might have the words `fast` and `fats`. It we sort the letters, we get `afst` in both cases.
Now we can add this to something like `lookup = dict()`, and whenever we want to get an anagram for `fats`,
we generate a fingerprint for it and we can do `lookup[get_fingerprint('fats')]` and get a list of anagrams,
in constant time
* We then check how many of each letter each fingerprint has, and make sure it fits in the anagram phrase

### Runtime

It behaves sort of like breadth-first search, as in the length in words of the anagram increases after
the anagrams of the previous length have all been found.

So let's assume that right now the length is 3 (as in 3 words). The program will generate combinations
(unordered, no repetitions) made up of the fingerprints found in the preprocessing phase, that's 3-1, so 2
words long. It will then make sure the length (as in characters) is less than the character count of the
phrase, which will allow us to skip a lot of invalid combos without having to do the same (slow) step 2 of
the preprocessing phase. If it passes that check though, it will go through that step. After that, it will
create a fingerprint out of the leftover letters, and check if that exists in the set generated in the
preprocessing stage, and add it to the "fingerprint stack" (the 2-word combo from before, creating a
3-word combo)

If it passes all these checks, it will go ahead and create permutations (ordered, no repetitions) from this
combo. From here on out, no more checks have to be made, while generate a lot of anagrams per checked combo.

Remember that these permutations are still just fingerprints, so for each permutation, it will go through
every fingerprint, get all the words that it corresponds to, and use that to yield anagrams.

You might notice there's no GPU, MultiThreading, or any of that involved. Why? Because honestly it would
cause more headaches in this situation than it is worth, especially since it's already extremely efficient
(see results below).

## Results (Core i7 6700K @ 4.6 GHz)

Using this program we were able to get all 3 anagrams in a ridiculousy efficient manner:
* The whole reading and pre-processing stage took around 450 ms
* The fist 2 anagrams (easy and medium) took an extra 1.5 seconds
* The third anagram (hard) took around 83 more seconds

The closest thing to that I found on GitHub was a [Ruby script](https://github.com/cathper/trustpilot-anagram)
that took 15 minutes to find the anagrams, though I could have easily missed something.

## Further Optimization

In case you wanna squeeze out a bit of extra performance:

* Rewrite in C/C++ (or use Cython, didn't actually test it with that)
* Multithreaded/GPU hashing
* Maybe figure out more ways to predict if the combination is valid beforehand, though that will be very
difficult, especially since that alone might add extra overhead.

## Conclusion

Algorithms are fun. As for Trustpilot, this is a really fun, well made puzzle. Great job team!
