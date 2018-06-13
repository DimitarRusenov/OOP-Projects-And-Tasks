#ifndef _LINK_POST_H_
#define _LINK_POST_H_

#include "Post.h"

class LinkPost : public Post
{
public:
	LinkPost(const size_t, const char *);
	virtual ~LinkPost();

public:
	virtual void visualize() override;
	virtual Post * clone() override;
};

#endif // _LINK_POST_H_