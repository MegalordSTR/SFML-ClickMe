#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourseHolder
{
public:
	void load(Identifier id, const std::string& path);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
	std::unordered_map<Identifier, std::unique_ptr<Resource>> resources;
};

template<typename Resource, typename Identifier>
inline void ResourseHolder<Resource, Identifier>::load(Identifier id, const std::string& path)
{
	std::unique_ptr<Resource> resource = std::make_unique<Resource>();

	if (!resource->loadFromFile(path))
	{
		throw std::runtime_error("ResourseHolder loading error: path = " + path);
	}

	insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
inline Resource& ResourseHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = resources.find(id);
	assert(found != resources.end());

	return *found->second;
}

template<typename Resource, typename Identifier>
inline const Resource& ResourseHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = resources.find(id);
	assert(found != resources.end());

	return *found->second;
}

template<typename Resource, typename Identifier>
inline void ResourseHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	auto inserted = resources.emplace(id, std::move(resource));
	assert(inserted.second);
}
