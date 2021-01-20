#include "util/patch.h"

// TEMPLATE // 

// inline Hook
void (*SomeFunc)();
void SomeFunc_hook()
{
    // some code //
    return SomeFunc(); // call orig Func
}

// Addr hook // - can hook hooked func 
HOOK_DATA AddrFunc_data;
void AddrFunc_hook()
{   
    // some code //

    return CPatch::CallFrom<void>(&AddrFunc_data/*, args...*/); // call orig
}

class main
{
public:
    main()
    {
        uintptr_t libTARGET = CPatch::FindLibrary("libTARGET.so"); // find base address

        CPatch::InlineHook(libTARGET, 0xADD, &SomeFunc_hook, &SomeFunc);
        CPatch::AddrHook(libTARGET + 0xADD, &AddrFunc_data, &AddrFunc_hook);

        // old hook func
        //CPatch::InitHookStuff();
        //CPatch::SetUpHook()

        // look in CPatch class for more funcs
    }

};

main Main;

