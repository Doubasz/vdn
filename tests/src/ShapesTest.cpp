#include <gtest/gtest.h>
#include "Shapes.h"

// Test pour la classe Point
TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point p(5.0f, 10.0f);
    EXPECT_EQ(p.x, 5.0f);
    EXPECT_EQ(p.y, 10.0f);
}

// Test pour la classe Rectangle
TEST(RectangleTest, DefaultConstructor) {
    Rectangle r;
    EXPECT_EQ(r.x, 0);
    EXPECT_EQ(r.y, 0);
    EXPECT_EQ(r.w, 1);
    EXPECT_EQ(r.h, 1);
}

TEST(RectangleTest, ParameterizedConstructor) {
    Rectangle r(10.0f, 20.0f, 100, 200);
    EXPECT_EQ(r.x, 10.0f);
    EXPECT_EQ(r.y, 20.0f);
    EXPECT_EQ(r.w, 100);
    EXPECT_EQ(r.h, 200);
}

TEST(RectangleTest, CopyConstructor) {
    Rectangle r1(10.0f, 20.0f, 100, 200);
    Rectangle r2 = r1;
    EXPECT_EQ(r2.x, 10.0f);
    EXPECT_EQ(r2.y, 20.0f);
    EXPECT_EQ(r2.w, 100);
    EXPECT_EQ(r2.h, 200);
}



TEST(RectangleTest, Overlap) {
    Rectangle r1(10.0f, 20.0f, 100, 100);
    Rectangle r2(50.0f, 70.0f, 100, 100);
    EXPECT_TRUE(r1.overlaps(r2));
}

TEST(RectangleTest, PlaceOnTop) {
    Rectangle r1(10.0f, 20.0f, 100, 100);
    Rectangle r2(50.0f, 200.0f, 100, 100);
    r1.placeOnTop(r2);
    EXPECT_EQ(r1.y, r2.y - r1.h);  // Rectangle should be placed above r2
}

// Test pour la classe Circle
TEST(CircleTest, DefaultConstructor) {
    Circle c(0, 0, 10);
    EXPECT_EQ(c.x, 0);
    EXPECT_EQ(c.y, 0);
    EXPECT_EQ(c.r, 10);
    EXPECT_EQ(c.centerX, 10);
    EXPECT_EQ(c.centerY, 10);
}

TEST(CircleTest, MoveCircle) {
    Circle c(10, 20, 30);
    c.addX(5);
    c.addY(-5);
    EXPECT_EQ(c.x, 15);
    EXPECT_EQ(c.y, 15);
    EXPECT_EQ(c.centerX, 45);
    EXPECT_EQ(c.centerY, 45);
}
