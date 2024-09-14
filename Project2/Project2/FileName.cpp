#include <conio.h> //������ cout ��ͻ
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

const int MAXN = 100; //������
char choice;

int raw, col;

void wait_for_enter() {
    cout << "\n���س�������";
    while (_getch() != '\r');
    cout << "\n\n";
}
void inputRC() {
    cout << "��������С�����(1-" << MAXN << "):";
    while (1) {
        cin >> raw >> col;
        if (cin.fail()) {
            cout << "������󣬷��������˳�����";
            exit(0);
        }
        else if (raw >= 1 and raw <= MAXN
            and col >= 1 and col <= MAXN) {
            break;
        }
        cout << "������Χ������������:";
    }
}
void inputMatrix(int matrix[MAXN * MAXN]) {
    for (int i = 0; i < raw * col; ++i) {
        cin >> matrix[i];
        if (cin.fail()) {
            cout << "������󣬷��������˳�����";
            exit(0);
        }
    }
}
void menu() {
    for (int i = 1; i <= 57; ++i) cout << "*";
    cout << "\n*       1 ����ӷ�      2 ��������      3 ����ת��      *";
    cout << "\n*       4 ����˷�      5 Hadamard�˻�  6 ������      *";
    cout << "\n*       7 ���Ӧ��      8 OTSU�㷨      9 ͼ��ָ�      *";
    cout << "\n*                       0 �˳�ϵͳ                      *\n";
    for (int i = 1; i <= 57; ++i) cout << "*";
    cout << "\nѡ��˵���<0~9>:";        // ��Ҫ������˵�ѡ����choice
    cin >> choice;
}
void matriplus() {
    inputRC();

    cout << "������� A ������:\n";
    int matrixA[MAXN * MAXN];
    inputMatrix(matrixA);

    cout << "������� B ������:\n";
    int matrixB[MAXN * MAXN];
    inputMatrix(matrixB);

    cout << "����֮��Ϊ:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << matrixA[i * col + j] + matrixB[i * col + j] << ' ';
        }
        cout << endl;
    }
    wait_for_enter();
}
void nummulti() {
    inputRC();

    cout << "������������:\n";
    int matrix[MAXN * MAXN];
    inputMatrix(matrix);

    cout << "��������:";
    int k;
    cin >> k;
    if (cin.fail()) {
        cout << "������󣬷��������˳�����";
        exit(0);
    }

    cout << "���˽��Ϊ:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << k * matrix[i * col + j] << ' ';
        }
        cout << endl;
    }
    wait_for_enter();
}
void matritrans() {
    inputRC();

    cout << "������������:\n";
    int matrix[MAXN * MAXN];
    inputMatrix(matrix);

    cout << "��ת��Ϊ:\n";
    for (int j = 0; j < col; ++j) {
        for (int i = 0; i < raw; ++i) {
            cout << matrix[i * col + j] << ' ';
        }
        cout << endl;
    }
    wait_for_enter();
}
void matrimulti() {
    inputRC();

    cout << "������� A ������:\n";
    int matrixA[MAXN * MAXN];
    inputMatrix(matrixA);

    cout << "������� B ������(1-" << MAXN << "):";
    int B_col;
    while (1) {
        cin >> B_col;
        if (cin.fail()) {
            cout << "������󣬷��������˳�����";
            exit(0);
        }
        else if (B_col >= 1 and B_col <= MAXN) {
            break;
        }
        cout << "������Χ������������:";
    }

    cout << "������� B ������:\n";
    int matrixB[MAXN * MAXN];
    for (int i = 0; i < col * B_col; ++i) {
        cin >> matrixB[i];
        if (cin.fail()) {
            cout << "������󣬷��������˳�����";
            exit(0);
        }
    }

    int sum = 0;
    cout << "�˻�Ϊ:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < B_col; ++j) {
            for (int z = 0; z < col; ++z) {
                sum += matrixA[i * col + z] * matrixB[z * B_col + j];
            }
            cout << sum << ' ';
            sum = 0;
        }
        cout << endl;
    }
    wait_for_enter();
}
void hadamulti() {
    inputRC();

    cout << "������� A ������:\n";
    int matrixA[MAXN * MAXN];
    inputMatrix(matrixA);

    cout << "������� B ������:\n";
    int matrixB[MAXN * MAXN];
    inputMatrix(matrixB);

    cout << "���ߵ� Hadamard �˻�Ϊ:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << matrixA[i * col + j] * matrixB[i * col + j] << ' ';
        }
        cout << endl;
    }
    wait_for_enter();
}
void conv() {
    inputRC();

    cout << "������������:\n";
    int matrix[MAXN * MAXN];
    inputMatrix(matrix);

    cout << "���� 3x3 �˾��������:\n";
    int kernel[9];
    for (int i = 0; i < 9; ++i) {
        cin >> kernel[i];
    }

    int result[MAXN * MAXN]{};
    for (int x = 0; x < raw; ++x) {
        for (int y = 0; y < col; ++y) { // ���������
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int nx = x + i;
                    int ny = y + j;
                    if (nx >= 0 && nx < raw && ny >= 0 && ny < col) { // ���߽磬����߽���Ϊ0�����
                        result[x * col + y] += matrix[nx * col + ny] * kernel[(i + 1) * 3 + (j + 1)];
                    }
                }
            }
        }
    }

    cout << "������Ϊ:\n";
    for (int i = 0; i < raw; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << result[i * col + j] << " ";
        }
        cout << endl;
    }
    wait_for_enter();
}
void demo() {
    int B[54]{ 1, 1, 1, 1, 1, 1, 1, 1, 1,
             -1, -2, -1, 0, 0, 0, 1, 2, 1,
             -1, 0, 1, -2, 0, 2, -1, 0, 1,
             -1, -1, -1, -1, 9, -1, -1, -1, -1,
             -1, -1, 0, -1, 0, 1, 0, 1, 1,
             1, 2, 1, 2, 4, 2, 1, 2, 1 },
        kernel[9];

    Mat image = imread(".//image//demolena.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    namedWindow("Image-original", WINDOW_NORMAL);
    imshow("Image-original", image);

    int matrix[256 * 256];
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            matrix[i * 256 + j] = image.ptr(i, j)[0];
        }
    }

    for (int b = 0; b < 6; ++b) {
        int kernel_sum = 0; //�����˵ĺ�
        for (int k = 0; k < 9; ++k) {
            kernel[k] = B[b * 9 + k];
            kernel_sum += kernel[k];
        }

        int result[256 * 256]{};
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 256; ++y) {
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        int nx = x + i;
                        int ny = y + j;
                        if (nx >= 0 && nx < 256 && ny >= 0 && ny < 256) {
                            result[x * 256 + y] += matrix[nx * 256 + ny] * kernel[(i + 1) * 3 + (j + 1)];
                        }
                    }
                }
                if (kernel_sum != 0) {
                    result[x * 256 + y] /= kernel_sum;
                }
                if (b == 1 or b == 2 or b == 4) {
                    result[x * 256 + y] += 128;    // �����ȹ��͵Ŀ��Լ�ƫ����
                }
                if (result[x * 256 + y] > 255) {
                    result[x * 256 + y] = 255;
                }
                else if (result[x * 256 + y] < 0) {
                    result[x * 256 + y] = 0;
                }
            }
        }

        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < 256; ++j) {
                image.ptr(i, j)[0] = image.ptr(i, j)[1] = image.ptr(i, j)[2] = result[i * 256 + j];
            }
        }
        string name = "B" + to_string(b + 1);
        namedWindow(name, WINDOW_NORMAL);
        imshow(name, image);
    }
    if (waitKey(30000)) destroyAllWindows();
}
void OTSU() {
    Mat image = imread(".//image//demolena.jpg");
    namedWindow("Image-original", WINDOW_NORMAL);
    imshow("Image-original", image);

    int threshold = 0; //�Ҷ�ֵ��ֵ

    int sumB = 0;
    int wB = 0;
    int wF = 0;
    double mB;
    double mF; //���Ծ�ֵ
    double varMax = 0; //��󷽲�
    double varBetween; //��䷽��

    int histogram[256]{};     //�Ҷ�ֱֵ��ͼ
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            histogram[image.ptr(i, j)[0]]++;
        }
    }

    int sum = 0;
    for (int i = 1; i < 256; ++i) {
        sum += i * histogram[i]; //�����ػҶ�ֵ�ܺ�
    }

    for (int i = 0; i < 256; ++i) {
        wB += histogram[i];
        if (wB == 0) continue; //Ϊ�㵼�·���Ϊ�㣬��������
        wF = 256 * 256 - wB;
        if (wF == 0) break; //˵���Ѿ�������ֵ����
        sumB += i * histogram[i];
        mB = (double)sumB / wB;
        mF = ((double)sum - (double)sumB) / wF;
        varBetween = wB * wF * (mB - mF) * (mB - mF);
        if (varBetween > varMax) {
            varMax = varBetween;  //������󷽲�����ֵ
            threshold = i;
        }
    }
    //��ֵ��
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            image.ptr(i, j)[0] = image.ptr(i, j)[0] > threshold ? 255 : 0;
            image.ptr(i, j)[1] = image.ptr(i, j)[1] > threshold ? 255 : 0;
            image.ptr(i, j)[2] = image.ptr(i, j)[2] > threshold ? 255 : 0;
        }
    }

    namedWindow("lena", WINDOW_NORMAL);
    imshow("lena", image);
    if (waitKey(30000)) destroyAllWindows();
}
void seg() {
    string path[4] = { "snowball","polyhedrosis","ship","brain" };
    for (int imageN = 0; imageN < 4; ++imageN) {
        Mat image = imread(".//image//" + path[imageN] + ".jpg"); // ԭͼ
        string name = "ORIGIN_IMAGE_" + to_string(imageN + 1);
        namedWindow(name, WINDOW_NORMAL);
        imshow(name, image);

        int threshold[3]{};
        for (int n = 0; n < 3; ++n) {
            int sumB = 0;
            int wB = 0;
            int wF = 0;
            double mB;
            double mF;
            double varMax = 0;
            double varBetween;
            int histogram[256]{};
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    histogram[image.ptr(i, j)[n]]++;
                }
            }
            int sum = 0;
            for (int i = 1; i < 256; ++i) {
                sum += i * histogram[i];
            }
            for (int i = 0; i < 256; ++i) {
                wB += histogram[i];
                if (wB == 0) continue;
                wF = image.rows * image.cols - wB;
                if (wF == 0) break;
                sumB += i * histogram[i];
                mB = (double)sumB / wB;
                mF = ((double)sum - (double)sumB) / wF;
                varBetween = wB * wF * (mB - mF) * (mB - mF);
                if (varBetween > varMax) {
                    varMax = varBetween;
                    threshold[n] = i;
                }
            }
        }
        //��ͼ�����߼������
        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                if (image.ptr(i, j)[0] < threshold[0] and image.ptr(i, j)[1] < threshold[1] and image.ptr(i, j)[2] < threshold[2])
                    image.ptr(i, j)[0] = image.ptr(i, j)[1] = image.ptr(i, j)[2] = 0;
            }
        }

        string result_name = "RESULT_" + to_string(imageN + 1);
        namedWindow(result_name, WINDOW_NORMAL);
        imshow(result_name, image);
    }
    if (waitKey(30000)) destroyAllWindows();
}

int main() {
    wait_for_enter();
    while (true) { // ע���ѭ���˳�������
        system("cls"); // ����
        menu(); // �˵�
        if (choice == '0') { // ѡ���˳�
            cout << "\n ȷ���˳���? (y/n):";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
                break;
            else
                continue;
        }
        switch (choice) {
        case '1':
            matriplus();
            break;
        case '2':
            nummulti();
            break;
        case '3':
            matritrans();
            break;
        case '4':
            matrimulti();
            break;
        case '5':
            hadamulti();
            break;
        case '6':
            conv();
            break;
        case '7':
            demo();
            break;
        case '8':
            OTSU();
            break;
        case '9':
            seg();
            break;
        default:
            cout << "\n �����������������\n";
            wait_for_enter();
        }
    }
    return 0;
}