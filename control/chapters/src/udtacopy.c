/*! @file udta_copy.c
*
*  @brief Hack to copy global GPMF data from an MP4 to another
*
*  @version 1.0.1
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
#include <sys/types.h>
#include <sys/stat.h>


#ifdef WIN32
#define LONGSEEK  _fseeki64
#else
#define LONGSEEK  fseeko
#endif

#define MAKEID(a,b,c,d)			(((d&0xff)<<24)|((c&0xff)<<16)|((b&0xff)<<8)|(a&0xff))
#define STR2FOURCC(s)			((s[0]<<0)|(s[1]<<8)|(s[2]<<16)|(s[3]<<24))

#define BYTESWAP64(a)			(((a&0xff)<<56)|((a&0xff00)<<40)|((a&0xff0000)<<24)|((a&0xff000000)<<8) | ((a>>56)&0xff)|((a>>40)&0xff00)|((a>>24)&0xff0000)|((a>>8)&0xff000000) )
#define BYTESWAP32(a)			(((a&0xff)<<24)|((a&0xff00)<<8)|((a>>8)&0xff00)|((a>>24)&0xff))
#define BYTESWAP16(a)			((((a)>>8)&0xff)|(((a)<<8)&0xff00))
#define NOSWAP8(a)				(a)

#define NESTSIZE(x) { int i = nest; while (i > 0 && nestsize[i] > 0) { nestsize[i] -= x; if(nestsize[i]>=0 && nestsize[i] <= 8) { nestsize[i]=0; nest--; } i--; } }



#define GPMF_VALID_FOURCC(a)	(((((a>>24)&0xff)>='a'&&((a>>24)&0xff)<='z') || (((a>>24)&0xff)>='A'&&((a>>24)&0xff)<='Z') || (((a>>24)&0xff)>='0'&&((a>>24)&0xff)<='9') || (((a>>24)&0xff)==' ') ) && \
								( (((a>>16)&0xff)>='a'&&((a>>24)&0xff)<='z') || (((a>>16)&0xff)>='A'&&((a>>16)&0xff)<='Z') || (((a>>16)&0xff)>='0'&&((a>>16)&0xff)<='9') || (((a>>16)&0xff)==' ') ) && \
								( (((a>>8)&0xff)>='a'&&((a>>24)&0xff)<='z') || (((a>>8)&0xff)>='A'&&((a>>8)&0xff)<='Z') || (((a>>8)&0xff)>='0'&&((a>>8)&0xff)<='9') || (((a>>8)&0xff)==' ') ) && \
								( (((a>>0)&0xff)>='a'&&((a>>24)&0xff)<='z') || (((a>>0)&0xff)>='A'&&((a>>0)&0xff)<='Z') || (((a>>0)&0xff)>='0'&&((a>>0)&0xff)<='9') || (((a>>0)&0xff)==' ') )) 


uint64_t LongSeek(FILE* fp, int64_t offset, uint64_t filesize, uint64_t pos)
{
	if (fp && offset)
	{
		if (pos + offset < filesize)
		{
#ifdef _WINDOWS
			_fseeki64(fp, (__int64)offset, SEEK_CUR);
#else
			fseeko(fp, (off_t)offset, SEEK_CUR);
#endif
			pos += offset;
		}
		else
		{
			pos = filesize;
		}
	}

	return pos;
}


#define MAX_NEST_LEVEL	20


uint64_t OpenSourceUDTA(char *filename, uint64_t *udta_offset, uint32_t *udta_size, uint64_t *moov_offset, uint32_t *moov_size, uint32_t **udta)
{
	FILE *fp;
	uint64_t pos = 0;


#ifdef _WINDOWS
	struct _stat64 mp4stat;
	_stat64(filename, &mp4stat);
#else
	struct stat mp4stat;
	stat(filename, &mp4stat);
#endif
	uint64_t filesize = (uint64_t)mp4stat.st_size;
	if (filesize < 64)
	{
		return 0;
	}


#ifdef _WINDOWS
	fopen_s(&fp, filename, "rb");
#else
	fp = fopen(filename, "rb");
#endif
	
	if (fp)
	{
		uint32_t qttag, qtsize32;
		size_t len;
		int32_t nest = 0;
		uint64_t nestsize[MAX_NEST_LEVEL] = { 0 };
		uint64_t lastsize = 0, qtsize;

		do
		{
			len = fread(&qtsize32, 1, 4, fp);
			len += fread(&qttag, 1, 4, fp);
			if (len == 8)
			{
				if (!GPMF_VALID_FOURCC(qttag) && qttag != 0x7a7978a9)
				{
					pos += len;
					pos = LongSeek(fp, lastsize - 8 - len, filesize, pos);

					NESTSIZE(lastsize - 8);
					continue;
				}

				qtsize32 = BYTESWAP32(qtsize32);

				if (qtsize32 == 1) // 64-bit Atom
				{
					pos += len;
					len = fread(&qtsize, 1, 8, fp);
					qtsize = BYTESWAP64(qtsize) - 8;
				}
				else
					qtsize = qtsize32;

				nest++;

				if (qtsize < 8) break;
				if (nest >= MAX_NEST_LEVEL) break;
				if (nest > 1 && qtsize > nestsize[nest - 1]+8) break;

				nestsize[nest] = qtsize;
				lastsize = qtsize;

				if (qttag == MAKEID('m', 'd', 'a', 't') ||
					qttag == MAKEID('f', 't', 'y', 'p'))
				{
					pos += len;
					pos = LongSeek(fp, qtsize - 8, filesize, pos);
					NESTSIZE(qtsize);
					continue;
				}

				if (qttag == MAKEID('m', 'o', 'o', 'v'))
				{
					*moov_offset = pos;
					*moov_size = qtsize32;
					pos += len;
					//pos = LongSeek(fp, qtsize - 8, filesize, pos);
					NESTSIZE(8);
					continue;
				}
				else if(qttag == MAKEID('u', 'd', 't', 'a'))
				{
					*udta_offset = pos;
					*udta_size = qtsize32;
					pos += len;

					*udta = malloc(qtsize32);
					uint32_t *ptr = *udta;

					ptr[0] = BYTESWAP32(qtsize32);
					ptr[1] = qttag;

					fread(&ptr[2], 1, qtsize32 - 8, fp);
					break;
				}
				else
				{
					pos += len;
					pos = LongSeek(fp, qtsize - 8, filesize, pos);
					NESTSIZE(qtsize);
					continue;
				}
			}
		} while (len > 0);
	}

	fclose(fp);
	return filesize;
}




int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage: udtacopy <source.mp4> <dest.mp4>\n");
		printf(" vers: 1.02\n");
		printf("\n");
		return -1;
	}


	uint32_t udta_size = 0, moov_size = 0;
	uint32_t udta_size2 = 0, moov_size2 = 0;
	uint64_t len, udta_offset = 0, moov_offset = 0;
	uint64_t len2, udta_offset2 = 0, moov_offset2 = 0;
	uint32_t *udta = NULL, *udta2 = NULL;

	len = OpenSourceUDTA(argv[1], &udta_offset, &udta_size, &moov_offset, &moov_size, &udta);
	len2 = OpenSourceUDTA(argv[2], &udta_offset2, &udta_size2, &moov_offset2, &moov_size2, &udta2);


	if (moov_offset2 && moov_size2 && udta_offset && udta_size && udta)
	{
		uint32_t size;
		uint32_t freetag = 0x65657266; /* free */
		uint32_t udtatag = 0x61746475; /* udta */
		FILE *fp = fopen(argv[2], "rb+");


#ifdef _WINDOWS
		_fseeki64(fp, (__int64)(moov_offset2), 0);
#else
		fseeko(fp, (off_t)(moov_offset2), 0);
#endif
		moov_size2 += udta_size;

		size = BYTESWAP32(moov_size2);
		fwrite(&size, 4, 1, fp);


		if (udta_offset2) // remove old udta
		{
#ifdef _WINDOWS
			_fseeki64(fp, (__int64)(udta_offset2 + 4), 0);
#else
			fseeko(fp, (off_t)(moov_offset2 + 4), 0);
#endif
			fwrite(&freetag, 4, 1, fp);
		}


#ifdef _WINDOWS
		_fseeki64(fp, (__int64)len2, 0);
#else
		fseeko(fp, (off_t)len2, 0);
#endif
		fwrite(udta, 1, udta_size, fp);		
		fclose(fp);
	}

	return 1;
}
