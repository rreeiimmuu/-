#include "CmderFactory.hpp"

namespace adas
{
CmderList CmderFactory::GetCmders(const std::string &commands) const noexcept
{
    CmderList cmderList;
    for (const auto cmd : parseCommandString(commands)) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            cmderList.push_back(it->second);
        }
    }
    return cmderList;
}
std::string CmderFactory::parseCommandString(std::string_view commands) const noexcept
{
    std::string result(commands);
    ReplaceAll(result, "TR", "Z");
    return result;
}
void CmderFactory::ReplaceAll(std::string &inout, std::string what, std::string with) const noexcept
{
    for (std::string::size_type pos{};  // std::string::size_type 是 std::string 的 size 类型
         inout.npos != (pos = inout.find(what.data(), pos, what.length())); pos += with.length()) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
}
}  // namespace adas