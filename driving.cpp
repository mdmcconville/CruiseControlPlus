#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
#include "driving.h"


using namespace std;
int Driving::Vehicle::instances = 0;

Driving::Vehicle::Vehicle(double speed, double location) {
	s0 = mph_to_fps(speed);
	x0 = location;
	xc = x0;
	instances++;
	if (instances == 1) {
		this->drive();
	}
}

double Driving::Vehicle::get_coord() {
	return this->xc;
}

void Driving::Vehicle::set_coord(double position) {
	this->xc = position;
}

double Driving::Vehicle::get_speed() {
	return this->s0;
}

void Driving::Vehicle::set_speed(double speed) {
	this->s0 = speed;
}

double Driving::Vehicle::get_distance_from(Vehicle other) {
	return other.get_coord() - this->get_coord();
}

double Driving::Vehicle::scan_speed(double other_x0, double other_x1, int time) {
	return ((other_x1 - other_x0) / time);
}

double Driving::Vehicle::mph_to_fps(double speed) {
	//speed mi/ * 5280 ft/ *    1 h/ 
	//       h         mi    3600 s
	return (speed * 5280 / 3600);
}

double Driving::Vehicle::fps_to_mph(double speed) {
	//speed ft/ *     1 mi/ * 3600 s/
	//       s     5280 ft       1 hr     
	return (speed * 3600 / 5280);
}

double Driving::Vehicle::safe_following_distance(double speed,
	Driving::road_conditions enum_val) {
	
	switch (enum_val) {
		case GOOD:
			return speed * 3;
			break;
		case BAD:
			return speed * 6;
			break;
	}
}

int Driving::Vehicle::stopping_time(double starting_s, double ending_s,
									Driving::road_conditions weather) {
	// According to http://www.csgnetwork.com/stopdistinfo.html,
	// in fair conditions with reasonable tires, a car can decelerate
	// approximately 15 fps
	
	return ceil((starting_s - ending_s) / 15);
}

void Driving::Vehicle::drive() {
	// In version 1, conditions are always good
	Driving::road_conditions weather = Driving::road_conditions::GOOD;
	
	// Keep track of our speed and x-coord and other car's x-coord
	vector<pair<pair<double, double>, double>> speed_and_coords;
	
	// Create a vehicle to follow driving 45 mph at x0 = 250 ft
	Driving::Vehicle::Vehicle other_car(45.0, 250);
	double speed = get_speed();
	cout << "The driving test is starting now." << endl << endl
		 << "Our car is starting at " << this->get_coord() 
		 << " ft with a speed of " 
		 << fixed << setprecision(2) << speed << " fps (" 
		 << this->fps_to_mph(speed) << " mph)" << endl
		 << "and a distance of " 
		 << (other_car.get_coord() - this->get_coord()) 
		 << " ft from the other vehicle. Conditions are fair." << endl << endl;

	int seconds = 0;
	// Each loop represents one second
	while ((this->get_coord() < Driving::DrivingConditions::COURSE_LENGTH)
		&&(other_car.get_coord() < 
		(Driving::DrivingConditions::COURSE_LENGTH + other_car.x0))) {
		
		speed = get_speed();
		// Add x-coords and speed to the vector
		speed_and_coords.push_back(
		std::pair<std::pair<double, double>, double>(
		std::pair<double, double>(speed, this->get_coord()),
			this->get_distance_from(other_car)));
			
		// Increment the time
		seconds++;
		// Update the cars' positions
		this->set_coord(this->get_coord() + s0);
		other_car.set_coord(other_car.get_coord() + other_car.get_speed());
		
		// TODO: Remove later; for testing purposes
		if (seconds % 5 == 0) {
			cout << "At " << seconds << " seconds:\n"
				 << "Our car's x-coord is now at " << this->get_coord()
				 << " ft with a speed of "
				 << fixed << setprecision(2) << speed << " fps"
				 << " and a distance\n"
				 << "of " << (other_car.get_coord() - this->get_coord()) 
				 << " ft from the other vehicle." << endl << endl;
		}
		
		 	 
		// Following too closely
		if (safe_following_distance(this->get_speed(), weather)
			> (other_car.get_coord() - this->get_coord())) {
			
			double their_s = this->scan_speed(speed_and_coords.back().second +
										speed_and_coords.back().first.second,
										this->get_distance_from(other_car) + 
											this->get_coord());
			
			// Determine other car's speed so we can match it
			cout << "We are too close to the other car.\n"
				 << "We are driving " << fps_to_mph(this->get_speed())
				 << " mph and they are driving "
				 << fps_to_mph(their_s) << " mph." << endl 
				 << "We should be " 
				 << this->safe_following_distance(this->get_speed(), weather) 
				 << " ft away; we're " << this->get_distance_from(other_car)
				 << " ft behind the other car." << endl << endl; 
				 
			// Match the other car's speed
			this->set_speed(their_s);
			
			// Determine the whole number of seconds it would take to
			// decelerate at a constant rate to match the other car's speed
			// up update the seconds accordingly
			int stop_time = stopping_time(speed_and_coords.back().first.first,
											this->get_speed());
			
			// Increment the time and coordinates
			seconds += stop_time;
			this->set_coord(this->get_coord() + (this->get_speed() * stop_time));
			other_car.set_coord(other_car.get_coord() + 
								(other_car.get_speed() * stop_time));
		}
	}
}