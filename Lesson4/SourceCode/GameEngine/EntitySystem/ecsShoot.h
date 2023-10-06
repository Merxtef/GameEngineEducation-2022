#pragma once
#include "flecs.h"

constexpr int MAGAZINE_SIZE = 6;
constexpr float MAX_RELOAD_TIME = 3.0f;
constexpr float MAX_NEXT_SHOT_TIME = 0.5f;
constexpr float FLOOR_WIDTH = 1.f;

struct Shooter {
	int ammo;
	int magazine;

	float reloadTime;
	float nextShotTime;

	float bulletVelocity[3];
};

struct Bullet {
	float radius;
	flecs::entity_t sender_id;
};

struct Floor {
	float x;
	float y;
	float z;
};

struct DestroyOnFloorCollision {};

struct DestroyAfter {
	float time;
};

struct Target {};

struct AmmoReward {
	int amount;
};

void register_ecs_shoot_systems(flecs::world& ecs);
