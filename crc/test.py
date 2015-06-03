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

from subprocess import call, check_output
from sys import argv, stdin
from random import shuffle

assert(len(argv) == 3)
assert(isinstance(int(argv[1]), int))
assert(isinstance(int(argv[2]), int))

call("make")

alphabet = [c for c in "1234567890abcdefghijklmnopqrstuvwxyz\
                        ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.?!"]

while len(alphabet) < int(argv[1]):
	alphabet *= 2

for i in range(int(argv[2])):
	print "generating random message ..."
	shuffle(alphabet)
	msg = "\"" + ''.join(alphabet[:int(argv[1])]) + "\""
	print "message: " + msg
	assert(check_output("./generator " + msg + " | ./verifier",
		   shell=True) == "success: crc correct\n")
	print "success! no errors."
	print "flipping random bits ..."
	assert(check_output("./generator " + msg + " | ./alter | ./verifier",
		   shell=True) == "error: crc not correct\n")
	print "success! error detected.\n"

call(["make", "clean"])