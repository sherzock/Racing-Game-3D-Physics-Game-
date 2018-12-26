#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "ModuleAudio.h"
#include "ModuleSceneProps.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	CreateMap();
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::CreateMap()
{
	App->props->CreateKillZone(10000, 1, 1000, 0, 4.5f, 0, Orange);
	
	//level 1
	App->props->CreateEndLine(10, ROAD_HEIGHT+0.01, 40, 4.99, 10, 85);
	App->props->CreateCollisionMaterial(500, ROAD_HEIGHT, 40, 250, 10, 85);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 50, 20, 90, Red);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 100, 20, 80, Red);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 150, 20, 90, Red);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 200, 20, 90, Red);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 250, 20, 80, Red);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 300, 20, 80, Red);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 350, 20, 90, Red);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 400, 20, 80, Red);
	App->props->CreateCollisionMaterialKill(20, 20, 30, 450, 20, 90, Red);
	App->props->CreateEnd(0.3f, 20, 40, 490, 10, 85);
	App->props->CreateEndLine(10, ROAD_HEIGHT + 0.01, 40, 499, 10, 85);

	//level 2
	App->props->CreateEndLine(10, ROAD_HEIGHT + 0.01, 40, 4.99, 10, 185);
	App->props->CreateCollisionMaterial(50, ROAD_HEIGHT, 40, 25, 10, 185);
	App->props->CreateJump(20, ROAD_HEIGHT, 5, 59, 13.5, 170, 20, { 0,0,1 });//left part
	App->props->CreateCollisionMaterial(200, ROAD_HEIGHT, 5, 168.5, 17, 170);
	App->props->CreateJump(10, ROAD_HEIGHT, 5, 100, 19, 170, 20, { 0,0,1 });
	App->props->CreateJump(10, ROAD_HEIGHT, 5, 150, 19, 170, 20, { 0,0,1 });
	App->props->CreateAccelerator(5, ROAD_HEIGHT, 5, 240, 17.01, 170);
	App->props->CreateAccelerator(5, ROAD_HEIGHT, 5, 245, 17.01, 170);
	App->props->CreateAccelerator(5, ROAD_HEIGHT, 5, 250, 17.01, 170);
	App->props->CreateJump(10, ROAD_HEIGHT, 5, 273, 19, 170, 20, { 0,0,1 });
	App->props->CreateEnd(1, 40, 20, 340, 19, 170);
	App->props->CreateEndLine(1, 40, 20, 340, 19, 170);
	App->props->CreateJump(20, ROAD_HEIGHT, 10, 59, 13.5, 200, 20, { 0,0,1 });//right part
	App->props->CreateCollisionMaterial(200, ROAD_HEIGHT, 5, 168.5, 17, 200);
	App->props->CreateAccelerator(5, ROAD_HEIGHT, 5, 100, 17.01, 200);
	App->props->CreateAccelerator(5, ROAD_HEIGHT, 5, 150, 17.01, 200);
	App->props->CreateAccelerator(5, ROAD_HEIGHT, 5, 200, 17.01, 200);
	App->props->CreateJump(10, ROAD_HEIGHT, 5, 273, 19, 200, 20, { 0,0,1 });
	App->props->CreateObstacle(125, 23, 200);
	App->props->CreateObstacle(175, 23, 200);
	App->props->CreateObstacle(225, 23, 200);
	App->props->CreateEnd(1, 40, 20, 340, 19, 200);
	App->props->CreateEndLine(1, 40, 20, 340, 19, 200);

	// level3
	App->props->CreateEndLine(10, ROAD_HEIGHT + 0.01, 40, 4.99, 10, 285);
	App->props->CreateCollisionMaterial(50, ROAD_HEIGHT, 40, 25, 10, 285);
	App->props->CreateAccelerator(5, ROAD_HEIGHT, 40, 45, 10.01, 285);
	App->props->CreateJump(20, ROAD_HEIGHT, 40, 59, 11.5, 285, 10, { 0,0,1 });
	App->props->CreateCollisionMaterial(150, ROAD_HEIGHT, 13, 150, 10, 255);
	App->props->CreateCollisionMaterial(150, ROAD_HEIGHT, 13, 150, 10, 315);
	App->props->CreateCollisionMaterial(30, ROAD_HEIGHT-0.01, 73, 240, 10, 285);
	App->props->CreateCollisionMaterial(50, ROAD_HEIGHT, 5, 280, 10, 285);
	App->props->CreateCollisionMaterialKill(50, ROAD_HEIGHT, 5, 280, 10, 290, Red);
	App->props->CreateCollisionMaterialKill(50, ROAD_HEIGHT, 5, 280, 10, 280, Red);
	App->props->CreateAccelerator(5, ROAD_HEIGHT, 5, 295, 10.01, 285);
	App->props->CreateJump(20, ROAD_HEIGHT, 5, 310, 12, 285, 10, { 0,0,1 });
	App->props->CreateEnd(40, 1, 40, 360, 5, 285);
	App->props->CreateEndLine(40, 1, 40, 360, 5, 285);
	App->props->CreateObstacle(125, 16, 255);
	App->props->CreateObstacle(175, 16, 255);
	App->props->CreateObstacle(225, 16, 255);
	App->props->CreateCollisionMaterialKill(4, 4, 4, 145, 12, 315, Red);
	App->props->CreateCollisionMaterialKill(4, 4, 4, 170, 12, 313, Red);
	App->props->CreateCollisionMaterialKill(4, 4, 4, 195, 12, 317, Red);
	App->props->CreateCollisionMaterialKill(4, 4, 4, 220, 12, 315, Red);
}

