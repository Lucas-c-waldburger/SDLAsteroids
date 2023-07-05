//#pragma once
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <iostream>
//
//
//
//
//
//class App
//{
//
//    bool init()
//    {
//
//        bool success = true;
//
//        if (SDL_Init(SDL_INIT_VIDEO) < 0)
//        {
//            std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//            success = false;
//        }
//        else
//        {
//            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
//                std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
//
//            if (!window.create())
//            {
//                std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//                success = false;
//            }
//            else
//            {
//                if (!renderWrapper.create(window()))
//                {
//                    std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
//                    success = false;
//                }
//                else
//                {
//                    renderWrapper.clear();
//
//                    // -------- INIT SDL_IMG -------- //
//                    int imgFlags = IMG_INIT_PNG;
//                    if (!(IMG_Init(imgFlags) & imgFlags))
//                    {
//                        std::cout << "SDL_image could not initialize! SDL_Image Error: " << IMG_GetError() << std::endl;
//                        success = false;
//                    }
//
//                    // -------- INIT SDL_TXT -------- //
//                    if (TTF_Init() == -1)
//                    {
//                        std::cout << "SDL_ttf could not initialize! SDL_TTF error: " << TTF_GetError() << std::endl;
//                        success = false;
//                    }
//                    else
//                    {
//                        ttfFont = TTF_OpenFont("style1.otf", 44); // path, font size
//                        if (!ttfFont)
//                        {
//                            std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
//                            success = false;
//                        }
//                    }
//                }
//            }
//        }
//        return success;
//    }
//
//
//    void close()
//    {
//        // Take in textures to free ( the vector of TextTexture objects )
//
//        TTF_CloseFont(ttfFont);
//        ttfFont = nullptr;
//
//        renderWrapper.destroy();
//        window.destroy();
//
//        TTF_Quit();
//        IMG_Quit();
//        SDL_Quit();
//    }
//};