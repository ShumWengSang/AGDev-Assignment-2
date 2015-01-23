#ifndef __NODE_H__
#define __NODE_H__


class CNode
{
public:
	CNode(void);
	virtual ~CNode(void);
	virtual void Draw(void);
	virtual void SetColor(const float red, const float green, const float blue);
};
#endif