#include "Direction.hpp"

namespace adas
{

// 4种方向
static const Direction directions[4] = {
    {0, 'E'},  // East
    {1, 'S'},  // South
    {2, 'W'},  // West
    {3, 'N'}   // North
};

// 4种前进坐标
static const Point points[4] = {
    {1, 0},   // East: 向右移动
    {0, -1},  // South: 向下移动
    {-1, 0},  // West: 向左移动
    {0, 1}    // North: 向上移动
};

const Direction &Direction::GetDirection(const char heading) noexcept
{
    for (const auto &dir : directions) {
        if (dir.heading == heading) {
            return dir;
        }
    }

    return directions[3];
}

Direction::Direction(const unsigned index, const char heading) noexcept : index(index), heading(heading)
{
}

const Point &Direction::Move() const noexcept
{
    return points[index % 4];
}

const Direction &Direction::LeftOne() const noexcept
{
    return directions[(index + 3) % 4];
}

const Direction &Direction::RightOne() const noexcept
{
    return directions[(index + 1) % 4];
}

const char Direction::GetHeading() const noexcept
{
    return heading;
}

}  // namespace adas