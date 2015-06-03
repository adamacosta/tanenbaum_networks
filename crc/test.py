"""
CRC error checking

Parameters
----------
argv[1]: int - the message length in bits 
argv[2]: int - the number of messages to generate

Output
----------
Sends messages to a generator program that computes and appends a CRC, 
storing the output in a variable that is then piped to a verifier program 
that outputs "success" if the CRC is 0 and "error" otherwise.
"""

from os import system
from sys import argv
from itertools import product

assert(len(argv) == 3)
assert(isinstance(int(argv[1]), int))
assert(isinstance(int(argv[2]), int))

system("make")

alphabet = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
perms = product(alphabet, repeat=int(argv[1]))

for i in range(int(argv[2])):
	system("./generator " + ''.join(next(perms)) + " | ./verifier")

system("make clean")