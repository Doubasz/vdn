#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <sstream>

/// A 2D Point 
///
class Point{
public:
    float x;
    float y;

    Point();
    Point(float x, float y);
};


/// A rectangle with special properties.
///
/// It automatically stores all important points of a rectangle
/// (topLeft, topRight, center...), making everything easier.
///
/// @note Since everything's public, take care to not
///       modify the attributes directly.
///       Use the predefined functions to alter
///       things!
///
/// Zendef:
/// @note NEVER NEVER try to modify `x/y/w/h` directly! Always do it
///       through the `add()`/`set()` methods!
///       That's because this class needs to refresh internal
///       points and stuff.
///
struct Rectangle{
    float x; ///< X of the top left point
    float y; ///< Y of the top left point
    int w; ///< width of the rect
    int h; ///< height of the rect

    float top;       ///< An alias for y
    float bottom;    ///< An alias for y + h
    float leftMost;  ///< An alias for x
    float rightMost; ///< An alias for x + w

    // Special points
    Point center;
    Point leftCenter;
    Point rightCenter;
    Point topLeft;
    Point topRight;
    Point topCenter;
    Point bottomLeft;
    Point bottomRight;
    Point bottomCenter;


    /// @brief Creates a rectangle with `x` and `y` coordinates and
	/// `w` and `y` dimensions.
	Rectangle(float x, float y, int w, int h);

    Rectangle(Rectangle* other);


	bool overlaps(const Rectangle& other) const;

	/// @brief Initialize by default all attributes with `0`
	Rectangle();

    /// Copies *other*'s internal values to this.
	void copy(Rectangle* other);

    /// Adds to the current x, making necessary internal calculations.
	///
	/// if you want to subtract,
	/// send a negative parameter.
	///
	void addX(float x);

    /// Adds to the current y, making necessary internal
	/// calculations.
	///
	/// Of course, if you want to subtract,
	/// send a negative parameter.
	///
	void addY(float y);

    /// Sets the current x, making necessary internal calculations.
	void setX(float x);

	/// Sets the current y, making necessary internal calculations.
	void setY(float y);

    /// Stretches the rectangle by `step`.
	///
	/// If you want to increase it's size by two, send 2.
	/// If you want to shrink it by two, send 0.2.
	void stretch(float scale);
	

    /// Refreshes all internal values.
	///
	/// @note This gets called all the time internally
	void update();

    /// Tells if this rectangle overlaps the other in any way.
	bool overlaps(Rectangle other);

	/// Tells if this rectangle overlaps the other in any way.
	bool overlaps(Rectangle* other);

	/// Places this rectangle immediately above `other`.
	///
	/// @note It only considers the y axis, x is left unchanged.
	///
	/// ## For developers
	///
	/// The only purpose of this method is to make possible
	/// for the player to stay above a platform.
	/// Say if it's collision Rectangle passes through the platform,
	/// we place it above it with this method.
	///
	void placeOnTop(Rectangle other);

    /// Return a string to write it in the std output
    std::string toString();
};


/// A circle, duh.
///
struct Circle
{
	float x;
	float y;
	int r; /// Radius

	float centerX;
	float centerY;

	/// Creates a nice circle with `x` and `y` coordinates and `r`
	/// radius.
	Circle(float x, float y, int r);

	/// Adds to the current x.
	///
	/// @note Although this seems useless, you must call this
	///       instead of directly modifying x because it
	///       refreshes internal points.
	///
	void addX(float x);

	/// Adds to the current y.
	///
	/// @note Although this seems useless, you must call this
	///       instead of directly modifying y because it
	///       refreshes internal points.
	///
	void addY(float y);

};


#endif //SHAPES_H