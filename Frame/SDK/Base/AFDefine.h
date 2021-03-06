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

#include "SDK/Base/AFCData.h"
#include "SDK/Base/AFCDataList.h"
#include "SDK/Base/AFGUID.h"
#include "SDK/Base/AFPlatform.hpp"


enum CLASS_OBJECT_EVENT
{
    COE_NONE                    = 0 ,
    COE_DESTROY                     ,
    COE_BEFOREDESTROY               ,
    COE_CREATE_NODATA               ,
    COE_CREATE_LOADDATA             ,
    COE_CREATE_BEFORE_EFFECT        ,
    COE_CREATE_EFFECTDATA           ,
    COE_CREATE_AFTER_EFFECT         ,
    COE_CREATE_HASDATA              ,
    COE_CREATE_FINISH               ,  //角色创建完成后再挂回调
};

struct DATA_TABLE_EVENT_DATA
{
    DATA_TABLE_EVENT_DATA()
        : nOpType(COE_NONE)
        , nRow(-1)
        , nCol(-1)
        , strName(NULL_STR.c_str())
    {
    }

    uint8_t nOpType;
    int16_t nRow;
    int16_t nCol;
    DataTableName strName;
};

using HEART_BEAT_FUNCTOR = std::function<int(const AFGUID&, const std::string&, const int64_t, const int)>;
using MODULE_HEART_BEAT_FUNCTOR = std::function<void()>;
using DATA_NODE_EVENT_FUNCTOR = std::function<int(const AFGUID&, const std::string&, const AFIData&, const AFIData&)>;
using DATA_TABLE_EVENT_FUNCTOR = std::function<int(const AFGUID&, const DATA_TABLE_EVENT_DATA&, const AFIData&, const AFIData&)>;
using CLASS_EVENT_FUNCTOR = std::function<bool(const AFGUID&, const std::string&, const CLASS_OBJECT_EVENT, const AFIDataList&)>;
using EVENT_PROCESS_FUNCTOR = std::function<int(const AFGUID&, const int, const AFIDataList&)>;
//using EVENT_ASYNC_PROCESS_BEGIN_FUNCTOR = std::function<int(const AFGUID&, const int, std::string&)>;
//using EVENT_ASYNC_PROCESS_END_FUNCTOR = std::function<int(const AFGUID&, const int, const int, const std::string&)>;

using HEART_BEAT_FUNCTOR_PTR = ARK_SHARE_PTR<HEART_BEAT_FUNCTOR>;
using MODULE_HEART_BEAT_FUNCTOR_PTR = ARK_SHARE_PTR<MODULE_HEART_BEAT_FUNCTOR>;
using DATA_NODE_EVENT_FUNCTOR_PTR = ARK_SHARE_PTR<DATA_NODE_EVENT_FUNCTOR>;
using DATA_TABLE_EVENT_FUNCTOR_PTR = ARK_SHARE_PTR<DATA_TABLE_EVENT_FUNCTOR>;
using CLASS_EVENT_FUNCTOR_PTR = ARK_SHARE_PTR<CLASS_EVENT_FUNCTOR>;
using EVENT_PROCESS_FUNCTOR_PTR = ARK_SHARE_PTR<EVENT_PROCESS_FUNCTOR>;

//using EVENT_ASYNC_PROCESS_BEGIN_FUNCTOR_PTR = ARK_SHARE_PTR<EVENT_ASYNC_PROCESS_BEGIN_FUNCTOR>;
//using EVENT_ASYNC_PROCESS_END_FUNCTOR_PTR = ARK_SHARE_PTR<EVENT_ASYNC_PROCESS_END_FUNCTOR>;