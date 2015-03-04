#include "Rectangle.h"

CRectangle::~CRectangle() {
}

void CRectangle::clipTo(const CRectangle &other_rect) {
	if (left < other_rect.left) {
		left = other_rect.left;
	}
	if (right > other_rect.right) {
		right = other_rect.right;
	}
	if (top < other_rect.top) {
		top = other_rect.top;
	}
	if (bottom > other_rect.bottom) {
		bottom = other_rect.bottom;
	}
}

void CRectangle::translate(int x, int y) {
	left = left + x;
	right = right + x;
	top = top + y;
	bottom = bottom + y;
}

bool CRectangle::completelyOutside(const CRectangle &other_rect) {
	if (other_rect.left > right || other_rect.right < left) {
		return true;
	}
	if (other_rect.top > bottom || other_rect.bottom < top) {
		return true;
	}
	return false;
}

bool CRectangle::completelyInside(const CRectangle &other_rect) {
	if (left > other_rect.left && right < other_rect.right) {
		if (top > other_rect.top && bottom < other_rect.bottom) {
			return true;
		}
	}
	return false;
}

bool CRectangle::partiallyInside(const CRectangle &other_rect) {
	if (right > other_rect.right || left < other_rect.left) {
		return true;
	}
	if (top < other_rect.top || bottom > other_rect.bottom) {
		return true;
	}
	return false;
}

bool CRectangle::intersects(const CRectangle &other) {
	if (left>other.right || right<other.left || top>other.bottom || bottom < other.top) {
		return false;
	}
	return true;
}