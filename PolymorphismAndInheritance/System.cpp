#include "System.h"

size_t System::post_ID_count = 0;

System::System(const char * name, const size_t years)
: admin(name, years),
users(nullptr),
users_cnt(0),
moderators(nullptr),
moderators_cnt(0),
posts(nullptr),
number_of_posts(0),
blocked_users(nullptr),
blocked_users_cnt(0)
{}

size_t System::getPostNumber()
{
	return post_ID_count++;
}

void System::clear()
{
	delete[] users;
	users = nullptr;
	delete[] moderators;
	moderators = nullptr;
	for (size_t i = 0; i < number_of_posts; i++)
	{
		delete posts[i];
	}
	delete[] posts;
	posts = nullptr;
	for (size_t i = 0; i < blocked_users_cnt; i++)
	{
		delete[] blocked_users[i];
	}
	delete[] blocked_users;
	blocked_users = nullptr;
}

System::~System()
{
	clear();
}

int System::checkIfUserExists(const char * name) const
{
	for (size_t i = 0; i < users_cnt; i++)
	{
		if (strcmp(users[i].getName(), name) == 0)
			return i;
	}
	return -1;
}

int System::checkIfModeratorExists(const char * name) const
{
	for (size_t i = 0; i < moderators_cnt; i++)
	{
		if (strcmp(moderators[i].getName(), name) == 0)
			return i;
	}
	return -1;
}

void System::resizeUsers(const size_t newSize)
{
	User * temp = users;
	users = new User[newSize];
	for (size_t i = 0; i < users_cnt; i++)
	{
		users[i] = temp[i];
	}
	delete[] temp;
}

void System::addUser(const char * a_name, const char * name, const size_t years)
{
	if (strcmp(a_name, admin.getName()) != 0)
	{
		std::cerr << "No such user : " << a_name << std::endl;
		return;
	}
	int userID = checkIfUserExists(name);
	int modID = checkIfModeratorExists(name);
	if (userID == -1 && modID == -1 &&
		(strcmp(name, admin.getName()) != 0))
	{
		resizeUsers(users_cnt + 1);
		admin.addUser(users, name, years, users_cnt);
		users_cnt++;
		std::cout << name << " created.\n";
	}
	else
	{
		std::cerr << "There is already a user with such name!\n";
	}
}


void System::resizeModerators(const size_t newSize)
{
	Moderator * temp = moderators;
	moderators = new Moderator[newSize];
	for (size_t i = 0; i < moderators_cnt; i++)
	{
		moderators[i] = temp[i];
	}
	delete[] temp;
}

void System::addModerator(const char * a_name, const char * name, const size_t years)
{
	if (strcmp(a_name, admin.getName()) != 0)
	{
		std::cerr << "No such user : " << a_name << std::endl;
		return;
	}
	int userID = checkIfUserExists(name);
	int modID = checkIfModeratorExists(name);
	if (userID == -1 && modID == -1 &&
		(strcmp(name, admin.getName()) != 0))
	{
		resizeModerators(moderators_cnt + 1);
		admin.addNewModerator(moderators, name, years, moderators_cnt);
		moderators_cnt++;
		std::cout << name << " created.\n";
	}
	else
	{
		std::cerr << "There is already a user with such name!\n";
	}
}

void System::removeUser(const char * a_name, const char * name)
{
	if (strcmp(a_name, admin.getName()) != 0)
	{
		std::cerr << "No such user : " << a_name << std::endl;
		return;
	}

	int userID = checkIfUserExists(name);
	int modID = checkIfModeratorExists(name);

	if (userID >= 0)
	{
		admin.removeUser(users, name, users_cnt);
		users_cnt--;
		resizeUsers(users_cnt);
		unblockUser(a_name, name); //in case the user is blocked, remove his name from the list of blocked users
		std::cout << name << " removed.\n";
		const size_t * temp = users[userID].getPosts();
		for (size_t i = 0; i < users[userID].getNumberOfPosts(); i++)
		{
			removePost(admin.getName(), temp[i]);
		}
	}
	else if (checkIfModeratorExists(name) >= 0)
	{
		admin.removeModerator(moderators, name, moderators_cnt);
		moderators_cnt--;
		resizeModerators(moderators_cnt);
		unblockUser(a_name, name);
		std::cout << name << " removed.\n";
		const size_t * temp = moderators[modID].getPosts();
		for (size_t i = 0; i < moderators[modID].getNumberOfPosts(); i++)
		{
			removePost(admin.getName(), temp[i]);
		}
	}
	else
	{
		std::cerr << "No such user : " << name << " to be removed!\n";
	}
}

bool System::checkIfBlocked(const char * name)
{
	for (size_t i = 0; i < blocked_users_cnt; i++)
	{
		if (strcmp(blocked_users[i], name) == 0)
			return true;
	}
	return false;
}

void System::resizeBlockedUsers(const size_t newSize)
{
	char ** temp = blocked_users;
	for (size_t i = 0; i < blocked_users_cnt; i++)
	{
		temp[i] = blocked_users[i];
	}

	blocked_users = new char*[newSize];
	for (size_t i = 0; i < blocked_users_cnt; i++)
	{
		blocked_users[i] = new char[strlen(temp[i]) + 1];
		strcpy_s(blocked_users[i], strlen(temp[i]) + 1, temp[i]);
	}

	for (size_t i = 0; i < blocked_users_cnt; i++)
		delete[] temp[i];
	delete[] temp;
}

void System::blockUser(const char * blocker, const char * name)
{
	int modID = checkIfModeratorExists(blocker);
	if (modID == -1 && strcmp(blocker, admin.getName()) != 0)
	{
		std::cerr << "No such user : " << blocker << std::endl;
		return;
	}

	if (checkIfBlocked(name))
	{
		std::cerr << "User has already been blocked!\n";
		return;
	}

	if (modID >= 0)
	{
		resizeBlockedUsers(blocked_users_cnt + 1);
		moderators[modID].blockUser(name, blocked_users, blocked_users_cnt);
		blocked_users_cnt++;
		std::cout << blocker << " blocked " << name << std::endl;
	}
	else if (strcmp(blocker, admin.getName()) == 0)
	{
		resizeBlockedUsers(blocked_users_cnt + 1);
		admin.blockUser(name, blocked_users, blocked_users_cnt);
		blocked_users_cnt++;
		std::cout << blocker << " blocked " << name << std::endl;
	}
}


void System::unblockUser(const char * unblocker, const char * name)
{
	int modID = checkIfModeratorExists(unblocker);
	if (modID == -1 && strcmp(unblocker, admin.getName()) != 0)
	{
		std::cerr << "No such user : " << unblocker << std::endl;
		return;
	}
	if (modID != -1)
	{
		moderators[modID].unblockUser(name, blocked_users, blocked_users_cnt);
		resizeBlockedUsers(blocked_users_cnt);
	}
	else
	{
		admin.unblockUser(name, blocked_users, blocked_users_cnt);
		resizeBlockedUsers(blocked_users_cnt);
	}


}
void System::resizePosts(const size_t newSize)
{
	Post ** temp = new Post*[newSize];
	for (size_t i = 0; i < number_of_posts; i++)
	{
		temp[i] = posts[i];
	}
	delete[] posts;
	posts = temp;
}

void System::addPost(const char * user, const char * type, const char * text, const size_t ID)
{
	if (checkIfBlocked(user))
	{
		std::cerr << "Post not created - user blocked!\n";
		return;
	}
	int userID = checkIfUserExists(user);
	int modID = checkIfModeratorExists(user);
	Post ** temp = new Post*[1];
	if (userID >= 0 || modID >= 0 || strcmp(user, admin.getName()) == 0)
	{
		if (strcmp(type, "[image]") == 0)
			temp[0] = new ImagePost(ID, text);
		if (strcmp(type, "[url]") == 0)
			temp[0] = new LinkPost(ID, text);
		if (strcmp(type, "[text]") == 0)
			temp[0] = new TextPost(ID, text);
	}
	else
	{
		delete temp[0];
		delete[] temp;
		std::cerr << "No such post type!\n";
		return;
	}

	if (userID >= 0)
	{
		resizePosts(number_of_posts + 1);
		users[userID].addPost(ID);
		posts[number_of_posts] = temp[0];
		number_of_posts++;
	}
	else if (modID >= 0)
	{
		resizePosts(number_of_posts + 1);
		moderators[modID].addPost(ID);
		posts[number_of_posts] = temp[0];
		number_of_posts++;
	}
	else if (strcmp(user, admin.getName()) == 0)
	{
		resizePosts(number_of_posts + 1);
		admin.addPost(ID);
		posts[number_of_posts] = temp[0];
		number_of_posts++;
	}
	else
	{
		std::cerr << "No such user : " << user << std::endl;
	}
}

void System::removePost(const char * name, const size_t ID)
{
	int postID = -1;
	for (size_t i = 0; i < number_of_posts; i++)
	{
		if (posts[i]->getPostID() == ID)
		{
			postID = i;
			break;
		}
	}
	if (postID == -1)
	{
		std::cerr << "No such post with ID : " << ID << std::endl;
		return;
	}

	if (checkIfBlocked(name))
	{
		std::cerr << "This user has been blocked!\n";
		return;
	}

	bool removed = false;
	for (size_t i = 0; i < users_cnt; i++)
	{
		if (strcmp(users[i].getName(), name) == 0)
		{
			if (users[i].checkForPost(ID) == -1)
			{
				std::cerr << "User does not own this post with ID : " << ID << std::endl;
				return;
			}
			else
			{
				users[i].removePost(ID);
				removed = true;
			}
		}
		break;
	}

	for (size_t i = 0; i < moderators_cnt; i++)
	{
		if (strcmp(moderators[i].getName(), name) == 0)
		{
			for (size_t i = 0; i < users_cnt; i++)
			{
				if (users[i].checkForPost(ID) >= 0)
				{
					users[i].removePost(ID);
					std::cout << "Post " << ID << " removed.\n";
					removed = true;
					break;
				}
			}
			for (size_t i = 0; i < moderators_cnt; i++)
			{
				if (moderators[i].checkForPost(ID) >= 0)
				{
					moderators[i].removePost(ID);
					std::cout << "Post " << ID << " removed.\n";
					removed = true;
					break;
				}
			}
		}
		break;
	}

	if (strcmp(admin.getName(), name) == 0)
	{
		if (admin.checkForPost(ID) >= 0)
		{
			admin.removePost(ID);
			removed = true;
		}
		else
		{
			for (size_t i = 0; i < users_cnt; i++)
			{
				if (users[i].checkForPost(ID) >= 0)
				{
					users[i].removePost(ID);
					removed = true;
					break;
				}
			}
			for (size_t i = 0; i < moderators_cnt; i++)
			{
				if (moderators[i].checkForPost(ID) >= 0)
				{
					moderators[i].removePost(ID);
					removed = true;
					break;
				}
			}
		}
	}

	if (removed)
	{
		for (size_t i = postID; i < number_of_posts - 1; i++)
		{
			delete posts[i];
			posts[i] = posts[i + 1]->clone();
		}
		number_of_posts--;
		resizePosts(number_of_posts);
	}
}

void System::view_post(const size_t ID) const
{
	for (size_t i = 0; i < number_of_posts; i++)
	{
		if (posts[i]->getPostID() == ID)
		{
			posts[i]->visualize();
		}
	}
}

void System::view_all_posts(const char * name) const
{
	if (strcmp(admin.getName(), name) == 0)
	{
		const size_t * temp = admin.getPosts();
		for (size_t j = 0; j < admin.getNumberOfPosts(); j++)
		{
			posts[temp[j]]->visualize();
		}
		return;
	}

	for (size_t i = 0; i < users_cnt; i++)
	{
		if (strcmp(users[i].getName(), name) == 0)
		{
			const size_t * temp = users[i].getPosts();
			for (size_t j = 0; j < users[i].getNumberOfPosts(); j++)
			{
				posts[temp[j]]->visualize();
			}
			return;
		}
	}

	for (size_t i = 0; i < moderators_cnt; i++)
	{
		if (strcmp(moderators[i].getName(), name) == 0)
		{
			const size_t * temp = moderators[i].getPosts();
			for (size_t j = 0; j < moderators[i].getNumberOfPosts(); j++)
			{
				posts[temp[j]]->visualize();
			}
			return;
		}
	}
}

void System::printYoungest() const
{
	size_t youngestUserIndex = 1024; // :)
	size_t youngestModeratorIndex = 1024; // :)
	if (users_cnt > 0)
	{
		youngestUserIndex = 0;
		for (size_t i = 1; i < users_cnt; i++)
		{
			if (users[i].getYears() < users[youngestUserIndex].getYears())
			{
				youngestUserIndex = i;
			}
		}
	}
	if (moderators_cnt > 0)
	{
		youngestModeratorIndex = 0;
		for (size_t i = 1; i < moderators_cnt; i++)
		{
			if (moderators[i].getYears() < users[youngestModeratorIndex].getYears())
			{
				youngestModeratorIndex = i;
			}
		}
	}
	if (users_cnt > 0 && moderators_cnt == 0)
	{
		std::cout << "Youngest : " << users[youngestUserIndex].getName() << " , " << users[youngestUserIndex].getYears() << std::endl;
	}
	else if (users_cnt == 0 && moderators_cnt > 0)
	{
		std::cout << "Youngest : " << moderators[youngestUserIndex].getName() << " , " << moderators[youngestUserIndex].getYears() << std::endl;
	}
	else if (users_cnt > 0 && moderators_cnt > 0)
	{
		if (users[youngestUserIndex].getYears() < moderators[youngestModeratorIndex].getYears())
		{
			std::cout << "Youngest : " << users[youngestUserIndex].getName() << " , " << users[youngestUserIndex].getYears() << std::endl;
		}
		else
		{
			std::cout << "Youngest : " << moderators[youngestUserIndex].getName() << " , " << moderators[youngestUserIndex].getYears() << std::endl;
		}
	}
	else
	{
		std::cout << "Youngest : " << std::endl;
	}

}
void System::printOldest() const
{
	int oldestUserIndex = -1;
	int oldestModeratorIndex = -1;
	if (users_cnt > 0)
	{
		oldestUserIndex = 0;
		for (size_t i = 1; i < users_cnt; i++)
		{
			if (users[i].getYears() > users[oldestUserIndex].getYears())
			{
				oldestUserIndex = i;
			}
		}
	}
	if (moderators_cnt > 0)
	{
		oldestModeratorIndex = 0;
		for (size_t i = 1; i < moderators_cnt; i++)
		{
			if (moderators[i].getYears() > users[oldestUserIndex].getYears())
			{
				oldestModeratorIndex = i;
			}
		}
	}
	if (users_cnt > 0 && moderators_cnt == 0)
	{
		std::cout << "Oldest : " << users[oldestUserIndex].getName() << " , " << users[oldestUserIndex].getYears() << std::endl;
	}
	else if (users_cnt == 0 && moderators_cnt > 0)
	{
		std::cout << "Oldest : " << moderators[oldestUserIndex].getName() << " , " << moderators[oldestUserIndex].getYears() << std::endl;
	}
	else if (users_cnt > 0 && moderators_cnt > 0)
	{
		if (users[oldestUserIndex].getYears() > moderators[oldestModeratorIndex].getYears())
		{
			std::cout << "Oldest : " << users[oldestUserIndex].getName() << " , " << users[oldestUserIndex].getYears() << std::endl;
		}
		else
		{
			std::cout << "Oldest : " << moderators[oldestUserIndex].getName() << " , " << moderators[oldestUserIndex].getYears() << std::endl;
		}
	}
	else
	{
		std::cout << "Oldest : " << std::endl;
	}
}

	
void System::info() const
{
	std::cout << "There are " << users_cnt + moderators_cnt + 1 << "users : " << std::endl;
	std::cout << admin.getName() << " - Administrator, " << admin.getNumberOfPosts() << " posts." << std::endl;
	for (size_t i = 0; i < moderators_cnt; i++)
	{
		std::cout << moderators[i].getName() << " - Moderator, " << moderators[i].getNumberOfPosts() << " posts." << std::endl;
	}
	for (size_t i = 0; i < users_cnt; i++)
	{
		std::cout << users[i].getName() << " - User, " << users[i].getNumberOfPosts() << " posts." << std::endl;
	}
	if (blocked_users_cnt > 0)
	{
		std::cout << "There are " << blocked_users_cnt << " blocked users." << std::endl;
	}
	else
	{
		std::cout << "There aren't any blocked users!" << std::endl;
	}
	printYoungest();
	printOldest();
}