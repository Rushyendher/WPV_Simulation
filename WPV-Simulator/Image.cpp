#include "Image.h"
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;


Image::Image(const size_t id, const int w, const int h, const char * img) 
	: width(w),height(h),imageId(id)
{
	int len = strlen(img) + 1;

	imgData = new char[len];
	strcpy_s(imgData,len,img);
	ConvertTo2D();
}

void Image::ConvertTo2D()
{

	image2Ddata = new char*[height+1];

	for (int i = 0; i <= height; i++)
	{
		image2Ddata[i] = new char[width+1];
		for (int j = 0; j <= width; j++)
		{
			image2Ddata[i][j] = imgData[j];
		}
	}
}

size_t Image::GetImageId() const
{
	return imageId;
}

int Image::GetWidth() const
{
	return width;
}

int Image::GetHeight() const
{
	return height;
}

char * Image::GetImgData() const
{
	return imgData;
}

int Image::SetWidth(const int & val)
{
	try
	{
		if (val <= 0)
			throw "Width cannot be neagtive or zero";
		width = val;
	}
	catch (const char *msg)
	{
		cout << msg << std::endl;
	}
	return width;
}

int Image::SetHeight(const int & val)
{
	try
	{
		if (val <= 0)
			throw "Height cannot be neagtive or zero";
		height = val;
	}
	catch (const char *msg)
	{
		cout << msg << std::endl;
	}
	return height;
}

void Image::Rotate()
{
	char **res;
	res = new char*[width+1];
	
	for (int i = 0; i <= width; i++)
	{
		res[i] = new char[height];
	}


	for (int i = 0; i <= height; i++)
	{
		char *track = image2Ddata[i];

		for (int j = 0; j <= width; j++)
		{
			res[j][i] = track[j];
		}
	}

	int temp = width;
	width = height;
	height = temp;

	image2Ddata = new char*[width + 1];
	for (int i = 0; i <= width; i++)
	{
		image2Ddata[i] = new char[height + 1];
	}

	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			image2Ddata[i][j] = res[i][j];
		}
	}
}

Image::~Image()
{
	delete[] imgData;
}
