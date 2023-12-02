#pragma once

namespace Config
{
	namespace Window
	{
		extern unsigned int width;
		extern unsigned int height;
		extern unsigned int bitsPerPixel;
	}

	namespace Text
	{
		extern float outlineScale; // TODO move to constants

		namespace Size
		{
			extern unsigned int small;
			extern unsigned int medium;
			extern unsigned int large;
			extern unsigned int huge;
		}
	}

	namespace World
	{
		extern float scale;
	}

	namespace Interface
	{
		extern float scale;
	}

	namespace Audio
	{
		extern float soundVolume;
		extern float musicVolume;
	}
}