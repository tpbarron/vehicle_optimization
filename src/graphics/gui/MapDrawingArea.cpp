/*
 * MapDrawingArea.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: trevor
 */

#include "MapDrawingArea.h"

#include <iostream>

#include <cairomm/context.h>


MapDrawingArea::MapDrawingArea(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder>& builder) :
		Gtk::DrawingArea(cobject)  {
}

MapDrawingArea::~MapDrawingArea() {
	// TODO Auto-generated destructor stub
}

bool MapDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	// coordinates for the center of the window
	int xc, yc;
	xc = width / 2;
	yc = height / 2;


	cr->rectangle(0, 0, width, height);
	// (37, 65, 23) is Dark Forest Green
	// http://www.computerhope.com/htmcolor.htm
	cr->set_source_rgb (37/255.0, 65/255.0, 23/255.0);
	cr->fill();
	draw_vehicle(cr);
//
//
//	cr->set_line_width(10.0);
//
//	// draw red lines out from the center of the window
//	cr->set_source_rgb(0.8, 0.0, 0.0);
//	cr->move_to(0, 0);
//	cr->line_to(xc, yc);
//	cr->line_to(0, height);
//	cr->move_to(xc, yc);
//	cr->line_to(width, yc);
//	cr->stroke();

	return true;
}

void MapDrawingArea::draw_road() {

}

void MapDrawingArea::draw_intersection() {

}

/*
 * draw at position and rotate for heading
 */
void MapDrawingArea::draw_vehicle(const Cairo::RefPtr<Cairo::Context>& cr) {
	Cairo::RefPtr< Cairo::ImageSurface > image_surface_ptr_;
	try
	{
		image_surface_ptr_ = Cairo::ImageSurface::create_from_png ("resources/images/vehicle.png");
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception on ImageFile::update what:" << e.what() << std::endl;
	}

	int image_width = image_surface_ptr_->get_width();
	int image_height = image_surface_ptr_->get_height();

	cr->set_source (image_surface_ptr_, 0.0, 0.0);
	cr->rectangle (0.0, 0.0, image_width, image_height);
	cr->clip();
	cr->paint();

//	cairo_translate (cr, 128.0, 128.0);
//	cairo_rotate (cr, 45* M_PI/180);
//	cairo_scale  (cr, 256.0/w, 256.0/h);
//	cairo_translate (cr, -0.5*w, -0.5*h);

//	cr->set_source_surface(image, 0, 0);
//	cr->paint();
//	cairo_surface_destroy (image);
}
