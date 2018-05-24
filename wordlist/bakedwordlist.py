class BakedWordList:


    def __init__(self, wordlist, phrase):

        self.fingerprints = list()

        # Count letters in anagram phrase
        phrase_letters = dict()
        phrase_chars = 0
        for word in phrase:
            phrase_chars += len(word)
            for char in word:
                try:
                    phrase_letters[char] += 1
                except KeyError:
                    phrase_letters[char] = 1

        # Add valid word fingerprints only: O(n)
        for fingerprint in wordlist.fingerprints:
            valid = True
            for k, v in wordlist.fingerprint_charmap[fingerprint].items():
                try:
                    if phrase_letters[k] < v:
                        valid = False
                        break
                except KeyError:
                    valid = False
                    break
            if valid:
                self.fingerprints.append(fingerprint)
            else:
                # Skip words that are too long
                if len(fingerprint) > phrase_chars:
                    break

        # At this point, the wordspace is drastically smaller than the original one, saving us a lot of computation
        # down the line
