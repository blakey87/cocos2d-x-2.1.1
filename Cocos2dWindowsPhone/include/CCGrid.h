/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009      On-Core

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

#ifndef __EFFECTS_CCGRID_H__
#define __EFFECTS_CCGRID_H__

#include "CCObject.h"
#include "CCNode.h"
#include "CCCamera.h"
#include "ccTypes.h"
#include "CCTexture2D.h"
#include <fstream>

NS_CC_BEGIN
class CCTexture2D;
class CCGrabber;

/** Base class for other
*/
class CCGridBase : public CCObject
{
public:
	virtual ~CCGridBase(void);

	/** wheter or not the grid is active */
	inline bool isActive(void) { return m_bActive; }
	void setActive(bool bActive);

	/** number of times that the grid will be reused */
	inline int getReuseGrid(void) { return m_nReuseGrid; }
	inline void setReuseGrid(int nReuseGrid) { m_nReuseGrid = nReuseGrid; }

	/** size of the grid */
	inline const ccGridSize& getGridSize(void) { return m_sGridSize; }
	inline void setGridSize(const ccGridSize& gridSize) { m_sGridSize = gridSize; }

	/** pixels between the grids */
	inline const CCPoint& getStep(void) { return m_obStep; }
	inline void setStep(const CCPoint& step) { m_obStep = step; }

	/** is texture flipped */
	inline bool isTextureFlipped(void) { return m_bIsTextureFlipped; }
	void setIsTextureFlipped(bool bFlipped);

	bool initWithSize(const ccGridSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
	bool initWithSize(const ccGridSize& gridSize);

	void beforeDraw(void);
	void afterDraw(CCNode *pTarget);
	virtual void blit(void);
	virtual void reuse(void);
	virtual void calculateVertexPoints(void);

public:
	static CCGridBase* create(const ccGridSize& gridSize, CCTexture2D *texture, bool flipped);
	static CCGridBase* create(const ccGridSize& gridSize);
	void set2DProjection(void);
	void set3DProjection(void);

protected:
	void applyLandscape(void);

protected:
	bool m_bActive;
	int  m_nReuseGrid;
	ccGridSize m_sGridSize;
	CCTexture2D *m_pTexture;
	CCPoint m_obStep;
	CCGrabber *m_pGrabber;
	bool m_bIsTextureFlipped;
	CCSize m_winSize;

protected:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_indexCount, m_vertexCount;

	virtual void initVertexBuffer();
	virtual void RenderVertexBuffer();
	void Render();

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;

	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);
	bool InitializeShader();
	bool SetShaderParameters(DirectX::XMMATRIX &viewMatrix, DirectX::XMMATRIX &projectionMatrix, ID3D11ShaderResourceView* texture);
	void RenderShader();

	struct MatrixBufferType
	{
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		//XMFLOAT4 color;
		DirectX::XMFLOAT2 texture;
	};

	CCvoid *m_pTexCoordinates;
	CCvoid *m_pVertices;
	CCvoid *m_pOriginalVertices;
	CCushort *m_pIndices;
};

/**
CCGrid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
*/
class CCGrid3D : public CCGridBase
{
public:
	~CCGrid3D(void);

	/** returns the vertex at a given position */
	ccVertex3F vertex(const ccGridSize& pos);
	/** returns the original (non-transformed) vertex at a given position */
	ccVertex3F originalVertex(const ccGridSize& pos);
	/** sets a new vertex at a given position */
	void setVertex(const ccGridSize& pos, const ccVertex3F& vertex);

	virtual void blit(void);
	virtual void reuse(void);
	virtual void calculateVertexPoints(void);

public:
	static CCGrid3D* create(const ccGridSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
	static CCGrid3D* create(const ccGridSize& gridSize);
	void initVertexBuffer();
	void RenderVertexBuffer();
	//void Render();

};

/**
CCTiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
the tiles can be separated from the grid.
*/
class CCTiledGrid3D : public CCGridBase
{
public:
	~CCTiledGrid3D(void);

	/** returns the tile at the given position */
	ccQuad3 tile(const ccGridSize& pos);
	/** returns the original tile (untransformed) at the given position */
	ccQuad3 originalTile(const ccGridSize& pos);
	/** sets a new tile */
	void setTile(const ccGridSize& pos, const ccQuad3& coords);

	virtual void blit(void);
	virtual void reuse(void);
	virtual void calculateVertexPoints(void);

public:
	static CCTiledGrid3D* create(const ccGridSize& gridSize, CCTexture2D *pTexture, bool bFlipped);
	static CCTiledGrid3D* create(const ccGridSize& gridSize);
	void initVertexBuffer();
	void RenderVertexBuffer();
	//void Render();

};
NS_CC_END

#endif // __EFFECTS_CCGRID_H__
