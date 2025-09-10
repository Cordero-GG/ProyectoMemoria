#include "json_serializer.h"
#include <chrono>
#include <iomanip>
#include <sstream>

using nlohmann::json;

static std::string timeToString(const std::chrono::system_clock::time_point& tp) {
    auto now = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&now), "%Y-%m-%dT%H:%M:%SZ");
    return ss.str();
}

json allocationToJson(void* ptr, size_t size, const char* file, int line) {
    return {
        {"type", "allocation"},
        {"address", reinterpret_cast<uintptr_t>(ptr)},
        {"size", size},
        {"file", file ? file : "unknown"},
        {"line", line},
        {"timestamp", timeToString(std::chrono::system_clock::now())}
    };
}

json deallocationToJson(void* ptr) {
    return {
        {"type", "deallocation"},
        {"address", reinterpret_cast<uintptr_t>(ptr)},
        {"timestamp", timeToString(std::chrono::system_clock::now())}
    };
}

json metricsToJson(size_t currentMemory, size_t activeAllocations,
                  size_t totalAllocations, size_t maxMemoryUsed) {
    return {
        {"type", "metrics"},
        {"current_memory", currentMemory},
        {"active_allocations", activeAllocations},
        {"total_allocations", totalAllocations},
        {"max_memory_used", maxMemoryUsed},
        {"timestamp", timeToString(std::chrono::system_clock::now())}
    };
}

json leakReportToJson(const std::unordered_map<void*, InfoMemoria>& leaks,
                     size_t totalLeakedMemory) {
    json leakArray = json::array();
    for (const auto& [address, info] : leaks) {
        leakArray.push_back({
            {"address", reinterpret_cast<uintptr_t>(address)},
            {"size", info.size},
            {"file", info.file ? info.file : "unknown"},
            {"line", info.line},
            {"allocation_time", timeToString(info.timestamp)}
        });
    }

    return {
        {"type", "leak_report"},
        {"total_leaked_memory", totalLeakedMemory},
        {"total_leaks", leaks.size()},
        {"leaks", leakArray}
    };
}

json fileSummaryToJson(const std::unordered_map<std::string,
                      std::pair<size_t, size_t>>& fileSummary) {
    json fileArray = json::array();
    for (const auto& [file, counts] : fileSummary) {
        fileArray.push_back({
            {"file", file},
            {"allocations_count", counts.first},
            {"total_memory", counts.second}
        });
    }

    return {
        {"type", "file_summary"},
        {"files", fileArray}
    };
}