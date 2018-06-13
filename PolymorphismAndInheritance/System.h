#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "Administrator.h"
#include "Post.h"
#include "ImagePost.h"
#include "LinkPost.h"
#include "TextPost.h"

class System
{
private:
	
	Administrator admin;

	User * users;
	size_t users_cnt;

	Moderator * moderators;
	size_t moderators_cnt;

	Post ** posts;
	size_t number_of_posts;

	char ** blocked_users;
	size_t blocked_users_cnt;

	static size_t post_ID_count;
	
public:
	System(const char *, const size_t); //The system is initialized with an admin.
	System(const System &) = delete;
	System & operator=(const System & other) = delete;
	~System();

public:

	void addUser(const char *, const char *, const size_t);
	void addModerator(const char *, const char *, const size_t);
	void removeUser(const char * ,const char *);
	
	void blockUser(const char *, const char *);
	void unblockUser(const char *, const char *);

	void addPost(const char * user, const char * type, const char * text, const size_t ID);
	void removePost(const char *, const size_t);

	void view_post(const size_t) const;
	void view_all_posts(const char *) const;
	
	void info() const;

	static size_t getPostNumber();

private:
	void resizeUsers(const size_t);
	void resizeModerators(const size_t);
	void resizeBlockedUsers(const size_t);

	void resizePosts(const size_t);	

	int checkIfUserExists(const char *) const;
	int checkIfModeratorExists(const char *) const;

	bool checkIfBlocked(const char *);

	void printYoungest() const;
	void printOldest() const;

	void clear();
};

#endif // _SYSTEM_H_