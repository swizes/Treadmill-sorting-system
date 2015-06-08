/*
 * ConfigManager.h
 *
 *  Created on: 07.05.2015
 *      Author: abq793
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#define DEFAULT_CONFIG_FILENAME "default.cf"
#define CONFIG_SEPARATOR ":"

class ConfigManager {
public:
	ConfigManager();
	virtual ~ConfigManager();

	bool readDefaultConfig();
	bool writeDefaultConfig();
	bool readConfig(char* configFileName);
	bool writeConfig(char* configFileName);

	bool hasKey(char* key);
	bool getConfigValue(char* key, char** outVal);
	bool setConfigValue(const char* key, const char* inVal);

private:
	void processConfigLine(char* line);
	// get key list?

private:

};

#endif /* CONFIGMANAGER_H_ */
