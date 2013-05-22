
#include "stdafx.h" 
#include <graphics.h>
#include <iostream>
#include <fstream>
using namespace std;



   //Ascii�ַ��ͻҶ�

const struct AsciiPix
{
	char ascii[32];
	int gray[32];
}ascpix = {' ','`','.','^',',',':','~','"','<','!','c','t','+','{','i','7','?',
		'u','3','0','p','w','4','A','8','D','X','%','#','H','W','M',
		70,68,66,63,61,59,55,53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23,21,19,17,15,13,9,7,5,0};

/*
   ��Ѱ�Ҷ�gray������ַ�
   gray���滻�ĻҶ�
   ascpix�����滻�ַ��Ͷ�Ӧ�ҶȽṹ��
   */
static char SearchAsc(struct AsciiPix ascpix, int gray)
{
	int loop;

	loop = 0;
	while(gray < ascpix.gray[loop] && loop < 32 - 1)
		loop++;
	return ascpix.ascii[loop];
}

/*
   ͼƬתΪ�ַ��������浽AscPic.txt��
   start��һ��ͼƬ�����
   end���һ��ͼƬ�����
   Ĭ��ͼ��ߴ�160��120����
   Ĭ��ɨ���Ϊ��1��2�ľ��Σ��߶Σ�
   ����汾�����˾��ȣ�֡��СΪ320*240
   */
void Pic2Asc(int start, int end)
{
	int row, col;
	int gray;
	int loop;
	char filename[64];

	//���ļ�
	FILE *fp;
	if((fp = fopen("AscPic.txt", "w")) == NULL)
	{
		outtextxy(0, 0, "�ļ���ʧ��");
		Sleep(3000);
		return;
	}

	//��ʼת��
	const int high=320,weight=240;
	PIMAGE img;
	for(img = newimage(), loop = start; loop <= end; loop++)
	{
		sprintf(filename, "pic%08d.jpg", loop);
		outtextxy(0, 0, filename);

		getimage(img, filename, 0, 0);
		for(row = 0; row < weight; row += 2)
		{
			for(col = 0; col < high; col++)	
			{	
				gray = (GetRValue(getpixel(col, row, img)) + GetRValue(getpixel(col, row + 1, img))) * 9 / 51;
				fputc(SearchAsc(ascpix, gray), fp);
			}
			fputc('\n', fp);
		}
		fputc('\n', fp);
	}

	//�ƺ���
	delimage(img);
	fclose(fp);
}


int main()
{	
	int e;
	ifstream cin("cfg.txt");
	cin>>e;
	initgraph(640, 480);
	
	Pic2Asc(0, e);
	getch();

    closegraph();
	return 0;
}

