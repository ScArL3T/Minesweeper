#include "SplashScreen.h"


SplashScreen::SplashScreen()
{
	//Load image and set temporary window
	img.loadFromFile("data/splash.png");
	window.create(sf::VideoMode(img.getSize().x, img.getSize().y), "", sf::Style::None);
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - img.getSize().x) / 2,
		(sf::VideoMode::getDesktopMode().height - img.getSize().y) / 2));
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::Create(unsigned char opacity, float time)
{
	//SplashScreen
	if (!setTransparent(window.getSystemHandle(), img, opacity))
	{
		//error
	}
	texture.loadFromImage(img);
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		deltaTime = clock.restart();
		elapsedTime += deltaTime;

		if (elapsedTime > sf::seconds(time))
			window.close();


		window.clear();
		window.draw(sprite);
		window.display();
	}
}

bool SplashScreen::setTransparent(HWND hWnd, const sf::Image& image, unsigned char alpha)
{
	const sf::Uint8* pixelData = image.getPixelsPtr();
	HRGN hRegion = CreateRectRgn(0, 0, image.getSize().x, image.getSize().y);

	//Determine the visible region
	for (unsigned int y = 0; y < image.getSize().y; y++)
	{
		for (unsigned int x = 0; x < image.getSize().x; x++)
		{
			if (pixelData[y * image.getSize().x * 4 + x * 4 + 3] == 0)
			{
				HRGN hRegionDest = CreateRectRgn(0, 0, 1, 1);
				HRGN hRegionPixel = CreateRectRgn(x, y, x + 1, y + 1);
				CombineRgn(hRegionDest, hRegion, hRegionPixel, RGN_XOR);
				DeleteObject(hRegion);
				DeleteObject(hRegionPixel);
				hRegion = hRegionDest;
			}
		}
	}

	SetWindowRgn(hWnd, hRegion, true);
	DeleteObject(hRegion);

	//Set the transparency
	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
	return true;
}