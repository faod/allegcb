/*
    Allegro CodeBase
    Copyright (C) 2012 Bayle Jonathan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Math functions for graphics (C99) */

#ifndef _GM_H_
#define _GM_H_

#include <math.h>

/* inline fix on non C99 compilers */
#ifdef __GNUC__
#define inline __inline__
#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
#define inline __inline
#endif

/* Point and Vector */
typedef struct { 
	float x,y;
} Point, Vector;

/* transformation matrix */
typedef struct {
	float m00, m01, m02;
	float m10, m11, m12;
	float m20, m21, m22;
} Hmat;

#ifndef ZERO
#define ZERO 1.e-8
#endif
#define nearly_zero(x) ((x)<ZERO && (x)>-ZERO)

#define SQR(a) (a*a)

/*
	POINTS
*/
static inline Point create_point(float x, float y) {
	Point p = {x, y};
	return p;
}

static inline float square_dist(Point A, Point B) {
	return SQR((B).x-(A).x) + SQR((B).y-(A).y);
}

static inline Point point_vector_addition(Point P, Vector U) {
	Point p = {(P.x+U.x), (P.y+U.y)};
	return p;
}

/*
	VECTORS
*/
static inline Vector create_vector(Point A, Point B) {
	Vector v = {(B.x-A.x), (B.y-A.y)};
	return v;
}

static inline Vector vector_scalar_product(Vector U, float s) {
	Vector v = {(U.x*s), (U.y*s)};
	return v;
}

static inline Vector vectors_addition(Vector U, Vector V) {
	Vector v = {(U.x+V.x), (U.y+V.y)};
	return v;
}

static inline Vector vectors_difference(Vector U, Vector V) {
	Vector v = {(U.x-V.x), (U.y-V.y)};
	return v;
}

static inline float vectors_product(Vector U, Vector V) {
	return U.x*V.y - U.y*V.x;
}
static inline float vectors_product_3p(Point A, Point B, Point C) {
	return ((B.x-A.x)*(C.y-A.y) - (B.y-A.y)*(C.x-A.x));
}

/* aka scalar product */
static inline float dot_product(Vector U, Vector V) {
	return U.x*V.x + U.y*V.y;
}
static inline float dot_product_3p(Point A, Point B, Point C) {
	return (((B).x-(A).x)*((C).x-(A).x)) + (((B).y-(A).y)*((C).y-(A).y));
}

static inline float norm(Vector V) { /* uses SQRT ! */
	return sqrtf(SQR(V.x) + SQR(V.y));
}

static inline Vector normalize(Vector U) { /* uses SQRT ! */
	float norm_U = sqrtf(SQR(U.x) + SQR(U.y));
	U.x = U.x/norm_U; U.y = U.y/norm_U;
	return U;
}

static inline float square_norm(Vector V) {
	return SQR(V.x) + SQR(V.y);
}

/* returns 1 if U -> V is counterclockwise */
static inline short vector_orient(Vector U, Vector V) {
	return ((U).x*(V).y>(U).y*(V).x)?+1:-1;
}

static inline Vector normal_vector(Vector U) {
	Vector v = {-U.y, U.x};
	return v;
}

static inline Vector normal_vector_2p(Point A, Point B) {
	Vector v = {((A).y-(B).y), ((B).x-(A).x)};
	return v;
}

/* 
	MATRICES
*/
Hmat create_translation_matrix_xy(float tx, float ty);
Hmat create_translation_matrix_vector(Vector U);

Hmat create_scaling_matrix_xy(float hx, float hy);
Hmat create_scaling_matrix_vector(Vector U);

Hmat create_rotation_matrix(float alpha);

/* Matrix*Matrix -> Matrix */
Hmat matrices_product(Hmat A,Hmat B);

/* Matrix*Point -> Point */
Point matrix_point_product(Hmat A, Point P);

/* Matrix*Vector -> Vector */
Vector matrix_vector_product(Hmat A, Vector U);

/*
	
*/
/* Orthogonal projections of C on [AB], returns dist between C and P */
float projection_point_line(Point A, Point B, Point C, Point *P);

/* Intersection between [AB] and [CD], return 1 if I is on the 2 segments, else return 0 */
int segments_intersection(Point A, Point B, Point C, Point D, Point *I);

/* If the tirangle ABC is positive in counterclockwise */
int is_positive(Point A, Point B, Point C);

/* Determine if P belongs to ABC */
int is_in_triangle(Point A, Point B, Point C, Point P);

/* Return the number of intersection between [AB] and the ellipse of center C, I = first inter ; J = second inter */
int segment_ellipse_intersection(Point A, Point B, Point C, float rx, float ry, Point *I, Point *J);

/* return -1 if no intersection, else return the distance between P and I (I is the intersection) */
float ray_circle_intersection(Point P, Vector v, Point C, float r, Point *I);

/* Process the angle (rad) of A,B ; return 0 if < PI/30 ; norm(A) = 1  */
float angle(Vector A, Vector B); /* SQRT !! (except < PI/30) */

/* Segment/Circle Intersection : 
 * -1 : no intersection
 *  0 : [AB] is inside the circle
 * +1 : [AB] is tangent to the circle
 * +2 : A inside,  B outside
 * +3 : A outside, B inside
 * +4 : A and B outside, 2 intersections */
int segment_circle_intersection(Point A, Point B, Point C, float r, Point *I1, Point *I2);

#endif /* _GM_H_ */
