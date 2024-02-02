#include <math.h>
// #include <Pla/pla_math.h> //TEMP using pla_math

float theta = 1.0f;
extern float theta;

int main()
{
    float f_sin( sin(theta) );
    float f_cos( cos(theta) );
    float f_tan( tan(theta) );
    float f_sqrt( sqrt(theta) );
    __builtin_printf("\nTheta %f\nSin %f\nCost %f\nTan %f\nSqrt %f",
                     theta, f_sin, f_cos, f_tan, f_sqrt );

    // pla::float4 f4_theta( theta );
    // pla::float4 f4_sin( pla::Sin(theta)) ;
    // pla::float4 f4_cos( pla::Cos(theta)) ;
    // pla::float4 f4_tan( pla::Tan(theta)) ;
    // pla::float4 f4_sqrt( pla::Sqrt(f4_theta)) ;
    // __builtin_printf("\nTheta %f\nSin %f\nCost %f\nTan %f\nSqrt %f",
    //                  f4_theta.x, f4_sin.x, f4_cos.x, f4_tan.x, f4_sqrt.x );

    return 0;
}

// Local Variables:
// beardbolt-gcc-optimization-flags: "-O3"
// beardbolt-preserve-directives: nil
// beardbolt-preserve-unused-labels: nil
// beardbolt-preserve-library-functions: t
// beardbolt-preserve-comments: t
// End:
