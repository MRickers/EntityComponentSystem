#include "gtest/gtest.h"
#include "ecs/entity_manager.h"

TEST(EntityManagerTest, CreateEntityTest) {
	ecs::EntityManager entity_manager(5);

	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)0);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)1);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)2);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)3);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)4);
}

TEST(EntityManagerTest, CreateEntityMaxCountTest) {
	ecs::EntityManager entity_manager(5);

	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)0);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)1);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)2);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)3);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)4);
	ASSERT_THROW(entity_manager.CreateEntity(), ecs::Exception);
}

TEST(EntityManagerTest, CreateEntityNegative) {
	ecs::EntityManager entity_manager(-5);
	const auto max_entity_count = 512;

	for (int i = 0; i < max_entity_count-1; i++) {
		ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)i);
	}
}

TEST(EntityManagerTest, DestroyEntity) {
	ecs::EntityManager e;

	const auto entity = e.CreateEntity();
	ASSERT_EQ(entity, (uint16_t)0);
	e.DestroyEntity(entity);
	ASSERT_TRUE(true);
}

TEST(EntityManagerTest, DestroyNotCreatedEntity) {
	ecs::EntityManager e;
	ASSERT_THROW(e.DestroyEntity(0), ecs::Exception);	
	ASSERT_THROW(e.DestroyEntity(-1), ecs::Exception);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}