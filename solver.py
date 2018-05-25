class Solver:

    def __init__(self, bwordlist, minLength, maxLength):
        self.wordlist = bwordlist
        self.minLength = max(1, minLength)
        self.maxLength = maxLength

    def __iter__(self):
        self.depth = self.minLength
        self.fingerprint_index_stack = list()
        self.word_index_stack        = list()
        self.charmap_left_stack      = list()
        return self

    def __next__(self):

        raise NotImplementedError

        #self.fingerprint_index_stack[depth-1] += 1

        # Breadth-First Search (sort of, since it's not actually searching for something in a node tree, but behaves in
        # a similar way)
        for depth in range(self.depth, self.maxLength+1):
            self.depth = depth

            # Prepare fingerprint index stack
            self.fingerprint_index_stack = [0] * depth

            # Loop decrementally through stack indices
            for f in range(depth-1, -1, -1):

                if self.fingerprint_index_stack[f] < len(self.wordlist.fingerprints):

                    # Increment the word's index so we get a different one next time
                    self.fingerprint_index_stack[f] += 1

                else:
                    self.fingerprint_index_stack[f] = 0










                # Prepare word index stack
                self.word_index_stack = [0] * depth

                # Loop decrementally through stack indices
                for i in range(depth-1, -1, -1):

                    # If the word index in this position is less than the length of the list of words with the same
                    # fingerprint
                    if self.word_index_stack[i] < len( self.wordlist.fingerprint_words[self.wordlist.fingerprints[self.fingerprint_index_stack[i]]] ):

                        # Get the list of words making up the anagram:
                        #  This works by iterating through every position in the stack, getting the fingerprint from
                        #  that position, getting the list of words with that fingerprint, selecting the word matching
                        #  the word index from that position, adding it to the list, rinsing and repeating.
                        result = [self.wordlist.fingerprint_words[self.wordlist.fingerprints[self.fingerprint_index_stack[x]]][self.word_index_stack[x]] for x in range(depth)]

                        # Increment the word's index so we get a different one next time
                        self.word_index_stack[i] += 1

                        # Return
                        return result

                    # Otherwise, set this word's index to 0 and try to increment the one before it
                    else:
                        self.word_index_stack[i] = 0

        raise StopIteration
