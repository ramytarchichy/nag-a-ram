from datetime import datetime

from wordlist import WordList
from bakedwordlist import BakedWordList
from solver import Solver

t1 = datetime.utcnow()

# Read file: O(n)
with open('wordlist_english.txt') as f:
    lines = [line.rstrip('\n') for line in f]

t2 = datetime.utcnow()

# Process wordlist: O(n log n)
wl = WordList(lines)

t3 = datetime.utcnow()

# Select the necessary words for the given anagram: O(n)
bwl = BakedWordList(wl, ['anagram'])

t4 = datetime.utcnow()

# Benchmark Results:
print('Fingerprints:', len(bwl.fingerprints))

print('Read File:', (t2 - t1).microseconds/1000, 'ms')
print('Phase 1:', (t3 - t2).microseconds/1000, 'ms')
print('Phase 2:', (t4 - t3).microseconds/1000, 'ms')

# ANAGRAMS!
s = Solver(bwl, 1, 3)
i = 0

t5 = datetime.utcnow()

for anagram in s.generator():
    i += 1

t6 = datetime.utcnow()

print('Anagrams:', i)
print('Time:', (t6 - t5).microseconds/1000, 'ms')
