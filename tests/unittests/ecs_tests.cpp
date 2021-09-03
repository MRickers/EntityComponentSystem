#include "gtest/gtest.h"
#include "ecs/entity_manager.h"
#include "ecs/component_array.h"

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
	ASSERT_NO_THROW(e.DestroyEntity(entity));
}

TEST(EntityManagerTest, DestroyNotCreatedEntity) {
	ecs::EntityManager e;
	ASSERT_THROW(e.DestroyEntity(0), ecs::Exception);	
	ASSERT_THROW(e.DestroyEntity(-1), ecs::Exception);
}

TEST(EntityManagerTest, SetSignature) {
	ecs::EntityManager e;

	const auto entity = e.CreateEntity();
	ASSERT_NO_THROW(e.SetSignature(entity, ecs::Signature{ "001" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::Signature{ "001" });
	ASSERT_NO_THROW(e.SetSignature(entity, ecs::Signature{ "010" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::Signature{ "010" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::Signature{ "100" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::Signature{ "100" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::Signature{ "110" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::Signature{ "110" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::Signature{ "011" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::Signature{ "011" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::Signature{ "101" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::Signature{ "101" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::Signature{ "111" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::Signature{ "111" });
}

TEST(EntityManagerTest, SetSignatureNotExist) {
	ecs::EntityManager e;

	ASSERT_THROW(e.SetSignature(0, ecs::Signature{ "000" }), ecs::Exception);
}

TEST(EntityManagerTest, GetSignatureNotExist) {
	ecs::EntityManager e;

	ASSERT_THROW(e.GetSignature(512), ecs::Exception);
	ASSERT_THROW(e.GetSignature(-1), ecs::Exception);
}

// ComponentArray

TEST(ComponentArrayTest, Insert) {
	ecs::ComponentArray<int> components;
	ASSERT_NO_THROW(components.Insert(0, 1));	
}

TEST(ComponentArrayTest, InsertThrow) {
	ecs::ComponentArray<int> components;
	for (int i = 0; i < 512; i++) {
		ASSERT_NO_THROW(components.Insert(i, 1));
	}
	ASSERT_THROW(components.Insert(513, 1), ecs::Exception);
	
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}