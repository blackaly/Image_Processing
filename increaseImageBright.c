#include <stdio.h>
#include <stdbool.h>

int main(){

	FILE* streamIn;
	streamIn = fopen("./lena512.bmp", "rb");


	unsigned char header[54];
	unsigned char colorTable[1024];

	for(int i = 0; i < 54; ++i) header[i] = getc(streamIn);


	int width = *(int*)&header[18];
	int height = *(int*)&header[22];
	int bitDepth = *(int*)&header[28];

	bool flag = (bitDepth <= 8) ? 1: 0;


	if(flag) fread(colorTable, sizeof(unsigned char), 1024, streamIn);

	unsigned char buff[height * width];
	fread(buff, sizeof(unsigned char), (height * width), streamIn);


	for(int i = 0; i < height * width; ++i)
		buff[i] += 25;


	FILE *fo = fopen("./newimage.bmp", "wb");

	fwrite(header, sizeof(unsigned char), 54, fo);

	if(flag) fwrite(colorTable, sizeof(unsigned char), 1024, fo);

	fwrite(buff, sizeof(unsigned char), (height * width), fo);

	fclose(fo);
	fclose(streamIn);




	return 0;

}
