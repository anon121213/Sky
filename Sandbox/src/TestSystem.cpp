#include "TestSystem.h"

#include "Sky/Components/Transform.h"

void TestSystem::OnAwake(Sky::World& world)
{
	const Sky::Entity firstEntity = GetRegistry().Create();
	const Sky::Entity secondEntity = GetRegistry().Create();
	const Sky::Entity thirdEntity = GetRegistry().Create();
	const Sky::Entity fourEntity = GetRegistry().Create();

	GetRegistry().CreateGroup<Sky::Transform>();

	GetRegistry().Replace<Sky::Transform>(firstEntity, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 1 });
	GetRegistry().Replace<Sky::Transform>(secondEntity, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 2, 1 });

	GetRegistry().Replace<Sky::Transform>(thirdEntity, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 1 });
	GetRegistry().Replace<Sky::Transform>(fourEntity, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 2, 1 });
}

void TestSystem::OnUpdate(Sky::World& world, Sky::Timestep dt)
{
	// group each
		
	const auto& foundGroup = GetRegistry().GetGroup<Sky::Transform>();

	foundGroup->Each([&dt](Sky::Entity e, Sky::Transform& t)
	{
		SKY_INFO("Group Entity {0}: pos {1} {2} {3}", e, t.Position.x, t.Position.y + dt, t.Position.z);
		SKY_INFO("Group Entity {0}: Rotation {1} {2} {3}", e, t.Rotation.x, t.Rotation.y + dt, t.Rotation.z);
		SKY_INFO("Group Entity {0}: Scale {1} {2} {3}", e, t.Scale.x, t.Scale.y + dt, t.Scale.z);
	});

	// view each

	GetRegistry().View<Sky::Transform>([&dt](Sky::Entity e, Sky::Transform& t)
	{
		SKY_INFO("Entity {0}: Position {1} {2} {3}", e, t.Position.x, t.Position.y + dt, t.Position.z);
		SKY_INFO("Entity {0}: Rotation {1} {2} {3}", e, t.Rotation.x, t.Rotation.y + dt, t.Rotation.z);
		SKY_INFO("Entity {0}: Scale {1} {2} {3}", e, t.Scale.x, t.Scale.y + dt, t.Scale.z);
	});
}
