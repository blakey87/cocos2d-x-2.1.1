/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

// For licensing information relating to this distribution please see Third Party Notices file.

#ifndef __CCATLAS_NODE_H__
#define __CCATLAS_NODE_H__

#include "CCNode.h"
#include "CCProtocols.h"
#include "ccTypes.h"

NS_CC_BEGIN
class CCTextureAtlas;

/** @brief CCAtlasNode is a subclass of CCNode that implements the CCRGBAProtocol and
CCTextureProtocol protocol

It knows how to render a TextureAtlas object.
If you are going to render a TextureAtlas consider subclassing CCAtlasNode (or a subclass of CCAtlasNode)

All features from CCNode are valid, plus the following features:
- opacity and RGB colors
*/
class CC_DLL CCAtlasNode : public CCNode, public CCRGBAProtocol, public CCTextureProtocol
{
protected:

	//! chars per row
	unsigned int m_uItemsPerRow;
	//! chars per column
	unsigned int m_uItemsPerColumn;

	//! width of each char
	unsigned int	m_uItemWidth;
	//! height of each char
	unsigned int	m_uItemHeight;

	ccColor3B	m_tColorUnmodified;

	CC_PROPERTY(CCTextureAtlas*, m_pTextureAtlas, TextureAtlas);

	// protocol variables
	CC_PROPERTY(bool, m_bIsOpacityModifyRGB, IsOpacityModifyRGB)
	CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc);
	CC_PROPERTY(CCubyte, m_cOpacity, Opacity);
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);

	// quads to draw
	CC_PROPERTY(unsigned int, m_uQuadsToDraw, QuadsToDraw);

public:
	CCAtlasNode();
	virtual ~CCAtlasNode();

	/** creates a CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	static CCAtlasNode * create(const char* tile,unsigned int tileWidth, unsigned int tileHeight, 
		unsigned int itemsToRender);

	/** initializes an CCAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
	bool initWithTileFile(const char* tile, unsigned int tileWidth, unsigned int tileHeight, unsigned int itemsToRender);

	/** updates the Atlas (indexed vertex array).
	* Shall be overriden in subclasses
	*/
	virtual void updateAtlasValues();

	virtual void draw();

	// CC Texture protocol

	/** returns the used texture*/
	virtual CCTexture2D* getTexture(void);

	/** sets a new texture. it will be retained*/
	virtual void setTexture(CCTexture2D *texture);

private :
	void calculateMaxItems();
	void updateBlendFunc();
	void updateOpacityModifyRGB();

};
NS_CC_END

#endif // __CCATLAS_NODE_H__


