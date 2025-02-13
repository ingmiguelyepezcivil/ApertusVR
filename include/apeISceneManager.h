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

#ifndef APE_ISCENEMANAGER_H
#define APE_ISCENEMANAGER_H

#ifdef _WIN32
#ifdef BUILDING_APE_SCENEMANAGER_DLL
#define APE_SCENEMANAGER_DLL_EXPORT __declspec(dllexport)
#else
#define APE_SCENEMANAGER_DLL_EXPORT __declspec(dllimport)
#endif
#else
#define APE_SCENEMANAGER_DLL_EXPORT 
#endif

#include "apeSingleton.h"
#include "apeINode.h"
#include "apeEntity.h"

namespace ape
{
	class APE_SCENEMANAGER_DLL_EXPORT ISceneManager : public Singleton<ISceneManager>
	{
	protected:
		virtual ~ISceneManager() {};

	public:
		virtual ape::NodeWeakPtrNameMap getNodes() = 0;

		virtual ape::NodeWeakPtr getNode(std::string name) = 0;

		virtual ape::NodeWeakPtr createNode(std::string name) = 0;

		virtual ape::EntityWeakPtrNameMap getEntities() = 0;

		virtual ape::EntityWeakPtr getEntity(std::string name) = 0;

		virtual ape::EntityWeakPtr createEntity(std::string name, ape::Entity::Type type) = 0;

		virtual void deleteNode(std::string name) = 0;

		virtual void deleteEntity(std::string name) = 0;
	};
}

#endif
