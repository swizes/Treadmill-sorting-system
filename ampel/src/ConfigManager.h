/*
 * ConfigManager.h
 *
 *  Created on: 07.05.2015
 *      Author: abq793
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_


class ConfigManager {
public:
	ConfigManager();
	virtual ~ConfigManager();

	bool readDefaultConfig();
	bool writeDefaultConfig();
	bool readConfig(char* configFileName);
	bool writeConfig(char* configFileName);

	bool hasKey(char* key);
	bool getConfigValue(char* key, char &outVal);
	bool setConfigValue(char* key, char* inVal);

	// get key list?

private:

};

#endif /* CONFIGMANAGER_H_ */
