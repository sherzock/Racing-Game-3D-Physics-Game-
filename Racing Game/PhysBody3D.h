#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"

class btRigidBody;
class Module;
class btVector3;
class btQuaternion;

enum typeofsensor {None = 0,accelerate,Killzone,EndofLevel,Obstaclesens};

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	btVector3 GetPos() const;
	void SetRotation(btQuaternion rotation) const;
	btQuaternion GetRotation() const;
	void CreateSensor()const;
private:
	btRigidBody* body = nullptr;

public:
	p2List<Module*> collision_listeners;
	typeofsensor type = None;
};

#endif // __PhysBody3D_H__