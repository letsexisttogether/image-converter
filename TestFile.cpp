#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

class A
{
public:
    A(const std::string& name, const std::int32_t age)
        : m_Name{ name }, m_Age{ age }
    { 
        puts("Copy name on A");
    }
    A(std::string&& name, const std::int32_t age)
        : m_Name{ std::move(name) }, m_Age{ age }
    {
        puts("Move name on A");
    }

    virtual ~A()
    {
        puts("~A");
    }

    virtual void PrintName() 
    {
        std::cout << "The AAAAA name is " << m_Name << std::endl;
    }

public: 
    std::string m_HelloMessage{ "Hello" };
protected:
    std::string m_Name{};
    std::int32_t m_Age{};
};

class B : public A
{
public: 
    B(const std::string& name, const std::string& job, const std::int32_t age)
        : A{ name, age }, m_Job{ job }
    { 
        puts("Copy name and job on B");
    }
    B(std::string&& name, std::string&& job, const std::int32_t age)
        : A{ std::forward<std::string>(name), age }, m_Job{ std::move(job) }
    {
        puts("Move name and job on B");
    }

    virtual ~B()
    {
        puts("~B");
    }

    void PrintName() override
    {
        std::cout << "The BBBBB name is " << m_Name << ' ' << m_Job << std::endl;
    }

private:
    std::string m_Job{};
};


void PrintSomething(A&& a)
{
    std::cout << a.m_HelloMessage << std::endl;

    a.PrintName();
}

std::int32_t main()
{
    PrintSomething(B{ "Alex", "Programmer", 32 });

    std::cout << "The end" << std::endl;

    return EXIT_SUCCESS;
}
