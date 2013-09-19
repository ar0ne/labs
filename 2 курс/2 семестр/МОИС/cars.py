#!/usr/bin/env python
# -*- coding: utf-8 -*-

import pygame, time, sys
from pygame.locals import *

BLACK = ( 0, 0, 0)
WHITE = ( 255, 255, 255)
GREEN = ( 0, 255, 0)
RED =   ( 255, 0, 0)
PINK =  ( 175, 25, 50)

START_Y = 50

FPS = 50 # m/s


class Block(pygame.sprite.Sprite):
	def __init__(self, color, width, height):
		pygame.sprite.Sprite.__init__(self)
		self.image = pygame.Surface([width, height])
		self.image.fill(color)
		self.rect = self.image.get_rect()

	def update(self,speed):
		self.rect.x += speed


pygame.init()

window_size = (1300, 400)
screen = pygame.display.set_mode(window_size)
pygame.display.set_caption("Симуляция обгона")
clock = pygame.time.Clock()
font = pygame.font.Font(None, 25)

cars_to_left = pygame.sprite.Group()
cars_to_right = pygame.sprite.Group()
all_sprites_list = pygame.sprite.Group()
player_group = pygame.sprite.Group()

width_car = height_car = 30

count_cars  = 3 # число машин в автоколонне

lenght_enemy_cars = width_car * count_cars + ((count_cars - 1) * width_car)

####	 АВТОКОЛОННА(Белая машина)	#####
enemy_cars = Block(BLACK, lenght_enemy_cars, width_car)
enemy_cars.rect.x = window_size[0] - lenght_enemy_cars - width_car*5 		# TODO; Сделать начальный отступ для автоколонны
enemy_cars.rect.y = START_Y

#### 	Красная машина		#######
player = Block(RED, height_car, width_car)
player.rect.x = window_size[0] 
player.rect.y = START_Y

player_group.add(player)

###		Зеленая машина		########
front_cars = Block(GREEN, height_car, width_car)
front_cars.rect.x = 0
front_cars.rect.y = START_Y * 2


# cars_to_left.add(player)
cars_to_left.add(enemy_cars)
cars_to_right.add(front_cars)


all_sprites_list.add(player)
all_sprites_list.add(enemy_cars)
all_sprites_list.add(front_cars)

done = False

speed_left = -1.0		# white
speed_right = 1.0		# green car

speed_player = -1.3
delta_y = 0
pause = False

while not done:
	for event in pygame.event.get():
		if event.type == pygame.QUIT or (event.type == KEYUP and event.key == K_ESCAPE):
			done = True
			break			
		if event.type == KEYUP and event.key == K_SPACE and not pause:
			pause = True
			time.sleep(1)
			pause = False

	screen.fill(WHITE)

	blocks_hit_list_left = pygame.sprite.spritecollide(player, cars_to_left, True)
	blocks_hit_list_right = pygame.sprite.spritecollide(player, cars_to_right, True)

	if len(blocks_hit_list_left) > 0 or len(blocks_hit_list_right) > 0:
		print("Произошла авария!!!")
		speed_left = speed_right = speed_player = delta_y = 0 # SEREEEEEEEEGA
		time.sleep(10)
		break

	# начало обгона автоколонны
	if  enemy_cars.rect.x + lenght_enemy_cars < player.rect.x < enemy_cars.rect.x + lenght_enemy_cars + width_car * 2.5 :
		delta_y = 1

	# окончание обгона
	if player.rect.x  + width_car * 2 <= enemy_cars.rect.x and player.rect.y > enemy_cars.rect.y :
		delta_y = -1

	# на встречке 
	if player.rect.y == START_Y * 2 and player.rect.x > (enemy_cars.rect.x + lenght_enemy_cars/2) or player.rect.y == START_Y and player.rect.x < (enemy_cars.rect.x + lenght_enemy_cars/2):
		delta_y = 0

	# если player вышел за длину дороги
	if player.rect.x + width_car < 0:
		time.sleep(2)
		done = True	

	player.rect.y += delta_y

	cars_to_left.update(speed_left)
	cars_to_right.update(speed_right)   
	player_group.update(speed_player)

	pygame.draw.rect(screen, PINK, [0, 30, window_size[0], 120])		# draw the road

	all_sprites_list.draw(screen)

	####### INFO ########

	text = font.render("Length: " + str(player.rect.x - front_cars.rect.x + width_car) + " m" ,True,BLACK)
	screen.blit(text, [70,200])
	text = font.render("Speed white cars: " + str(FPS*speed_left*(-1)) + " m/s, Length:" + str(lenght_enemy_cars) ,True,BLACK)
	screen.blit(text, [70,240])
	text = font.render("Speed red car: " + str(FPS*speed_player*(-1)) + " m/s" ,True,BLACK)
	screen.blit(text, [70,280])
	text = font.render("Speed green car: " + str(FPS*speed_right) + " m/s" ,True,BLACK)
	screen.blit(text, [70,320])

	########################

	pygame.display.flip()

	clock.tick(FPS)

pygame.quit()
sys.exit()
