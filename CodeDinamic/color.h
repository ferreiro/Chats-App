#ifndef color_h
#define color_h
	
	#include <Windows.h>

	typedef enum {
		black, dark_blue, dark_green, dark_cyan, dark_red,
		dark_magenta, dark_yellow, light_gray, dark_gray,
		light_blue, light_green, light_cyan, light_red,
		light_magenta, light_yellow, white
	} tColor;

	void setColor(tColor color);

#endif
