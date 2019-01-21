#include "AutoPilotScript.h"
#include "extern.h"

void AutoPilotScript::update(float dt) {
	Transform& trans = ECS.getComponentFromEntity<Transform>(owner_);
	
	Collider& right_ray_collider = ECS.getAllComponents<Collider>()[right_ray_id];
	Collider& left_ray_collider = ECS.getAllComponents<Collider>()[left_ray_id];

	if (overrideControl) {
		print("control overrided!");
		//Should rotate and remember the longest collision distance, or find a rotation value w no collision

		//Rotate a bit
		trans.rotateLocal(dt, lm::vec3(0, 1, 0));

		//if the ray does not collide, override control = false; return;
		if (!right_ray_collider.colliding || !left_ray_collider.colliding) {
			overrideControl = false;
			//reset values?
		}
		/*
		//Get the current max collision dist.
		float max_current_dist = right_ray_collider.collision_distance;
		if (max_current_dist < left_ray_collider.collision_distance) {
			max_current_dist = left_ray_collider.collision_distance;
		}

		//Check if the collision distance is bigger than the stored one
		if (max_collision_distance < max_current_dist) {
			// if so, save the rotation and update the biggest collision distance
			max_collision_distance = max_current_dist;
			//max_collision_rotation
		}
			
		
		//if the rotation >= 360
			//Rotate to the biggest collision distance degree; override = false;
		
		*/
		return;
	}

	frame_interval_count += dt;
	if (frame_interval_count > movement_check_interval) {
		
		frame_interval_count = 0;
		
		float distance = last_position.distance(trans.position());

		print(distance);

		if (distance < 0.3) {
			overrideControl = true;
		}

		last_position = trans.position();
	}
	
	

	float turn_multiplier = 1;
	float velocity_multiplier = 1;

	float current_rotation_velocity = 0;
	float desired_rotation = 0;
	if (right_ray_collider.colliding || left_ray_collider.colliding) {


		float min_distance = left_ray_collider.collision_distance;
		min_distance = (left_ray_collider.collision_distance > right_ray_collider.collision_distance) ? right_ray_collider.collision_distance : min_distance;

		if (min_distance < 3) {
			turn_multiplier = 2;
			velocity_multiplier = 0.5;
			if (min_distance < 2) {
				turn_multiplier = 4;
				velocity_multiplier = 0.25;
				if (min_distance < 1) {
					turn_multiplier = 10;
					velocity_multiplier = 0.1;
					if (min_distance < 0.3) {
						turn_multiplier = 100;
						velocity_multiplier = 0;
					}
				}
			}
		}else {
			turn_multiplier = 1;
			velocity_multiplier = 1;
		}

		if (right_ray_collider.collision_distance > left_ray_collider.collision_distance) {
			desired_rotation = rotation_velocity * turn_multiplier;
		}
		else {
			desired_rotation = -rotation_velocity * turn_multiplier;
		}
	}
	else {
		desired_rotation = 0;
		turn_multiplier = 1;
		velocity_multiplier = 1;
	}

	current_rotation_velocity = lerp(current_rotation_velocity, desired_rotation, 0.2f);
	
	trans.rotateLocal(dt * current_rotation_velocity, lm::vec3(0, 1, 0));

	trans.translate(trans.front().x*dt*general_velocity * velocity_multiplier, trans.front().y*dt*general_velocity * velocity_multiplier, trans.front().z*dt*general_velocity * velocity_multiplier);
}

