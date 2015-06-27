import unittest
from subprocess import check_output
from random import shuffle


alphabet = 10 * [c for c in "1234567890abcdefghijklmnopqrstuvwxyz\
                             ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.?!"]


class TestCRC(unittest.TestCase):

	def test_all(self):
		for i in range(8):
			print "generating random message ..."
			shuffle(alphabet)
			msg = "\"" + ''.join(alphabet[:64]) + "\""
			print "message: " + msg
			output = check_output("./generator " + msg + " | ./verifier",
				                  shell=True)
			self.assertEqual(output, "success: crc correct\n")
			print "success! no errors."
			print "flipping random bits ..."
			output = check_output("./generator " + msg + " | ./alter | ./verifier",
				                  shell=True)
			self.assertEqual(output, "error: crc not correct\n")
			print "success! error detected.\n"

if __name__ == '__main__':
	unittest.main()