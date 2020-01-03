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

class AISystem
{
public:
	UnitAI GetAIComponent(int id);
	void AddAIComponent(UnitAI ai);
	void RemoveAIComponent(int id);
	bool HasAIComponent(int id);
	void Update()
	{
		for (auto i = 0; i < AIComponents.size(); ++i)
		{
			AIComponents[i].Update();
		}
	}
private:
	std::vector<UnitAI> AIComponents;
};

class PhysicsSystem
{
public:
	UnitPhysics GetPhysicsComponent(int id);
	void AddPhysicsComponent(UnitPhysics phy);
	void RemovePhysicsComponent(int id);
	bool HasPhysicsComponent(int id);
	void Update()
	{
		for (auto i = 0; i < PhysicsComponents.size(); ++i)
		{
			PhysicsComponents[i].Update();
		}
	}

private:
	std::vector<UnitPhysics> PhysicsComponents;
};

class RenderingSystem
{
public:
	UnitRendering GetRenderingComponent(int id);
	void AddRenderingComponent(UnitRendering phy);
	void RemoveRenderingComponent(int id);
	bool HasRenderingComponent(int id);
	void Update()
	{
		for (auto i = 0; i < RenderingComponents.size(); ++i)
		{
			RenderingComponents[i].Update();
		}
	}
	void Render()
	{
		for (auto i = 0; i < RenderingComponents.size(); ++i)
		{
            if(isAcitive())
			RenderingComponents[i].Render();
		}
	}

private:
	std::vector<UnitRendering> RenderingComponents;
    std::vector<UnitRendering> showCom;
    std::vector<UnitRendering> offCom;
};

class Engine
{
public:
	void Init();

	void Update(float dt)
	{
		AIComponents.Update();
		PhysicsComponents.Update();
		RenderComponents.Update();
	}

	void Render()
	{
		RenderComponents.Render();
	}

	void MainLoop()
	{
		Update(timer.GetDeltaTime());
		Render();
	}


private:
	AISystem AIComponents;
	PhysicsSystem PhysicsComponents;
	RenderingSystem RenderComponents;

	Timer timer;
};

class Timer
{
public:
	float GetDeltaTime();
};

class Animation{};
class Vector{};
class LootType {};

class AIComponent
{
public:
	void Update();

private:
	Animation* animation;
	double evergy_;
	Vector goalPos;
	LootDrop* Loot;
};



class LootDrop
{
	friend class AIComponent;
	LootType drop;
	int minDrops;
	int maxDrops;
	double changeOfDrop;
};