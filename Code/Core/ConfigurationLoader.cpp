#include "ConfigurationLoader.h"
#include "ConfigurationLoadingException.h"
#include "Configuration.h"

#include <fstream>

ConfigurationLoader::ConfigurationLoader()
{
}

ConfigurationLoader::~ConfigurationLoader()
{
}

ConfigurationParameter ConfigurationLoader::getConfigurationParameter(std::string key)
{
	return { this->parametersMap[key] };
}

void ConfigurationLoader::loadLines(Lines lines)
{
	for (Lines::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		std::string key = (*it).substr(0, (*it).find("="));
		std::string value = (*it).substr((*it).find("=") + 1);
		this->parametersMap.insert(MapPair(key, value));
	}
}

Configuration * ConfigurationLoader::loadFromFile(std::string path)
{
	try
	{
		std::ifstream ifs(path.c_str());
		std::string str;
		std::vector<std::string> lines;
		while (std::getline(ifs, str))
		{
			lines.push_back(str);
		}

		ifs.close();

		return this->loadFromLines(lines);
	}
	catch (...)
	{
		throw ConfigurationLoadingException("Cannot load configuration.");
	}
}

Configuration * ConfigurationLoader::loadFromLines(std::vector<std::string> lines)
{
	try
	{
		this->loadLines(lines);
		return new Configuration(getConfigurationParameter(TAG_LOWER_BOUND),
			getConfigurationParameter(TAG_UPPER_BOUND),
			getConfigurationParameter(TAG_ACCELERATION),
			getConfigurationParameter(TAG_ANALYTICAL_FUNCTION),
			getConfigurationParameter(TAG_SCHEMA),
			getConfigurationParameter(TAG_GRID_SIZE),
			getConfigurationParameter(TAG_TIME_LEVELS),
			getConfigurationParameter(TAG_DELTA_T));
	}
	catch (...)
	{
		throw ConfigurationLoadingException("");
	}
}
