/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#include "GeometryNet.h"

namespace FileGDB_DotNet 
{
	public ref class PointNet : GeometryNet
	{
	public:
		PointNet() : GeometryNet(1)
		{
		}

		PointNet(double x, double y) : GeometryNet(1)
		{
			this->x = x;
			this->y = y;
		}

		double x;
		double y;
	};
}