int foo(int arg)
{
    float f1 = 2.0f; //interesting comment
    float f2 = float(arg);
    // this is fine
    return int(f1 * f2);
}

float bar(float arg)
{
    int s1 = 4;
    int s2 = int(arg);
    return float(s1 * s2);
}

float foobar(int i, float f)
{
    return foo(i) + bar(f);
}

int main()
{
    __builtin_printf("%f", foobar(1,2) );
     return 0;
}

// Local Variables:
// beardbolt-asm-format: att
// beardbolt-gcc-optimization-flags: "-O0"
// beardbolt-gcc-arch-flags: "-march=x86-64 -mavx2"
// beardbolt-execute-args: "fdfdfdf"
// End:
