#ifndef _DRIVING_H_
#define _DRIVING_H_

#include <vector>

namespace Driving {

struct DrivingConditions {
	// The length of the course being driven
	static const int COURSE_LENGTH = 800;
};
	enum road_conditions {GOOD, BAD};

class Vehicle {
private:
	double s0;	// Starting speed
	double x0;	// Starting x-coord
	double xc;  // Current x-coord
	static int instances; // How many cars there are
	void drive_other(); // Drive the other vehicle
	
public:
	// Constructor
	Vehicle(double speed, double location = 0.0);
	// Returns the x-coord of the vehicle
	double get_coord();
	// Sets the x-coord of the vehicle
	void set_coord(double position);
	// Returns the speed of the vehicle
	double get_speed();
	// Sets the speed of the vehicle
	void set_speed(double speed);
	// Returns the distance between the vehicles
	double get_distance_from(Vehicle other);
	// Converts the speed in mph to fps
	double mph_to_fps(double speed);
	// Converts the speed in fps to mph
	double fps_to_mph(double speed);
	// Determines safe following distance based on road/weather conditions
	double safe_following_distance(double speed, 
		Driving::road_conditions enum_val);
	// Calculate the speed of the driver in front of us
	double scan_speed(double other_x0, double other_x1, int time = 1);
	// Determine the number of seconds rounded-up it takes to decelerate
	int stopping_time(double starting_s, double ending_s,
									Driving::road_conditions weather=GOOD);
	void drive();
};

}

#endif