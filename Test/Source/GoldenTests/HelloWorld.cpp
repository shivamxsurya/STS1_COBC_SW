#include <rodos.h>

uint32_t printfMask = 0;
namespace cobc
{
class HelloWorld : public StaticThread<>
{
    void run() override
    {
        printfMask = 1;
        PRINTF("Hello, World!\n");
        hwResetAndReboot();
    }
};

auto const helloWorld = HelloWorld();
}