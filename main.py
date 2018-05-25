from datetime import datetime

from wordlist import WordList
from bakedwordlist import BakedWordList
from solver import Solver

from hashlib import md5

# Lists (of bytes) are not hashable, plus since there are only 3 hashes "in" performance loss is negligeable
hashes =[
    'e4820b45d2277f3844eac66c903e84be',
    '23170acc097c24edb98fc5488ab033fe',
    '665e5bcb0c20062fe8abaaf4628bb154'
]
hashes_bytes = [bytes.fromhex(h) for h in hashes]

t1 = datetime.utcnow()

# Read file: O(n)
with open('wordlist_trustpilot.txt') as f:
    lines = [line.rstrip('\n') for line in f]

t2 = datetime.utcnow()

# Process wordlist: O(n log n)
wl = WordList(lines)

t3 = datetime.utcnow()

# Select the necessary words for the given anagram: O(n)
bwl = BakedWordList(wl, 'poultry outwits ants'.split(' '))

t4 = datetime.utcnow()

# Benchmark Results:
print('Fingerprints:', len(bwl.fingerprints))

print('Read File:', (t2 - t1).microseconds/1000, 'ms')
print('Phase 1:', (t3 - t2).microseconds/1000, 'ms')
print('Phase 2:', (t4 - t3).microseconds/1000, 'ms')

# ANAGRAMS!
s = Solver(bwl, 3, 3)
i = 0

t5 = datetime.utcnow()

for anagram in s.generator():
    i += 1
    if md5(' '.join(anagram).encode('utf8')).digest() in hashes_bytes:
        print(anagram)

t6 = datetime.utcnow()

print('Anagrams:', i)
print('Time:', (t6 - t5).seconds + (t6 - t5).microseconds/1000000, 's')
