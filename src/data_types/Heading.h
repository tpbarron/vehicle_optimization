/*
 * Heading.h
 *
 *  Created on: Sep 4, 2014
 *      Author: trevor
 */

#ifndef HEADING_H_
#define HEADING_H_

/*
 * http://en.wikipedia.org/wiki/Course_%28navigation%29
 */

class Heading {
public:
	Heading();
	Heading(double h);
	virtual ~Heading();

	const double get_heading() const;
	void set_heading(double h);

private:

	double _heading;

};

#endif /* HEADING_H_ */
