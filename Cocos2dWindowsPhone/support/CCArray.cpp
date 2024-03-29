/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* Copyright (c) 2010 ForzeField Studios S.L. http://forzefield.com
* Copyright (c) 2010 cocos2d-x.org
* 
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
* 
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at 
* 
* http://www.apache.org/licenses/LICENSE-2.0 
* 
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "pch.h"

#include "CCArray.h"
NS_CC_BEGIN
//namespace cocos2d
//{

CCArray::CCArray()
: data(NULL)
{
    init();
}
CCArray::CCArray(unsigned int capacity)
: data(NULL)
{
    initWithCapacity(capacity);
}

CCArray* CCArray::create()
{
    CCArray* pArray = new CCArray();

    if (pArray && pArray->init())
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}


CCArray* CCArray::createWithObject(CCObject* pObject)
{
    CCArray* pArray = new CCArray();

    if (pArray && pArray->initWithObject(pObject))
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    return pArray;
}
CCArray* CCArray::create(CCObject* pObject, ...)
{
    va_list args;
    va_start(args,pObject);

    CCArray* pArray = create();
    if (pArray && pObject)
    {
        pArray->addObject(pObject);
        CCObject *i = va_arg(args, CCObject*);
        while(i) 
        {
            pArray->addObject(i);
            i = va_arg(args, CCObject*);
        }
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }

    va_end(args);

    return pArray;
}
CCArray* CCArray::createWithArray(CCArray* otherArray)
{
     CCArray* pRet = (CCArray*)otherArray->copy();
    pRet->autorelease();
    return pRet;
}
CCArray* CCArray::createWithCapacity(unsigned int capacity)
{
    CCArray* pArray = new CCArray();
    
    if (pArray && pArray->initWithCapacity(capacity))
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}

CCArray* CCArray::createWithContentsOfFile(const char* pFileName)
{
    CCArray* pRet = CCArray::createWithContentsOfFileThreadSafe(pFileName);
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

extern CCArray* ccFileUtils_arrayWithContentsOfFileThreadSafe(const char* pFileName);

CCArray* CCArray::createWithContentsOfFileThreadSafe(const char* pFileName)
{
    return ccFileUtils_arrayWithContentsOfFileThreadSafe(pFileName);
}
bool CCArray::init()
{
    return initWithCapacity(1);
}
bool CCArray::initWithObject(CCObject* pObject)
{
    ccArrayFree(data);
    bool bRet = initWithCapacity(1);
    if (bRet)
    {
        addObject(pObject);
    }
    return bRet;
}

/** Initializes an array with some objects */
bool CCArray::initWithObjects(CCObject* pObject, ...)
{
    ccArrayFree(data);
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(pObject != NULL);

        va_list args;
        va_start(args, pObject);

        CCArray* pArray = new CCArray();
        if (pArray && pObject)
        {
            pArray->addObject(pObject);
            CCObject* i = va_arg(args, CCObject*);
            while(i) 
            {
                pArray->addObject(i);
                i = va_arg(args, CCObject*);
            }
            bRet = true;
        }
        else
        {
            CC_SAFE_DELETE(pArray);
        }
        va_end(args);

    } while (false);

    return bRet;
}
bool CCArray::initWithCapacity(unsigned int capacity)
{
    data = ccArrayNew(capacity);
    return true;
}

bool CCArray::initWithArray(CCArray* otherArray)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! initWithCapacity(otherArray->data->num));

        addObjectsFromArray(otherArray);
        bRet = true;
    } while (0);
    
    return bRet;
}

unsigned int CCArray::count()
{
    return data->num;
}

unsigned int CCArray::capacity()
{
    return data->max;
}

unsigned int CCArray::indexOfObject(CCObject* object)
{
    return ccArrayGetIndexOfObject(data, object);
}

CCObject* CCArray::objectAtIndex(unsigned int index)
{
    CCAssert(index < data->num, "index out of range in objectAtIndex()");

    return data->arr[index];
}

CCObject* CCArray::lastObject()
{
    if( data->num > 0 )
        return data->arr[data->num-1];

    return NULL;
}

CCObject* CCArray::randomObject()
{
   if (data->num==0)
    {
        return NULL;
    }

    float r = CCRANDOM_0_1();
    
    if (r == 1) // to prevent from accessing data-arr[data->num], out of range.
    {
        r = 0;
    }
    
    return data->arr[(int)(data->num * r)];
}

bool CCArray::containsObject(CCObject* object)
{
    return ccArrayContainsObject(data, object);
}
bool CCArray::isEqualToArray(CCArray* otherArray)
{
    for (unsigned int i = 0; i< this->count(); i++)
    {
        if (!this->objectAtIndex(i)->isEqual(otherArray->objectAtIndex(i)))
        {
            return false;
        }
    }
    return true;
}
void CCArray::addObject(CCObject* object)
{
    ccArrayAppendObjectWithResize(data, object);
}

void CCArray::addObjectsFromArray(CCArray* otherArray)
{
    ccArrayAppendArrayWithResize(data, otherArray->data);
}

void CCArray::insertObject(CCObject* object, unsigned int index)
{
    ccArrayInsertObjectAtIndex(data, object, index);
}

void CCArray::removeLastObject(bool bReleaseObj)
{
    CCAssert(data->num, "no objects added");
    ccArrayRemoveObjectAtIndex(data, data->num-1,bReleaseObj);
}

void CCArray::removeObject(CCObject* object, bool bReleaseObj/* = true*/)
{
    ccArrayRemoveObject(data, object, bReleaseObj);
}

void CCArray::removeObjectAtIndex(unsigned int index, bool bReleaseObj)
{
    ccArrayRemoveObjectAtIndex(data, index,bReleaseObj);
}

void CCArray::removeObjectsInArray(CCArray* otherArray)
{
    ccArrayRemoveArray(data, otherArray->data);
}

void CCArray::removeAllObjects()
{
    ccArrayRemoveAllObjects(data);
}

void CCArray::fastRemoveObjectAtIndex(unsigned int index)
{
    ccArrayFastRemoveObjectAtIndex(data, index);
}

void CCArray::fastRemoveObject(CCObject* object)
{
    ccArrayFastRemoveObject(data, object);
}

void CCArray::exchangeObject(CCObject* object1, CCObject* object2)
{
    unsigned int index1 = ccArrayGetIndexOfObject(data, object1);
    if(index1 == UINT_MAX)
    {
        return;
    }

    unsigned int index2 = ccArrayGetIndexOfObject(data, object2);
    if(index2 == UINT_MAX)
    {
        return;
    }

    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void CCArray::exchangeObjectAtIndex(unsigned int index1, unsigned int index2)
{
    ccArraySwapObjectsAtIndexes(data, index1, index2);
}

void CCArray::reverseObjects()
{
    if (data->num > 1)
    {
        //floor it since in case of a oneven number the number of swaps stays the same
        int count = (int) floorf(data->num/2.f); 
        unsigned int maxIndex = data->num - 1;

        for (int i = 0; i < count ; i++)
        {
            ccArraySwapObjectsAtIndexes(data, i, maxIndex);
            maxIndex--;
        }
    }
}

void CCArray::reduceMemoryFootprint()
{
    ccArrayShrink(data);
}

CCArray::~CCArray()
{
    ccArrayFree(data);
}
CCObject* CCArray::copyWithZone(CCZone* pZone)
{
    CCAssert(pZone == NULL, "CCArray should not be inherited.");
    CCArray* pArray = new CCArray();
    pArray->initWithCapacity(this->data->num > 0 ? this->data->num : 1);

    CCObject* pObj = NULL;
    CCObject* pTmpObj = NULL;
    CCARRAY_FOREACH(this, pObj)
    {
        pTmpObj = pObj->copy();
        pArray->addObject(pTmpObj);
        pTmpObj->release();
    }
    return pArray;
}
//}
NS_CC_END