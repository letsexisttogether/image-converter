#include <map>
#include <stdexcept>

template <class _Key, class _Value, class ... _Argc>
class CreationalFabric
{
public:
    using ConstructingFunc = _Value* (*) (_Argc...);
    using FunctionsMap = std::map<_Key, ConstructingFunc>;

    CreationalFabric() = delete;
    CreationalFabric(const CreationalFabric&) = default;
    CreationalFabric(CreationalFabric&&) = default;

    CreationalFabric(const FunctionsMap& map)
        : m_Functions{ map }
    {}

    CreationalFabric(FunctionsMap&& map)
        : m_Functions{ std::move(map) }
    {}

    ~CreationalFabric() = default;

    _Value* SpawnObject(const _Key& key, _Argc&& ... argc) noexcept(false)
    {
        const auto& iter = m_Functions.find(key);

        if (iter == m_Functions.end())
        {
            throw std::runtime_error{ "DEV: wrong format" };
        }

        return iter->second(std::forward<_Argc>(argc) ...);
    }

    bool CheckParserExistance(const _Key& key) const noexcept
    {
        return (m_Functions.find(key) != m_Functions.end());
    }

    CreationalFabric& operator = (const CreationalFabric&) = delete;
    CreationalFabric& operator = (CreationalFabric&&) = delete;

private:
    const FunctionsMap m_Functions{};
};
