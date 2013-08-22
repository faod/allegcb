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

#include "gmath.h"

Hmat create_translation_matrix_vector(Vector t) {
	Hmat A;
	A.m00 = 1.0; A.m01 = 0.0; A.m02 = t.x;
	A.m10 = 0.0; A.m11 = 1.0; A.m12 = t.y;
	A.m20 = 0.0; A.m21 = 0.0; A.m22 = 1.0;
	return A;
}

Hmat create_translation_matrix_xy(float tx, float ty) {
	Hmat A;
	A.m00 = 1.0; A.m01 = 0.0; A.m02 = tx;
	A.m10 = 0.0; A.m11 = 1.0; A.m12 = ty;
	A.m20 = 0.0; A.m21 = 0.0; A.m22 = 1.0;
	return A;
}

Hmat create_scaling_matrix_vector(Vector h) {
	Hmat A;
	A.m00 = h.x; A.m01 = 0.0; A.m02 = 0.0;
	A.m10 = 0.0; A.m11 = h.y; A.m12 = 0.0;
	A.m20 = 0.0; A.m21 = 0.0; A.m22 = 1.0;
	return A;
}

Hmat create_scaling_matrix_xy(float hx, float hy) {
	Hmat A;
	A.m00 = hx ; A.m01 = 0.0; A.m02 = 0.0;
	A.m10 = 0.0; A.m11 = hy ; A.m12 = 0.0;
	A.m20 = 0.0; A.m21 = 0.0; A.m22 = 1.0;
	return A;
}

Hmat create_rotation_matrix(float alpha) {
	Hmat A;
	A.m00 = +cosf(alpha); A.m01 = -sinf(alpha); A.m02 = 0.0;
	A.m10 = +sinf(alpha); A.m11 = +cosf(alpha); A.m12 = 0.0;
	A.m20 = 0.0         ; A.m21 = 0.0         ; A.m22 = 1.0;
	return A;
}

Vector matrix_vector_product(Hmat A,Vector V) {
	Vector W;  
	W.x = A.m00*V.x + A.m01*V.y;
	W.y = A.m10*V.x + A.m11*V.y;
	return W;
}

Point matrix_point_product(Hmat A, Point P){
	Point Q;
	Q.x = A.m00*P.x + A.m01*P.y + A.m02;
	Q.y = A.m10*P.x + A.m11*P.y + A.m12;
	return Q;
}

Hmat matrices_product(Hmat A,Hmat B) {
	Hmat C;
	/* 1st col */
	C.m00 = A.m00*B.m00 + A.m01*B.m10 + A.m02*B.m20;
	C.m10 = A.m10*B.m00 + A.m11*B.m10 + A.m12*B.m20;
	C.m20 = A.m20*B.m00 + A.m21*B.m10 + A.m22*B.m20;
	/* 2nd col */
	C.m01 = A.m00*B.m01 + A.m01*B.m11 + A.m02*B.m21;
	C.m11 = A.m10*B.m01 + A.m11*B.m11 + A.m12*B.m21;
	C.m21 = A.m20*B.m01 + A.m21*B.m11 + A.m22*B.m21;
	/* 3rd col */
	C.m02 = A.m00*B.m02 + A.m01*B.m12 + A.m02*B.m22;
	C.m12 = A.m10*B.m02 + A.m11*B.m12 + A.m12*B.m22;
	C.m22 = A.m20*B.m02 + A.m21*B.m12 + A.m22*B.m22;
	return C;  
}

/* Projection of pC on [pA pB] */
float projection_point_line(Point pA, Point pB, Point pC, Point *P) {
	Vector ab, ac; float dist;
	ab = create_vector(pA, pB);
	ac = create_vector(pA, pC);
	dist = dot_product(ab, ac) / square_norm(ab);
        
	ac = vector_scalar_product(ab, dist);
	*P = point_vector_addition(pA, ac);
	
	return dist;
}

/* Intersection between [pA pB] and [pC pD], return 1 if I is on the 2 segments, else return 0 */
int segments_intersection(Point pA, Point pB, Point pC, Point pD, Point *I) {
	Vector cdOrth, ab, ac, cd, ci;
	Point tmpI;
	float dist, cmp;
	
	cdOrth = normal_vector_2p(pC, pD);
	ab = create_vector(pA, pB);
	ac = create_vector(pA, pC);
	cd = create_vector(pC, pD);
	
	if (nearly_zero((dist = dot_product(ab, cdOrth)))) return 0;
	
	dist = dot_product(ac, cdOrth) / dist;
	ac = vector_scalar_product(ab, dist);
	tmpI = point_vector_addition(pA, ac);
	
	ci = create_vector(pC, tmpI);
	
	if (I) *I = tmpI;
	/* return 1 if I belongs to [AB] */
	return ((cmp = dot_product(ci, cd)) >= 0 && cmp <= square_norm(cd) && dist>= 0 && dist<=1) ? 1: 0;
}

/* if the triangle ABC is positif in counterclockwise */
int is_positive(Point pA, Point pB, Point pC) {
	return (vectors_product_3p(pA,pB,pC) >= 0) ? 1: 0;
}

/* Determine if P belongs to ABC */
int is_in_triangle(Point pA, Point pB, Point pC, Point P) {
	int cmp = is_positive(pA, pB, pC);
	
	if (cmp != is_positive(pA, pB, P)) return 0;
	if (cmp != is_positive(pB, pC, P)) return 0;
	if (cmp != is_positive(pC, pA, P)) return 0;
	
	return 1;
}

/* Return the number of intersection between [AB] and the ellipse of center C, I = first inter ; J = second inter*/
int segment_ellipse_intersection(Point pA, Point pB, Point pC, float rx, float ry, Point *I, Point *J) {
	Point Ap, Bp, Ip, Jp;
	Hmat direct, indirect;
	int n;
	
	direct = create_translation_matrix_xy(pC.x, pC.y);
	direct = matrices_product(direct, create_scaling_matrix_xy(rx, ry));
	
	indirect = create_scaling_matrix_xy(1.0f/rx, 1.0f/ry);
	indirect = matrices_product(indirect, create_translation_matrix_xy(-pC.x, -pC.y));
	
	Ap = matrix_point_product(indirect, pA);
	Bp = matrix_point_product(indirect, pB);
	
	n = segment_circle_intersection(Ap, Bp, create_point(0.0, 0.0), 1.0, &Ip, &Jp);

	*I = matrix_point_product(direct, Ip);
	*J = matrix_point_product(direct, Jp);
	
	return n;
}

/* Particle 'P' of speed 'v' will enter in colision with the cercle of center C and of radius r */
float ray_circle_intersection(Point P, Vector v, Point C, float r, Point *I) {
	Vector pc, cp;
	float a, b, c, delta, dist;
	
	pc = create_vector(P, C);
	if (dot_product(v, pc)<0) return -1;
	
	cp = create_vector(C, P);
	a = square_norm(v);
	b = 2.0f * dot_product(v, cp);
	c = square_norm(cp) - SQR(r);
	delta = SQR(b) - 4.0f * a * c;
	
	if (delta <= 0) return -1;
	
	dist = (-1.0f*b-sqrtf(delta)) / (2.0f*a);
	
	v = vector_scalar_product(v, dist);
	*I = point_vector_addition(P, v);
	
	return dist;
}

#define SMALL 0.0055
#define IsSmall(x) ((x)<SMALL && (x)>-SMALL)

float angle(Vector A, Vector B) { /* Assuming ||A|| = 1 */
	float res, tmp;
	
	res = dot_product(A, B);
	
	tmp = (res - square_norm(B));
	
	if (IsSmall(tmp)) return 0.0; /* less than PI/30 */
	
	res = acosf(res/norm(B));
	return res * vector_orient(A, B);
}

int segment_circle_intersection(Point A, Point B, Point C, float r, Point *I1, Point *I2) {
	int boolA, boolB;
	Point P;
	float xab, yab, d, t, r2=r*r;

	boolA = (square_dist(A,C)<=r2);
	boolB = (square_dist(B,C)<=r2);

	if (boolA && boolB) { *I1=A; *I2=B; return 0; }

	t=projection_point_line(A,B,C,&P);
	d=square_dist(C,P);
	
	if (!boolA)
	{
		if (!boolB)
		{
			if (t<ZERO || t>1.) return -1;

			if (d>r2) return -1;

			if (nearly_zero(d-r2))
			{
				*I1=*I2=P;
				return 1;
			}
			
			d=sqrtf((r2-d)/square_dist(A,B));
			xab = d*(B.x-A.x);
			yab = d*(B.y-A.y);
			I1->x = P.x-xab; I1->y = P.y-yab;
			I2->x = P.x+xab; I2->y = P.y+yab;
			return 4;
		}
		d=sqrtf((r2-d)/square_dist(A,B));
		xab = d*(B.x-A.x);
		yab = d*(B.y-A.y);
		I1->x = I2->x = P.x-xab; 
		I1->y = I2->y = P.y-yab;
		return 3;
	}
	d=sqrtf((r2-d)/square_dist(A,B));
	xab = d*(B.x-A.x);
	yab = d*(B.y-A.y);
	I1->x = I2->x = P.x+xab; 
	I1->y = I2->y = P.y+yab;
	return 2;
}
