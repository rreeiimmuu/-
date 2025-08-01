#pragma once

#include <functional>
#include <list>
#include <map>
#include <unordered_map>

#include "ActionGroup.hpp"
#include "Command.hpp"

namespace adas
{
using Cmder = std::function<ActionGroup(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator)>;
using CmderList = std::list<Cmder>;
class CmderFactory final
{
public:
    CmderFactory(void) = default;
    ~CmderFactory(void) = default;

    CmderFactory(const CmderFactory &) = delete;
    CmderFactory &operator=(const CmderFactory &) = delete;

public:
    CmderList GetCmders(const std::string &commands) const noexcept;

private:
    const std::unordered_map<char, Cmder> cmderMap{

        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()},  {'Z', TurnRoundCommand()},
    };

private:
    std::string parseCommandString(std::string_view commands) const noexcept;

    void ReplaceAll(std::string &inout, std::string what, std::string with) const noexcept;
};
}  // namespace adas