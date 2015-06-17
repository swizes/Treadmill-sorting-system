/*
 * FileHelper.h
 *
 *  Created on: 23.04.2015
 *      Author: abq793
 */

#ifndef FILEHELPER_H_
#define FILEHELPER_H_

#define DEFAULT_CONFIG_PATH "/tmp/"
#define DEFAULT_LOG_PATH "/tmp/"

class FileHelper {
public:
	FileHelper();
	virtual ~FileHelper();

	void test1();
	static char* getConfigDir();
	static char* getLogDir();

private:

};

#endif /* FILEHELPER_H_ */
