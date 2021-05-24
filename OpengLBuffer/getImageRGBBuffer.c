/*
 *  OpengLBuffer
 *  Copyright (C) 2021 Mahdi Abdullah
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <stdio.h>
#include <png.h>
#include <stdlib.h>



int getImageRGBBuffer(char * filename, unsigned char * INdataPointer, int * INwidth, int * INheight, int * INbit_depth){

  void *header = malloc(8);

  //open the file and send the signal
  FILE *fp = fopen(filename, "rb");
  if (!fp)
  {
    printf("filename of that file not found\n");
    return 0;
  }


  // read the file signature
  fread(header, 1, 8, fp);
  int is_png = !png_sig_cmp(header, 0, 8);
  if (!is_png)
  {
      printf("is not png \n" );
      return 0;
  }
  free(header);

  // create png structre and info structre pointer and alloate memory for it
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
  if (!png_ptr)
    return 0;

  // info pointer
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    return 0;
  }

  // end pointer
  png_infop end_info = png_create_info_struct(png_ptr);
  if (!end_info)
  {
    png_destroy_read_struct(&png_ptr, &info_ptr,
        (png_infopp)NULL);
        return 0;
  }

  // set input code for the filename
  png_init_io(png_ptr, fp);
  // say libpng theat i have read 8 byte to cheak the file signature;
  png_set_sig_bytes(png_ptr, 8);


  //read the png with png and info structre
  png_read_png(png_ptr, info_ptr, 0, NULL);

  // extract data from the header
  int width;
  int height;
  int bit_depth;
  int color_type;
  int interlace_method;
  int compression_method;
  int filter_method;
  png_get_IHDR (png_ptr, info_ptr, & width, & height, & bit_depth,
		  & color_type, & interlace_method, & compression_method,
		  & filter_method);

  printf("This image height is %d \nThis image width is %d\nThis image color bit_depth %d\n", height,  width, bit_depth );

  // extracting data buffer from the png image
  png_bytepp rows;
  int rowBytes;


  rowBytes  = png_get_rowbytes (png_ptr, info_ptr);
  printf("The row bytes value is %d\n", rowBytes );
  rows = png_get_rows (png_ptr, info_ptr);
  //INdataPointer = rows;
  *INwidth = width;
  *INheight = height;
  INbit_depth = bit_depth;

  unsigned char * Data = malloc(height * width * 4);

  for (int j = 0; j < height; j++) {
	   int i;
	   png_bytep row;
	   row = rows[j];
	   for (i = 0; i < width; i++) {   // 307692
      int x = j * width + i;
      png_byte pixel;
	     pixel = row[i];
       printf("%d \n", x );
       *(Data + j * width + i * 4 + 1) = pixel;
      }
    }
  INdataPointer = Data;
  printf("DATA 0x%X \n", Data);
  printf("DAta 0x%X \n" ,INdataPointer);

  printf("PNG width %d\n PNG height %d\n", width, height);
  return 1;
}
