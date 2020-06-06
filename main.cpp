// BigInteger2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<time.h>
#include"BigInteger.h"
using namespace std;
int main()
{
    clock_t start, finish;
    BigInteger a = (string)"9550402409777390394186958791544651496691743978829688919046036501754766168174422400203299653084969099306132708784489748148168555728657144898792410639006777";
    BigInteger b = (string)"763280796902010109709102165447154899457766327801";
    BigInteger n = (string)"9073323022371872597172072987726512502013488541023383002359822489597693630029312818715091885717467185335667238089412774093071473191438635819154507467262129";

    pair<string, string> re;
    start = clock();
    re = a.divide(a.absolute(), b);
    finish = clock();
    double totaltime = (double)(finish - start);
    cout << "\n此程序的运行时间为" << totaltime << "ms！" << endl;
    std::cout << re.first << std::endl;
    std::cout << re.second << std::endl;
    /*bool f = a.getNumber()[a.getNumber().size() - 1] & 0x01 == 0x00;
    std::cout << f << std::endl;*/
    //std::cout <<(a.modInverse(a,n)).getNumber() << std::endl;
    //std::cout << (a % b).getNumber() << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
