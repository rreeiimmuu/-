#pragma once

#include <functional>

#include "../src/ExecutorImpl.hpp"
#include "../src/core/PoseHandler.hpp"
#include "CmderOrchestrator.hpp"
namespace adas
{
class MoveCommand final
{
public:
        ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        return orchestrator.Move(poseHandler);
    }
};

class TurnLeftCommand final
{
public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        return orchestrator.TurnLeft(poseHandler);
    }
};

class TurnRightCommand final
{
public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        return orchestrator.TurnRight(poseHandler);
    }
};

class FastCommand final
{
public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        ActionGroup actionGroup;

        actionGroup.PushAction(ActionType::BE_FAST_ACTION);  // 切换加速状态
        return actionGroup;
    }
};

class ReverseCommand final
{
public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);  // 切换倒车状态
        return actionGroup;
    }
};
class TurnRoundCommand final
{
public:
    ActionGroup operator()(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator) const noexcept
    {
        return orchestrator.TurnRound(poseHandler);
    }
};
}  // namespace adas