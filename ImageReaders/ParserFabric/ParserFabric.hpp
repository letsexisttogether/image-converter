#include <map>
#include <stdexcept>

template <class _Key, class _Value, class ... Argc>
class ParserFabric
{
public:
    using ConstructingFunc = _Value* (*) (Argc...);
    using FunctionsMap = std::map<_Key, ConstructingFunc>;

    ParserFabric() = delete;
    ParserFabric(const ParserFabric&) = default;
    ParserFabric(ParserFabric&&) = default;

    ParserFabric(const FunctionsMap& map)
        : m_Functions{ map }
    {}

    ParserFabric(FunctionsMap&& map)
        : m_Functions{ std::move(map) }
    {}

    ~ParserFabric() = default;

    _Value* GetParser(const _Key& key, Argc&& ... argc) noexcept(false)
    {
        const auto& iter = m_Functions.find(key);

        if (iter == m_Functions.end())
        {
            throw std::runtime_error{ "DEV: wrong format" };
        }

        return iter->second(std::forward<Argc>(argc) ...);
    }

    bool CheckParserExistance(const _Key& key) const noexcept
    {
        return (m_Functions.find(key) != m_Functions.end());
    }

    ParserFabric& operator = (const ParserFabric&) = delete;
    ParserFabric& operator = (ParserFabric&&) = delete;

private:
    const FunctionsMap m_Functions{};
};
