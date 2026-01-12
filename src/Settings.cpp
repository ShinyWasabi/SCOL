#include "Settings.hpp"
#include <nlohmann/json.hpp>

namespace SCOL
{
    static nlohmann::json LoadJson(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
            return nlohmann::json::object();

        nlohmann::json json;

        try
        {
            file >> json;
        }
        catch (...)
        {
            return nlohmann::json::object();
        }

        return json;
    }

    static void SaveJson(const std::string& path, const nlohmann::json& json)
    {
        std::ofstream file(path);
        file << json.dump(4);
    }

    void Settings::InitImpl(const std::string& file)
    {
        m_FileName = file;
        Load();
    }

    void Settings::LoadImpl()
    {
        nlohmann::json json = LoadJson(m_FileName);

        bool dirty = false;

        auto& settings = json["Settings"];

        if (!settings.contains("ScriptsFolder"))
        {
            settings["ScriptsFolder"] = ".";
            dirty = true;
        }

        if (!settings.contains("ScriptOverridesFolder"))
        {
            settings["ScriptOverridesFolder"] = "script-overrides";
            dirty = true;
        }

        if (!settings.contains("ReloadKey"))
        {
            settings["ReloadKey"] = VK_F5;
            dirty = true;
        }

        if (dirty)
            SaveJson(m_FileName, json);

        g_Variables.ScriptsFolder = settings.value("ScriptsFolder", ".");
        g_Variables.ScriptOverridesFolder = settings.value("ScriptOverridesFolder", "script-overrides");
        g_Variables.ReloadKey = settings.value("ReloadKey", VK_F5);
    }

    void Settings::UpdateImpl()
    {
        const auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - m_LastUpdate) < 3s)
            return;

        m_LastUpdate = now;

        Load();
    }

    Settings::ScriptData Settings::GetScriptDataImpl(const std::string& name)
    {
        nlohmann::json json = LoadJson(m_FileName);

        bool dirty = false;

        auto& entry = json[name];

        if (!entry.contains("Args"))
        {
            entry["Args"] = nlohmann::json::array();
            dirty = true;
        }

        if (!entry.contains("StackSize"))
        {
            entry["StackSize"] = 1424;
            dirty = true;
        }

        if (!entry.contains("CleanupFunction"))
        {
            entry["CleanupFunction"] = 0;
            dirty = true;
        }

        if (dirty)
            SaveJson(m_FileName, json);

        ScriptData data;
        data.Args = entry.value("Args", std::vector<std::uint64_t>{});
        data.StackSize = entry.value("StackSize", 1424);
        data.CleanupFunction = entry.value("CleanupFunction", 0);

        return data;
    }
}