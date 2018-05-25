from datetime import datetime

from wordlist import WordList
from bakedwordlist import BakedWordList
from solver import Solver

t1 = datetime.utcnow()

# Read file
with open('wordlist_english.txt') as f:
    lines = [line.rstrip('\n') for line in f]

t2 = datetime.utcnow()

# Process wordlist
wl = WordList(lines)

t3 = datetime.utcnow()

# Select the necessary words for the given anagram
bwl = BakedWordList(wl, ['anagram'])

t4 = datetime.utcnow()

# Benchmark Results:
print('Fingerprints:', len(bwl.fingerprints))

print('Read File:', (t2 - t1).microseconds/1000, 'ms')
print('Phase 1:', (t3 - t2).microseconds/1000, 'ms')
print('Phase 2:', (t4 - t3).microseconds/1000, 'ms')


# ANAGRAMS!
s = Solver(bwl, 2, 4)
for anagram in s:
    print(' '.join(anagram))
