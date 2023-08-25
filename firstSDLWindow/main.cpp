#include <iostream>
#include <string>
#include "Flags.h"
#include "sdl2.h"
#include "Ship.h"
#include "Asteroid.h"
#include "ObjectDestructionManager.h"
#include "DifficultyManager.h"
#include "BackgroundDecorations.h"


GameFlags flags;

int main(int argc, char* argv[])
{
    try
    {

        sdl2::App app;
        sdl2::Window window("main", SCREEN_WIDTH, SCREEN_HEIGHT);
        sdl2::Renderer renderer(window);

        Ship ship{ renderer, 38, LDPoint{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 } };
        AsteroidGenerator asteroidGenerator(renderer);
        ObjectDestructionManager objectDestructionManager;
        ScoreDisplay::ScoreBoard scoreBoard(renderer);
        BackgroundDecorations::StarMaker starMaker(renderer, 18);
        DifficultyManager difficultyManager{};

        SDL_Event e;
        while (!flags.isSet(quit))
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    flags.setFlag(quit);
                }
            }

            objectDestructionManager.resolveAll(ship, asteroidGenerator);
            if (ship.markedDestroy)
            {
                flags.setFlag(quit);
            }

            else
            {
                scoreBoard.setTotalScore(asteroidGenerator.getNumDestroyed());
                difficultyManager.handleDifficulty(asteroidGenerator, scoreBoard);

                const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
                ship.handleKeyStates(keyStates);

                renderer.clear();

                starMaker.drawAll();
                ship.draw();
                ship.bulletGenerator.drawAll();
                asteroidGenerator.drawAll();
                scoreBoard.draw();



                renderer.present();
            }
        }
    }

    catch (std::runtime_error& e)
    {
        std::cout << e.what() << '\n';
    }


    return 0;
}