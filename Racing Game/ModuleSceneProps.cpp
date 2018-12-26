#include "Globals.h"
#include "Application.h"
#include "ModuleSceneProps.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "ModuleAudio.h"

ModuleSceneProps::ModuleSceneProps(Application* app, bool start_enabled) : Module(app, start_enabled) {}
ModuleSceneProps::~ModuleSceneProps(){}

update_status ModuleSceneProps::Update(float dt)
{

	for (p2List_item<Cube>* item = Cubes.getFirst(); item; item = item->next)
	{
		item->data.Render();
	}
	for (p2List_item<Obstacle>* item = KillRotationThings.getFirst(); item; item = item->next){
		
		btQuaternion aux = item->data.body_cube2->GetRotation();
		
		aux = aux.normalized();
		
		float angle = 2 * acos(aux.w()) * 180 / 3.14;
		float den = sqrt(1 - aux.w() *aux.w());
		
		item->data.cube2.SetRotation(angle, { aux.x() / den,aux.y() / den,aux.z() / den });
		item->data.cube2.SetPos(item->data.body_cube2->GetPos().x(), item->data.body_cube2->GetPos().y(), item->data.body_cube2->GetPos().z());
		item->data.cube2.Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneProps::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->type == accelerate){App->player->accelerator = true;}
	else if (body1->type == Killzone){App->player->RespawnCar();}
	else if (body1->type == EndofLevel){ App->player->level++; App->player->RespawnCar();}
	else if (body1->type == Obstaclesens){App->player->Crash();}
}

void ModuleSceneProps::CreateCollisionMaterial(float width, float height, float large, float x, float y, float z, Color color)
{
	Cube aux(width, height, large);
	aux.SetPos(x, y, z);
	aux.color = color;
	Cubes.add(aux);
	App->physics->AddBody(aux, 0);
}

void ModuleSceneProps::CreateEndLine(float width, float height, float large, float x, float y, float z)
{
	
	Cube aux(width, height, large);
	aux.SetPos(x, y, z);
	aux.color = White;
	Cubes.add(aux);
	App->physics->AddBody(aux, 0);
}

void ModuleSceneProps::CreateAccelerator(float width, float height, float large, float x, float y, float z, Color color){
	
	Cube aux(width, height, large);
	aux.SetPos(x, y, z);
	aux.color = color;
	Cubes.add(aux);


	Cube sensor = aux;
	sensor.SetPos(x, y + 1.5f, z);


	PhysBody3D* auxbody = App->physics->AddBody(sensor, 0, typeofsensor::accelerate);


	auxbody->CreateSensor();
	auxbody->collision_listeners.add(this);
}

void ModuleSceneProps::CreateJump(float width, float height, float large, float x, float y, float z, float degree, vec3 axis, Color color) {
	
	Cube aux(width, height, large);
	aux.SetPos(x, y, z);
	aux.color = color;
	aux.SetRotation(degree, axis);
	Cubes.add(aux);


	App->physics->AddBody(aux, 0);
}

void ModuleSceneProps::CreateKillZone(float width, float height, float large, float x, float y, float z, Color color) {
	
	Cube aux(width, height, large);
	aux.SetPos(x, y, z);
	aux.color = color;
	Cubes.add(aux);
	
	PhysBody3D* auxbody = App->physics->AddBody(aux, 0, typeofsensor::Killzone);
	
	auxbody->CreateSensor();
	auxbody->collision_listeners.add(this);
}

void ModuleSceneProps::CreateEnd(float width, float height, float large, float x, float y, float z) {

	Cube aux(width, height, large);
	aux.SetPos(x, y, z);
	

	typeofsensor sensor;
	sensor = EndofLevel;
	

	PhysBody3D* auxbody = App->physics->AddBody(aux, 0, sensor);
	auxbody->CreateSensor();
	auxbody->collision_listeners.add(this);
}

void ModuleSceneProps::CreateObstacle(float x, float y, float z, Color color) {

	Cube Obstacles(1, 1, 1);
	Obstacles.SetPos(x, y, z);
	
	
	PhysBody3D* Auxbod = App->physics->AddBody(Obstacles, 0);
	Cube auxcube(5, 9.5f, 1);
	auxcube.SetPos(x + 5, y, z);
	
	
	PhysBody3D* Auxbod2 = App->physics->AddBody(auxcube, 50, typeofsensor::Obstaclesens);
	auxcube.color = Red;
	Auxbod2->CreateSensor();
	Auxbod2->collision_listeners.add(this);
	App->physics->AddConstraintHinge(*Auxbod, *Auxbod2, { 0,0,0 }, { 0,1,0 }, { 0,0,8 }, { 1,0,0 }, true);
	
	
	Obstacle Adder(Obstacles, auxcube, Auxbod, Auxbod2);
	KillRotationThings.add(Adder);
}