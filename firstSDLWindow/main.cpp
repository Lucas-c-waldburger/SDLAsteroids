// ship derives from cinscribed triangle
	// has vector of bullets 


#include <iostream>
#include <string>
#include "Flags.h"
#include "sdl2.h"
#include "LineDraw.h"
#include "CInscribedTriangle.h"

//using namespace Utils;


GameFlags flags;

MousePosLog mousePos;



int main(int argc, char* argv[])
{
	try
	{
		sdl2::App app;
		sdl2::Window window("main", SCREEN_WIDTH, SCREEN_HEIGHT);
		sdl2::Renderer renderer(window);

		/*LineDraw lineDraw{ renderer };*/
		//CircleDraw circle{ renderer, 50, LDPoint{ 200, 200 } };
		CInscribedTriangle circle{ renderer, 50, LDPoint{ 200, 200 } };


		SDL_Event e;
		while (!flags.isSet(quit))
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					flags.setFlag(quit);
				}
				
				//else 
				//{
				//	/*lineDraw.handleEvent(&e);*/

				//	circle.handleEvent(&e);
				//}
			}

			const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
			circle.handleKeyStates(keyStates);


			renderer.clear();

			//if (lineDraw.points.size() > 0)
			//	lineDraw.show();

			//if (lineDraw.lines.size() > 0)
			//	lineDraw.draw();
			

			circle.draw();


			circle.bulletGenerator.drawAll();

			//mousePos.update();
			//if (circle.isInsidePerimeter(mousePos.current))
			//	circle.drawFill(SDL_Color{0, 255, 0});

			//else
			//	circle.drawFill(SDL_Color{ 255, 0, 0 });

			

			renderer.present();

		}
	}

	catch (std::runtime_error& e)
	{
		std::cout << e.what() << '\n';
	}


	return 0;
}