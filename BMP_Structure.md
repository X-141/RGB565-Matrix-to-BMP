# Overview
The overall structure of the BMP file generated by this repository is quite simple. However, the journey to understanding what actually goes into a BMP file (Hexadecimal reading and all) is a bit ambigious. So! Hopefully, this piece of documentation kinda helps you (and me especially) understand how to build a simple BMP file.

## BMP FILE HEADER
The BMP file header defines some general information about the bitmap. As you can see in the table below, a lot of the information we write in the header makes sense. We need to tell the image processor how to read the data!

The total length of the File Header is 14 bytes.
| Field | Length (bytes) | Notes |
| -- | -- | -- |
| file type | 2 unsigned bytes | Always going to be ***0x4D42*** |
| file size | 4 unsigned bytes | Length of the file itself (BMP FILE HEADER + BMP INFO HEADER + BMP COLOR HEADER + LENGTH OF IMAGE) <sub>1</sub> |
| reserved 1 | 2 unsigned bytes | Unused. Zero'd typically |
| reserved 2 | 2 unsigned bytes | Unused. Zero'd typically |
| offset data | 4 unsigned bytes | Starting point of the actual image data we want the processor to display. In this repo, its always set to ***0x0000008A*** <sub>2</sub>

 1. Generally speaking the equation is always going to be the following: (14 + 40 + 84 + (horizontal * vertical)). However, Depending on the length of the horizontal dimension, the formula is different. If the horizontal dimension is odd, the formula is (14 + 40 + 84 + (horizontal + 2) * width)
 2. If you've read the documentation a couple times, you've likely noticed ***0x0000008A*** is just (14 + 40 + 84) in hexadecimal!

## BMP INFO HEADER
The BMP info header contains a variety of information. Some are easier to understand than others. But! this is a living piece of documentation so information can be added/amended.

The total length of the Info Header is 40 bytes.
| Field | Length (bytes) | Notes |
| -- | -- | -- |
| Header Size | 4 unsigned bytes | Length of this header + the color header. Set as ***0x0000007C*** (124 in decimal) |
| Width | 4 signed bytes | Width of the image we are storing |
| Height | 4 signed bytes | Height of the image we are storing |
| Planes | 2 unsigned bytes | Number of color planes. Set as ***0x0001*** |
| Bit Count | 2 unsigned bytes | Number of bits per pixel. Set as ***0x0010*** (16 bits per pixel) |
| Compression | 4 unsigned bytes | Compression method used. For 16-bit images its used. Set as ***0x00000003***
| Image Size | 4 unsigned bytes | Size of the raw image. (length * width * channel) |
| X Pixels Per Meter | 4 unsigned bytes | Pixels per meter. Set as ***0x00000000*** |
| Y Pixels Per Meter | 4 unsigned bytes | Pixels per meter. Set as ***0x00000000*** |
| Color Used | 4 unsigned bytes | Number of colors in the palette. Set as ***0x00000000***
| Important Colors | 4 unsigned bytes | Number of important colors. Set as ***0x00000000***|

## BMP COLOR HEADER
The color header essentially tells the image processor how to read each pixel stored in the bitmap. This is essential (especially given the specific RBG565 format) in order for our image to look correct!

Because we are using the RGB565 format, that means each pixel needs to be 16 bits in length. And for each of those pixels, three distinct bit subset represent a color. How those color values are stored follows the masking values below.

The total length of the Color Header is 84 bytes.
| Field | Length (bytes) | Notes |
| -- | -- | -- |
| Red Mask | 4 unsigned bytes | Which set of bits represent the color red. Set as ***0x0000f800*** <sub>1</sub>
| Green Mask | 4 unsigned bytes | Which set of bits represent the color green. Set as ***0x000007E0*** <sub>2</sub>
| Blue Mask | 4 unsigned bytes | Which set of bits represent the color blue. Set as ***0x0000001F*** <sub>3</sub>
| Alpha Mask | 4 unsigned bytes | Which set of bits represent transparenct. Not used. Set as ***0x00000000***
| Unused | 68 unsigned bytes | Unused space in the color header. All set to ***0x00***.

 1. The first 5 bits represent the color red:           1111100000000000
 2. The subsequent 6 bits represent the color green:    0000011111100000
 3. The last 5 bits represent the color blue:           0000000000011111

## Pixel Storage
Storing pixels is a fairly straight forward process within the context of this repo. However, there are two ground rules:
 1. The pixels are stored from bottom-up left-right.
 2. If the horizontal dimension is odd, we need add 2 additional bytes to the array before iterating to the next row.

Thankfully, there is not much else to detail about this process. 

**Side Note:** In older forms of this repository, a lot of work was required to convert the matrix into a 16 bit value. This was due to the color values being stored in seperate channels. However, I've since shrunk the complexity to instead store color data in the correct format in a 16 bit value.

### Citations
Always gotta cite your sources!
 * https://en.wikipedia.org/wiki/BMP_file_format
 * https://cdn.hackaday.io/files/274271173436768/Simplified%20Windows%20BMP%20Bitmap%20File%20Format%20Specification.htm