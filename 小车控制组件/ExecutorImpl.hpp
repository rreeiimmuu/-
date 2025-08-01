#pragma once
#include <memory>
#include <string>

#include "../include/Executor.hpp"
#include "../src/cmder/CmderOrchestrator.hpp"
#include "../src/cmder/Command.hpp"
#include "../src/core/PoseHandler.hpp"
namespace adas
{

class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose &pose, CmderOrchestrator *orchestrator) noexcept;

    ~ExecutorImpl() noexcept = default;

    ExecutorImpl(const ExecutorImpl &) = delete;

    ExecutorImpl &operator=(const ExecutorImpl &) = delete;

public:
    Pose Query() const noexcept override;

    void Execute(const std::string &command) noexcept override;

private:
    PoseHandler poseHandler;
    std::unique_ptr<CmderOrchestrator> orchestrator;
};

}  // namespace adas