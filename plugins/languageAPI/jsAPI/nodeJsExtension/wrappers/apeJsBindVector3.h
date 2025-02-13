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

#ifndef APE_JSBIND_VECTOR3_H
#define APE_JSBIND_VECTOR3_H

#include "apeVector3.h"
#include "nbind/nbind.h"
#include "nbind/api.h"

using namespace ape;

#ifdef NBIND_CLASS

NBIND_CLASS(Vector3)
{
	construct<>();
	construct<Vector3>();
	construct<float, float, float>();
	construct<float>();

	method(getX);
	method(getY);
	method(getZ);

	method(squaredLength);
	method(crossProduct);
	method(isNaN);
	method(normalise);
	method(equalTo);

	method(toString);
	method(toJsonString);
	method(toVector);
}

#endif

#endif
