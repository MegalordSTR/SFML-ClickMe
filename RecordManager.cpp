#include "RecordManager.h"

#include <fstream>
#include <cassert>
#include <stdexcept>

using json = nlohmann::json;

RecordManager::RecordManager(std::string path) :
	filepath(path)
{
}

void RecordManager::addRecord(const Record& r)
{
	std::vector<RecordManager::Record> oldRecords = getRecords();
	oldRecords.push_back(r);
	std::sort(oldRecords.begin(), oldRecords.end(),
		[](const RecordManager::Record& rl, const RecordManager::Record& rr) {return rl.score > rr.score; });

	std::ofstream file(filepath);
	if (!file.is_open())
		throw std::runtime_error("records file is not opened: " + filepath);

	json j = oldRecords;
	file << j;

	file.close();
}

std::vector<RecordManager::Record> RecordManager::getRecords() const
{
	assert(filepath != "");
	std::ifstream file(filepath);

	if (!file.is_open())
		throw std::runtime_error("records file is not opened: " + filepath);

	json j;
	file >> j;
	file.close();

	std::vector<RecordManager::Record> records;
	records.reserve(j.size());

	for (auto& jsonRecord : j)
	{
		Record r;
		from_json(jsonRecord, r);
		records.push_back(r);
	}

	return records;
}
