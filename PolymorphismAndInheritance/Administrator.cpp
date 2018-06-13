#include "Administrator.h"

Administrator::Administrator() : Moderator() {}

Administrator::Administrator(const char * name, const size_t years) : Moderator(name, years)
{
	posts = nullptr;
	number_of_posts = 0;
}

Administrator::Administrator(const Administrator & other) :  Moderator(other) {};

Administrator & Administrator :: operator=(const Administrator & other)
{
	if (this != &other)
	{
		User::clear();
		User::operator=(other);
	}
	return *this;
}

void Administrator::addUser(User * users, const char * name, const size_t years, const size_t number_of_users)
{
	User temp(name, years);
	users[number_of_users] = temp;
}

void Administrator::removeUser(User * users, const char * name, const size_t number_of_users)
{
	for (size_t i = 0; i < number_of_users; i++)
	{
		if (strcmp(name, users[i].getName()) == 0)
		{
			for (size_t j = i; j < number_of_users - 1; j++)
			{
				users[j] = users[j + 1];
			}
			break;
		}
	}
}

void Administrator::addNewModerator(Moderator * moderators, const char * name, const size_t years, const size_t number_of_moderators)
{
	Moderator temp(name, years);
	moderators[number_of_moderators] = temp;
}

void Administrator::addModeratorFromUser(User & a, Moderator * moderators, const size_t number_of_moderators)
{
	Moderator temp(a);
	moderators[number_of_moderators] = temp;
}

void Administrator::removeModerator(Moderator * moderators, const char * name, const size_t number_of_moderators)
{
	for (size_t i = 0; i < number_of_moderators; i++)
	{
		if (strcmp(name, moderators[i].getName()) == 0)
		{
			for (size_t j = i; j < number_of_moderators - 1; j++)
			{
				moderators[j] = moderators[j + 1];
			}
			break;
		}
	}
}