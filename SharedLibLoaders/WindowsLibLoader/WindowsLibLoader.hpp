#pragma once 

#include <utility>
#include <windows.h>

#include "SharedLibLoaders/SharedLibLoader.hpp"

template<class _DLLClass, class ... _Argc>
class WindowsLibLoader : public SharedLibLoader<_DLLClass, _Argc...>
{
public:
    WindowsLibLoader(const std::filesystem::path& dllPath, 
            const std::string& ctorName)
        : SharedLibLoader<_DLLClass, _Argc...>{ dllPath, ctorName }
    {}

    ~WindowsLibLoader()
    {
        FreeLibrary(m_DLLAddress);        
    }

    void LoadLib() noexcept(false) override
    {
        SharedLibLoader<_DLLClass, _Argc...>::LoadLib(); 

        m_DLLAddress = LoadLibrary(this->m_DLLPath.string().c_str());
    }

    _DLLClass* SpawnObject(_Argc ... argc) noexcept(false) override
    {
        auto ctor = reinterpret_cast<CreationalFunction>
            (GetProcAddress(m_DLLAddress, this->m_CtorName.c_str()));

        if (!ctor)
        {
            throw std::runtime_error{ "DEV: Failed to get constructor address" };
        }

        return ctor(std::forward<_Argc>(argc)...);
    }

private:
    HMODULE m_DLLAddress{ nullptr };
};
