#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>

#include "Types.h"

class ShaderConstants
{
public:
	enum
	{
		InvalidSampler = 0xFFFFFFFF
	};

	~ShaderConstants();

	uint find(std::string c);
	uint getSampler(uint c);

	bool setFloat(uint c, float f);

	bool setVec2(uint c, const vec2& v);
	bool setVec3(uint c, const vec3& v);
	bool setVec4(uint c, const vec4& v);
	bool setMat3(uint c, const mat3& m);
	bool setMat4(uint c, const mat4& m);

	LPD3DXCONSTANTTABLE constants = 0;

private:
	std::vector<D3DXHANDLE> handles;
};

class Shader
{
public:
	~Shader();

	bool compile(std::string vert, std::string pixel);
	bool compileasm(std::string vert, std::string pixel);

	LPDIRECT3DVERTEXSHADER9 VShader = 0;
	LPDIRECT3DPIXELSHADER9  PShader = 0;

	ShaderConstants VConstants;
	ShaderConstants PConstants;
};

class Surface
{
public:
	~Surface();

	bool createDepthStencil(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool discard);
	bool createFromPointer(LPDIRECT3DSURFACE9 surf);
	bool createRenderTarget(uint width, uint height, D3DFORMAT format, D3DMULTISAMPLE_TYPE ms, uint msquality, bool lockable);

	bool setRenderTarget(uint level);
	static bool resetRenderTarget(uint level);

	bool setDepthBuffer();
	static bool resetDepthBuffer();

	bool update(Surface& surf);

	LPDIRECT3DSURFACE9 surf;

protected:
	uint surfUsage;
	uint surfPool;
	uint surfWidth;
	uint surfHeight;
};

class Texture
{
public:
	enum MipMaps
	{
		MipMapsNone     = 0x00,
		MipMapsGenerate = 0x01,
		MipMapsFromFile = 0x02
	};

	~Texture();

	bool create(uint width, uint height, uint levels, uint usage, D3DFORMAT format, D3DPOOL pool);
	bool generateMipMaps();
	bool getSurface(uint level, Surface& surf);
	uint getSurfaceCount();
	bool loadFromFile(std::string file, MipMaps mipmaps);
	bool loadFromFileInMemory(const void* data, uint length, MipMaps mipmaps);
	bool setMipMapFilter(D3DTEXTUREFILTERTYPE filter);
	bool update(Texture& src);

	LPDIRECT3DTEXTURE9 tex = 0;

private:
	enum
	{
		FlagMipMaps = 0x01
	};

	uint flags;
};
