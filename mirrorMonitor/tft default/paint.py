import pygame
import random
import serial

import time
i=0
SerialObj = serial.Serial('COM4')
SerialObj.baudrate = 115200  # set Baud rate to 9600
SerialObj.bytesize = 8     # Number of data bits = 8
SerialObj.parity   ='N'    # No parity
SerialObj.stopbits = 1     # Number of Stop bits = 1
# Making canvas
screen = pygame.display.set_mode((900, 700))

# Setting Title
pygame.display.set_caption('GFG Paint')


draw_on = False
last_pos = (0, 0)

# Radius of the Brush
radius = 5
ReceivedString = SerialObj.readline()
print(ReceivedString ,"\n")

def roundline(canvas, color, start, end, radius=1):
	Xaxis = end[0]-start[0]
	Yaxis = end[1]-start[1]
	dist = max(abs(Xaxis), abs(Yaxis))
	for i in range(dist):
		x=ReceivedString/10000
		y=ReceivedString %10000
		#x = int(start[0]+float(i)/dist*Xaxis)
		#y = int(start[1]+float(i)/dist*Yaxis)
		pygame.draw.circle(canvas, color, (x, y), radius)


try:
	while True:
		e = pygame.event.wait()
		
		if e.type == pygame.QUIT:
			raise StopIteration
			
		if e.type == pygame.MOUSEBUTTONDOWN:		
			# Selecting random Color Code
			color = (random.randrange(256), random.randrange(
				256), random.randrange(256))
			# Draw a single circle wheneven mouse is clicked down.
			pygame.draw.circle(screen, color, e.pos, radius)
			draw_on = True
		# When mouse button released it will stop drawing
		if e.type == pygame.MOUSEBUTTONUP:
			draw_on = False
		# It will draw a continuous circle with the help of roundline function.
		if e.type == pygame.MOUSEMOTION:
			if draw_on:
				pygame.draw.circle(screen, color, e.pos, radius)
				roundline(screen, color, e.pos, last_pos, radius)
			last_pos = e.pos
		pygame.display.flip()

except StopIteration:
	pass

# Quit
SerialObj.close()
pygame.quit()
