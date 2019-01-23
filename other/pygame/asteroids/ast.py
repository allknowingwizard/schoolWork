import sys, pygame, time
pygame.init()

size = width, height = 800, 500
speed = [3, 3]
black = 0, 0, 0

screen = pygame.display.set_mode(size)

ball = pygame.image.load("ball.png")
ballrect = ball.get_rect()

while 1:
    time.sleep(.01)
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()

    ballrect = ballrect.move(speed)
    if ballrect.left < 0 or ballrect.right > width:
        speed[0] = -speed[0]
    if ballrect.top < 0 or ballrect.bottom > height:
        speed[1] = -speed[1]

    screen.fill(black)
    screen.blit(ball,ballrect)
    pygame.display.flip()
def changePosition(nX, nY):
    ballrect.x = nX;
    ballrect.y = nY;
def receivePositionThread():
    while True:
        data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
        pos=data.decode('utf-8')).split(',')
        changePosition(pos[0],pos[1])
