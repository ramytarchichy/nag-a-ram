class Solver:

    def __init__(self, bwordlist):
        self.wordlist = bwordlist

    def __iter__(self):
        self.fingerprint_index_stack = list()
        self.word_index_stack        = list()
        self.charmap_left_stack      = list()
        return self

    def __next__(self):

        raise NotImplementedError

        #self.fingerprint_index_stack.append(0)
        #self.fingerprint_index_stack[len(self.fingerprint_index_stack)-1] += 1
        #self.fingerprint_index_stack.pop()
        #self.charmap_left_stack.pop()
        #self.word_index_stack = [0] * len(self.fingerprint_index_stack)
        #raise StopIteration

        # Loop decrementally through stack indices
        for i in range(len(self.word_index_stack)-1, -1, -1):

            # If the word index in this position is less than the length of the list of words with the same fingerprint
            if self.word_index_stack[i] < len( self.wordlist.fingerprint_words[self.wordlist.fingerprints[self.fingerprint_index_stack[i]]] ):

                # Get the list of words making up the anagram:
                #  This works by iterating through every position in the stack, getting the fingerprint from that
                #  position, getting the list of words with that fingerprint, selecting the word matching the word index
                #  from that position, adding it to the list, rinsing and repeating.
                result = [self.wordlist.fingerprint_words[self.wordlist.fingerprints[self.fingerprint_index_stack[x]]][self.word_index_stack[x]] for x in range(len(self.word_index_stack))]

                # Increment the word's index so we get a different one next time
                self.word_index_stack[i] += 1

                # Return
                return result

            # Otherwise, set this word's index to 0 and try to increment the one before it
            else:
                self.word_index_stack[i] = 0
