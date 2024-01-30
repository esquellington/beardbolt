#include <stdio.h>
#include <chrono>
#include <vector>
using namespace std;
const int cNumEntries(100000000);
__attribute__ ((noinline))
void Lerp_Vector( std::vector<float>& dst, float lambda01, const std::vector<float>& src1, const std::vector<float>& src2 )
{
    const float w1( 1.0f - lambda01 ); const float w2( lambda01 ); const int count( dst.size() );
    auto s = chrono::system_clock::now();
    for( int i=0; i<count; ++i )
    {
        dst[i] = w1*src1[i] + w2*src2[count-1-i];
        dst[i] += src1[i] + src2[i];
        dst[i] -= src1[count-1-i/2] + src2[count-1-i/2];
    }
    auto e = chrono::system_clock::now();
    float acc(0.0f); for( auto v : dst ) acc += v;
    printf( "LerpV  %1.6f %e\n", chrono::duration<float>(e-s).count(), acc);
}
__attribute__ ((noinline))
void Lerp_NoRestrict( float* dst, int count, float lambda01, const float* src1, const float* src2 )
{
    const float w1( 1.0f - lambda01 ); const float w2( lambda01 );
    auto s = chrono::system_clock::now();
    for( int i=0; i<count; ++i )
    {
        dst[i] = w1*src1[i] + w2*src2[count-1-i];
        dst[i] += src1[i] + src2[i];
        dst[i] -= src1[count-1-i/2] + src2[count-1-i/2];
    }
    auto e = chrono::system_clock::now();
    float acc(0.0f); for( int i=0; i<count; ++i ) acc += dst[i];
    printf( "LerpNR %1.6f %e\n", chrono::duration<float>(e-s).count(), acc);
}
__attribute__ ((noinline))
void Lerp_Restrict( float* __restrict__ dst, int count, float lambda01, const float* __restrict__ src1, const float* __restrict__ src2 )
{
    const float w1( 1.0f - lambda01 ); const float w2( lambda01 );
    auto s = chrono::system_clock::now();
    for( int i=0; i<count; ++i )
    {
        dst[i] = w1*src1[i] + w2*src2[count-1-i];
        dst[i] += src1[i] + src2[i];
        dst[i] -= src1[count-1-i/2] + src2[count-1-i/2];
    }
    auto e = chrono::system_clock::now();
    float acc(0.0f); for( int i=0; i<count; ++i ) acc += dst[i];
    printf( "LerpR  %1.6f %e\n", chrono::duration<float>(e-s).count(), acc);
}
int main()
{
    // Alloc and init/warmup all memory
    std::vector<float> src1( cNumEntries, 0.0f );
    std::vector<float> src2( cNumEntries, 1.0f );
    std::vector<float> dst( cNumEntries, 0.5f );
    // Profile with no aliasing (Equal
    printf( "Lerp %d with no aliasing --> restrict is safe\n", cNumEntries);
    Lerp_Vector( dst, 0.5f, src1, src2 );
    Lerp_NoRestrict( &dst[0], cNumEntries, 0.5f, &src1[0], &src2[0] );
    Lerp_Restrict( &dst[0], cNumEntries, 0.5f, &src1[0], &src2[0] );
    // Profile with aliasing (-
    printf( "Lerp %d with aliasing --> restrict is unsafe\n", cNumEntries);
    for( int i=0; i<cNumEntries; ++i ) dst[i] = float(i)/(cNumEntries-1);
    Lerp_Vector( dst, 0.33f, dst, dst );
    for( int i=0; i<cNumEntries; ++i ) dst[i] = float(i)/(cNumEntries-1);
    Lerp_NoRestrict( &dst[0], cNumEntries, 0.33f, &dst[0], &dst[0] );
    for( int i=0; i<cNumEntries; ++i ) dst[i] = float(i)/(cNumEntries-1);
    Lerp_Restrict( &dst[0], cNumEntries, 0.33f, &dst[0], &dst[0] );
    return 0;
}

// Local Variables:
// beardbolt-asm-format: intel
// End:
