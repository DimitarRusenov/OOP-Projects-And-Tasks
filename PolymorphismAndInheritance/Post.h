#ifndef _POST_H_
#define _POST_H_

#include <iostream>
#include <fstream>

class Post
{
protected:
	size_t post_ID;
	char * content;

public:
	Post(const size_t, const char *);
	Post(const Post & other);
	Post & operator = (const Post & other);
	virtual ~Post();

	const size_t getPostID() const;
	const char * getPostContent() const;

	virtual void visualize() = 0;
	virtual Post * clone() = 0;

protected:
	const char * createPostName() const;

private:
	void copyFrom(const Post & other);
	void clear();

};

#endif // _POST_H_