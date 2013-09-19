#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
var	n 	m 	images	method
10	19	19	5,8,3	hopfild*

входные образы:
3
1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1
5
1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1
8
1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1
"""
# единичная матрица NxN 
def setI(N):
	I = []
	for i in range(N):
		I.append([])
		for j in range(N):
			if i == j:
				I[i].append(1)
			else:
				I[i].append(0)
	return I

# создаем матрицу  весовых коэффциентом NxN для образа image 
def setImageW(image, size):
	y,w = [],[]
	I = setI(size)		# единичная матрица
	
	for i in range(size):
		if image[i] == 1:
			y.append(1)
		else:
			y.append(-1)

	for i in range(size):
		w.append([])
		for j in range(size):
			w[i].append(y[i]*y[j] - I[i][j])
			
	return w

# создаем сумарную матрицу из N весовых коэф в w
def makeSumW(w, size, N):
	
	sum_w = []
	temp = 0
	for i in range(size):
		sum_w.append([])
		for j in range(size):
			for image in range(N):
				temp += w[image][i][j]
			sum_w[i].append(temp)
			temp = 0
			
	return sum_w


def main():
	imgs = []
	imgs.append([1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1])
	imgs.append([1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1])
	imgs.append([1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1])

	size = len(imgs[0])
	N = len(imgs)

	all_w = []
	for i in range(N):
		all_w.append(setImageW(imgs[i], size))

	w = makeSumW(all_w, size, N)

	# sync mode
	# Y(t+1) = sign(S(t))
	# S(t) = Y(t) * W
	# Y(t+1) равен F( умножения образа Y(t) на матрицу весовых коэф  W)
	
	Y = [1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1]		# Зашумленный образ
	out = [0 for i in range(size)]
	
	last_img = []
	#while Y != imgs[0] and Y != imgs[1] and Y != imgs[2] :
	while Y != last_img:
# 		if last_img == Y :
# 			print("Вероятно произошло зацикливание")
# 			break
		
		last_img = Y
		for i in range(size):
			temp = 0
			for j in range(size):
				temp += w[i][j] * Y[j]
			out[i] = 1 if temp > 0 else 0
		Y = out
		print(Y)
		

	for i in range(len(imgs)):
		if imgs[i] == Y:
			print("Синхронный режим:\nЗашумленный образ распознан как ", i+1,"\n")
			
	# async mode 
	# y[i] = sign(W[i] * Y)
	# i-ый нейрон образа равен F (умножения i-го cтолбца W на образ Y)
	
# 	Y = [0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0]
# 	
# 	while Y != imgs[0] and Y != imgs[1] and Y != imgs[2] :
# 		for i in range(size):		
# 			S = 0
# 			for j in range(len(imgs[0])):	
# 				S += Y[j] * w[j][i]		
# 			S = 1 if S > 0 else 0
# 			
# 			if Y[i] != S:		# если значение образа изменилось
# 				Y[i] = S
# 		print(Y)
# 	
# 	for i in range(len(imgs)):
# 		if imgs[i] == Y:
# 			print("Аcинхронный режим:\nЗашумленный образ распознан как ", i+1,"\n")

if __name__ == '__main__':
	main()