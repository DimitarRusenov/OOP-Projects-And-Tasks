#include "LinkPost.h"

LinkPost::LinkPost(const size_t ID, const char * text) : Post(ID, text) {}

LinkPost::~LinkPost() {}

void LinkPost::visualize()
{
	const char * temp = createPostName();
	std::ofstream file(temp);
	if (file.is_open())
	{
		file << "<a href=\"" << content << "\"> " << content << " </a>\n";
	}
	file.close();

	delete[] temp;
}

Post * LinkPost::clone()
{
	return new LinkPost(*this);
}
