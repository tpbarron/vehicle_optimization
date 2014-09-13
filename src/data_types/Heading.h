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

	double get_heading();
	void set_heading(double h);

private:

	double heading;

};

#endif /* HEADING_H_ */
