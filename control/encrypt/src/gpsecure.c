/*! @file GPMF_demo.c
*
*  @brief Demo to decrypt an MP4
*
*  @version 1.1.0
*
*  (C) Copyright 2017-2021 GoPro Inc (http://gopro.com/).
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define VER "1.03"

#ifdef _WINDOWS

#define _CRT_SECURE_NO_WARNINGS

#endif

char g_initseckey[] = "?TB5=)qwF*;*B9m$";
uint8_t g_seckey[16];
uint8_t g_dekey[16];
uint8_t g_secure = 1;


int main(int argc, char *argv[])
{
	uint8_t password[17] = { 0 };
	int len,i;

	// get file return data
	if (argc < 3)
	{
		printf("usage: gpsecure <GoPro MP4s or JPGs> -pPassword\n");
		printf("examples: gpsecure SOPR0018.JPG -pTest\n");
		printf("          gpsecure SX010019.MP4 SL010019.LRV -pUnlock\n");
		printf("          gpsecure S*0019.* -p123456\n");
		printf("          gpsecure S*.* -pSecret\n");
		printf("version: %s\n", VER);
		return -1;
	}

	for (i = 1; i < argc; i++)
	{
		if (strlen(argv[1]) >= 6 && argv[i][0] == '-' && argv[i][1] == 'p')
			strncpy(password, &argv[i][2], 16);
	}
	password[16] = 0;

	len = (int)strlen(password);
	if (len < 4)
	{
		printf("need a password of 4-16 characters\n");
		printf("usage: %s <GoPro MP4s> -pPassword\n", argv[0]);
		return -1;
	}

	memcpy(g_seckey, g_initseckey, 16);
	memcpy(g_seckey, password, len);
	memcpy(g_dekey, g_seckey, 16);

	extern int decryptFile(char* path, char* name);
	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
		{
			int ret = decryptFile("", argv[i]);

			if(ret > 0)
				printf("encrypted from %s  \n", argv[i]);
			else if(ret < 0)
				printf("decrypted from %s  \n", argv[i]);
			else
				printf("failed to open or en/decrypt %s\n", argv[i]);
		}
	}

	return 0;
}
