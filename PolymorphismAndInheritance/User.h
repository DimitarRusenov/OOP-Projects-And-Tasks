#ifndef _USER_H_
#define _USER_H_

#include <iostream>

class User
{
protected:
	char * nickname;
	size_t years;
	size_t number_of_posts;
	size_t * posts; // holds the IDs of the posts which the user has posted
	
public:
	User();
	User(const char *, const size_t);
	User(const User &);
	User & operator=(const User &);
	~User();

public:
	void setNickname(const char *);

	const char * getName() const;
	const size_t getNumberOfPosts() const;
	const size_t getYears() const;
	const size_t * getPosts() const;
public:
	/* The user only adds the ID of the post which belongs to him, the post itself is stored in the System 
	In case we want to see the user's posts, the user asks the system to give him the posts with the IDs stored in "posts" 
	*/
	void addPost(const size_t);
	void removePost(const size_t);
	
	//Returns -1 if the user does not own the post.
	//Else, returns the index of the post in the "posts" array.
	int checkForPost(const size_t);

protected:
	void resizePosts(const size_t);
	void clear();
	void copyFrom(const User &);

public:
	void print() const;
};

#endif // _USER_H_