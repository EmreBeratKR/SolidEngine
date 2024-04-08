#include <chrono>


#include "time_api.h"


namespace Engine
{
    double ms_StartTime {0};
    double ms_Time {0};
    double ms_DeltaTime {0};


    void TimeAPI::OnAttach()
    {
        ms_Time = GetEpochInSeconds();
        ms_StartTime = ms_Time;
    }

    void TimeAPI::OnUpdate()
    {
        auto time = GetEpochInSeconds();

        ms_DeltaTime = time - ms_Time;
        ms_Time = time;
    }


    double TimeAPI::Seconds()
    {
        return ms_Time;
    }

    double TimeAPI::SecondsSinceStart()
    {
        return GetEpochInSeconds() - ms_StartTime;
    }

    double TimeAPI::DeltaTime()
    {
        return ms_DeltaTime;
    }


    double TimeAPI::GetEpochInSeconds()
    {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<double> epoch = currentTime.time_since_epoch();

        return epoch.count();
    }
}