from PIL import Image
import math
import argparse
import colorsys
from collections import deque
import time

def main():
        parser = argparse.ArgumentParser(description="Fuck up an image")
        parser.add_argument('filename', type=str, help="File to fuck")
        parser.add_argument('iterations', type=int, help="Number of Interations to Complete");
        args = parser.parse_args()

        filename = args.filename
        iter = args.iterations

        input_image = Image.open(filename).convert()
        width, height = input_image.size

        # Init input pixel list, and modify it to only use appropriate colors
        input_pixels = input_image.load()
        output_image = Image.new(input_image.mode, input_image.size)
        for z in range(iter):
                for x in range(width):
                        for y in range(height):
                                #a = input_pixels[x, y][0] / 255.0
                                #b = input_pixels[x, y][1] / 255.0
                                #c = input_pixels[x, y][2] / 255.0

                                avg = [0,0,0]
                                avg[0] = input_pixels[x,y][0]
                                avg[1] = input_pixels[x,y][1]
                                avg[2] = input_pixels[x,y][2]

                                for i in range(0,3):
                                        #if(avg[i] < 64):
                                        #        if(avg[i] % 2 == 0):
                                        #                avg[i] += 50
                                        #        else:
                                        #                avg[i] -= 50
                                        #elif(avg[i] < 128):
                                        #        if(avg[i] % 2 == 0):
                                        #                avg[i] += 100
                                        #        else:
                                        #                avg[i] -= 100
                                        #elif(avg[i] < 196):
                                        #        if(avg[i] % 2 == 0):
                                        #                avg[i] += 150
                                        #        else:
                                        #                avg[i] -= 150
                                        #else:
                                        #        if(avg[i] % 2 == 0):
                                        #                avg[i] += 200
                                        #        else:
                                        #                avg[i] -= 200
                                        avg[i] = int(3*pow(avg[i],3) + pow(avg[i], 2) -4 * avg[i])
                                        avg[i] %= 256
                                
                                input_pixels[x,y] = tuple(avg)
                                output_image.putpixel((x,y),(input_pixels[x,y][0], input_pixels[x,y][1], input_pixels[x,y][2]))
                print(z);
       # for x in range(width):
       #                 for y in range(height):
       #                         output_image.putpixel((x,y),(input_pixels[x,y][0], input_pixels[x,y][1], input_pixels[x,y][2]))
        output_image.save(filename + '_output.jpg')
        output_image.show()

def get_adj_RGB(color, searched, order, color_size):
        cs = color_size - 1
        adj = []
        for channel in order:
                if color[channel] > 0:
                        c = color[:channel] + (color[channel]-1,) + color[channel+1:]
                        if c not in searched:
                                adj.append(c)
                if color[channel] < cs:
                        c = color[:channel] + (color[channel]+1,) + color[channel+1:]
                        if c not in searched:
                                adj.append(c)
        return adj
if __name__ == '__main__':
        main()
