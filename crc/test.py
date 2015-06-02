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