#ifndef _TEXT_POST_H_
#define _TEXT_POST_H_

#include "Post.h"

class TextPost : public Post
{
public:
	TextPost(const size_t, const char *);
	virtual ~TextPost();

public:
	virtual void visualize() override;
	virtual Post * clone() override;
};

#endif // _TEXT_POST_H_