#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

#include "User.h"
#include "Moderator.h"

class Administrator : public Moderator
{
public:
	Administrator();
	Administrator(const char *, const size_t);
	Administrator(const Administrator &);
	Administrator & operator = (const Administrator &);

public:
	void addUser(User * , const char *, const size_t, const size_t); // ok
	void removeUser(User *, const char *, const size_t); // ok

	void addNewModerator(Moderator *,  const char *, const size_t, const size_t);
	void addModeratorFromUser(User & , Moderator *, const size_t);
	void removeModerator(Moderator *, const char *, const size_t);
};

#endif // _ADMINISTRATOR_H_