#include <Sts1CobcSw/EduCommunicationErrorThread.hpp>
#include <Sts1CobcSw/TopicsAndSubscribers.hpp>

#include <rodos-no-using-namespace.h>

namespace sts1cobcsw
{
constexpr auto stackSize = 4'000U;
std::int32_t eduCommunicationErrorCounter = 0;

class EduCommunicationErrorThread : public RODOS::StaticThread<stackSize>
{
public:
    EduCommunicationErrorThread() : StaticThread("EduCommunicationErrorThread")
    {
    }

private:
    void init() override
    {
    }


    void run() override
    {
        while(true)
        {
            RODOS::AT(RODOS::END_OF_TIME);

            eduCommunicationErrorCounter++;

            // Reset edu
            edu.TurnOff();
            RODOS::AT(RODOS::NOW() + 2 * RODOS::SECONDS);
            edu.TurnOn();

            // Busy wait
            auto eduIsAlive = false;
            while(not eduIsAlive)
            {
                eduIsAliveBuffer.get(eduIsAlive);
            }
        }
    }
} eduCommunicationErrorThread;

// TODO: Think about whether this is the right way to declare, design, use, etc. this
class ResumeEduErrorCommunicationThread : public RODOS::TimeEvent
{
public:
    auto handle() -> void override
    {
        eduCommunicationErrorThread.resume();
        RODOS::PRINTF("EduCommunicationThread resumed\n");
    }
} resumeEduErrorCommunicationThread;


auto ResumeEduErrorCommunicationThread() -> void
{
    resumeEduErrorCommunicationThread.handle();
}

}
