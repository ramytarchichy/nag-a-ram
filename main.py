from wordlist.wordlist import WordList
from wordlist.bakedwordlist import BakedWordList

print('Start')

lines = list()
with open('wordlist_english.txt') as f:
    for line in f:
        lines.append(line.replace('\n', ''))

wl = WordList(lines)
bwl = BakedWordList(wl, ['anagram'])

print(len(bwl.fingerprints))
