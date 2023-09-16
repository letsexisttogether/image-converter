#pragma once 

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

    void LoadLibrary() noexcept(false) override
    {
        SharedLibLoader<_DLLClass, _Argc...>::LoadLibrary(); 

        m_DLLAddress = LoadLibrary(m_DLLPath.wstring().c_str());
    }

    _DLLClass* SpawnObject(_Argc ... argc) noexcept(false) override
    {
        auto ctor = reinterpret_cast<CreationalFunction>
            (GetProcAddress(m_DLLAddress, m_CtorName));

        if (!ctor)
        {
            throw std::runtime_error{ "DEV: Failed to get constructor address" };
        }

        return ctor(argc...);
    }

private:
    HMODULE m_DLLAddress{ nullptr };
};
