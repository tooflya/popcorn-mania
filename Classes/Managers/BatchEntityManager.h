#ifndef CONST_BATCHENTITYMANAGER_H
#define CONST_BATCHENTITYMANAGER_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class BatchEntityManager : public CCSpriteBatchNode
{
	protected:
		int mLastElementNumber;
		int mCapacity;

public:
        void init(int pCreateCount, Entity* pEntity, CCNode* pScreen, int pZOrder);
    
        BatchEntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen);
        BatchEntityManager(int pCreateCount, Entity* pEntity, CCNode* pScreen, int pZOrder);
		
		int getCount();
		int getCapacity();

		void clear();

		CCObject* objectAtIndex(int pIndex);

		Entity* create();
		void destroy(int pIndex);
    
        void pauseSchedulerAndActions();
        void resumeSchedulerAndActions();
    
        void setOpacity(GLubyte pOpaquee);
};

#endif