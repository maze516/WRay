#pragma once
#include "stdafx.h"
#include <atlstr.h>
#include "Primitive.h"
//#include "DisplaySystem.h"
#define OBJ_READ_CHECK_COUNTER 300000
#ifndef FILEREADINGPROCESSMSG
#define FILEREADINGPROCESSMSG WM_USER+1
#endif
struct float3
{
	float x,y,z;
};
struct float2
{
	float u,v;
};
struct ObjTriangle
{
	unsigned int vertIndex[3];			//vertex index--->即是三角片上三个点坐标对应的索引值
	unsigned int texcoordIndex[3];		//texture coordinate index--->即是三角片上三个点坐标的材质坐标对应的索引值
	unsigned int norIndex[3];			//normal index--->基本同上。。
	unsigned int mtlIndex;				//material index
};
struct ObjPrimitive   //--->这是一个物体
{
	string name;				//primitive name---->物体的名字
	vector<float3>vertices;	//vertex coordinate---->物体顶点的集合
	vector<float2>texcoords;	//texture coordinate---->物体材质坐标的集合
	vector<float3>normals;		//normal coordinate---->物体顶点法向量的集合
	vector<ObjTriangle>faces;	//faces---->物体三角片面的集合
};
struct ObjMaterial
{
	string name;				//name of material
	float3 diffuse;			//漫反射颜色
	float3 specular;			// specular color
	float3 emission;			//自发光颜色
	float3 transparency;		//透明度
	float   glossiness;			//高光强度
	bool   isTransparent(){return transparency.x < 1 || transparency.y < 1 || transparency.z < 1;}
	bool   isShiny(){return glossiness > 0;}
};

class ObjReader
{
public:
	static enum coordType{VERTCOORDS,TEXCOORDS,NORCOORDS};
	static enum indexType{VERTINDICES,TEXINDICES,NORINDICES};
	ObjReader();
	~ObjReader();
	vector<ObjPrimitive>primitives;  //---->场景中物体的集合
	vector<ObjMaterial>Materials;   //---->物体对应材质的集合，这里似乎只是简单的漫反射材质
	//读取obj以及连带的mtl文件
	//obj和mtl文件必须在同一目录
	void readFile(const std::string& fileName);
	//只读取obj文件
	void readObjFile(const char*fileName);
	//只读取mtl文件
	void readMtlFile(const char*fileName);
	//return vertex buffer
	bool getWireArray(int primitive,WGLWireArray*vB);
	void showObj();
	void showMtl();
	void clear();
	void ObjReader::fillPrimitive(unsigned int nthPrimitive,MeshObject&pri);
	int getReadingProcess(){return readingProcess;}
private:
	//把vector类型的坐标数组转化成float类型数组
	//pArray为数组指针，nFloats为数组元素个数
	//type有3种取值：OBJ_VERTICES,OBJ_TEXCOORDS,OBJ_NORMALS
	//表示返回对应类型的数组
	//nthPrimitive指定返回哪一个物体的数组
	void getCoordArray(float*&pArray,unsigned int&nFloats,
		unsigned nthPrimitive,coordType type);
	//把vector类型的索引数组转化成unsigned int类型数组
	//参数与getCoordArray类似，nInt是索引数，为面数*3
	//注意索引值的3倍才是对应顶点，法向量数组的下标
	//注意索引值的2倍才是对应贴图坐标数组的下标
	void getIndexArray(unsigned int*&pArray,unsigned int &nInts,
		unsigned nthPrimitive,indexType type);
	ifstream file;
	float readingProcess;
};
