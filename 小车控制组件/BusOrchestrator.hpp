#pragma once
#include "NormalOrchestrator.hpp"

namespace adas
{
class BusOrchestrator : public NormalOrchestrator
{
public:
    ActionGroup TurnLeft(const PoseHandler &poseHandler) const noexcept override
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(GetStepAction(poseHandler));
        actionGroup += OnFast(poseHandler);

        const auto turnAction =
            poseHandler.IsReverse() ? ActionType::REVERSE_TURN_LEFT_ACTION : ActionType::TURN_LEFT_ACTION;

        actionGroup.PushAction(turnAction);
        return actionGroup;
    }
    ActionGroup TurnRight(const PoseHandler &poseHandler) const noexcept override
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(GetStepAction(poseHandler));
        actionGroup += OnFast(poseHandler);
        const auto turnAction =
            poseHandler.IsReverse() ? ActionType::REVERSE_TURN_RIGHT_ACTION : ActionType::TURN_RIGHT_ACTION;

        actionGroup.PushAction(turnAction);
        return actionGroup;
    }
};
}  // namespace adas