#pragma once
class CRectangle {
	public:
		CRectangle() : left(0), right(0), top(0), bottom(0) {};
		CRectangle(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b){};
		~CRectangle();

		int width() const { return right - left; }
		int height() const { return bottom - top; }
		int getLeft() const { return left; }
		int getTop() const { return top; }
		int getOffset(int srcWidth) const { return left + top * srcWidth; }
		void clipTo(const CRectangle &other_rect);
		void translate(int x, int y);
		bool completelyOutside(const CRectangle &other_rect);
		bool completelyInside(const CRectangle &other_rect);
		bool partiallyInside(const CRectangle &other_rect);
		bool intersects(const CRectangle &other);
	private:
		int left, right, top, bottom = 0;
};

