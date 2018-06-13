#include "TextPost.h"

#include "TextPost.h"

TextPost::TextPost(const size_t ID, const char * text) : Post(ID, text) {}

TextPost::~TextPost() {}

void TextPost::visualize()
{
	const char * temp = createPostName();
	std::ofstream file(temp);
	if (file.is_open())
	{
		file << content << "\n";
	}
	file.close();

	delete[] temp;
}

Post * TextPost::clone()
{
	return new TextPost(*this);
}
