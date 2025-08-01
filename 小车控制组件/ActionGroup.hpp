#pragma once

#include <list>

#include "../src/core/PoseHandler.hpp"

namespace adas
{
enum class ActionType : uint16_t {
    FORWARD_1_STEP_ACTION = 0,
    BACKWARD_1_STEP_ACTION,
    TURN_LEFT_ACTION,
    REVERSE_TURN_LEFT_ACTION,
    TURN_RIGHT_ACTION,
    REVERSE_TURN_RIGHT_ACTION,
    BE_FAST_ACTION,
    BE_REVERSE_ACTION,
};

class ActionGroup final
{
public:
    ActionGroup(void) = default;
    explicit ActionGroup(const std::list<ActionType> &actions) noexcept;
    ~ActionGroup() = default;

    ActionGroup &operator+=(const ActionGroup &rhs) noexcept;

    void PushAction(const ActionType &ActionType) noexcept;
    void DoOperate(PoseHandler &poseHandler) const noexcept;

private:
    std::list<ActionType> actions;
}  // namespace adas