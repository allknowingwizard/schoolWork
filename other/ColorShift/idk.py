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
                                a = input_pixels[(x,y)][0]
                                b = input_pixels[(x,y)][1]
                                c = input_pixels[(x,y)][2]

                                avg = [0,0,0]
                                adj = 0
                                if y > 0:
                                        up = input_pixels[x,y-1]
                                        for i in range(0,2):
                                                avg[i] += up[i]
                                        adj+=1
                                if y < height-1:
                                        down = input_pixels[x,y+1]
                                        for i in range(0,2):
                                                avg[i] += down[i]
                                        adj+=1
                                if x > 0:
                                        left = input_pixels[x-1,y]
                                        for i in range(0,2):
                                                avg[i] += left[i]
                                        adj+=1
                                if x < width-1:
                                        right = input_pixels[x+1,y]
                                        for i in range(0,2):
                                                avg[i] += right[i]
                                        adj+=1
                                for i in range(0,2):
                                        avg[i] /= adj
                                input_pixels[(x,y)] = avg
                print(z);
        for x in range(width):
                        for y in range(height):
                                output_image.putpixel((x,y),(int(avg[0]), int(avg[1]), int(avg[2])))
        output_image.save(filename + '_output.bmp')
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
