#include "stdafx.h"

/// <summary>
/// replace text
/// </summary>
/// <param name="str">The text</param>
/// <param name="from">what to find in text</param>
/// <param name="to">with what to replace in text</param>
/// <returns>true if replaced; else false.</returns>
static bool replace_string(std::string& str, const std::string& from, const std::string& to);

/// <summary>
/// replace text
/// </summary>
/// <param name="str">The text</param>
/// <param name="from">what to find in text</param>
/// <param name="to">with what to replace in text</param>
/// <returns>true if replaced; else false.</returns>
static bool replace_string(std::string& str, const std::string& from, const std::string& to) 
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;

    str.replace(start_pos, from.length(), to);
    return true;
}
