class BakedWordList:


    def __init__(self, wordlist, phrase):

        self.fingerprints = list()

        # Count letters in anagram phrase
        phrase_letters = {}
        phrase_chars = 0
        for word in phrase:
            for char in word:
                phrase_chars += 1
                try:
                    phrase_letters[char] += 1
                except KeyError:
                    phrase_letters[char] = 1

        # Add valid word fingerprints only: O(n)
        for fingerprint in wordlist.fingerprints:
            try:
                valid = True
                for k, v in wordlist.fingerprint_charmap[fingerprint].items():
                    if phrase_letters[k] < v:
                        valid = False
                        break
                if valid:
                    self.fingerprints.append(fingerprint)
                else:
                    # Skip words that are too long
                    if len(fingerprint) > phrase_chars:
                        break
            except KeyError:
                pass

        # At this point, the wordspace is drastically smaller than the original one, saving us a lot of computation
        # down the line

        self.compatible_fingerprints = dict()

        for x in range(len(self.fingerprints)):
            for y in range(x, len(self.fingerprints)):

