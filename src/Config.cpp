#include "Config.h"

namespace Config
{
	namespace Window
	{
		unsigned int width = 1600;
		unsigned int height = 900;
		unsigned int bitsPerPixel = 32;
	}

	namespace Text
	{
		float outlineScale = 0.125f;

		namespace Size
		{
			unsigned int small = 24;
			unsigned int medium = 32;
			unsigned int large = 64;
			unsigned int huge = 96;
		}
	}

	namespace World
	{
		float scale = 8.0f;
	}

	namespace Interface
	{
		float scale = 8.0f;
	}

	namespace Audio
	{
		float soundVolume = 50.0f;
		float musicVolume = 10.0f;
	}
}