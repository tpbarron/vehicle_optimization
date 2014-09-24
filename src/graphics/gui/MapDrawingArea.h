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


class MapDrawingArea : public Gtk::DrawingArea {
public:
	MapDrawingArea(BaseObjectType* cobject,
			const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~MapDrawingArea();


protected:
  //Override default signal handler:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:

  void draw_road();
  void draw_intersection();
  void draw_vehicle(const Cairo::RefPtr<Cairo::Context>& cr);

};

#endif /* MAPDRAWINGAREA_H_ */
