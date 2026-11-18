from PIL import Image
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="make a tilemap")
    parser.add_argument(
        "infile",
        type=str
    )
    parser.add_argument(
        "outfile",
        type=str
    )
    args = parser.parse_args()
    image = Image.open(args.infile, "r")

    color_table = [
        (0,0,0),
        (0x55,0,0),
        (0xA4,0,0),
        (0xEF,0,0),
    ]


    pixels = []
    out_bytes = bytearray()
    full_byte = 0
    bit = 0

    for tile_y in range(image.size[1]//8):
        for tile_x in range(image.size[0]//8):
            for y in range(8):
                for x in range(8):
                    pixel = image.getpixel(((tile_x*8)+x,(tile_y*8)+y))

                    pixel = color_table.index(tuple(list(pixel)[:-1]))

                    full_byte |= pixel << bit
                    bit += 2
                    if bit == 8:
                        bit = 0
                        out_bytes.append(full_byte)
                        full_byte = 0

    open(args.outfile, "wb").write(out_bytes)