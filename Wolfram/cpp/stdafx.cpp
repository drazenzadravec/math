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
/// if a line in the stream contains the value in contain then do do include in the result
/// </summary>
/// <param name="stream">The stream that has lines to search</param>
/// <param name="contains">The value to search for if exists.</param>
/// <returns>The new stream</returns>
static std::stringstream if_line_in_stream_contains_exclude(std::stringstream& stream, const std::string& contains);

/// <summary>
/// attempt to find some indication of an error in the stream.
/// </summary>
/// <param name="stream">The stream that has lines to search</param>
/// <returns>The true is error: else false</returns>
static bool find_error_in_stream(std::stringstream& stream);

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

/// <summary>
/// if a line in the stream contains the value in contain then do do include in the result
/// </summary>
/// <param name="stream">The stream that has lines to search</param>
/// <param name="contains">The value to search for if exists.</param>
/// <returns>The new stream</returns>
static std::stringstream if_line_in_stream_contains_exclude(std::stringstream& stream, const std::string& contains)
{
    std::string line;
    std::stringstream resultStream;

    // while data.
    while (std::getline(stream, line)) {

        // if line contains value then skip
        if (line.find(contains) != std::string::npos) {
            // do nothing
        }
        else
        {
            // write to stream.
            resultStream << line << std::endl;
        }
    }

    // return the result
    return resultStream;
}

/// <summary>
/// attempt to find some indication of an error in the stream.
/// </summary>
/// <param name="stream">The stream that has lines to search</param>
/// <returns>The true is error: else false</returns>
static bool find_error_in_stream(std::stringstream& stream)
{
    bool hasError = false;
    std::string line;

    // while data.
    while (std::getline(stream, line)) {

        // if line contains value.
        if (line.find("Syntax") != std::string::npos) {

            // has error
            hasError = true;
            break;
        }

        // if line contains value.
        if (line.find("syntax") != std::string::npos) {

            // has error
            hasError = true;
            break;
        }
    }

    // return error
    return hasError;
}
