/*
 * ConfigManager.cpp
 *
 *  Created on: 07.05.2015
 *      Author: abl441
 */


#include "ConfigManager.h"
#include "FileHelper.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

std::map<char*, char*> configMap;

ConfigManager::ConfigManager(){

}

ConfigManager::~ConfigManager() {

}

bool ConfigManager::readDefaultConfig() {
	return readConfig(DEFAULT_CONFIG_FILENAME);
}

bool ConfigManager::writeDefaultConfig() {
	return writeConfig(DEFAULT_CONFIG_FILENAME);
}

bool ConfigManager::readConfig(char* configFileName) {
	string fName = string(configFileName);
	string fPath = FileHelper::getConfigDir() + fName;
	cout << "read config from " << configFileName << endl;

	configMap.clear();

	string line;
	ifstream st_file (configFileName);

	if (st_file.is_open())
	{
		while ( getline (st_file,line) )
		{
		  cout << line << '\n';
		}
		st_file.close();
	} else {
		cout << "unable to read config!" << endl;
	}
}

bool ConfigManager::writeConfig(char* configFileName) {
	string fName = string(configFileName);
	string fPath = FileHelper::getConfigDir() + fName;
	cout << "write config (" << configMap.size() << " values) to " << configFileName << endl;

	string line;
	ofstream st_file (configFileName);

	if (st_file.is_open())
	{
		for (std::map<char*,char*>::iterator it=configMap.begin(); it!=configMap.end(); ++it)
		{
			st_file << it->first << ":" << it->second << endl;
		}
	} else {
		cout << "unable to write config!" << endl;
	}
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

bool ConfigManager::getConfigValue(char* key, char **outVal) {
	for (std::map<char*,char*>::iterator it=configMap.begin(); it!=configMap.end(); ++it)
	{
		if(strcmp(it->first, key) == 0)
		{
			*outVal = it->second;
			return true;
		}
	}

	return false;
}

bool ConfigManager::setConfigValue(const char* key, const char* inVal) {
	char* pk = (char*)key;
	char* pv = (char*) inVal;
	configMap[pk] = pv;
	return true;
}

void ConfigManager::processConfigLine(char* line) {
	string sline = string(line);

	//if(sline == null) return;
	std::size_t pos = sline.find(CONFIG_SEPARATOR);
	if(pos != string::npos && sline.length() > pos) {
		string key = sline.substr(0, pos);
		string val = sline.substr(pos+1);
		setConfigValue(key.c_str(), val.c_str());
	}
}
