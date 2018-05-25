from itertools import combinations, permutations

class Solver:

    def __init__(self, bwordlist, minLength, maxLength):
        self.wordlist = bwordlist
        self.minLength = max(1, minLength)
        self.maxLength = maxLength

    def generator(self):
        # Breadth-First Search (sort of, since it's not actually searching for something in a node tree, but behaves in
        # a similar way)
        for depth in range(self.minLength, self.maxLength+1):
            too_long = True
            for subset in combinations(self.wordlist.fingerprints, depth):

                valid = True

                # Make sure the amount of characters matches
                charlen = 0
                for fingerprint in subset:
                    charlen += len(fingerprint)
                if charlen <= self.wordlist.phrase_charcount:
                    too_long = False
                if charlen != self.wordlist.phrase_charcount:
                    valid = False

                # Check if the letters themselves match
                if valid:
                    chars_left = self.wordlist.phrase_charmap.copy()
                    for fingerprint in subset:
                        for k, v in self.wordlist.fingerprint_charmap[fingerprint].items():
                            chars_left[k] -= v
                            if chars_left[k] < 0:
                                valid = False
                                break
                        if not valid:
                            break

                # Proceed if it's a valid combination
                if valid:

                    for fingerprint_stack in permutations(subset):

                        # Prepare word index stack
                        word_index_stack = [0] * depth

                        # Loop decrementally through stack indices
                        for i in range(depth-1, -1, -1):

                            # If the word index in this position is less than the length of the list of words with the same
                            # fingerprint
                            while word_index_stack[i] < len(self.wordlist.fingerprint_words[fingerprint_stack[i]]):

                                # Get the list of words making up the anagram:
                                #  This works by iterating through every position in the stack, getting the fingerprint from
                                #  that position, getting the list of words with that fingerprint, selecting the word matching
                                #  the word index from that position, adding it to the list, rinsing and repeating.
                                result = [self.wordlist.fingerprint_words[fingerprint_stack[x]][word_index_stack[x]] for x in range(depth)]

                                # Increment the word's index so we get a different one next time
                                word_index_stack[i] += 1

                                # Return
                                yield result

                            # Set this word's index to 0 and try to increment the one before it
                            word_index_stack[i] = 0
            # No more anagrams
            if too_long:
                break
