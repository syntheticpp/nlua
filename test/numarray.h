#ifndef NLUA_TEST_NUM_ARRAY_H
#define NLUA_TEST_NUM_ARRAY_H

class NumArray
{
public:
    NumArray() : size(1) {}
    int size;
    double values[1];

private:
    NumArray(const NumArray&);
    NumArray& operator=(const NumArray&);
};


const char* test_script_28_1 =
        "print('')                      \n"
        "a = array.new(1000)            \n"
        "print(a)                       \n"
        "print(array.size(a))           \n"
        "for i = 1, 1000 do             \n"
        "    array.set(a, i, 1/i)       \n"
        "end                            \n"
        "print(array.get(a, 10))        \n";


const char* test_script_28_2 =
        "array.get(io.stdin, 10)        \n";


const char* test_script_28_3 =
        "a = array.new(1000)            \n"
        "print(a:size())     --> 1000   \n"
        "a:set(10, 3.4)                 \n"
        "print(a:get(10))    --> 3.4    \n";


const char* test_script_28_4 =
        "a = array.new(1000)            \n"
        "a[10] = 3.4                    \n"
        "print(a[10])        --> 3.4    \n";


void reportOnError(int err, lua_State* L)
{
    if (err != 0) {
        printf("\nLua error:\n     %s\n\n", lua_tostring(L, -1));
    }
}


#endif
