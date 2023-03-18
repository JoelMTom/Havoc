#pragma once

extern Havoc::Application* Havoc::CreateApplication();

int main()
{

    Havoc::Log::Init();
    auto app = Havoc::CreateApplication();
    app->Run();
    return 0;
}