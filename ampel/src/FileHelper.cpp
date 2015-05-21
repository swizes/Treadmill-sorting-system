/*
 * FileHelper.cpp
 *
 *  Created on: 23.04.2015
 *      Author: abq793
 */

#include "FileHelper.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

FileHelper::FileHelper() {

}

FileHelper::~FileHelper() {

}

void FileHelper::test1() {
	DIR *dp;
	struct dirent *ep;

	dp = opendir ("/");
	if (dp != NULL)
	{
	  while (ep = readdir (dp))
		puts (ep->d_name);
	  (void) closedir (dp);
	}
	else
	perror ("Couldn't open the directory");
}

//bool FileHelper::

char* FileHelper::getConfigDir() {

}

char* FileHelper::getLogDir() {

}
