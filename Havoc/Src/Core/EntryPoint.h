#pragma once

extern Havoc::Application* Havoc::CreateApplication();

int main()
{

    Havoc::Log::Init();
    auto app = Havoc::CreateApplication();
    app->Run();
    H_CORE_FATAL("Havoc Engine");
    H_CORE_ERROR("Havoc Engine");
    H_CORE_WARN("Havoc Engine");
    H_CORE_DEBUG("Havoc Engine");
    H_CORE_INFO("Havoc Engine");
    H_CORE_TRACE("Havoc Engine\n\n");

    

    H_CLIENT_FATAL("Havoc Land");
    H_CLIENT_ERROR("Havoc Land");
    H_CLIENT_WARN("Havoc Land");
    H_CLIENT_DEBUG("Havoc Land");
    H_CLIENT_INFO("Havoc Land");
    H_CLIENT_TRACE("Havoc Land");
    return 0;
}