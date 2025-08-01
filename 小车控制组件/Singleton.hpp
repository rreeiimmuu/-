#pragma once

namespace adas
{
template <typename T>
class Singleton final
{
public:
    static T &Instance(void) noexcept
    {
        static T instance;
        return instance;
    }
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    Singleton() noexcept = default;
    ~Singleton() noexcept = default;
};  //

}  // namespace adas