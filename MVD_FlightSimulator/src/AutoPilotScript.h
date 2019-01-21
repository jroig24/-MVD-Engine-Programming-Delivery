#pragma once
#include "ScriptSystem.h"
#include "includes.h"

class AutoPilotScript : public Script {
public:

	AutoPilotScript(int owner, int right_c, int left_c) : Script(owner) {
		right_ray_id = right_c;
		left_ray_id = left_c;
	}

	void update(float dt);

	float rotation_velocity = 1;
	float general_velocity = 8.0;

private:
	int right_ray_id;
	int left_ray_id;

	float frame_interval_count = 0;
	float movement_check_interval = 1;
	lm::vec3 last_position;

	bool was_colliding = false;

	bool overrideControl = false;

	float initial_rotation = 0;
	float override_rotation_count = 0;
	float current_override_rotation = 0;
	float max_collision_distance = 0;
	float max_collision_rotation = 0;

	float lerp(float initial, float target, float percent) {
		return (initial + percent * (target - initial));
	}

};

