#ifndef CONST_ENTITY
#define CONST_ENTITY

#include "Entity.h"
#include "EntityManager.h"
#include "BatchEntityManager.h"

void Entity::constructor(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent)
{
	this->initWithFile(pszFileName);

	if(pParent)
	{
		pParent->addChild(this);
	}

	this->mTextureFileName = pszFileName;

	this->mWidth  = this->getTextureRect().size.width;
	this->mHeight = this->getTextureRect().size.height;

	this->mFrameWidth = this->mWidth / pHorizontalFramesCount;
	this->mFrameHeight = this->mHeight / pVerticalFramesCount; 

	this->mFramesCount = pHorizontalFramesCount * pVerticalFramesCount;

	this->mHorizontalFramesCount = pHorizontalFramesCount;
	this->mVerticalFramesCount   = pVerticalFramesCount;

	this->mWasTouched = false;

	this->setAnchorPoint(ccp(0.5f, 0.5f));

	this->mEntityManager = NULL;
	this->mBatchEntityManager = NULL;
    
    this->mIsShadowed = false;

	/**
	 *
	 * We must remember all coordinates of each frame
	 * for quick get x and y of it.
	 *
	 */

	this->mFramesCoordinatesX = new float[this->mFramesCount];
	this->mFramesCoordinatesY = new float[this->mFramesCount];

	int counter = 0;

	for(int i = 0; i < this->mVerticalFramesCount; i++)
	{
		for(int j = 0; j < this->mHorizontalFramesCount; j++, counter++)
		{
			this->mFramesCoordinatesX[counter] = j * (this->mWidth / this->mHorizontalFramesCount);
			this->mFramesCoordinatesY[counter] = i * (this->mHeight / this->mVerticalFramesCount);
		}
	}

	/**
	 *
	 * Setting zero frame
	 *
	 */

	this->setCurrentFrameIndex(0);

	/**
	 *
	 *
	 * Take care about an animations
	 *
	 */

	this->mAnimationTime = 0;
	this->mAnimationTimeElapsed = 0;
    
	this->mAnimationScaleDownTime = 0.2f;
	this->mAnimationScaleUpTime = 0.2f;
    
	this->mAnimationScaleDownFactor = 0.8f;
	this->mAnimationScaleUpFactor = 1.0f;

	this->mAnimationStartTimeout = 0;

	this->mPauseBeforeNewAnimationCircleTime = 0;
	this->mPauseBeforeNewAnimationCircleTimeElapsed = 0;

	this->mAnimationRunning = false;

	this->mIsRegisterAsTouchable = false;

	this->mAnimationRepeatCount = -1;

	this->mAnimationStartFrame = -1;
	this->mAnimationFinishFrame = -1;

	this->mAnimationFramesElapsed = 0;

	this->mIsAnimationReverse = false;
	this->mIsAnimationReverseNeed = false;

	this->scheduleUpdate();

	this->retain();
	this->release();

	this->destroy();
}


Entity::Entity()
{
}

Entity::Entity(const char* pszFileName)
{
	this->constructor(pszFileName, 1, 1, NULL);
}

Entity::Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount)
{
	this->constructor(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, NULL);
}

Entity::Entity(const char* pszFileName, CCNode* pParent)
{
	this->constructor(pszFileName, 1, 1, pParent);
}

Entity::Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent)
{
	this->constructor(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, pParent);
}

void Entity::setShadowed(const char* pTextureFileName)
{
    this->mShadow = new Entity(pTextureFileName, this->mHorizontalFramesCount, this->mVerticalFramesCount, this->getParent());
    
    this->mIsShadowed = true;
}

float Entity::getWidth()
{
	return this->getContentSize().width;
}

float Entity::getHeight()
{
	return this->getContentSize().height;
}

float Entity::getWidthScaled()
{
	return this->getContentSize().width * this->getScaleX();
}

float Entity::getHeightScaled()
{
	return this->getContentSize().height * this->getScaleX();
}

/**
 *
 * Take care about careful position
 *
 */

void Entity::setPosition(float pX, float pY)
{
	CCSprite::setPosition(ccp(pX - this->getWidth() / 2, pY + this->getHeight() / 2));
}

void Entity::setCenterPosition(float pX, float pY)
{
	CCSprite::setPosition(ccp(pX, pY));
}

void Entity::setCenterPosition(float pX, float pY, bool setWithoutChecks)
{
	CCSprite::setPosition(ccp(pX, pY));
}

void Entity::setX(float pX)
{
	// TODO: Write this method
}

void Entity::setY(float pY)
{
	// TODO: Write this method
}

float Entity::getCenterPosition()
{
	return 0; // TODO: Write this method
}

float Entity::getX()
{
	return this->getPosition().x - this->getWidth() / 2;
}

float Entity::getY()
{
	return this->getPosition().y + this->getHeight() / 2;
}

float Entity::getCenterX()
{
	return this->getPosition().x;
}

float Entity::getCenterY()
{
	return this->getPosition().y;
}

void Entity::setSpeed(float pSpeed)
{
	this->mSpeed = (pSpeed);
}

float Entity::getSpeed(float pDeltaTime)
{
	return this->mSpeed * pDeltaTime;
}

/**
 *
 * Take care about EntityManager
 *
 */

Entity* Entity::create()
{
	this->setVisible(true);
    
    this->setScale(1.0f);
    this->setRotation(0.0f);
    
    if(this->mIsShadowed)
    {
        if(!this->mShadow->getParent())
        {
            this->getParent()->addChild(this->mShadow, 1);
        }
        
        this->mShadow->create();
    }
    
    this->onCreate();

	return this;
}

bool Entity::destroy(bool pManage)
{
	this->setVisible(false);
    
    if(this->mIsShadowed)
    {
        this->mShadow->destroy();
    }

	if(pManage)
	{
		if(this->hasEntityManager() == 1)
		{
			this->mEntityManager->destroy(this->id);
		}
		else if(this->hasEntityManager() == 2)
		{
			this->mBatchEntityManager->destroy(this->id);
		}
	}
    
    this->onDestroy();

	return false;
}

bool Entity::destroy()
{
	return this->destroy(true);
}

void Entity::onCreate()
{
    
}

void Entity::onDestroy()
{
    
}

void Entity::setEntityManager(EntityManager* pEntityManager)
{
	this->mEntityManager = pEntityManager;
}

void Entity::setEntityManager(BatchEntityManager* pBatchEntityManager)
{
	this->mBatchEntityManager = pBatchEntityManager;
}

int Entity::hasEntityManager()
{
	if(this->mEntityManager == NULL && this->mBatchEntityManager == NULL)
	{
		return 0;
	}
	else if(this->mBatchEntityManager == NULL)
	{
		return 1;
	}
	else
	{
		return 2;
	}

	return 0;
}

void Entity::setEntityManagerId(int pId)
{
	this->id = pId;
}

int Entity::getEntityManagerId()
{
	return this->id;
}

/**
 *
 * Take care about animation
 *
 */

int Entity::getCurrentFrameIndex()
{
	return this->mCurrentFrameIndex;
}

void Entity::setCurrentFrameIndex(int pIndex)
{
	if(pIndex < this->mHorizontalFramesCount * this->mVerticalFramesCount && pIndex >= 0)
	{
		this->setTextureRect(CCRectMake(this->mFramesCoordinatesX[pIndex], this->mFramesCoordinatesY[pIndex], this->mWidth / this->mHorizontalFramesCount, this->mHeight / this->mVerticalFramesCount));

		this->mCurrentFrameIndex = pIndex;
	}
	else
	{
		this->setCurrentFrameIndex(0);
	}
}

void Entity::previousFrameIndex()
{
	int potencialNextFrame = this->getCurrentFrameIndex() - 1;

	this->setCurrentFrameIndex(potencialNextFrame > 0 ? potencialNextFrame : 0);
}

void Entity::nextFrameIndex()
{
	int potencialNextFrame = this->getCurrentFrameIndex() + 1;

	this->setCurrentFrameIndex(potencialNextFrame > this->mFramesCount ? 0 : potencialNextFrame);
}

void Entity::changeTexture(Texture* pTexture)
{
	CCRect textureRectanle = CCRect(0, 0, pTexture->getTexture()->getContentSize().width, pTexture->getTexture()->getContentSize().height);

	this->setTexture(pTexture->getTexture());
	this->setTextureRect(textureRectanle);

	this->mWidth  = this->getTextureRect().size.width;
	this->mHeight = this->getTextureRect().size.height;

	this->mFrameWidth = this->mWidth / pTexture->getHorizontalFramesCount();
	this->mFrameHeight = this->mHeight / pTexture->getVerticalFramesCount(); 

	this->mFramesCount = pTexture->getHorizontalFramesCount() * pTexture->getVerticalFramesCount();

	this->mHorizontalFramesCount = pTexture->getHorizontalFramesCount();
	this->mVerticalFramesCount   = pTexture->getVerticalFramesCount();

	this->mTextureFileName = pTexture->mTextureFileName;

	int counter = 0;

	for(int i = 0; i < this->mVerticalFramesCount; i++)
	{
		for(int j = 0; j < this->mHorizontalFramesCount; j++, counter++)
		{
			this->mFramesCoordinatesX[counter] = j * (this->mWidth / this->mHorizontalFramesCount);
			this->mFramesCoordinatesY[counter] = i * (this->mHeight / this->mVerticalFramesCount);
		}
	}

	this->setCurrentFrameIndex(0);
}

void Entity::animate(float pAnimationTime)
{
	this->mAnimationFramesElapsed = 0;

	this->mAnimationTimeElapsed = 0;
	this->mAnimationTime = pAnimationTime;

	this->mAnimationRunning = true;

	this->onAnimationStart();
}

void Entity::animate(float pAnimationTime, int pRepeatCount)
{
	this->mAnimationRepeatCount = pRepeatCount;

	this->animate(pAnimationTime);
}

void Entity::animate(float pAnimationTime, int pRepeatCount, bool pReverseNeed)
{
	this->mIsAnimationReverseNeed = pReverseNeed;

	this->animate(pAnimationTime, pRepeatCount);
}

void Entity::animate(float pAnimationTime, float pPauseBeforeNewAnimationCircleTime)
{
	this->mPauseBeforeNewAnimationCircleTime = pPauseBeforeNewAnimationCircleTime;

	this->animate(pAnimationTime);
}

void Entity::animate(float pAnimationTime, int pRepeatCount, float pPauseBeforeNewAnimationCircleTime)
{
	this->mPauseBeforeNewAnimationCircleTime = pPauseBeforeNewAnimationCircleTime;

	this->animate(pAnimationTime, pRepeatCount);
}

void Entity::animate(float pAnimationTime, int pStartFrame, int pFinishFrame, int pRepeatCount)
{
	this->animate(pAnimationTime);

	this->mAnimationStartFrame = pStartFrame;
	this->mAnimationFinishFrame = pFinishFrame;

	this->mAnimationRepeatCount = pRepeatCount;

	this->setCurrentFrameIndex(pStartFrame);
}

void Entity::animate(float pAnimationTime, int pStartFrame, int pFinishFrame)
{
	this->animate(pAnimationTime, pStartFrame, pFinishFrame, -1);
}

void Entity::onAnimationStart()
{
}

void Entity::onAnimationEnd()
{
}

void Entity::onAnimationCircleEnd()
{
}

void Entity::setAnimationStartTimeout(float pSecodsTimeout)
{
	this->mAnimationStartTimeout = pSecodsTimeout;
}

void Entity::setStartFrame(int pStartFrame)
{
	this->mAnimationFinishFrame = (this->mAnimationFinishFrame - this->mAnimationStartFrame) + pStartFrame;
	this->mAnimationStartFrame = pStartFrame;
    
    this->setCurrentFrameIndex(pStartFrame);
}

void Entity::setFinishFrame(int pFinishFrame)
{
	this->mAnimationFinishFrame = pFinishFrame;
}

bool Entity::isAnimationRunning()
{
	return this->mAnimationRunning;
}

void Entity::setAnimationReverse(bool pReverse)
{
    this->mIsAnimationReverseNeed = pReverse;
}

/**
 *
 * Checing for touch detector
 *
 */

void Entity::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	CCSprite::onEnter();
}

void Entity::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);

	CCSprite::onExit();
}

bool Entity::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(!this->containsTouchLocation(touch) || !this->isVisible() || !this->getParent()->isVisible())
	{
		return false;
	}

	if(Touchable::ccTouchBegan(touch, event))
	{
        //this->setCurrentFrameIndex(1);
        
		this->mWasTouched = true;
        
		this->runAction(CCScaleTo::create(this->mAnimationScaleDownTime, this->mAnimationScaleDownFactor));

		return true;
	}

	return false;
}

void Entity::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(!containsTouchLocation(touch))
	{
		if(this->mWasTouched)
		{
			if(this->getScale() < this->mAnimationScaleUpFactor)
			{
				this->runAction(CCScaleTo::create(this->mAnimationScaleUpTime, this->mAnimationScaleUpFactor));
                
				this->mWasTouched = false;
                
                //this->setCurrentFrameIndex(0);
			}
		}
	}
}

void Entity::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(this->mWasTouched)
	{
		this->onTouch(touch, event);
        
		this->runAction(CCScaleTo::create(this->mAnimationScaleUpTime, this->mAnimationScaleUpFactor));
	}

	this->mWasTouched = false;
    
    //this->setCurrentFrameIndex(0);
}

bool Entity::containsTouchLocation(CCTouch* touch)
{
	return CCRectMake(-this->mFrameWidth/ 2, -this->mFrameHeight / 2, this->mFrameWidth, this->mFrameHeight).containsPoint(this->convertTouchToNodeSpaceAR(touch));
}

/**
 *
 * Let's take care about object copy
 *
 */

Entity* Entity::deepCopy()
{
	return new Entity(this->mTextureFileName, this->mHorizontalFramesCount, this->mVerticalFramesCount);
}

void Entity::update(float pDeltaTime)
{
	if(!this->isVisible()) return;

	if(this->mAnimationStartTimeout >= 0)
	{
		this->mAnimationStartTimeout -= pDeltaTime;
	}
	else
	{
		if(this->mAnimationRunning && (this->mAnimationRepeatCount > 0 || this->mAnimationRepeatCount < 0))
		{
			this->mAnimationTimeElapsed += pDeltaTime;

			if(this->mAnimationTimeElapsed >= this->mAnimationTime)
			{
				this->mAnimationTimeElapsed -= this->mAnimationTime;
                
                if(this->mIsAnimationReverseNeed)
                {
                    if(this->mIsAnimationReverse)
                    {
                        this->previousFrameIndex();
                        
                        if(this->getCurrentFrameIndex() <= 0)
                        {
                            this->mIsAnimationReverse = false;
                        }
                    }
                    else
                    {
                        this->nextFrameIndex();
                        
                        if(this->getCurrentFrameIndex() >= this->mFramesCount - 1)
                        {
                            this->mIsAnimationReverse = true;
                        }
                    }
                    
                    return;
                }

				if(this->mAnimationStartFrame == -1 && this->mAnimationFinishFrame == -1)
				{
					if(this->mIsAnimationReverse && this->getCurrentFrameIndex() == 0) // TODO: Add animation repeat counter.
					{
						this->mAnimationRunning = false;
						this->mIsAnimationReverse = false;

						this->mAnimationRunning = false;

						this->onAnimationEnd();
							
						return;
					}
                    if(this->mAnimationRepeatCount > 0 && this->getCurrentFrameIndex() == this->mFramesCount - 1)
					{
						this->mAnimationRepeatCount--;

						if(this->mAnimationRepeatCount == 0)
						{
							if(this->mIsAnimationReverseNeed)
							{
								this->mAnimationRepeatCount++;

								this->mIsAnimationReverseNeed = false;
								this->mIsAnimationReverse = true;
						
								this->previousFrameIndex();

								return;
							}
							else
							{
								this->mAnimationRunning = false;

								this->onAnimationEnd();
							}
						}
					}

					if(this->getCurrentFrameIndex() == this->mFramesCount - 1)
					{
						this->onAnimationCircleEnd();

						if(this->mPauseBeforeNewAnimationCircleTime > 0)
						{
							this->mPauseBeforeNewAnimationCircleTimeElapsed += pDeltaTime;

							if(this->mPauseBeforeNewAnimationCircleTimeElapsed < this->mPauseBeforeNewAnimationCircleTime)
							{
								return;
							}
							else
							{
								this->mPauseBeforeNewAnimationCircleTimeElapsed = 0;
							}
						}
					}

					if(this->mIsAnimationReverse)
					{
						this->previousFrameIndex();
					}
					else
					{
						this->nextFrameIndex();
					}
				}
				else
				{
					if(this->getCurrentFrameIndex() < this->mAnimationFinishFrame)
					{
						this->setCurrentFrameIndex(this->mAnimationStartFrame + this->mAnimationFramesElapsed + 1);

						this->mAnimationFramesElapsed++;
					}
					else
					{
						if(this->mAnimationRepeatCount > 0)
						{
							this->mAnimationRepeatCount--;
                            
							this->mAnimationFramesElapsed = 0;
                            
							if(this->mAnimationRepeatCount == 0)
							{
								this->mAnimationRunning = false;
                                
								this->onAnimationEnd();
							}
						}
						else
						{
							this->mAnimationFramesElapsed = 0;
                            
							this->setCurrentFrameIndex(this->mAnimationStartFrame);
						}
					}
				}
			}
		}
	}
    
    if(this->mIsShadowed)
    {
        this->mShadow->setCenterPosition(this->getCenterX() - Utils::coord(20.0f), this->getCenterY() - Utils::coord(20.0f));
        this->mShadow->setScaleY(this->getScaleY() - 0.1f);
        this->mShadow->setScaleX(this->getScaleX() - 0.1f);
        this->mShadow->setRotation(this->getRotation());
        this->mShadow->setCurrentFrameIndex(this->getCurrentFrameIndex());
        //this->mShadow->setVisible(this->isVisible());
    }
}

void Entity::draw()
{
	CCSprite::draw();
}

#endif