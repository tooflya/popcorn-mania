#ifndef CONST_ENTITY_H
#define CONST_ENTITY_H

#include "cocos2d.h"

#include "Touchable.h"
#include "Texture.h"
#include "Utils.h"
#include "Options.h"

#include "Resources.h"

using namespace cocos2d;

class EntityManager;
class BatchEntityManager;

class Entity : public CCSprite, public Touchable
{
    protected:
        // ===========================================================
        // Inner Classes
        // ===========================================================
    
        // ===========================================================
        // Constants
        // ===========================================================
    
        // ===========================================================
        // Fields
        // ===========================================================
    
        float mWidth;
        float mHeight;
    
        float mFrameWidth;
        float mFrameHeight;
    
        float mSpeed;
    
        float mPauseBeforeNewAnimationCircleTime;
        float mPauseBeforeNewAnimationCircleTimeElapsed;
    
        float mAnimationTime;
        float mAnimationTimeElapsed;
    
        float mAnimationStartTimeout;
    
        float* mFramesCoordinatesX;
        float* mFramesCoordinatesY;
    
        int mFramesCount;
    
        int mHorizontalFramesCount;
        int mVerticalFramesCount;
    
        int mCurrentFrameIndex;
    
        int mAnimationStartFrame;
        int mAnimationFinishFrame;
        int mAnimationFramesElapsed;
    
        int mAnimationRepeatCount;
    
        bool mIsAnimationReverse;
        bool mIsAnimationReverseNeed;
    
        bool mAnimationRunning;
    
        int id;
    
        EntityManager* mEntityManager;
        BatchEntityManager* mBatchEntityManager;
    
        // ===========================================================
        // Constructors
        // ===========================================================
    
        // ===========================================================
        // Methods
        // ===========================================================
    
        // ===========================================================
        // Virtual Methods
        // ===========================================================
    
    private:
        // ===========================================================
        // Inner Classes
        // ===========================================================
    
        // ===========================================================
        // Constants
        // ===========================================================
    
        // ===========================================================
        // Fields
        // ===========================================================
    
        // ===========================================================
        // Constructors
        // ===========================================================
    
        void constructor(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent);
    
        // ===========================================================
        // Methods
        // ===========================================================
    
        // ===========================================================
        // Virtual Methods
        // ===========================================================
    
    public:
        // ===========================================================
        // Inner Classes
        // ===========================================================
    
        // ===========================================================
        // Constants
        // ===========================================================
    
        // ===========================================================
        // Fields
        // ===========================================================
    
        const char* mTextureFileName;
    
        // ===========================================================
        // Constructors
        // ===========================================================
    
        Entity();
        Entity(const char* pszFileName);
        Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);
        Entity(const char* pszFileName, CCNode* pParent);
        Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent);
    
        // ===========================================================
        // Methods
        // ===========================================================
    
        float getWidth();
        float getHeight();
    
        float getWidthScaled();
        float getHeightScaled();
    
        /**
         *
         * Take care about careful position
         *
         */
    
        void setPosition(float pX, float pY);
        void setCenterPosition(float pX, float pY);
        void setCenterPosition(float pX, float pY, bool setWithoutChecks);
        void setX(float pX);
        void setY(float pY);
    
        float getCenterPosition();
        float getX();
        float getY();
        float getCenterX();
        float getCenterY();
    
        /**
         *
         * Take care about speed
         *
         */
    
        float getSpeed(float pDeltaTime);
        void setSpeed(float pSpeed);
    
        /**
         *
         * Take care about EntityManager
         *
         */
    
    
        virtual Entity* create();
    
        virtual bool destroy();
        virtual bool destroy(bool pManage);
    
        void setEntityManager(EntityManager* pEntityManager);
        void setEntityManager(BatchEntityManager* pBatchEntityManager);
    
        int hasEntityManager();
    
        void setEntityManagerId(int pId);
    
        int getEntityManagerId();
    
        /**
         *
         * Take care about animation
         *
         */
    
        int getCurrentFrameIndex();
    
        virtual void setCurrentFrameIndex(int pIndex);
    
        void previousFrameIndex();
        void nextFrameIndex();
    
        virtual void changeTexture(Texture* pTexture);
    
        bool isAnimationRunning();
    
        void animate(float pAnimationTime);
        void animate(float pAnimationTime, int pRepeatCount);
        void animate(float pAnimationTime, int pRepeatCount, bool pNeedReverse);
        void animate(float pAnimationTime, float pPauseBeforeNewAnimationCircleTime);
        void animate(float pAnimationTime, int pRepeatCount, float pPauseBeforeNewAnimationCircleTime);
        void animate(float pAnimationTime, int pStartFrame, int pFinishFrame, int pRepeatCount);
        void animate(float pAnimationTime, int pStartFrame, int pFinishFrame);
    
        void setStartFrame(int pStartFrame);
        void setFinishFrame(int pFinishFrame);
    
        void setAnimationStartTimeout(float pSecodsTimeout);
    
        void setAnimationReverse(bool pReverse);
    
        virtual void onAnimationStart();
        virtual void onAnimationEnd();
        virtual void onAnimationCircleEnd();
    
        /**
         *
         * Checing for touch detector
         *
         */
    
        void onEnter();
    
        void onExit();
    
        bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    
        void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
        void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
        bool containsTouchLocation(CCTouch* touch);
    
        virtual void update(float pDeltaTime);
    
        virtual void draw();
    
        /**
         *
         * Let's take care about object copy
         *
         */
    
        virtual Entity* deepCopy();
    
        // ===========================================================
        // Virtual Methods
        // ===========================================================
		
};

#endif