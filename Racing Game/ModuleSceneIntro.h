#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2
#define ROAD_HEIGHT 0.1f


struct PhysBody3D;
struct PhysMotor3D;

struct Obstacle {

	Obstacle() {}
	Obstacle(Cube c, Cube c2, PhysBody3D* bc, PhysBody3D* bc2) : cube(c), cube2(c2), body_cube(bc), body_cube2(bc2) {}

	Cube cube;
	Cube cube2;

	PhysBody3D* body_cube = nullptr;
	PhysBody3D* body_cube2 = nullptr;

};


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateMap();

public:
	PhysBody3D * pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

};
