# Jack Schefer, 1/26/16
#
#
from sys  import argv
from time import time
#
###########################################################################
#
def isNeighbor(a,b):
  diff = 0
  for i in range(len(a)):
    if diff > 1: return False
    if a[i] != b[i]: diff += 1
  return diff == 1
  #
#
############################################################################
#
def naive(words):
  #
  graph = {}
  #
  for w in words:
    nbrs = []
    for i in range(len(words)):
      tString = words[i]
      if isNeighbor(w, tString): nbrs.append(tString)
    #
    graph[w] = nbrs
    #
  #
  return graph
  #
#
###########################################################################
#
letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
def reverse(words):
  #
  graph = {}
  wordSet = set(words)
  #wordSet = words
  #
  for w in words:
    #nbrs = set()
    nbrs = []
    for i in range(len(w)):
      for letter in letters:
        newW = w[:i] + letter + w[i + 1:]
        if newW not in nbrs and newW in wordSet and newW != w: nbrs.append(newW)
    #
    #nbrs = list(nbrs)
    nbrs.sort()
    graph[w] = nbrs
  #
  return graph
  #
#
#
#
#
########################################################################
#
#
#
if __name__ == '__main__':
  wordList = open('words.txt').read().split()
  tic = time()
  g1 = naive(wordList)
  toc = time()
  t1 = toc - tic
  print('Naive Approach: ', t1, ' seconds')
  print('abased nbrs: ', g1['abased'])
  #
  tic = time()
  g2 = reverse(wordList)
  toc = time()
  t2 = toc - tic
  print('Reverse Engineered Approach: ', t2, ' seconds')
  print('abased nbrs: ', g2['abased'])
  #
  percent = t2 / t1 * 100
  if g1 == g2: print('Same graph built in ', percent, '% of the time.')
  else: print('Different result')
  #
#
# End of file.
