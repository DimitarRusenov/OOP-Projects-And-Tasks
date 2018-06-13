#include "User.h"

void User::clear()
{
	delete[] nickname;
	nickname = nullptr;
	delete[] posts;
	posts = nullptr;
}

User::User() : nickname(nullptr), years(0), number_of_posts(0), posts(nullptr) {}

User::User(const char * name, const size_t age)
:	years(age),
	posts(nullptr)
{
	nickname = new char[strlen(name) + 1];
	strcpy_s(nickname, strlen(name) + 1, name);
}

User::User(const User & other)
{
	copyFrom(other);
}

User & User :: operator=(const User & other)
{
	if (this != &other)
	{
		clear();
		copyFrom(other);
	}
	return *this;
}

User::~User()
{
	clear();
}

void User::setNickname(const char * name)
{
	nickname = new char[strlen(name) + 1];
	strcpy_s(nickname, strlen(name) + 1, name);
}

void User::copyFrom(const User & other)
{
	setNickname(other.nickname);
	years = other.years;
	number_of_posts = other.number_of_posts;
	posts = new size_t[number_of_posts];
	for (size_t i = 0; i < number_of_posts; i++)
	{
		posts[i] = other.posts[i];
	}
}

const char * User::getName() const
{
	return nickname;
}
const size_t User::getNumberOfPosts() const
{
	return number_of_posts;
}

const size_t User::getYears() const
{
	return years;
}

const size_t * User:: getPosts() const
{
	return posts;
}
void User::resizePosts(const size_t size)
{
	size_t * temp = posts;
	posts = new size_t[size];
	for (size_t i = 0; i < number_of_posts; i++)
	{
		posts[i] = temp[i];
	}
	delete[] temp;
}

void User::addPost(const size_t ID)
{
	resizePosts(number_of_posts+1);
	posts[number_of_posts++] = ID;
}

int User::checkForPost(const size_t ID)
{
	for (size_t i = 0; i < number_of_posts; i++)
	{
		if (posts[i] == ID)
		{
			return i;
		}
	}
	return -1;
}

void User::removePost(const size_t ID)
{
	int x = checkForPost(ID);
	if (x >= 0)
	{
		for (int i = x; i < number_of_posts - 1; i++)
		{
			posts[i] = posts[i + 1];
		}
	}
	number_of_posts--;
	resizePosts(number_of_posts);
}

void User::print() const
{
	std::cout << nickname << std::endl;
	for (int i = 0; i < number_of_posts; i++)
	{
		std::cout << posts[i] << " ";
	}
	std::cout << std::endl;
}