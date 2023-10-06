#include "ecsShoot.h"
#include "ecsPhys.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "../InputHandler.h"

void register_ecs_shoot_systems(flecs::world& ecs)
{
	static auto inputQuery = ecs.query<InputHandlerPtr>();

	// Shooting
	ecs.system<const Position, Shooter>()
		.each([&](flecs::entity e, const Position& pos, Shooter& shooter)
			{
				if (shooter.magazine <= 0)
					return;

				if (shooter.reloadTime > 0)
				{
					shooter.reloadTime -= e.delta_time();
					return;
				}

				if (shooter.nextShotTime > 0)
				{
					shooter.nextShotTime -= e.delta_time();
					return;
				}

				inputQuery.each([&](InputHandlerPtr input)
					{
						if (!input.ptr->GetInputState().test(eIC_Shoot))
							return;

						e.world().entity()
							.set(Position{ pos })
							.set(Velocity{ shooter.bulletVelocity[0], shooter.bulletVelocity[1], shooter.bulletVelocity[2] })
							.set(Gravity{ 0.f, -9.8065f, 0.f })
							.set(Floor{ 0.f, 1.f, 0.f })
							.set(BouncePlane{ 0.f, 1.f, 0.f, 0.3f })
							.set(FrictionAmount{ 1.f })
							.set(Bounciness{ 0.2f })
							.set(Bullet{ 1.0f, e.id()})
							.add<CubeMesh>()
							.add<DestroyOnFloorCollision>();

						--shooter.magazine;

						if (shooter.magazine > 0)
						{
							shooter.nextShotTime = MAX_NEXT_SHOT_TIME;
							return;
						}

						if (shooter.ammo <= 0)
							return;

						shooter.reloadTime = MAX_RELOAD_TIME;
						if (shooter.ammo < MAGAZINE_SIZE) 
						{
							shooter.magazine = shooter.ammo;
							shooter.ammo = 0;
						}
						else
						{
							shooter.magazine = MAGAZINE_SIZE;
							shooter.ammo -= MAGAZINE_SIZE;
						}
					});
			});
	
	// Set destruction timer of floor collision
	ecs.system<const Position, const Floor, const DestroyOnFloorCollision>()
		.each([&](flecs::entity e, const Position& pos, const Floor& floor, const DestroyOnFloorCollision& _)
			{
				float altitude = floor.x * pos.x + floor.y * pos.y + floor.z * pos.z;

				if (altitude < FLOOR_WIDTH) {
					e.remove<DestroyOnFloorCollision>();
					e.set(DestroyAfter{ 0.5f });
				}
			});

	// General bullet logic
	ecs.system<Bullet, const Position>()
		.each([&](flecs::entity e, Bullet& bullet, const Position& pos)
			{
				// Target collision
				e.world().filter<Target, const Position>()
					.each([&](flecs::entity t, Target& target, const Position& tPos) {
							float dx = tPos.x - pos.x;
							float dy = tPos.y - pos.y;
							float dz = tPos.z - pos.z;

							if (dx * dx + dy * dy + dz * dz > bullet.radius)
								return;

							t.set(DestroyAfter{ -1 });

							auto* reward = t.get<AmmoReward>();

							if (reward)
							{
								e.world().filter<Shooter>()  // Looks already too much...
									.each([&](flecs::entity t, Shooter& shooter) {
											if (t.id() != bullet.sender_id)
												return;

											shooter.magazine += reward->amount;
										});
							}
						});
			});

	// Destroy after timer runs out
	ecs.system<DestroyAfter, const RenderProxyPtr>()
		.each([&](flecs::entity e, DestroyAfter& d, const RenderProxyPtr& proxy)
			{
				d.time -= e.delta_time();

				if (d.time > 0)
					return;

				delete proxy.ptr;
				e.destruct();
			});
}
