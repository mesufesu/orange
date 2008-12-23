#ifndef _MATHLIBMY_H_
#define _MATHLIBMY_H_

#define PI 3.14
#define	Q_PI 3.14159265358979323846

void AngleMatrix(const float *angles, float (*matrix)[4] );
void VectorRotateSSE( const float *in1, float (*in2)[4], float *out1 );

#endif