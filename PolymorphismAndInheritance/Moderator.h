#ifndef _MODERATOR_H_
#define _MODERATOR_H_

#include "User.h"

class Moderator : public User
{
public:
	Moderator();
	Moderator(const char *, const size_t);
	Moderator(const User &); //when the user is promoted to a Moderator
	Moderator & operator=(const Moderator &);

public:
	void removeUsersPost(User &, const size_t);
	void blockUser(const char *, char **, size_t &);
	void unblockUser(const char *, char **, size_t &);


};

#endif // _MODERATOR_H_