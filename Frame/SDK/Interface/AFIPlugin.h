/*
* This source file is part of ArkGameFrame
* For the latest info, see https://github.com/ArkGame
*
* Copyright (c) 2013-2017 ArkGame authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#pragma once

#include "SDK/Base/AFPlatform.hpp"
#include "SDK/Base/AFMap.h"
#include "SDK/Interface/AFIModule.h"
#include "SDK/Interface/AFIPluginManager.h"
#include "SDK/Base/AFArrayMap.hpp"

//mxModules defines in AFIPlugin
#define REGISTER_MODULE(pManager, classBaseName, className)             \
    assert((TIsDerived<classBaseName, AFIModule>::Result));             \
    assert((TIsDerived<className, classBaseName>::Result));             \
    AFIModule* pRegisterModule##className = new className(pManager);    \
    pRegisterModule##className->strName = (#className);                 \
    pManager->AddModule(#classBaseName, pRegisterModule##className);    \
    mxModules.AddElement(#classBaseName, pRegisterModule##className);

#define UNREGISTER_MODULE(pManager, classBaseName, className)           \
    AFIModule* pUnRegisterModule##className =                           \
    dynamic_cast<AFIModule*>(pManager->FindModule(#classBaseName));     \
    pManager->RemoveModule(#classBaseName);                             \
    mxModules.RemoveElement(#classBaseName);                            \
    delete pUnRegisterModule##className;                                \
    pUnRegisterModule##className = NULL;                                \


#define CREATE_PLUGIN(pManager, className)                              \
    AFIPlugin* pCreatePlugin##className = new className(pManager);      \
    pManager->Registered(pCreatePlugin##className);

#define DESTROY_PLUGIN(pManager, className) pManager->UnRegistered(pManager->FindPlugin((#className)));

#define GET_CLASS_NAME(className) (#className);

/*
#define REGISTER_COMPONENT(pManager, className)  AFIComponent* pRegisterComponent##className= new className(pManager); \
    pRegisterComponent##className->strName = (#className); \
    pManager->AddComponent( (#className), pRegisterComponent##className );

#define UNREGISTER_COMPONENT(pManager, className) AFIComponent* pRegisterComponent##className =  \
        dynamic_cast<AFIComponent*>( pManager->FindComponent( (#className) ) ); pManager->RemoveComponent( (#className) ); delete pRegisterComponent##className;
*/

class AFIPluginManager;

class AFIPlugin : public AFIModule
{
public:
    virtual int GetPluginVersion() = 0;
    virtual const std::string GetPluginName() = 0;

    virtual void Install() = 0;

    virtual bool Init()
    {
        size_t nModuleCount = mxModules.GetCount();
        for (size_t i = 0; i < nModuleCount; ++i)
        {
            AFIModule* pModule = mxModules[i];
            bool bRet = pModule->Init();
            ARK_ASSERT_RET_VAL(bRet, false);
        }

        return true;
    }

    virtual bool AfterInit()
    {
        size_t nModuleCount = mxModules.GetCount();
        for (size_t i = 0; i < nModuleCount; ++i)
        {
            AFIModule* pModule = mxModules[i];
            bool bRet = pModule->AfterInit();
            ARK_ASSERT_RET_VAL(bRet, false);
        }

        return true;
    }

    virtual bool CheckConfig()
    {
        size_t nModuleCount = mxModules.GetCount();
        for (size_t i = 0; i < nModuleCount; ++i)
        {
            AFIModule* pModule = mxModules[i];
            bool bRet = pModule->CheckConfig();
            ARK_ASSERT_RET_VAL(bRet, false);
        }

        return true;
    }

    virtual void Update()
    {
        size_t nModuleCount = mxModules.GetCount();
        for (size_t i = 0; i < nModuleCount; ++i)
        {
            AFIModule* pModule = mxModules[i];
            pModule->Update();
        }
    }

    virtual bool BeforeShut()
    {
        size_t nModuleCount = mxModules.GetCount();
        for (size_t i = 0; i < nModuleCount; ++i)
        {
            AFIModule* pModule = mxModules[i];
            bool bRet = pModule->BeforeShut();
            ARK_ASSERT_RET_VAL(bRet, false);
        }

        return true;
    }

    virtual bool Shut()
    {
        size_t nModuleCount = mxModules.GetCount();
        for (size_t i = 0; i < nModuleCount; ++i)
        {
            AFIModule* pModule = mxModules[i];
            bool bRet = pModule->Shut();
            ARK_ASSERT_RET_VAL(bRet, false);
        }

        return true;
    }

    virtual void Uninstall() = 0;

protected:
    //All registered modules
    AFArrayMap<std::string, AFIModule> mxModules;
};