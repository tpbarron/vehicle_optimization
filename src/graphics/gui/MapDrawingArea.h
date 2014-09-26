/*
 * MapDrawingArea.h
 *
 *  Created on: Sep 23, 2014
 *      Author: trevor
 */

#ifndef MAPDRAWINGAREA_H_
#define MAPDRAWINGAREA_H_

#include <gtkmm/drawingarea.h>
#include <gtkmm/builder.h>

#include "sim/Scenario.h"


class MapDrawingArea : public Gtk::DrawingArea {
public:
	MapDrawingArea(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~MapDrawingArea();


protected:
  //Override default signal handler:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:

  const std::string VEHICLE_IMAGE_128x128 = "resources/images/vehicle.png";

  void draw_road();
  void draw_intersection();
  void draw_vehicle(const Cairo::RefPtr<Cairo::Context>& cr);
  void draw_scale(const Cairo::RefPtr<Cairo::Context>& cr);
  void draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
			std::string text, int x, int y, int rectangle_width, int rectangle_height);

};

#endif /* MAPDRAWINGAREA_H_ */
