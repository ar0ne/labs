
#ifndef _POINT_H
#define _POINT_H

namespace POINT_NAMESPACE {

	class POINT {
	private:
		int x;
	protected:
		int y;
	public:
		POINT(const int = 0,const int = 0);
		POINT(const POINT &);
		void ToShowPoint() const;
		void ToSetPoint(const int, const int );
		int  ToGetX(void) const;
		int  ToGetY(void) const;
	};
}

#endif
