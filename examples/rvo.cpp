#include <string>

struct MyStruct
{
    MyStruct() = default;
    MyStruct(const MyStruct& obj) = default;
    int a = 666;
    float b;
    std::string c;
};

template<typename T>
struct force_rvo: T {
    force_rvo() {}
    using T::T;
    force_rvo(const force_rvo &) = delete;
    force_rvo(force_rvo &&) = delete;
};

template<typename T>
T f()
{
    // Fails
    // auto a = T();
    // return a;

    // Succeed
    return T();
}

int main()
{
    __builtin_printf("CLZ=%d\n",__builtin_clz(0));
    __builtin_printf("CTZ=%d\n",__builtin_ctz(0));
    __builtin_printf("v=%d\n",f<force_rvo<MyStruct>>().a);
    return f<force_rvo<MyStruct>>().a;
}
