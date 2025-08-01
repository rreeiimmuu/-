#pragma once
#include <string>

namespace adas
{
enum class ExecutorType {
    NORMAL,
    SPORTS_CAR,
    BUS,
    // 区分不同类型汽车
};

struct Pose  // 位置和朝向
{
    int x;
    int y;
    char heading;
};
class Executor
{
public:
    static Executor *NewExecutor(const Pose &pose = {0, 0, 'N'},
                                 const ExecutorType executorType = ExecutorType::NORMAL) noexcept;

    Executor(void) = default;
    virtual ~Executor(void) = default;

    Executor(const Executor &) = delete;

    Executor &operator=(const Executor &) = delete;

public:
    virtual void Execute(const std::string &command) noexcept = 0;
    virtual Pose Query(void) const noexcept = 0;
};

}  // namespace adas