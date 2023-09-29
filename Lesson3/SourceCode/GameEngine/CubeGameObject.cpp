#include "CubeGameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

constexpr float g = 9.8f;

CubeGameObject::CubeGameObject()
{
	m_pRenderProxy = new CubeRenderProxy();
}

AbstractCube::AbstractCube()
{
	m_pRenderProxy = new CubeRenderProxy();
}

void AbstractCube::SetStart(float x, float y, float z)
{
    start_x = x;
    start_y = y;
    start_z = z;

    this->SetPosition(x, y, z);
}

UserControlledCube::UserControlledCube(float speed)
    : speed(speed) { }

void UserControlledCube::Act(InputHandler* inputHandler, float dt)
{
    float x = this->m_vPosition[0];
    float y = this->m_vPosition[1];
    float z = this->m_vPosition[2];

    float velocity = 0.0f;
    if (inputHandler->GetInputState().test(eIC_GoLeft))
        velocity -= 1.0f;
    if (inputHandler->GetInputState().test(eIC_GoRight))
        velocity += 1.0f;
    x += speed * velocity * dt;

    this->SetPosition(x, y, z);
}

JumpingCube::JumpingCube(float current_speed, float floor_level)
    : current_speed(current_speed), floor_level(floor_level) { }

void JumpingCube::Act(InputHandler* inputHandler, float dt)
{
    float x = this->m_vPosition[0];
    float y = this->m_vPosition[1];
    float z = this->m_vPosition[2];

    current_speed -= g * dt;
    y += current_speed * dt;

    if (y < floor_level)
    {
        y = floor_level;
        current_speed *= -1;
    }

    this->SetPosition(x, y, z);
}

SelfMovingCube::SelfMovingCube(float speed, float max_dz)
    : speed(speed), max_dz(max_dz) { }

void SelfMovingCube::Act(InputHandler* inputHandler, float dt)
{
    float x = this->m_vPosition[0];
    float y = this->m_vPosition[1];
    float z = this->m_vPosition[2];

    z += cur_speed * dt;

    float dz = z - start_z;

    if (dz > max_dz)
    {
        cur_speed = -speed;
        z = start_z + max_dz;
    }
    else if (dz < -max_dz)
    {
        cur_speed = speed;
        z = start_z - max_dz;
    }

    this->SetPosition(x, y, z);
}
