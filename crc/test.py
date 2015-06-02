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

from subprocess import call, Popen, PIPE
from sys import argv, exit
from itertools import product

assert(len(argv) == 3)
assert(isinstance(int(argv[1]), int))
assert(isinstance(int(argv[2]), int))

call(["make"])

bit_perms = product('01', repeat=int(argv[1]))

for i in range(int(argv[2])):
	perm = ''.join(next(bit_perms))
	stdout = Popen('./generator ' + perm, shell=True, stdout=PIPE).stdout
	output = stdout.read()
	call(["./verifier", output])

call(["make", "clean"])