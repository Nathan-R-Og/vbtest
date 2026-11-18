from PIL import Image
from glob import glob

image = Image.open("buffer_test.png", "r")

color_table = [
    (0,0,0),
    (0x55,0,0),
    (0xA4,0,0),
    (0xEF,0,0),
]


pixels = []

for y in range(image.size[1]):
    for x in range(image.size[0]):
        pixels.append(image.getpixel((x,y)))

v_pixels = []
for x in range(image.size[0]):
    for y in range(image.size[1]):
        i = x+(y*image.size[0])
        v_pixels.append(pixels[i])

out_bytes = bytearray()
full_byte = 0
bit = 0
for pixel in v_pixels:
    full_byte |= pixel << bit
    bit += 2
    if bit == 8:
        bit = 0
        out_bytes.append(full_byte)
        full_byte = 0

open("buffer_test.bin", "wb").write(out_bytes)
