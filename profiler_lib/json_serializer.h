#pragma once
#include "profiler.h"
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

// Funciones para serializar datos a JSON
nlohmann::json allocationToJson(void* ptr, size_t size, const char* file, int line);
nlohmann::json deallocationToJson(void* ptr);
nlohmann::json metricsToJson(size_t currentMemory, size_t activeAllocations,
                            size_t totalAllocations, size_t maxMemoryUsed);
nlohmann::json leakReportToJson(const std::unordered_map<void*, InfoMemoria>& leaks,
                               size_t totalLeakedMemory);
nlohmann::json fileSummaryToJson(const std::unordered_map<std::string,
                                std::pair<size_t, size_t>>& fileSummary);