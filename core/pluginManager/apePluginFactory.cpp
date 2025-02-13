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

#include "apePluginFactory.h"

ape::PluginFactory::CallbackMap ape::PluginFactory::mPluginCallbackMap;

void ape::PluginFactory::RegisterPlugin(const std::string &type, CreateCallback createCb, DestroyCallback destroyCb)
{
	PluginCallbacks pb;
	pb.createCb = createCb;
	pb.destroyCb = destroyCb;
	mPluginCallbackMap[type] = pb;
}

void ape::PluginFactory::UnregisterPlugin(const std::string &type, ape::IPlugin *plugin)
{
	CallbackMap::iterator it = mPluginCallbackMap.find(type);
	if (it != mPluginCallbackMap.end())
		it->second.destroyCb(plugin);
	mPluginCallbackMap.erase(type);
}

ape::IPlugin* ape::PluginFactory::CreatePlugin(const std::string &type)
{
	CallbackMap::iterator it = mPluginCallbackMap.find(type);
	if (it != mPluginCallbackMap.end())
		return (it->second.createCb)();
    return NULL;
}

