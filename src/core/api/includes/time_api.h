#pragma once


#include "layer.h"


namespace Engine
{
    class TimeAPI : public Layer
    {
    public:
        virtual void OnAttach();
        virtual void OnUpdate();

    private:
        static double GetEpochInSeconds();

    public:
        static double Seconds();
        static double SecondsSinceStart();
        static double DeltaTime();
    };    
}