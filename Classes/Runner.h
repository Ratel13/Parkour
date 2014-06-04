#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "chipmunk.h"

enum RunnerState
{
    RunnerStateRunning = 0,
    RunnerStateJumpUp,
    RunnerStateJumpDown,
    RunnerStateCrouch,
    RunnerStateIncredible
};

class Runner : public cocos2d::extension::CCPhysicsSprite
{
public:

	static Runner *create(cpSpace* space);

	Runner(cpSpace *space);
	~Runner();

	void initAction();
	void initBody();
	void initShape(const char* type);
	void levelUp();
	void jump();
	void crouch();
	void step(float dt);
	void loadNormal(float dt);
	float getoffsetPx() {return m_offsetPx;}

	static const cocos2d::CCSize getCrouchContentSize()
	{
		CCPhysicsSprite* sprite = CCPhysicsSprite::createWithSpriteFrameName("runnerCrouch0.png");
		return sprite->getContentSize();
	}

private:
	RunnerState m_state;
	cocos2d::CCSize  m_runningSize;
	cocos2d::CCSize m_crouchSize;

    cpSpace* space;
    cpBody* body;
    cpShape* shape;

	cocos2d::CCAction* m_actionRunning;
	cocos2d::CCAction* m_actionJumpUp;
	cocos2d::CCAction* m_actionJumpDown;
	cocos2d::CCAction* m_actionCrouch;

    cocos2d::CCParticleFlower* m_emitter;

    float m_offsetPx;
};

