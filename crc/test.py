"""
CRC error checking

Parameters
----------
argv[1]: int - the message length in bytes 
argv[2]: int - the number of messages to generate

Output
----------
Sends messages to a generator program that computes and appends a CRC, 
storing the output in a variable that is then piped to a verifier program 
that outputs "success" if the CRC is 0 and "error" otherwise.
"""

from os import system
from sys import argv
from random import shuffle

assert(len(argv) == 3)
assert(isinstance(int(argv[1]), int))
assert(isinstance(int(argv[2]), int))

system("make")

alphabet = [c for c in "1234567890abcdefghijklmnopqrstuvwxyz\
                        ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.?!"]

while len(alphabet) < int(argv[1]):
	alphabet *= 2

for i in range(int(argv[2])):
	print "generating random message ..."
	shuffle(alphabet)
	msg = "\"" + ''.join(alphabet[:int(argv[1])]) + "\""
	print "message: " + msg
	system("./generator " + msg + " | ./verifier")

system("make clean")