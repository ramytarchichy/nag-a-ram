from nagaram import get_fingerprint

# Before you point out that I can make this faster by taking into account the phrase to generate anagrams for,
# this was actually originally built that way, but later modified under the assumption that the wordlist would not
# need to be modified often, but the phrase would. Therefore we try to move as much of the optimization and
# pre-processing to this stage, despite the fact that this will result in more overall computation required.

class WordList:

    def __init__(self, wordlist):

        # Remove duplicates: O(n)
        seen = set()
        words = [x for x in wordlist if not (x in seen or seen.add(x))]

        # Sort words from shortest to longest, which will allow us to skip all words that don't fit anymore: O(n log n)
        words.sort(key=len)

        # Pre-process words
        self.fingerprint_charmap = dict()
        self.fingerprint_words = dict()
        self.fingerprints = list()

        fingerprint_set = set()

        for word in words:

            # Generate word's anagram fingerprint: O(w log w), but negligeable since words aren't that long
            fingerprint = get_fingerprint(word)

            # Use a hash table to find single-word anagrams in O(1).
            try:
                self.fingerprint_words[fingerprint].append(word)
            except KeyError:
                self.fingerprint_words[fingerprint] = [word]

            # Stuff that only needs to be processed once for each anagram fingerprint
            if fingerprint not in fingerprint_set:

                # Count characters: O(w)
                word_letters = dict()
                for char in fingerprint:
                    try:
                        word_letters[char] += 1
                    except KeyError:
                        word_letters[char] = 1

                # Save this for later
                self.fingerprint_charmap[fingerprint] = word_letters

                # Add to set so we don't have to re-process it, and to list for iteration at generation time
                self.fingerprints.append(fingerprint)
                fingerprint_set.add(fingerprint)
