#pragma once
#pragma warning(push, 0)
#include <JSON/json.hpp>
#pragma warning(pop)

#include <string>
#include <vector>

class RecordManager
{
public:

	struct Record
	{
		std::string name;
		int32_t score;
	};

	RecordManager(std::string path);

	void addRecord(const Record& r);
	std::vector<Record> getRecords() const;

private:
	std::string filepath;
};

inline void to_json(nlohmann::json& j, const RecordManager::Record& r) {
	j = nlohmann::json{ {"name", r.name}, {"score", r.score} };
}

inline void from_json(const nlohmann::json& j, RecordManager::Record& r) {
	j.at("name").get_to(r.name);
	j.at("score").get_to(r.score);
}

