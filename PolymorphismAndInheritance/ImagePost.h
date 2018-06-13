#ifndef _IMAGE_POST_H_
#define _IMAGE_POST_H_

#include "Post.h"

class ImagePost : public Post
{
public:
	ImagePost(const size_t, const char *);
	virtual ~ImagePost(); // not needed

public:
	virtual void visualize() override;
	virtual Post * clone() override;
};

#endif // _IMAGE_POST_H_