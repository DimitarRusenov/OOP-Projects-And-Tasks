#include "Post.h"

void Post::clear()
{
	delete[] content;
	content = nullptr;
}

void Post::copyFrom(const Post & other)
{
	content = new char[strlen(other.content) + 1];
	strcpy_s(content, strlen(other.content) + 1, other.content);
	post_ID = other.post_ID;
}

Post::Post(const size_t ID, const char * text) : post_ID(ID)
{
	content = new char[strlen(text) + 1];
	strcpy_s(content, strlen(text) + 1, text);
}

Post::Post(const Post & other)
{
	copyFrom(other);
}

Post & Post::operator=(const Post & other)
{
	if (this != &other)
	{
		clear();
		copyFrom(other);
	}
	return *this;
}

Post::~Post()
{
	clear();
}

const size_t Post::getPostID() const
{
	return post_ID;
}

const char * Post::getPostContent() const
{
	return content;
}

const char * Post::createPostName() const
{
	size_t cnt = 0;
	size_t tmp = post_ID;
	while (tmp > 0)
	{
		cnt++;
		tmp /= 10;
	}
	tmp = post_ID;
	char * buffer = new char[cnt + 6];
	buffer[cnt] = '.';
	buffer[cnt + 1] = 'h';
	buffer[cnt + 2] = 't';
	buffer[cnt + 3] = 'm';
	buffer[cnt + 4] = 'l';
	buffer[cnt + 5] = '\0';

	while (cnt-- > 0)
	{
		buffer[cnt] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return buffer;
}