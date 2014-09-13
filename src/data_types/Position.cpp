/*
 * Position.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: trevor
 */

#include "Position.h"

Position::Position() {
	lat = 0;
	lng = 0;
}

Position::Position(double lat, double lng) {
	Position::lat = lat;
	Position::lng = lng;
}

Position::~Position() {
}

void Position::set_lat(double lat) {
	Position::lat = lat;
}

void Position::set_lng(double lng) {
	Position::lng = lng;
}

double Position::get_lat() {
	return lat;
}

double Position::get_lng() {
	return lng;
}

/*
 * Haversine formula
 *http://www.movable-type.co.uk/scripts/latlong.html
 *

var R = 6371; // km
var φ1 = lat1.toRadians();
var φ2 = lat2.toRadians();
var Δφ = (lat2-lat1).toRadians();
var Δλ = (lon2-lon1).toRadians();

var a = Math.sin(Δφ/2) * Math.sin(Δφ/2) +
        Math.cos(φ1) * Math.cos(φ2) *
        Math.sin(Δλ/2) * Math.sin(Δλ/2);
var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));

var d = R * c;
 */
Distance* Position::get_distance_to(Position &other) {
	Distance *d = new Distance();

	return d;
}
