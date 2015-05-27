/*
 * ConfigManager.cpp
 *
 *  Created on: 07.05.2015
 *      Author: abl441
 */


#include "ConfigManager.h"
#include <map>

char* configDir = null;
char* defaultConfigFileName = null;
std::map<char*, char*> configMap;

ConfigManager::ConfigManager(){

}

ConfigManager::ConfigManager() {

}

bool ConfigManager::readDefaultConfig() {

}

bool ConfigManager::writeDefaultConfig() {

}

bool ConfigManager::readConfig(char* configFileName) {

}

bool ConfigManager::writeConfig(char* configFileName) {

}

bool ConfigManager::hasKey(char* key) {
	for (std::map<char*,char*>::iterator it=configMap.begin(); it!=configMap.end(); ++it)
	{
		if(strcmp(it->first, key) == 0)
		{
			return true;
		}
	}

	return false;
}

bool ConfigManager::getConfigValue(char* key, char &outVal) {
	for (std::map<char*,char*>::iterator it=configMap.begin(); it!=configMap.end(); ++it)
	{
		if(strcmp(it->first, key) == 0)
		{
			outVal = it->second;
			return true;
		}
	}

	return false;
}

bool ConfigManager::setConfigValue(char* key, char* inVal) {
	configMap[key] = inVal;
}
