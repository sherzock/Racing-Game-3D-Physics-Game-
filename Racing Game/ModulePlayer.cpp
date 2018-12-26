#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), car(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo infocar;

	// Car properties ----------------------------------------
	infocar.chassis_size.Set(2.0f, 1.2f, 4);
	infocar.chassis_offset.Set(0, 1.6f, 0.5f);
	infocar.mass = 450.0f;
	infocar.suspensionStiffness = 17.88f;
	infocar.suspensionCompression = 0.83f;
	infocar.suspensionDamping = 0.88f;
	infocar.maxSuspensionTravelCm = 1000.0f;
	infocar.frictionSlip = 50.5;
	infocar.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 2.0f;
	float wheel_radius = 0.75f;
	float wheel_width = 0.65f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = infocar.chassis_size.x*0.5f;
	float half_length = infocar.chassis_size.z*0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	infocar.num_wheels = 4;
	infocar.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	infocar.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	infocar.wheels[0].direction = direction;
	infocar.wheels[0].axis = axis;
	infocar.wheels[0].suspensionRestLength = suspensionRestLength;
	infocar.wheels[0].radius = wheel_radius;
	infocar.wheels[0].width = wheel_width;
	infocar.wheels[0].front = true;
	infocar.wheels[0].drive = true;
	infocar.wheels[0].brake = false;
	infocar.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	infocar.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	infocar.wheels[1].direction = direction;
	infocar.wheels[1].axis = axis;
	infocar.wheels[1].suspensionRestLength = suspensionRestLength;
	infocar.wheels[1].radius = wheel_radius;
	infocar.wheels[1].width = wheel_width;
	infocar.wheels[1].front = true;
	infocar.wheels[1].drive = true;
	infocar.wheels[1].brake = false;
	infocar.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	infocar.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	infocar.wheels[2].direction = direction;
	infocar.wheels[2].axis = axis;
	infocar.wheels[2].suspensionRestLength = suspensionRestLength;
	infocar.wheels[2].radius = wheel_radius;
	infocar.wheels[2].width = wheel_width;
	infocar.wheels[2].front = false;
	infocar.wheels[2].drive = false;
	infocar.wheels[2].brake = true;
	infocar.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	infocar.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	infocar.wheels[3].direction = direction;
	infocar.wheels[3].axis = axis;
	infocar.wheels[3].suspensionRestLength = suspensionRestLength;
	infocar.wheels[3].radius = wheel_radius;
	infocar.wheels[3].width = wheel_width;
	infocar.wheels[3].front = false;
	infocar.wheels[3].drive = false;
	infocar.wheels[3].brake = true;
	infocar.wheels[3].steering = false;

	car = App->physics->AddVehicle(infocar);
	PositionCar();

	timer.Start();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

btVector3 ModulePlayer::getPos() const
{
	return car->GetPos();
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{

		turn = acceleration = brake = 0.0f;

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {acceleration = MAX_ACCELERATION;}

		if (acceleration == MAX_ACCELERATION && SDL_GetTicks() > acceleration_fx_Time) { acceleration_fx_Time = SDL_GetTicks() + 450;}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {if (turn < TURN_DEGREES){turn += TURN_DEGREES;}}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) { if (turn > -TURN_DEGREES){ turn -= TURN_DEGREES; } }

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT){ acceleration -= MAX_ACCELERATION / 2; }

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
			if (car->GetKmh() > 7.5f){brake = BRAKE_POWER;}
			else {brake = BRAKE_POWER;}
		}

	if (accelerator) {
		acceleration += TURBO_ACCELERATION;
		accelerator = false;
	}

	car->ApplyEngineForce(acceleration);
	car->Turn(turn);
	car->Brake(brake);
	car->Render();

	/*if (timer.ReadSec() > 25) {
		RespawnCar();
	}*/

	char title[80];
	sprintf_s(title, "%.1f Km/h    %.1f sec     Number of Deaths %i ", car->GetKmh(), timer.ReadSec(), Deaths);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::Crash() { RespawnCar(); }
void ModulePlayer::RespawnCar() {
	Deaths++;
	PositionCar();
	car->SetRotation({ 0,1,0,1 });
	car->vehicle->getRigidBody()->setAngularVelocity({ 0, 0, 0 });
	car->vehicle->getRigidBody()->setLinearVelocity({ 0, 0, 0 });
	timer.Start();
}


void ModulePlayer::PositionCar() const {
	if (level == 1) {
		car->SetRotation({ 0,1,0,1 });
		car->SetPos(5, 10.1f, 85);
	}
	else if (level == 2) {
		car->SetRotation({ 0,1,0,1 });
		car->SetPos(5, 10.1f, 185);
	}
	
}