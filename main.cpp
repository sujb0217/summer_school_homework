#include <iostream>
#include <unistd.h>
#include <ctime>
using namespace std;

time_t now = time(0);
char * dt = ctime(&now);
// Hint print
void Hint()
{
    cout << "========== 药品供销管理系统 ==========" << endl << endl;
    cout << "     -----     欢迎使用！   -----    " << endl;
    cout << "       " << dt << endl << endl;
    cout << "     * 1: 设置及修改密码" << endl;
    cout << "     * 2: 录入药品基本信息" << endl;
    cout << "     * 3: 药品入库管理" << endl;
    cout << "     * 4: 药品销售管理" << endl;
    cout << "     * 5: 修改药品基本信息" << endl;
    cout << "     * 6: 输出全部药品信息" << endl;
    cout << "     * 7: 查询管理" << endl;
    cout << "     * 8: 统计管理" << endl;
    cout << "     * 9: 汇总报表" << endl;
    cout << "     * q: 退出系统" << endl << endl;
    cout << "所有功能在执行完毕后，都会自动将当前信息保存进文件" << endl << endl;
}

// Loading Bar
void progressBar() {
    cout << "* Loading" << '\n';
    sleep(2);
    cout << "###############    " << "(1/2)" << '\n';
    sleep(1);
    cout << "###############    " << "(2/2)";
}

int main() {
    Hint();
    return 0;
}