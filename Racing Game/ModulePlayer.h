#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Timer.h"

struct PhysVehicle3D;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	btVector3 getPos() const;

	void PositionCar();
	void RespawnCar();
	void Crash();

public:

	uint lostfx = 0;
	uint wonfx = 0;
	uint carfx = 0;
	int level = 1;
	PhysVehicle3D* car;
	float turn = 0;
	float acceleration = 0;
	float acceleration_fx_Time = 0;
	float brake = 0;
	bool accelerator = false;

	mutable Timer timer;
	int Deaths = 0;
};