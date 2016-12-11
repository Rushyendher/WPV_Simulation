#ifndef _IMAGE_H
#define _IMAGE_H

#include<iostream>


extern int totalImages;

class Image
{
private:

	size_t imageId;

	int width;
	int height;
	char *imgData;

	char **image2Ddata;
	void ConvertTo2D();

public:

	Image(const size_t id = 1,const int w = 1, const int h = 1, const char *img = "IMAGE");



	size_t GetImageId() const;
	int GetWidth() const;
	int GetHeight() const;
	char * GetImgData() const;

	int SetWidth(const int &val);
	int SetHeight(const int &val);

	void Rotate();

	void Display2dImage()
	{
		std::cout << "Id: " << imageId << "- Total images: " << totalImages;
		std::cout << std::endl;
		for (int i = 0; i < height; i++)
		{
			std::cout << "\t\t\t\t";
			for (int j = 0; j < width; j++)
			{
				std::cout << image2Ddata[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void Display2dImageForGV()
	{
		std::cout << imageId;
		std::cout << std::endl;
		for (int i = 0; i < height; i++)
		{
			std::cout << "\t";
			for (int j = 0; j < width; j++)
			{
				std::cout << image2Ddata[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}


	~Image();
};

#endif