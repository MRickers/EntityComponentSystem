#include "gtest/gtest.h"
#include "ecs/core/entity_manager.h"
#include "ecs/core/component_array.h"
#include "ecs/core/component_manager.h"
#include "ecs/core/system_manager.h"
#include "ecs/core/entity_component_system.h"
#include "logging/logging.h"

/*#include "ecs/event/event.h"
#include "ecs/event/event_handler.h"
*/
#include "ecs/event/event_new.h"

TEST(EntityManagerTest, CreateEntityTest) {
	ecs::core::EntityManager entity_manager(5);

	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)0);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)1);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)2);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)3);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)4);
}

TEST(EntityManagerTest, CreateEntityMaxCountTest) {
	ecs::core::EntityManager entity_manager(5);

	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)0);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)1);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)2);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)3);
	ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)4);
	ASSERT_THROW(entity_manager.CreateEntity(), ecs::core::Exception);
}

TEST(EntityManagerTest, CreateEntityNegative) {
	ecs::core::EntityManager entity_manager(-5);
	const auto max_entity_count = 512;

	for (int i = 0; i < max_entity_count-1; i++) {
		ASSERT_EQ(entity_manager.CreateEntity(), (uint16_t)i);
	}
}

TEST(EntityManagerTest, DestroyEntity) {
	ecs::core::EntityManager e;

	const auto entity = e.CreateEntity();
	ASSERT_EQ(entity, (uint16_t)0);
	ASSERT_NO_THROW(e.DestroyEntity(entity));
}

TEST(EntityManagerTest, DestroyNotCreatedEntity) {
	ecs::core::EntityManager e;
	ASSERT_THROW(e.DestroyEntity(0), ecs::core::Exception);	
	ASSERT_THROW(e.DestroyEntity(-1), ecs::core::Exception);
}

TEST(EntityManagerTest, SetSignature) {
	ecs::core::EntityManager e;

	const auto entity = e.CreateEntity();
	ASSERT_NO_THROW(e.SetSignature(entity, ecs::core::Signature{ "001" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::core::Signature{ "001" });
	ASSERT_NO_THROW(e.SetSignature(entity, ecs::core::Signature{ "010" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::core::Signature{ "010" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::core::Signature{ "100" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::core::Signature{ "100" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::core::Signature{ "110" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::core::Signature{ "110" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::core::Signature{ "011" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::core::Signature{ "011" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::core::Signature{ "101" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::core::Signature{ "101" });

	ASSERT_NO_THROW(e.SetSignature(entity, ecs::core::Signature{ "111" }));
	ASSERT_EQ(e.GetSignature(entity), ecs::core::Signature{ "111" });
}

TEST(EntityManagerTest, SetSignatureNotExist) {
	ecs::core::EntityManager e;

	ASSERT_THROW(e.SetSignature(0, ecs::core::Signature{ "000" }), ecs::core::Exception);
}

TEST(EntityManagerTest, GetSignatureNotExist) {
	ecs::core::EntityManager e;

	ASSERT_THROW(e.GetSignature(512), ecs::core::Exception);
	ASSERT_THROW(e.GetSignature(-1), ecs::core::Exception);
}

// ComponentArray

TEST(ComponentArrayTest, Insert) {
	ecs::core::ComponentArray<int> components;
	ASSERT_NO_THROW(components.Insert(0, 1));	
}

TEST(ComponentArrayTest, InsertThrow) {
	ecs::core::ComponentArray<int> components;
	for (int i = 0; i < 512; i++) {
		ASSERT_NO_THROW(components.Insert(i, 1));
	}
	ASSERT_THROW(components.Insert(513, 1), ecs::core::Exception);
}

TEST(ComponentArrayTest, Remove) {
	ecs::core::ComponentArray<int> components;

	ASSERT_NO_THROW(components.Insert(0, 0));
	ASSERT_NO_THROW(components.Insert(1, 1));
	ASSERT_NO_THROW(components.Insert(35, 35));
	ASSERT_NO_THROW(components.Insert(44, 44));

	ASSERT_NO_THROW(components.Remove(0));
	ASSERT_NO_THROW(components.Remove(35));
	ASSERT_NO_THROW(components.Remove(44));
	ASSERT_NO_THROW(components.Remove(1));

	ASSERT_THROW(components.Get(0), ecs::core::Exception);
	ASSERT_THROW(components.Get(35), ecs::core::Exception);
	ASSERT_THROW(components.Get(44), ecs::core::Exception);
	ASSERT_THROW(components.Get(1), ecs::core::Exception);
}

TEST(ComponentArrayTest, RemoveEmptyThrow) {
	ecs::core::ComponentArray<int> components;

	ASSERT_THROW(components.Remove(0), ecs::core::Exception);
}

TEST(ComponentArrayTest, Destroy) {
	ecs::core::ComponentArray<int> components;

	ASSERT_NO_THROW(components.Insert(0, 0));
	ASSERT_NO_THROW(components.Insert(1, 1));
	ASSERT_NO_THROW(components.Insert(35, 35));
	ASSERT_NO_THROW(components.Insert(44, 44));

	ASSERT_NO_THROW(components.DestroyEntity(0));
	ASSERT_NO_THROW(components.DestroyEntity(35));
	ASSERT_NO_THROW(components.DestroyEntity(44));
	ASSERT_NO_THROW(components.DestroyEntity(1));

	ASSERT_THROW(components.Get(0), ecs::core::Exception);
	ASSERT_THROW(components.Get(35), ecs::core::Exception);
	ASSERT_THROW(components.Get(44), ecs::core::Exception);
	ASSERT_THROW(components.Get(1), ecs::core::Exception);
}


TEST(ComponentArrayTest, DestroyEmptyThrow) {
	ecs::core::ComponentArray<int> components;

	ASSERT_THROW(components.DestroyEntity(0), ecs::core::Exception);
}

TEST(ComponentArrayTest, Get) {
	ecs::core::ComponentArray<int> components;

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
	ecs::core::ComponentArray<int> components;

	ASSERT_THROW(components.Get(25), ecs::core::Exception);
}

TEST(CompontenManagerTest, RegisterComponent) {
	ecs::core::ComponentManager components;

	components.RegisterComponent<int>();
}

TEST(ComponentManagerTest, AddComponent) {
	struct Vec { int x; int y; };

	ecs::core::ComponentManager components;
	struct Vec v{0,1};

	components.RegisterComponent<Vec>();
	ASSERT_NO_THROW(components.AddComponent<Vec>(0, v));
}

TEST(ComponentManagerTest, AddComponentNotRegistered) {
	struct Vec { int x; int y; };

	ecs::core::ComponentManager components;
	struct Vec v { 0, 1 };

	ASSERT_THROW(components.AddComponent<Vec>(0, v), ecs::core::Exception);
}

TEST(ComponentManagerTest, RemoveComponent) {
	struct Vec { int x; int y; };

	ecs::core::ComponentManager components;
	struct Vec v { 0, 1 };

	components.RegisterComponent<Vec>();
	ASSERT_NO_THROW(components.AddComponent<Vec>(0, v));
	ASSERT_NO_THROW(components.RemoveComponent<Vec>(0));
	ASSERT_THROW(components.GetComponent<Vec>(0), ecs::core::Exception);
}

TEST(ComponentManagerTest, RemoveComponentNotAdded) {
	struct Vec { int x; int y; };

	ecs::core::ComponentManager components;
	struct Vec v { 0, 1 };

	components.RegisterComponent<Vec>();
	ASSERT_THROW(components.RemoveComponent<Vec>(0), ecs::core::Exception);
}

TEST(ComponentManagerTest, GetComponent) {
	struct Vec { int x; int y; };

	ecs::core::ComponentManager components;
	struct Vec v { 0, 1 };
	components.RegisterComponent<Vec>();
	ASSERT_NO_THROW(components.AddComponent<Vec>(0, v));

	const auto& c = components.GetComponent<Vec>(0);
	ASSERT_EQ(c.x, v.x);
	ASSERT_EQ(c.y, v.y);
}

TEST(ComponentManagerTest, GetComponentChangeValue) {
	struct Vec { int x; int y; };

	ecs::core::ComponentManager components;
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

	ecs::core::ComponentManager components;
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

	ecs::core::ComponentManager components;
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

TEST(ComponentManagerTest, GetComponentType) {
	struct Vec { int x; int y; };
	struct Property { float version = 0; std::string name = ""; };

	ecs::core::ComponentManager components;
	components.RegisterComponent<Vec>();
	components.RegisterComponent<Property>();

	ASSERT_EQ(components.GetComponentType<Vec>(), 0);
	ASSERT_EQ(components.GetComponentType<Property>(), 1);
}

TEST(ComponentManagerTest, GetComponentTypeEmpty) {
	struct Vec { int x; int y; };
	ecs::core::ComponentManager components;

	ASSERT_THROW(components.GetComponentType<Vec>(), ecs::core::Exception);
}

TEST(ComponentManagerTest, GetComponentTypeNotRegistered) {
	struct Vec { int x; int y; };
	struct Property { float version = 0; std::string name = ""; };
	ecs::core::ComponentManager components;

	ASSERT_THROW(components.GetComponentType<Property>(), ecs::core::Exception);
}

TEST(SystemManagerTest, RegisterSystem) {
	struct TestSystem : public ecs::core::System {};

	ecs::core::SystemManager systems;
	ASSERT_NO_THROW(systems.RegisterSystem<TestSystem>());
}

TEST(SystemManagerTest, RegisterSystemDouble) {
	struct TestSystem : public ecs::core::System {};

	ecs::core::SystemManager systems;
	ASSERT_NO_THROW(systems.RegisterSystem<TestSystem>());
	ASSERT_THROW(systems.RegisterSystem<TestSystem>(), ecs::core::Exception);
}

TEST(SystemManagerTest, SetSignature) {
	struct TestSystem : public ecs::core::System {};

	ecs::core::SystemManager systems;
	ASSERT_NO_THROW(systems.RegisterSystem<TestSystem>());
	ASSERT_NO_THROW(systems.SetSignature<TestSystem>(ecs::core::Signature{ "001" }));
}

TEST(SystemManagerTest, SetSignatureDouble) {
	struct TestSystem : public ecs::core::System {};

	ecs::core::SystemManager systems;
	ASSERT_NO_THROW(systems.RegisterSystem<TestSystem>());
	ASSERT_NO_THROW(systems.SetSignature<TestSystem>(ecs::core::Signature{ "001" }));
	ASSERT_THROW(systems.SetSignature<TestSystem>(ecs::core::Signature("010")), ecs::core::Exception);
}

TEST(SystemManagerTest, SetEntitySignature) {
	struct TestSystem : public ecs::core::System {};

	ecs::core::SystemManager systems;
	ASSERT_NO_THROW(systems.RegisterSystem<TestSystem>());
	ASSERT_NO_THROW(systems.SetSignature<TestSystem>(ecs::core::Signature("001")));
	ASSERT_NO_THROW(systems.SetEntitySignature(0, ecs::core::Signature("001")));
	ASSERT_NO_THROW(systems.SetEntitySignature(0, ecs::core::Signature("010")));
}

TEST(SystemManagerTest, DestroyEntity) {
	struct TestSystem : public ecs::core::System {};

	ecs::core::SystemManager systems;
	ASSERT_NO_THROW(systems.RegisterSystem<TestSystem>());
	ASSERT_NO_THROW(systems.SetSignature<TestSystem>(ecs::core::Signature("001")));
	ASSERT_NO_THROW(systems.SetEntitySignature(0, ecs::core::Signature("001")));
	ASSERT_NO_THROW(systems.DestroyEntity(0));
}

TEST(EntityComponentSystem, Create) {
	ecs::core::EntityComponentSystem ECS;
}

TEST(Logging, ConsoleLogTest) {
	lLog(lDebug) << "ConsoleTest" << " abcdefg " << 5 * 5;
	lLog(lDebug) << "Hello " << " there " << "!";
}
/*
TEST(MemberFunctionHandler, InvokeCallback) {
	struct TestEvent : public ecs::event::IEvent {
	public:
		TestEvent(int x, int y) : x_(x), y_(y) {}
		int x_; int y_;
	};

	class TestSystem : public ecs::core::System {
	public:
		TestSystem() = default;
		~TestSystem() = default;

		void testCallback(const std::shared_ptr<TestEvent> test) {
			test->x_ += 1;
			test->y_ += 1;
		}
	};

	ecs::event::MemberFunctionHandler handler {std::make_unique<TestSystem>(), & TestSystem::testCallback};
	
	ASSERT_NO_THROW(handler.Exec(std::make_shared<TestEvent>(1, 2)));
}

TEST(EventHandler, InvokeCallback) {
	struct TestEvent : public ecs::event::IEvent {
	public:
		TestEvent(int x, int y) : x_(x), y_(y) {}
		int x_; int y_;
	};

	class TestSystem : public ecs::core::System {
	public:
		TestSystem() = default;
		~TestSystem() = default;

		void testCallback(const std::shared_ptr<TestEvent> test) {
			test->x_ += 1;
			test->y_ += 1;
		}
	};
	
	ecs::event::EventHandler event_handler;

	ASSERT_NO_THROW(event_handler.Subscribe(std::make_unique<TestSystem>(), &TestSystem::testCallback));
	const auto testo = std::make_shared<TestEvent>(1, 1);
	ASSERT_NO_THROW(event_handler.Publish(testo));
	ASSERT_EQ(testo->x_, 2);
	ASSERT_EQ(testo->y_, 2);
} */

TEST(EventHandler, Subscribe) {
	struct TestEvent {
	public:
		TestEvent(int x, int y) : x_(x), y_(y) {}
		int x_; int y_;
	};

	class TestSystem : public ecs::core::System {
	public:
		TestSystem() = default;
		~TestSystem() = default;

		void testCallback(const ecs::event::Event& test) {
			auto data = test.GetData<TestEvent>();
			data.x_ += 1;
			data.y_ += 1;
		}
	};

	ecs::event::EventHandler event_handler;
	ASSERT_NO_THROW(event_handler.Subscribe(0, std::bind(&TestSystem::testCallback, std::make_shared<TestSystem>(), std::placeholders::_1)));
	ecs::event::Event test_event {TestEvent{1, 1}, 0};
	ASSERT_NO_THROW(event_handler.Publish(test_event));
	const auto data = test_event.GetData<TestEvent>();
	ASSERT_EQ(data.x_, 2);
	ASSERT_EQ(data.y_, 2);
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}