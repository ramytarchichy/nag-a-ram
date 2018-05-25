from datetime import datetime

from wordlist import WordList
from bakedwordlist import BakedWordList

t1 = datetime.utcnow()

# Read file (didn't bother optimizing, not sure if it can be made to run faster, though it already only takes a few
# milliseconds) and I don't wanna bother with that)
lines = list()
with open('wordlist_english.txt') as f:
    for line in f:
        lines.append(line.replace('\n', ''))

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
