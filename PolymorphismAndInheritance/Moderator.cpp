#include "Moderator.h"

Moderator::Moderator() : User() {}

Moderator::Moderator(const char * name, const size_t years)
: User(name, years)
{
	posts = nullptr;
	number_of_posts = 0;
}

Moderator::Moderator(const User & other) : User(other) {}

Moderator & Moderator :: operator=(const Moderator & other)
{
	if (this != &other)
	{
		clear();
		User::operator=(other);
	}
	return *this;
}

void Moderator::removeUsersPost(User & user, const size_t ID)
{
	user.removePost(ID);
}

void Moderator::blockUser(const char * name, char ** blocked_users, size_t & number_of_blocked_users)
{
	blocked_users[number_of_blocked_users] = new char[strlen(name) + 1];
	strcpy_s(blocked_users[number_of_blocked_users], strlen(name) + 1, name);
}

void Moderator::unblockUser(const char * name, char ** blocked_users, size_t & number_of_blocked_users)
{
	for (size_t i = 0; i < number_of_blocked_users; i++)
	{
		if (strcmp(name, blocked_users[i]) == 0)
		{
			for (size_t j = i; j < number_of_blocked_users - 1; j++)
			{
				delete[] blocked_users[j];	
				blocked_users[j] = new char[strlen(blocked_users[j + 1]) + 1];
				strcpy_s(blocked_users[j], strlen(blocked_users[j + 1]) + 1, blocked_users[j + 1]);
			}
			number_of_blocked_users--;
			break;
		}

	}
}