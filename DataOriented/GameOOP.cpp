
#include <vector>

enum ComponentType
{
	AI,
	PHYSICS,
	RENDERING
};

class Component
{
public:
	virtual ~Component() {}
	virtual void Update() = 0;

private:
	int cId;
};

class UnitAI :public Component
{
public:
	virtual ~UnitAI() {}
	virtual void Update();
};

class UnitPhysics :public Component
{
public:
	virtual ~UnitPhysics() {}
	virtual void Update();
};

class UnitRendering :public Component
{
public:
	virtual ~UnitRendering() {}
	virtual void Update();
	void Render();
	bool IsAcitve();
};

class Entity
{
public:
	Component *GetComponent(int id);
	void AddComponent(Component *comp);
	void RemoveComponent(int id);
	bool HasComponent(int id);

	std::vector<Component*> GetComponents()
	{
		return mComponents;
	}

private:
	std::vector<Component *> mComponents;
	int eId;
};

class EntityManager
{
public:
	Entity *GetEntity(int id);
	void AddEntity(Entity * ent);
	void RemoveEntity(int id);
	bool HasEntity(int id);

	std::vector<Entity*> GetEntities()
	{
		return mEntities;
	}

private:
	std::vector<Entity *> mEntities;
};

class Engine
{
public:
	void Init();

	void Update(float dt)
	{
		for (auto EMit = mEntityManagers.begin(); EMit != mEntityManagers.end(); ++EMit)
		{
			for (auto Eit = (*EMit)->GetEntities().begin(); Eit != (*EMit)->GetEntities().end(); ++Eit)
			{
				for (auto Cit = (*Eit)->GetComponents().begin(); Cit != (*Eit)->GetComponents().end(); ++Cit)
				{
					(*Cit)->Update();
				}
			}
		}
	}

	void Render()
	{
		for (auto EMit = mEntityManagers.begin(); EMit != mEntityManagers.end(); ++EMit)
		{
			for (auto Eit = (*EMit)->GetEntities().begin(); Eit != (*EMit)->GetEntities().end(); ++Eit)
			{
				UnitRendering* renderCom = static_cast<UnitRendering*>((*Eit)->GetComponent(RENDERING));
				renderCom->Render();
			}
		}
	}

	void MainLoop()
	{
		Update(timer.GetDeltaTime());
		Render();
	}

	void Add(EntityManager &EM);

private:
	std::vector<EntityManager *> mEntityManagers;
	Timer timer;
};

class Timer
{
public:
	float GetDeltaTime();
};
