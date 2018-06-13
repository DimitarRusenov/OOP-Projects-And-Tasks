#include "ImagePost.h"

ImagePost::ImagePost(const size_t ID, const char * text) : Post(ID, text) {}

ImagePost::~ImagePost(){}

void ImagePost::visualize()
{
	const char * temp = createPostName();
	std::ofstream file(temp);

	if (file.is_open())
	{
		file << "<img src=\"" << content << "\">\n";
	}

	file.close();

	delete[] temp;
}

Post * ImagePost::clone()
{
	return new ImagePost(*this);
}