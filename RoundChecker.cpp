#include "RoundChecker.h"

#define	LED	17

using namespace std;
using namespace cv;
using namespace raspicam;

tpledef(T)
T** arr2dmake(int M, int N)
{
	T** array;
	array = (T**)malloc(sizeof(T*) * M);
	for (int i = 0; i < M; i++)
	{
		array[i] = (T*)malloc(sizeof(T) * M);
	}
	return array;
}
//ʹ��ģ����߸���
tpledef(T)
void arr2ddisp(T** array, int M, int N)
{
	for (int i = 0; i < M; i++)
		free(array[i]);
	free(array);
}

bool roundCheck(bool** map, int ic, int jc)
{
	int totalp = 0;
	for (int i = 0; i < ic + MINSTRP; i++)
	{
		for (int j = 0; j < jc + MINSTRP; j++)
		{
			//�˴������ټ�һ��Բ���ʽ�жϵ��Ƿ���Բ�����һ��Ҳû��Ҫ
			totalp += map[i][j];
		}
	}
	double z = (double)totalp / (double)(MINSTRP * MINSTRP);
	return z >= MINTHES;
}

void tMatMain(Mat* img)
{
	int w = img->rows, h = img->cols;
	bool** arr = arr2dmake<bool>(w, h);  //ע�ⲻ����bool[w][h]��ջ�Ų���
	for (int y = 0; y < img->rows; y++)
	{
		uchar* data = img->ptr<uchar>(y);
		for (int x = 0; x < img->cols; x++)
		{
			uchar b = data[3 * x],
				g = data[3 * x + 1],
				r = data[3 * x + 2];
			arr[x][y] = r < MAXBLACKPTCOLOR && g < MAXBLACKPTCOLOR && b < MAXBLACKPTCOLOR;
			//BGRֵ��С��MAXBLACKPTCOLOR(ֵ����)��Ϊ1
		}
	}
	//��ͼƬ�ж���һ��bool����(����������Ϊ1)
	bool founded = false;
	for (int y = MINSTRP; y < img->rows - MINSTRP; y++)
	{
		for (int x = MINSTRP; x < img->cols - MINSTRP; x++)
		{
			if (arr[x][y])
			{
				if (roundCheck(arr, x, y))
				{
					digitalWrite(LED, LOW);
					founded = true;
					goto TEND;
				}
			}
		}
	}
	digitalWrite(LED, HIGH);
TEND:
	//�ͷ��ڴ�
	arr2ddisp(arr, w, h);
}

