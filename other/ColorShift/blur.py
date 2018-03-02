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
                                adj = 0
                                if y > 0:
                                        up = input_pixels[x,y-1]
                                        for i in range(0,3):
                                                avg[i] += up[i]
                                        adj+=1
                                if y < height-1:
                                        down = input_pixels[x,y+1]
                                        for i in range(0,3):
                                                avg[i] += down[i]
                                        adj+=1
                                if x > 0:
                                        left = input_pixels[x-1,y]
                                        for i in range(0,3):
                                                avg[i] += left[i]
                                        adj+=1
                                if x < width-1:
                                        right = input_pixels[x+1,y]
                                        for i in range(0,3):
                                                avg[i] += right[i]
                                        adj+=1
                                for i in range(0,3):
                                        avg[i] /= adj
                                        avg[i] = int(avg[i])
                                        if(abs(avg[i] - input_pixels[x,y][i]) >= 20):
                                                avg[i] = 255 - input_pixels[x,y][i];
                                
                                input_pixels[x,y] = tuple(avg)
                print(z);
        for x in range(width):
                        for y in range(height):
                                xm = (x%2 == 0)
                                ym = (y%2 == 1)
                                temp = [];
                                temp.append(input_pixels[x,y][0])
                                temp.append(input_pixels[x,y][1])
                                temp.append(input_pixels[x,y][2])
                                if (xm & ym) & (~xm & ~ym):
                                                temp[0] = 255 - temp[0]
                                                temp[1] = 255 - temp[1]
                                                temp[2] = 255 - temp[2]
                                                input_pixels[x,y] = tuple(temp)
                                
                                output_image.putpixel((x,y),(input_pixels[x,y][0], input_pixels[x,y][1], input_pixels[x,y][2]))
        output_image.save(filename + '_output.png')
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
