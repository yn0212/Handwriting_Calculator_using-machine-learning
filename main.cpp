#include "yn.h"
using namespace jyn;
int main(void) {
	Mat img(500, 1500, CV_8UC1, Scalar(0)); //guiȭ�� ���
	draw(img); //gui ȭ�� ���� �׸��� �Լ�

	setMouseCallback("img", onMouse, &img); //���콺 �ݹ��Լ� ���
	imshow("img", img); //���� ���
	waitKey(); //���� ���

	return 0; //0�� �ܺη� ��ȯ
}
