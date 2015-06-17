/*
 * ConfigManager.h
 *
 *  Created on: 07.05.2015
 *      Author: abq793
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#define DEFAULT_CONFIG_FILENAME "default.cfg"
#define CONFIG_SEPARATOR ":"

#include <string>

class ConfigManager {
public:
	ConfigManager();
	virtual ~ConfigManager();

	bool readDefaultConfig();
	bool writeDefaultConfig();
	bool readConfig(std::string configFileName);
	bool writeConfig(std::string configFileName);

	bool hasKey(std::string key);
	bool getConfigValue(std::string key, std::string* outVal);
	bool setConfigValue(std::string key, std::string inVal);

private:
	void processConfigLine(std::string line);
	// get key list?

private:

};

#endif /* CONFIGMANAGER_H_ */
