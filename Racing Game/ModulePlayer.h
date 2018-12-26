#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Timer.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURBO_ACCELERATION 8000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 75.0f



class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	btVector3 getPos() const;

	void PositionCar() const;
	void RespawnCar();
	void Crash();

public:

	int level = 1;
	PhysVehicle3D* car;
	float turn = 0;
	float acceleration = 0;
	float acceleration_fx_Time = 0;
	float brake = 0;
	bool accelerator = false;

	mutable Timer timer;
	float best_time = 100;
};