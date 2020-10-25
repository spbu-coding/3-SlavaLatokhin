#include <stdio.h>
#include <math.h>

void version_1_f(float *x2, float *y2, float deviation) {
	*y2 = (0.0001f + deviation) * 10000;
	*x2 = 2.0f - *y2;
}

void version_1_d(double *x2, double *y2, double deviation) {
	*y2 = (0.0001 + deviation) * 10000;
	*x2 = 2.0 - *y2;
}

void version_2_f(float *x2, float *y2, float deviation) {
	*y2 = (2.0001f - 2.0f + deviation) * 10000;
	*x2 = 2.0f - *y2;
}

void version_2_d(double *x2, double *y2, double deviation) {
	*y2 = (2.0001 - 2 + deviation) * 10000;
	*x2 = 2.0 - *y2;
}

void float_value(void (*method)(float*, float*, float)) {
	float x1 = 1, y1 = 1, x2, y2, deviation = 0.0001, a1 = 2.0001, a2, distance = -1, prev_distance;
	int n = 0;
	do {
		a2 = a1 + deviation;
		method(&x2, &y2, deviation);
		prev_distance = distance;
		distance = sqrtf((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
		n++;
		printf("%-2d  deviation = %.20f  distance = %.20f\n", n, deviation, distance);
		deviation /= 2;
	} while (distance > 0.000001f && distance != prev_distance);
	printf("Total steps: %-2d  distance = %.20f\n", n, distance);
	printf("x2 = %f  y2 = %f\n", x2, y2);
}

void double_value(void (*method)(double*, double*, double)) {
	double x1 = 1, y1 = 1, x2, y2, deviation = 0.0001, a1 = 2.0001, a2, distance = -1, prev_distance;
	int n = 0;
	do {
		a2 = a1 + deviation;
		method(&x2, &y2, deviation);
		prev_distance = distance;
		distance = sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
		n++;
		printf("%-2d  deviation = %.20lf  distance = %.20lf\n", n, deviation, distance);
		deviation /= 2;
	} while (distance > 0.000001 && distance != prev_distance);
	printf("Total steps: %-2d  distance = %.20lf\n", n, distance);
	printf("x2 = %lf  y2 = %lf\n", x2, y2);
}

int main() {
	printf("Version_1_float\n");
	float_value(version_1_f);
	printf("\nVersion_1_double\n");
	double_value(version_1_d);
	printf("\nVersion_2_float\n");
	float_value(version_2_f);
	printf("\nVersion_2_double\n");
	double_value(version_2_d);
	return 0;
}
