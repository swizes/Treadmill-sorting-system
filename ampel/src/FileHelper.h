/*
 * FileHelper.h
 *
 *  Created on: 23.04.2015
 *      Author: abq793
 */

#ifndef FILEHELPER_H_
#define FILEHELPER_H_


class FileHelper {
public:
	FileHelper();
	virtual ~FileHelper();

	void test1();
	char* getConfigDir();
	char* getLogDir();

private:

};

#endif /* FILEHELPER_H_ */
