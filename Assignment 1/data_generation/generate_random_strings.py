#generate n random strings with average string length a, plus or minus v
# Written by Alex Finkel 
#July 2013


from sys import argv, exit

if len(argv) != 4:
	print "Usage: python generate_random_strings.py n avg_string_length plus_or_minus_length"
	exit()
else:
	n = int(argv[1])
	a = int(argv[2]) # average string length
	v = int(argv[3]) # average variance, i.e. plus or minus this number

choices = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_123456789+-/<>"

from random import randint

def nextchoice():
	return choices[randint(0, len(choices))-1]

def nextstring():
	string = ""
	var = randint(-v, v)
	n_choices = max(1, a + var)
	for i in range(0, n_choices):
		string += nextchoice()
	return string

while n > 0:
	n -= 1
	print nextstring()
