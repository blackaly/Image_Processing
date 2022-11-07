#include <stdio.h>

int main(){

	FILE* streamIn;
	streamIn = fopen("./lena512.bmp", "r");


	unsigned char header[54];
	unsigned char colorTable[1024]; 

	for(int i = 0; i < 54; ++i) header[i] = getc(streamIn);


	int width = *(int*)&header[18];
	int height = *(int*)&header[22];
	int bitDepth = *(int*)&header[28];


	if(bitDepth <= 8) fread(colorTable, sizeof(unsigned char), 1024, streamIn);

	unsigned char buff[height * width];
	fread(buff, sizeof(unsigned char), (height * width), streamIn);

	FILE *fo = fopen("./newimage.bmp", "wb");

	fwrite(header, sizeof(unsigned char), 54, fo);

	if(bitDepth <= 8) fwrite(colorTable, sizeof(unsigned char), 1024, fo);

	fwrite(buff, sizeof(unsigned char), (height * width), fo);

	fclose(fo);
	fclose(streamIn);




	return 0;

}
