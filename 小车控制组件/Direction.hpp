#pragma once

#include "Point.hpp"

namespace adas
{

class Direction final
{
public:
    // 根据方向字符获取方向
    static const Direction &GetDirection(const char heading) noexcept;

public:
    Direction(const unsigned index, const char heading) noexcept;

public:
    const Point &Move(void) const noexcept;          // 前进
    const Direction &LeftOne(void) const noexcept;   // 左转
    const Direction &RightOne(void) const noexcept;  // 右转

    const char GetHeading(void) const noexcept;

private:
    unsigned index;
    char heading;
};

}  // namespace adas