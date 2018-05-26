class BakedWordList:

    def __init__(self, wordlist, phrase):

        self.fingerprints = list()

        # Count letters in anagram phrase
        self.phrase = phrase
        self.phrase_charmap = dict()
        self.phrase_charcount = 0
        for word in phrase:
            self.phrase_charcount += len(word)
            for char in word:
                try:
                    self.phrase_charmap[char] += 1
                except KeyError:
                    self.phrase_charmap[char] = 1

        # Add valid word fingerprints only: O(n)
        for fingerprint in wordlist.fingerprints:
            valid = True
            for k, v in wordlist.fingerprint_charmap[fingerprint].items():
                try:
                    if self.phrase_charmap[k] < v:
                        valid = False
                        break
                except KeyError:
                    valid = False
                    break
            if valid:
                self.fingerprints.append(fingerprint)
            else:
                # Skip words that are too long
                if len(fingerprint) > self.phrase_charcount:
                    break

        # At this point, the wordspace is drastically smaller than the original one, saving us a lot of computation
        # down the line

        # Add fingerprints to set for O(1) lookup: O(n)
        self.fingerprint_set = set(self.fingerprints)

        # Copy necessary data: O(n)
        self.fingerprint_charmap = dict()
        self.fingerprint_words = dict()
        for fingerprint in self.fingerprints:
            self.fingerprint_charmap[fingerprint] = wordlist.fingerprint_charmap[fingerprint]
            self.fingerprint_words[fingerprint] = wordlist.fingerprint_words[fingerprint]
