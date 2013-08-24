#generate n random integers in the range of x to y
# Written by Alex Finkel 
#July 2013


from sys import argv, exit

if len(argv) != 4:
	print "Usage: python generate_random_integers.py n x y"
	exit()
else:
	n = int(argv[1])
	x = int(argv[2])
	y = int(argv[3])

from random import randint

while n > 0:
	n -= 1
	print randint(x, y)
