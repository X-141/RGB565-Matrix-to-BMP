# RGB565-Matrix-to-BMP
Convert RGB565 Matrix data (N * M) into BMP files. RGB565 is commonly used in embedded systems. The purpose of this repo is to allow for easy manipulation.

See BMP_Structure.md for implementation details.

# Build Instructions

 1. Clone this repo
 2. cd RGB565-Matrix-to-BMP
 3. mkdir build
 4. cd build
 5. cmake ..
 6. make -j n # where n is the number of threads you wish to dedicate

After building this project, you should have an executable available that will generate a BMP file.
