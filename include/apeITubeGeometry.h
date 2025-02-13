/*MIT License

Copyright (c) 2018 MTA SZTAKI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef APE_ITUBEGEOMETRY_H
#define APE_ITUBEGEOMETRY_H

#include <string>
#include <vector>
#include "apeGeometry.h"
#include "apeVector2.h"
#include "apeVector3.h"
#include "apeINode.h"

namespace ape
{
	struct GeometryTubeParameters
	{
		float height;
		float tile;

		GeometryTubeParameters()
		{
			this->height = 0.0f;
			this->tile = 0.0f;
		}

		GeometryTubeParameters(
		    float height,
		    float tile)
		{
			this->height = height;
			this->tile = tile;
		}
	};

	class ITubeGeometry : public ape::Geometry
	{
	protected:
		ITubeGeometry(std::string name) : ape::Geometry(name, ape::Entity::GEOMETRY_TUBE) {}

		virtual ~ITubeGeometry() {};

	public:
		virtual void setParameters(float height, float tile) = 0;

		virtual ape::GeometryTubeParameters getParameters() = 0;

		virtual void setParentNode(ape::NodeWeakPtr parentNode) = 0;

		virtual void setMaterial(ape::MaterialWeakPtr material) = 0;

		virtual ape::MaterialWeakPtr getMaterial() = 0;
	};
}

#endif
