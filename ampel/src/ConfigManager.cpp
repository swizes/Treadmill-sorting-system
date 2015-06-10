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

#include <cstring>

using namespace std;

std::map<string, string> configMap;

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

bool ConfigManager::readConfig(string configFileName) {
	string fName = configFileName;
	string fPath = FileHelper::getConfigDir() + fName;
	cout << "read config from " << configFileName << endl;

	configMap.clear();

	string line;
	ifstream st_file (configFileName.c_str());

	if (st_file.is_open())
	{
		while ( getline (st_file,line) )
		{
		  //cout << line << '\n';
		  processConfigLine(line);
		}
		st_file.close();
	} else {
		cout << "unable to read config!" << endl;
	}
}

bool ConfigManager::writeConfig(string configFileName) {
	string fName = configFileName;
	string fPath = FileHelper::getConfigDir() + fName;
	cout << "write config (" << configMap.size() << " values) to " << configFileName << endl;

	string line;
	ofstream st_file (configFileName.c_str());

	if (st_file.is_open())
	{
		for (std::map<string,string>::iterator it=configMap.begin(); it!=configMap.end(); ++it)
		{
			st_file << it->first << ":" << it->second << endl;
		}
	} else {
		cout << "unable to write config!" << endl;
	}
}

bool ConfigManager::hasKey(string key) {
	for (std::map<string,string>::iterator it=configMap.begin(); it!=configMap.end(); ++it)
	{
		if(it->first.compare(key) == 0)
		{
			return true;
		}
	}

	return false;
}

bool ConfigManager::getConfigValue(string key, string *outVal) {
	for (std::map<string,string>::iterator it=configMap.begin(); it!=configMap.end(); ++it)
	{
		if(it->first.compare(key) == 0)
		{
			outVal->assign(it->second);
			return true;
		}
	}

	return false;
}

bool ConfigManager::setConfigValue(string key, string inVal) {
	configMap[key] = inVal;
	return true;
}

void ConfigManager::processConfigLine(string line) {
	//if(sline == null) return;
	std::size_t pos = line.find(CONFIG_SEPARATOR);
	if(pos != string::npos && line.length() > pos) {
		setConfigValue(line.substr(0, pos).c_str(), line.substr(pos+1).c_str());
	}
}
