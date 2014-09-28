/*
 * MapDrawingArea.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: trevor
 */

#include "MapDrawingArea.h"

#include <iostream>

#include <boost/lexical_cast.hpp>

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

	cr->rectangle(0, 0, width, height);
	// (37, 65, 23) is Dark Forest Green
	// http://www.computerhope.com/htmcolor.htm
	cr->set_source_rgb (37/255.0, 65/255.0, 23/255.0);
	cr->fill();

	draw_scale(cr);

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

void MapDrawingArea::draw_scale(const Cairo::RefPtr<Cairo::Context>& cr) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	int map_width = Scenario::_map.get_width();
	int map_height = Scenario::_map.get_height();

	if (map_width == -1 || map_height == -1)
		return;

	double pixels = 50.0;
	double meters = pixels / (((double)width) / ((double)map_width));

	cr->rectangle(width-125, 25, 100, 75);
	cr->set_source_rgb(1, 1, 1);
	cr->fill();

	cr->rectangle(width-95, 50, pixels, 10);
	cr->set_source_rgb(0, 1, 0);
	cr->fill();

	std::string text = boost::lexical_cast<std::string>(meters) + " meters";

	draw_text(cr, text, width-120, 60, 50, 25);
}


void MapDrawingArea::draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
		std::string text, int x, int y, int rectangle_width, int rectangle_height) {
  // http://developer.gnome.org/pangomm/unstable/classPango_1_1FontDescription.html
  Pango::FontDescription font;

  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_BOLD);

  // http://developer.gnome.org/pangomm/unstable/classPango_1_1Layout.html
  Glib::RefPtr<Pango::Layout> layout = create_pango_layout(text);

  layout->set_font_description(font);

  int text_width;
  int text_height;

  //get the text dimensions (it updates the variables -- by reference)
  layout->get_pixel_size(text_width, text_height);

  // Position the text
  cr->move_to(x, y);

  layout->show_in_cairo_context(cr);
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
		image_surface_ptr_ = Cairo::ImageSurface::create_from_png (VEHICLE_IMAGE_128x128);
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
