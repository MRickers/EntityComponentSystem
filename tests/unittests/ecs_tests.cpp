#include "gtest/gtest.h"
#include "ecs/entity_manager.h"
#include "ecs/component_array.h"
#include "ecs/component_manager.h"

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


TEST(ComponentArrayTest, Remove) {
	ecs::ComponentArray<int> components;

	ASSERT_NO_THROW(components.Insert(0, 0));
	ASSERT_NO_THROW(components.Insert(1, 1));
	ASSERT_NO_THROW(components.Insert(35, 35));
	ASSERT_NO_THROW(components.Insert(44, 44));

	ASSERT_NO_THROW(components.Remove(0));
	ASSERT_NO_THROW(components.Remove(35));
	ASSERT_NO_THROW(components.Remove(44));
	ASSERT_NO_THROW(components.Remove(1));
}


TEST(ComponentArrayTest, RemoveEmptyThrow) {
	ecs::ComponentArray<int> components;

	ASSERT_THROW(components.Remove(0), ecs::Exception);
}

TEST(ComponentArrayTest, Get) {
	ecs::ComponentArray<int> components;

	ASSERT_NO_THROW(components.Insert(25, 25));
	ASSERT_NO_THROW(components.Insert(33, 33));
	ASSERT_NO_THROW(components.Insert(400, 400));
	ASSERT_NO_THROW(components.Insert(8799, 8799));

	ASSERT_EQ(components.Get(25), 25);
	ASSERT_EQ(components.Get(33), 33);
	ASSERT_EQ(components.Get(400), 400);
	ASSERT_EQ(components.Get(8799), 8799);
}

TEST(ComponentArrayTest, GetEmptyThrow) {
	ecs::ComponentArray<int> components;

	ASSERT_THROW(components.Get(25), ecs::Exception);
}

TEST(CompontenManagerTest, RegisterComponent) {
	ecs::ComponentManager components;

	components.RegisterComponent<int>();
}

TEST(ComponentManagerTest, AddComponent) {
	struct Vec { int x; int y; };

	ecs::ComponentManager components;
	struct Vec v{0,1};

	components.RegisterComponent<Vec>();
	ASSERT_NO_THROW(components.AddComponent<Vec>(0, v));
}

TEST(ComponentManagerTest, AddComponentNotRegistered) {
	struct Vec { int x; int y; };

	ecs::ComponentManager components;
	struct Vec v { 0, 1 };

	ASSERT_THROW(components.AddComponent<Vec>(0, v), ecs::Exception);
}

TEST(ComponentManagerTest, GetComponent) {
	struct Vec { int x; int y; };

	ecs::ComponentManager components;
	struct Vec v { 0, 1 };
	components.RegisterComponent<Vec>();
	ASSERT_NO_THROW(components.AddComponent<Vec>(0, v));

	const auto& c = components.GetComponent<Vec>(0);
	ASSERT_EQ(c.x, v.x);
	ASSERT_EQ(c.y, v.y);
}

TEST(ComponentManagerTest, GetComponentChangeValue) {
	struct Vec { int x; int y; };

	ecs::ComponentManager components;
	struct Vec v { 0, 1 };
	components.RegisterComponent<Vec>();
	ASSERT_NO_THROW(components.AddComponent<Vec>(0, v));

	auto& c = components.GetComponent<Vec>(0);
	c.x = 2;
	c.y = 2;

	ASSERT_EQ(components.GetComponent<Vec>(0).x, 2);
	ASSERT_EQ(components.GetComponent<Vec>(0).y, 2);
}

TEST(ComponentManagerTest, GetComponentMultipleEntities) {
	struct Vec { int x; int y; };

	ecs::ComponentManager components;
	components.RegisterComponent<Vec>();

	for (int i = 0; i < 512; ++i) {
		ASSERT_NO_THROW(components.AddComponent<Vec>(i, { i,i }));
	}

	for (int i = 0; i < 512; ++i) {
		ASSERT_EQ(components.GetComponent<Vec>(i).x, i);
		ASSERT_EQ(components.GetComponent<Vec>(i).y, i);
	}
}

TEST(ComponentManagerTest, GetComponentMultipleComponents) {
	struct Vec { int x; int y; };
	struct Property { float version=0; std::string name=""; };
	struct Test { uint16_t t1=0; int32_t t2=0; std::string t3=""; };

	ecs::ComponentManager components;
	components.RegisterComponent<Vec>();
	components.RegisterComponent<Property>();
	components.RegisterComponent<Test>();

	for (int i = 0; i < 512; ++i) {
		ASSERT_NO_THROW(components.AddComponent<Vec>(i, { i,i }));
		Property prop{ i,"name" };
		ASSERT_NO_THROW(components.AddComponent<Property>(i, prop));
		Test testo{ i + 1, i + 2, "hello" };
		ASSERT_NO_THROW(components.AddComponent<Test>(i, testo));
	}

	for (int i = 0; i < 512; ++i) {
		ASSERT_EQ(components.GetComponent<Vec>(i).x, i);
		ASSERT_EQ(components.GetComponent<Vec>(i).y, i);
		ASSERT_EQ(components.GetComponent<Property>(i).version, i);
		ASSERT_EQ(components.GetComponent<Property>(i).name, "name");
		ASSERT_EQ(components.GetComponent<Test>(i).t1, i+1);
		ASSERT_EQ(components.GetComponent<Test>(i).t2, i + 2);
	}
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}