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
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>


typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;
#define WinWidth 1000
#define WinHeight 1000

int main (int ArgCount, char **Args)
{

    u32 WindowFlags = SDL_WINDOW_OPENGL ;
    SDL_Window *Window = SDL_CreateWindow("OpenGL Test", 0, 0, WinWidth, WinHeight, WindowFlags);
    assert(Window);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);

    b32 Running = 1;
    b32 FullScreen = 0;

    // loading the image from the the file to the memory
    unsigned char * imageData;
    int imageHeight, imageWidth;
    getImageRGBBuffer("./PngItem_370296.png",imageData, &imageWidth, &imageHeight, NULL);

    printf("inside main height is %d and with is %d\n", imageHeight, imageWidth);
    if(imageData == NULL){
      printf("no image loaded\n");
    }


      //pixels data;
      unsigned char * pixels, * pptr;

      pptr = pixels = malloc(imageHeight * imageWidth * 4); int j;
      printf("passed \n");

      int x;
      for(int i=0; i<imageHeight; i++) {
         for(j=0; j<imageWidth; j++) {
              printf("Image data of red %d  \n", *imageData);
             *(pptr++) = *(imageData + j* imageWidth + i*4) ; /*red*/
             *(pptr++) = *(imageData + j* imageWidth + i*4 + 1);  /* green */
             *(pptr++) = *(imageData + j* imageWidth + i*4 + 2);  /* blue */
           }
       }


      while (Running)
      {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
          if (Event.type == SDL_KEYDOWN)
          {
            switch (Event.key.keysym.sym)
            {
              case SDLK_ESCAPE:
                Running = 0;
                break;
              case 'f':
                FullScreen = !FullScreen;
                if (FullScreen)
                {
                  SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
                else
                {
                  SDL_SetWindowFullscreen(Window, WindowFlags);
                }
                break;
              default:
                break;
            }
          }
          else if (Event.type == SDL_QUIT)
          {
            Running = 0;
          }
        }



        glViewport(0, 0, WinWidth, WinHeight);


        //glClearColor(1.f, 0.f, 1.f, 0.f);
        //glClear(GL_COLOR_BUFFER_BIT);


        glDrawPixels(1000, 1000, GL_RGB, GL_UNSIGNED_BYTE, pixels);



        SDL_GL_SwapWindow(Window);
      }
      return 0;
}
