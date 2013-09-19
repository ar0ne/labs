#! /usr/bin/env python3

from time import sleep
from random import random

def generate(graph, gran):
	for i in range(graph):
		for j in range(gran):
			if i%2 == 0:
				print("Generation of graph: %d of vertex: %d" % (i,j))
			else:
				print("Generation of graph: %d of vertex: %d" % (i-1, j))
			sleep(random())
		sleep(2)
	print('\n >>> K', i, j-i)


def izomorph(graph, gran):
	for i in range(graph):
		for j in range(gran):
			if i%2 == 0:
				print('Check on izomorph...\tK -> %d ->3' % (i))
			else:
				print('Check on izomorph...\tK -> %d ->3' % (i-1))
				
			if random()> 0.7 :
				print('IZOMORPH')
			else:
				print('OK')
			sleep(random())
		sleep(2)

    
if __name__ == '__main__':
    generate(10,5)
    izomorph(10,5)
