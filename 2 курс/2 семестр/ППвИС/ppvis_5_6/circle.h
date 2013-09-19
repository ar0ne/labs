
#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "main.h"
#include "point.h"

using namespace POINT_NAMESPACE;

	class CIRCLE : public POINT {
	private:
		char * 	color;
		float  	radius;
	public:
		CIRCLE(const char * = "red", const float = 3.5 , const int = 0, const int = 0);
		CIRCLE(const CIRCLE & );
		void  ToSetColor(const char *);
		void  ToSetRadius(const float);
		void  ToShowCircle(void);
		void  ToSetCircle(const char *, const float, const int, const int);
		float ToGetSquare() const;
		~CIRCLE();
};

#endif
