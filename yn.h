
#ifndef YN_H
#define YN_H
#include<opencv2/opencv.hpp>
#include<iostream>
#include <vector>
#include <iostream>
#include<string>
#include<stdlib.h>
using namespace std;
using namespace cv::dnn;
using namespace cv;
namespace jyn
{


    extern int cnt ; // ���ڿ��� ��ȣ ������ ���� ���� ����
    extern String message; //�νĵ� ���ڿ��� �����ϴ� ���� ����
    extern double ans;
    void calc_op(double* val1, double* val2, int op_index, string str);   //�ΰ��� �� �����ϴ� �Լ�
    string calc1();                                                      //���ڿ��� ���� ǥ������� ����� ��� �Լ�
    double calc2(string str);                                           // ����ǥ��� ����ϴ� �Լ�
    void ce_button(Mat img);                                           //ce��ư ���� �Լ�
    void Object_Recognition(Mat img, vector<Rect>& r);                // =��ư ���� �Լ�, ��ü �ν�& ��ü ���̺�
    void draw(Mat img);                                                    //gui ȭ�� ���� �׸��� �Լ�
    void onMouse(int event, int x, int y, int flags, void* userdata);     //���콺 �ݹ� �Լ�
    void draw_q(Mat img, Mat dst, double value, int ox);                // ��� ��� ��� ��� �Լ�
    void tm_machine(Mat dst, vector<Rect>& r);

}
#endif