#include "StdAfx.h"
#include "MetropolisIntegrator.h"

WMetropolisIntegrator::WMetropolisIntegrator(	
	Scene*iscene,WAccelerator*itree,Camera* icamera):WSurfaceIntegrator(iscene,itree)
{
	tree = itree;
	scene = iscene;
	camera = icamera;
}

WMetropolisIntegrator::~WMetropolisIntegrator(void)
{
}
