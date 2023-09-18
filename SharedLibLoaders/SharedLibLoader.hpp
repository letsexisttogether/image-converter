#pragma once

#include <stdexcept>
#include <filesystem>
#include <string>

template<class _DLLClass, class ... _Argc>
class SharedLibLoader
{
public:
    using CreationalFunction = _DLLClass* (*) (_Argc...);
public:
    SharedLibLoader(const std::filesystem::path& dllPath, 
            const std::string& ctorName)
        : m_DLLPath{ dllPath }, m_CtorName{ ctorName }
    {}

    virtual ~SharedLibLoader() = default;

    virtual void LoadLib() noexcept(false)
    {
        if (!std::filesystem::exists(m_DLLPath))
        {
            throw std::runtime_error{ "DEV: no such .dll found" };
        }
    }

    virtual _DLLClass* SpawnObject(_Argc ... argc) noexcept(false) = 0;

protected:
    const std::filesystem::path m_DLLPath;
    const std::string m_CtorName;
};
