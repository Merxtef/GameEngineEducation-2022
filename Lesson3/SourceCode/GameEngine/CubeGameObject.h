#pragma once

#include "GameObject.h"
#include "InputHandler.h"

class AbstractCube : public GameObject
{
public:
	AbstractCube();

	virtual void Act(InputHandler* inputHandler, float dt) = 0;

	void SetStart(float x, float y, float z);

protected:
	float start_x = 0;
	float start_y = 0;
	float start_z = 0;
};

class UserControlledCube : public AbstractCube
{
public:
	UserControlledCube(float speed);

	virtual void Act(InputHandler* inputHandler, float dt) override;

private:
	float speed = 1.0f;
};

class JumpingCube : public AbstractCube
{
public:
	JumpingCube(float current_speed, float floor_level);

	virtual void Act(InputHandler* inputHandler, float dt) override;

private:
	float current_speed = 0.0f;
	float floor_level = 0.0f;
};

class SelfMovingCube : public AbstractCube
{
public:
	SelfMovingCube(float speed, float max_dz);

	virtual void Act(InputHandler* inputHandler, float dt) override;

private:
	const float speed = 1.0f;
	const float max_dz = 10.0f;
	float cur_speed = speed;
};

