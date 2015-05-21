/*
 * ConfigManager.cpp
 *
 *  Created on: 07.05.2015
 *      Author: abl441
 */


#include "ConfigManager.h"
#include <string>

char* configDir = null;
char* defaultConfigFileName = null;
std::map<string, string> configMap;

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

}

bool ConfigManager::getConfigValue(char* key, char &outVal) {

}

bool ConfigManager::setConfigValue(char* key, char* inVal) {

}
