﻿#include "yn.h"
namespace jyn {

    String message = "";
    double ans = 0;
    void calc_op(double* val1, double* val2, int op_index, string str) { //두개의 값 연산하는 함수
        if ((int)str[op_index] == 120) { //곱셈
            *val1 = (*val1) * (*val2);
        }
        else if ((int)str[op_index] == 45) { //-
            *val1 -= (*val2);
        }
        else if ((int)str[op_index] == 47) {// /
            *val1 /= (*val2);
        }
        else if ((int)str[op_index] == 43) { //덧셈
            *val1 += *val2;
        }
    }

    string calc1() {  //문자열을 후위 표기법으로 만들기 기능 함수
        vector<char> op;// 연산자를 저장할 벡터
        string num = ""; // 숫자를 저장할 문자열 변수
        //문자를 숫자로
        int start = 0; 
        int ox = 0;
        int i, num_cnt = 0;
        for (i = 0; i < message.size(); i++) // 후위 표기법 만들기
        {
            if (((int)message[i] <= 57 && (int)message[i] > 47) && i == message.size() - 1) { // 문자열의 맨마지막이고  문자가 숫자이면
                num_cnt++;
                string s = message.substr(start, num_cnt);// 숫자
                num += s; //연산자 앞 숫자 자른 문자열 숫자로 바꿔서 넣기
                num += " ";
            }
            else if (((int)message[i] <= 57 && (int)message[i] > 47) || message[i] == '.') { //문자가 숫자 이거나 소수점이면

                num_cnt++; // 숫자 자리수,카운트하기
            }
            else { // 연산자이면
                if ((int)message[i - 1] <= 57 && (int)message[i - 1] > 47) { //연산자 앞이 숫자이면
                    string s = message.substr(start, num_cnt);//연산자 앞 숫자 만 자르기
                    num += s; //연산자 앞 숫자를 자른 문자열 숫자로 바꿔서 변수에 저장
                    num += " "; // 한 숫자 구분 띄어쓰기.
                    num_cnt = 0; //숫자 자리수 0개로 대입.
                }
                start = i + 1; //연산자 뒷 숫자의 인덱스
                if (op.empty()) {//연산자가 없으면, 첫 연산자가 등장시
                    op.push_back((char)message[i]); //연산자 넣기
                }
                else if (message[i] == '(' || message[i] == 'x' || message[i] == '/') { //이 연산자이면 벡터에 push
                    op.push_back((char)message[i]);
                }
                else if (message[i] == '+' || message[i] == '-') { //여는 괄호있으면  (위의 모든 연산자 출력, (없으면 벡터의 끝까지 출력 후 스택에push
                    for (int j = 0; j < op.size(); j++) //'+' '-' 연산이 나오면 여는 괄호 이후부터 끝까지 문자열에 입력
                    {
                        if (op[j] == '(') { //괄호 안  연산자 출력
                            if (op.size() - 1 == j) { // 괄호 위에 아무것도 없으면
                            }
                            else {
                                //여는 괄호 이후부터 끝까지 문자열에 입력
                                for (int k = op.size() - 1; k >= j + 1; k--)
                                {
                                    num += op[k];
                                    num += " "; // 구분

                                    op.pop_back(); // 연산자 벡터에서 마지막 연산자 삭제
                                }
                            }
                            ox++;
                        }
                    }
                    if (ox == 0) // 괄호 없으면 스택의 끝까지 출력
                    {
                        for (int k = op.size() - 1; k >= 0; k--)
                        {
                            num += op[k]; // 출력
                            num += " "; // 구분
                            op.pop_back();// 연산자 벡터에서 마지막 연산자 삭제

                        }
                    }
                    op.push_back((char)message[i]); // push
                    ox = 0;
                }
                else if (message[i] == ')') { // 닫는 괄호 나오면 여는 괄호까지 모든 op비우기

                    for (int j = 0; j < op.size(); j++)
                    {
                        if (op[j] == '(') {//여는 괄호까지 모든 op비우기
                            for (int k = op.size() - 1; k >= j + 1; k--)
                            {
                                num += op[k];//출력
                                num += " "; // 구분
                                op.pop_back();// 연산자 벡터에서 마지막 연산자 삭제

                            }

                            op.pop_back();// 연산자 벡터에서 마지막 연산자 삭제
                        }
                    }
                }
            }
        }
        if (i == message.size()) { // message의 식이 끝나면 벡터에 남아있는 연산자 모두 num에 출력
            for (int j = op.size() - 1; j >= 0; j--)
            {

                num += op[j]; //남아있는 연산자 넣기
                num += " "; // 구분
            }
        }
        cout << num << endl; // 후위표기법 출력
        return num;// 후위표기법 출력
    }
    double calc2(string str) { // 후위표기법 계산
        vector<double> v;
        int cur_position = 0; // 시작위치
        int position; // 공백 인덱스
        int cnt = 0;
        double val1, val2, value = 0;
        bool ox = false;
        while ((position = str.find(" ", cur_position)) != std::string::npos) {//문자열 앞에서부터 ' ' 공백을 기준으로 끊기
            int len = position - cur_position;//공백을 기준으로 끊은 문자의 개수
            string result = str.substr(cur_position, len);//문자열 시작위치에서 len개수만큼 잘라낸 문자열
            for (int i = 0; i < result.size(); i++) {
                if (((int)result[i] <= 57 && (int)result[i] > 47) || result[i] == '.') { // 숫자이거나 소수점이면
                    ox = true; // 숫자이면 벡터에 push
                    cnt++; //숫자이면 
                }
            }
            if (ox) { // 숫자이면
                v.push_back(stod(result));//숫자이면 벡터에 push
                ox = false;
            }
            if (cnt == 0) { //연산자이면 벡터의 마지막 요소와 마지막 전 요소끼리 연산후 두개의 요소를 pop하고 결과값을 벡터에 push

                val2 = v.back();// 벡터의 마지막 요소
                val1 = v[v.size() - 2];//마지막 전 요소
                //cout << "val1:" << val1 << "val2:" << val2 << endl;
                calc_op(&val1, &val2, cur_position, str);//벡터의 마지막 요소와 마지막 전 요소끼리 연산
                v.pop_back();//두개의 요소를 pop
                v[v.size() - 1] = val1; // 결과값을 벡터에 push
            }
            cur_position = position + 1; //시작위치 갱신
            cnt = 0;
        }
        value = v[0]; //계산 결괏값
        cout << "답:" << v[0] << endl;////계산 결괏값 출력
        return value;
    }

 
    void ce_button(Mat img) { //ce버튼 구현 함수
        Mat labels, stats, centroids;
        int cnt = connectedComponentsWithStats(img, labels, stats, centroids);//객체 레이블링
        //cout << stats.rows<<"개의 레이블 배경포함 객체수"<<endl;
        vector<Rect> r;
        for (int i = 0; i < cnt; i++)      //바운딩 박스 정보 vector<Rect>r에 저장
        {
            int* p = stats.ptr<int>(i); //행 역역 추출
            r.push_back(Rect(p[0], p[1], p[2], p[3]));  //바운딩 박스 정보 vector<Rect>r에 저장
        }
        Rect tmp;
        for (int i = 1; i < r.size(); i++)      // 벡터 r의 저장된 순서를 x좌표가 작은순부터 저장되도록 정렬
        {
            for (int j = 0; j < r.size() - i; j++)
            {
                if (r[j].x > r[j + 1].x) {// x좌표가 작은순부터 저장되도록 정렬
                    tmp = r[j];
                    r[j] = r[j + 1];
                    r[j + 1] = tmp;
                }
            }
        }
        int x = r[r.size() - 1].x; //마지막에 그려진 객체 영역 설정
        int y = r[r.size() - 1].y; //마지막에 그려진 객체 영역 설정
        int w = r[r.size() - 1].width; //마지막에 그려진 객체 영역 설정
        int h = r[r.size() - 1].height; //마지막에 그려진 객체 영역 설정
        Mat last = img(Rect(x, y, w, h)); //마지막에 그려진 객체 영역 설정
        last = Scalar(0); // 객체 영역 초기화
    }

    //문자 인식 기능 함수
    void Object_Recognition(Mat img, vector<Rect>& r) {   //필기체 입력구간 객체 인식, 레이블링 하는 함수
        Mat labels, stats, centroids; //객체 레이블링에 필요한 변수 생성
        int cnt = connectedComponentsWithStats(img, labels, stats, centroids);// 객체 레이블링

        for (int i = 0; i < cnt; i++)      //바운딩 박스 정보 vector<Rect>r에 저장
        {
            int* p = stats.ptr<int>(i); //i행 단위 정보 추출
            r.push_back(Rect(p[0]-30, p[1]-30, p[2]+60, p[3]+60)); // 바운딩 박스 정보에 여백을 포함한 크기를 벡터에 저장
        }

        Rect tmp; // 레이블링된 객체를 벡터r에 저장된 순서를 바꾸기위한 빈 객체 생성
        for (int i = 1; i < r.size(); i++)      // 벡터 r의 저장된 순서를 x좌표가 작은순부터 저장되도록 정렬
        {
            for (int j = 0; j < r.size() - i; j++) 
            {       // x좌표가 더 작은 객체가 작은 인덱스를 가지도록 설정
                if (r[j].x > r[j + 1].x) {// 객체의 x좌표 비교
                    tmp = r[j]; //x좌표가 큰 객체를대입
                    r[j] = r[j + 1]; //x좌표가 더 작은 객체 대입해 위치 변경
                    r[j + 1] = tmp; //대입
                }
            }
        }

    }
    int cnt = 0; //괄호 개수 세는 변수

    void tm_machine(Mat dst, vector<Rect>& r) //문자인식 기능 함수
    {
        int charcnt = 0;
        for (int i = 1; i < r.size(); i++) //객체 인식
        {
            if (r[i].width < 100 && r[i].height < 100) { //객체 높이와 넓이가 100이하이면 소수점 처리
                message += "."; // 예측결과 넣기
                cout << "예측 결과 : 소수점 ." << endl;
            }
            else { //소수점이 아니면 문자 인식 수행
                Mat img =dst(r[i]); //레이블링된 객체 이미지 추출

                vector<String> classNames = { "0","1","2","3","4","5","6","7","8","9","/","+","-","x","(","A","N","S" }; //클래스 이름 
                // Load network
                Net net = readNet("frozen_model.pb"); //모델 파일 불러오기
                if (net.empty()) { cerr << "Network load failed!" << endl; } //에러처리
                // Load an image
                if (img.empty()) { //에러처리
                    cerr << "Image load failed!" << endl;
                }
                // Inference
                Mat predict; //예측 이미지
                cvtColor(img, predict, COLOR_GRAY2RGB); //채널변경

                Mat inputBlob = blobFromImage(predict, 1 / 127.5, Size(224, 224), -1, 0); //블롭 객체 생성
                net.setInput(inputBlob);//네트워크 입력으로 설정
                Mat prob = net.forward(); //네트워크를 실행
                // Check results & Display

                double maxVal; // 최대값 저장할 변수
                Point maxLoc; //최대값 위치 저장할 변수
                minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
                if (classNames[maxLoc.x] == "A" || classNames[maxLoc.x] == "N" || classNames[maxLoc.x] == "S") { //문자처리
                    if (classNames[maxLoc.x] == "A" && charcnt == 0) { //a가 인식되면 
                        message += to_string(ans); //ans값 대입
                        charcnt = 1;
                        i += 2;
                    }
                    else if (classNames[maxLoc.x] == "N" && charcnt==0) { //n가 인식되면 
                        message += to_string(ans); //ans값 대입
                        charcnt = 1;
                        i ++;
                    }
                    else if (classNames[maxLoc.x] == "S" && charcnt == 0) { //s가 인식되면 
                        message += to_string(ans); //ans값 대입
                        charcnt = 1;
                    }
                }
                else if (classNames[maxLoc.x] == "(") { //괄호 처리
                    if (cnt == 0) { // 여는 괄호
                        message += classNames[maxLoc.x]; // ( 넣기!!!!!!!!!
                        cnt = 1;
                    }
                    else if (cnt == 1) {//닫는 괄호이면
                        message += ")"; // ( 넣기!!!!!!!!!
                        cnt = 0;
                    }
                }
                else {
                    message += classNames[maxLoc.x]; // 예측결과 넣기!!!!!!!!!
                }
                String str = classNames[maxLoc.x] + format("(%4.2lf%%)", maxVal *
                    100);
                cout << "예측 결과" << str << endl;//예측 결과 출력
                
                img = Scalar(0, 0, 0); //창 지우기

            }

        }

    }


    void draw(Mat img) {//gui 화면 구성 그리기 함수

        line(img, Point(0, 100), Point(img.cols, 100), Scalar(255), 2);//gui화면 구성 그리기
        line(img, Point(1300, 0), Point(1300, img.rows), Scalar(255), 2);//gui화면 구성 그리기
        line(img, Point(1300, 200), Point(img.cols, 200), Scalar(255), 2);//gui화면 구성 그리기
        line(img, Point(1300, 300), Point(img.cols, 300), Scalar(255), 2);//gui화면 구성 그리기

        putText(img, "AC", Point(1350, 70), FONT_HERSHEY_SIMPLEX, 2.5, Scalar(255), 3);//gui 기능별 버튼 그리기
        putText(img, "CE", Point(1350, 175), FONT_HERSHEY_SIMPLEX, 2.5, Scalar(255), 3);//gui 기능별 버튼 그리기
        putText(img, "Ans", Point(1350, 275), FONT_HERSHEY_SIMPLEX, 2, Scalar(255), 3);//gui 기능별 버튼 그리기
        putText(img, "=", Point(1350, 420), FONT_HERSHEY_SIMPLEX, 4, Scalar(255), 3);//gui 기능별 버튼 그리기
        imshow("img", img);
    }
    // 계산 결과 출력 기능 함수
    void draw_q(Mat img, Mat dst, double value, int ox) {
        draw(img); //gui 화면 구성 그리기 함수
        if (ox == 1) { //=일때 결괏값 출력
            int ok = -1;
            for (int i = 0; i < message.size(); i++)
            {
                if (message[i] == '(') { //괄호 한개이면 출력에서 지우기
                    ok = i;
                }
                else if (message[i] == ')') { //괄호 두개이면
                    ok = -1;//정상
                }
            }
            if (ok != -1) { //괄호가 안닫혀지면
                cout << "괄호 안 닫힘" << endl;
                message[ok] = ' ';
            }
            putText(img, message + " = ", Point(50, 80), FONT_HERSHEY_SIMPLEX, 3, Scalar(255), 3);//=일때 결괏값 출력
            dst = Scalar(0); //필기체 입력 칸 지우기

            putText(img, to_string(value), Point(200, 350), FONT_HERSHEY_SIMPLEX, 4, Scalar(255), 3);//=일때 결괏값 출력
        }
        else { //ans일때 값 출력
            img = Scalar(0); //화면 지우기
            putText(img, "Ans = " + to_string(ans), Point(50, 80), FONT_HERSHEY_SIMPLEX, 3, Scalar(255), 3);//ans일때 값 출력

        }
        imshow("img", img); //영상 출력
    }

    void onMouse(int event, int x, int y, int flags, void* userdata) { //마우스 콜백 함수
        Mat img = *(Mat*)userdata; // gui화면과 연결
        static Point ptOld; // 마지막 입력 좌표 저장

        Mat dst = img(Rect(0, 120, 1280, 380)); // 필기체 입력 구간 부분 영역 추출
        static double value;
        vector<Rect> r;
        static int level = 0;


        if (event == EVENT_LBUTTONDOWN) { //마우스 왼쪽 버튼
            ptOld = Point(x, y); // 마지막 입력 좌표 저장
            if (x >= 1300 && y >= 310) { // = 버튼 구간 설정 !                        
                Object_Recognition(dst, r); //필기체 입력구간 객체 인식, 레이블링
                tm_machine(dst, r); //문자인식 기능 함수

                //계산 기능 함수
                string str = calc1(); // 문자열을 후위표기법 으로 변환
                value = calc2(str); // 후위 표기법 계산

                img = Scalar(0); // 화면 지우기

                draw_q(img, dst, value, 1); //계산 결과값 출력 기능 함수

                message = "";
                level = 1;

            }
            else if (x >= 1300 && y <= 100) { // ac버튼 구간 설정
                img = Scalar(0); // 필기체 입력칸 지우기
                draw(img); // 필기체 구성 그리기 함수 호출

                level = 2;
            }
            else if (x >= 1300 && (y < 300 && y>200)) { // ans구간 설정
                if (level == 1) { // =버튼 입력 뒤에 사용가능
                    ans = value; //값 대입
                    cout << "ans:" << ans << endl; //출력
                    draw_q(img, dst, ans, 0); //값 출력
                    draw(img);
                    imshow("img", img);

                }
            }
            else if (x >= 1300 && y <= 200) { //ce 버튼 구간 설정

                ce_button(dst); //ce 버튼 구현 함수 호출
                imshow("img", img); //출력
            }


        }
        else if (event == EVENT_MOUSEMOVE) { //필기체 입력 그리기
            if (flags & EVENT_FLAG_LBUTTON) {
                if (x < 1300 && y >= 100) { //구간 설정
                    line(img, ptOld, Point(x, y), Scalar(255), 10); //그리기
                    imshow("img", img); //영상 출력
                    ptOld = Point(x, y); //마지막 좌표 저장

                }
            }
        }

    }
}