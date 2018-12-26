#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

class ModuleSceneProps : public Module {
public:
	ModuleSceneProps(Application* app, bool start_enabled = true);
	~ModuleSceneProps();

	update_status Update(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	
	void CreateCollisionMaterial(float width, float height, float large, float x, float y, float z, Color color = Grey);
	void CreateCollisionMaterialKill(float width, float height, float large, float x, float y, float z, Color color = Grey);
	void CreateEndLine(float width, float height, float large, float x, float y, float z);
	void CreateAccelerator(float width, float height, float large, float x, float y, float z, Color color = Blue);
	void CreateJump(float width, float height, float large, float x, float y, float z, float degree, vec3 axis, Color color = Grey);
	void CreateKillZone(float width, float height, float large, float x, float y, float z, Color color = Cyan);
	void CreateEnd(float width, float height, float large, float x, float y, float z);
	void CreateObstacle(float x, float y, float z, Color color = Red);

public:

	p2List<Cube> Cubes;
	p2List<Obstacle> KillRotationThings;
};