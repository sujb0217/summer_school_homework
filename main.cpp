/*
 *      学术与工程实践I（计算机）
 *      药品供销管理系统
 *      Environment: MacOS 10.15 / CentOS 7
 *      Language: C++
 *      Version: -std=c++ 11 or Later
 *      Author: 苏靖博(BOBLT Sudo)
 *      Date:
 */

#include <iostream>
#include <list>
#include <unistd.h>
#include <fstream>
#include <utility>
#include <ctime>
using namespace std;
/*      Attention: "NOLINT" is used to prevent errors on CLion    */

// Loading Bar
void progressBar()
{
    cout << "* Loading" << '\n';
    sleep(2);
    cout << "###############    "
         << "(1/2)" << '\n';
    sleep(1);
    cout << "###############    "
         << "(2/2)";
}

class Medicine
{
private:
    struct medicineMessage
    {
        string number;
        string name;
        string species;
        string manufacture;
        string price;
        string indate;
        string attentionMatters;
        string stock;
    };

    // 文件IO使用
    list<medicineMessage> ioMedicineList;
    string fileBasePath = "medicine_base.dat";

public:
    // First!
    // Put file content into List (Read)
    Medicine()
    {
        ifstream ifstr(fileBasePath, ios_base::in);
        // Just in case
        if (!ifstr.is_open())
        {
            ofstream tmp(fileBasePath, ios_base::out);
            if (!tmp.is_open())
            {
                cout << "文件打开失败" << endl;
                exit(-1);
            }
            tmp.close();
        }

        system("clear");
        // system("cls");

        // Open successfully
        ifstr.open(fileBasePath, ios_base::in);

        cout << "读取中 *" << endl;
        sleep(1);
        progressBar();
        cout << endl;

        medicineMessage msg;
        char ch[30];
        // Read the empty first line
        ifstr.getline(ch, sizeof(ch));

        while (!ifstr.eof())
        {
            ifstr.getline(ch, sizeof(ch));
            msg.number = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.name = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.species = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.manufacture = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.price = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.indate = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.attentionMatters = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.stock = ch;

            ioMedicineList.push_back(msg);
        }
        ifstr.close();
        cout << "文件读取完成" << endl;
    }

    bool logMedicineMessage()
    {
        medicineMessage message;
        cout << endl
             << "========= 药品信息录入 =========" << endl;
        cout << "@@@ 若想退出录入请输入\'q\' @@@" << endl
             << endl;
    L1:
        cout << "请输入药品编号";
        cin >> message.number;
        if (message.number == "q")
        {
            return false;
        }
        for (auto &item : ioMedicineList)
        {
            if (item.number == message.number)
            {
                cout << endl
                     << "药品重复录入，请检查录入药品的编号！" << endl
                     << endl;
                goto L1;
            }
        }

        // Log message until return false
        cout << endl;
        cout << "请输入药品名称：";
        cin >> message.name;
        if (message.name == "q")
        {
            return false;
        }
        cout << "请输入药品种类：";
        cin >> message.species;
        if (message.species == "q")
        {
            return false;
        }
        cout << "请输入药品生产厂家：";
        cin >> message.manufacture;
        if (message.manufacture == "q")
        {
            return false;
        }
        cout << "请输入药品价格：";
        cin >> message.price;
        if (message.price == "q")
        {
            return false;
        }
        cout << "请输入药品有效日期：";
        cin >> message.indate;
        if (message.indate == "q")
        {
            return false;
        }
        cout << "请输入药品注意事项：";
        cin >> message.attentionMatters;
        if (message.attentionMatters == "q")
        {
            return false;
        }
        cout << "请输入药品库存量（初始为0）：";
        cin >> message.stock;
        if (message.stock == "q")
        {
            return false;
        }
        cout << endl;

        ioMedicineList.push_back(message);

        ofstream ofstr(fileBasePath, ios_base::app);
        ofstr << endl
              << message.number << endl
              << message.name << endl
              << message.species << endl
              << message.manufacture << endl
              << message.price << endl
              << message.indate << endl
              << message.attentionMatters << endl
              << message.stock;

        ofstr.close();
        return true;
    }

    static double stringToDouble(const string &str)
    {
        double res = 0;
        int size = str.size() - 1;
        int i = 0;
        while (str[i] != '.' && i < size)
        {
            res = res * 10 + str[i] - '0';
            ++i;
        }
        // if(i < size) str[i] = '.'
        double tmp = 0;
        if (i < size)
        {
            for (int j = size - 1; j > i; --j)
            {
                tmp = (tmp + static_cast<double>(str[j] - '0')) / 10;
            }
        }

        return (res + tmp);
    }
    static int stringToInteger(const string &str)
    {
        int res = 0;
        int size = str.size() - 1;
        for (int i = 0; i < size; ++i)
        {
            res = res * 10 + str[i] - '0';
        }
        return res;
    }

    // May can not be used
    bool listSearch(const string &Name, const string &Num)
    {
        for (const auto &item : ioMedicineList) /* NOLINT */
        {
            if (item.name == Name && item.number == Num)
            {
                return true;
            }
        }
        return false;
    }

    // Match the "price" of medicine
    double perPrice(const string &medicineName)
    {
        double per_price;
        for (const auto &item : ioMedicineList)
        {
            if (item.name == medicineName)
            {
                per_price = stringToDouble(item.price);
            }
        }
        return per_price;
    }

    // TODO:删改的函数接口，注意变更后的刷新
    friend void modify();

private:
    string fileDealPath = "medicine_deal.dat";
    struct intoStorageMessage
    {
        string medicineName;
        string medicineNum;
        string intoStoragePerPrice;
        string intoStorageNum;
        string intoStoragePrice; // intoStoragePrice = intoStoragePerPrice * intoStorageNum
        string intoStorageTime;
        string intoStoragePerson;
        string intoStorageType;
    };

public:
    bool intoStorageMedicine()
    {
        intoStorageMessage iSM;
        cout << "========= 药品入库 =========" << endl;
        cout << "@@@ 若想要退出请输入\'q\' @@@" << endl
             << endl;
    L1:
        cout << "请输入入库药品编号：";
        cin >> iSM.medicineNum;
        if (iSM.medicineNum == "q")
        {
            return false;
        }
        bool flag = true;
        for (auto &item : ioMedicineList)
        {
            // Find match
            if (item.number == iSM.medicineNum)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            cout << "无药品信息，请重新输入" << endl;
            goto L1;
        }
        // TODO: 判断一下这里是否需要else?
        cout << "请输入入库药品名称：";
        cin >> iSM.medicineName;
        if (iSM.medicineName == "q")
        {
            return false;
        }
        cout << "请输入入库药品单价：";
        cin >> iSM.intoStoragePerPrice;
        if (iSM.intoStoragePerPrice == "q")
        {
            return false;
        }
        cout << "请输入入库药品数量：";
        cin >> iSM.intoStorageNum;
        if (iSM.intoStorageNum == "q")
        {
            return false;
        }
        int perPrice = stringToInteger(iSM.intoStoragePerPrice);
        int intoNum = stringToInteger(iSM.intoStorageNum);
        iSM.intoStoragePrice = to_string(perPrice * intoNum);
        cout << "入库药品金额：" << iSM.intoStoragePrice << endl;

        time_t now = time(nullptr);
        string dt = ctime(&now);
        iSM.intoStorageTime = dt;
        cout << "药品入库时间：" << iSM.intoStorageTime << endl;

        cout << "请输入入库员姓名：";
        cin >> iSM.intoStoragePerson;
        if (iSM.intoStoragePerson == "q")
        {
            return false;
        }
        cout << "交易类型：采购" << endl;
        iSM.intoStorageType = "采购";
        if (iSM.intoStorageType == "q")
        {
            return false;
        }

        // Refresh ioMedicineList.stock
        for (auto &item : ioMedicineList)
        {
            if (item.number == iSM.medicineNum)
            {
                int Prc = stringToInteger(item.stock);
                Prc += intoNum;
                item.stock = to_string(Prc);
            }
        }

        // Write into file

        ofstream ofstr(fileDealPath, ios_base::app);
        ofstr << endl
              << iSM.medicineNum << endl
              << iSM.medicineName << endl
              << iSM.intoStoragePerPrice << endl
              << iSM.intoStorageNum << endl
              << iSM.intoStoragePrice << endl
              << iSM.intoStorageTime << endl
              << iSM.intoStoragePerson << endl
              << iSM.intoStorageType;

        ofstr.close();
        return true;
    }

private:
    struct outStockMessage
    {
        string medicineName;
        string medicineNum;
        string outStockPerPrice;
        string outStockNum;
        string outStockPrice; // outStockPrice = outStockPerPrice * outStockNum
        string outStockTime;
        string outStockPerson;
        string outStockType;
    };

public:
    bool outStockMedicine()
    {
        outStockMessage oSM;
        cout << "========= 药品销售 =========" << endl;
        cout << "@@@ 如果想要退出输入，请输入\'q\' @@@" << endl;
    L2:
        cout << "请输入销售药品编号：";
        cin >> oSM.medicineNum;
        bool flag = true;
        int stockNum = 0;
        for (auto &item : ioMedicineList)
        {
            if (item.number == oSM.medicineNum)
            {
                stockNum = stringToInteger(item.stock);
                flag = false;
                break;
            }
        }
        if (flag)
        {
            cout << "无药品信息，请重新输入" << endl;
            goto L2;
        }
        // flag == false
        cout << "请输入购买数量：";
        cin >> oSM.outStockNum;
        // If it is more than stock?
        int outNum = stringToInteger(oSM.outStockNum);
        if (outNum > stockNum)
        {
            cout << "库存不足，请重新输入" << endl;
            goto L2;
        }
        else
        {

            cout << "销售药品编号：" << oSM.medicineNum << endl;

            cout << "请输入销售药品名称：";
            cin >> oSM.medicineName;
            if (oSM.medicineName == "q")
            {
                return false;
            }
            cout << "请输入交易单价：";
            cin >> oSM.outStockPerPrice;
            if (oSM.outStockPerPrice == "q")
            {
                return false;
            }
            cout << "交易数量：" << outNum << endl;
            oSM.outStockNum = to_string(outNum);

            cout << "交易金额：" << stringToInteger(oSM.outStockPerPrice) * outNum << endl;
            oSM.outStockPrice = to_string(stringToInteger(oSM.outStockPerPrice) * outNum);

            time_t now = time(nullptr);
            string dt = ctime(&now);
            oSM.outStockTime = dt;
            cout << "交易时间：" << dt << endl;

            cout << "请输入购买者姓名：";
            cin >> oSM.outStockPerson;
            if (oSM.outStockPerson == "q")
            {
                return false;
            }

            oSM.outStockType = "销售";
            cout << "交易类型："
                 << "销售" << endl;

            ofstream ofstr(fileDealPath, ios_base::app);
            ofstr << endl
                  << oSM.medicineName << endl
                  << oSM.medicineNum << endl
                  << oSM.outStockPerPrice << endl
                  << oSM.outStockNum << endl
                  << oSM.outStockPrice << endl
                  << oSM.outStockTime << endl
                  << oSM.outStockPerson << endl
                  << oSM.outStockType;

            ofstr.close();
            return true;
        }
    }

    // Func.6 Output all messages
    void outputAllMessages()
    {
        // Output medicine basic messages
        cout << "药品的基本信息：" << endl;
        for (auto &item : ioMedicineList)
        {
            cout << "药品编号：" << item.number << endl;
            cout << "药品名称：" << item.name << endl;
            cout << "药品种类：" << item.species << endl;
            cout << "生产厂家：" << item.manufacture << endl;
            cout << "药品价格：" << item.price << endl;
            cout << "药品有效期：" << item.indate << endl;
            cout << "药品注意事项：" << item.attentionMatters << endl;
            cout << "药品库存量：" << item.stock << endl;
        }
        cout << endl
             << "药品交易信息：" << endl;
    }
};

// Clarify a Medicine Class
Medicine medicine; /* NOLINT */
// Func.5 Modify or delete the basic information of medicine
void modify()
{
}

// Set and reset the password
string password;
bool pwd = false;
bool flag = true;
const string root = "20105050110"; /* NOLINT */
void login()
{
    if (!pwd)
    {
        // The password is not set
        cout << "请为系统设置密码：";
        cin >> password;
        pwd = true;
    }
    else
    {
        // The password has been set
        cout << endl
             << "##### 按「l」以输入密码登录系统 ##### 按「r」以重设密码 #####" << endl;
        char ch;
        getchar();      // Get the top '\n'
        ch = getchar(); /* NOLINT */
        getchar();      // Get the input '\n'
        switch (ch)
        {
        case 'l':
        {
        L1:
            cout << "请输入密码：";
            string tmp;
            cin >> tmp;
            if (tmp == password)
            {
                cout << endl;
                progressBar();
                cout << endl;
                sleep(1);
                cout << endl;
                cout << "@@@@@@ 欢 迎 使 用 @@@@@@" << endl
                     << endl;
                flag = false;
                sleep(1);
                system("clear");
                //                  system("cls");
            }
            else
            {
                sleep(1);
                cout << "您输入的密码不匹配，请重新输入！" << endl
                     << endl;
                goto L1;
            }
            break;
        }
        case 'r':
        {
        L2:
            cout << "请输入root密码：";
            string tmp;
            cin >> tmp;
            if (tmp == root)
            {
                sleep(1);
                cout << "====== Admin ======" << endl;
                sleep(1);
                cout << "尊敬的管理员欢迎您！" << endl;
                sleep(1);
                cout << "请输入您想重设的密码：" << endl;
                cin >> password;
                pwd = true;
                flag = false;
                progressBar();
                sleep(1);
                cout << endl
                     << "密码已经重新设置！" << endl
                     << endl;
                system("clear");
            }
            else
            {
                cout << "密码错误！若想重设密码请联系管理员" << endl;
                goto L2;
            }
            break;
        }

        default:
            break;
        }
    }
}

// Hint print
void Hint()
{
    time_t now = time(nullptr);
    string dt = ctime(&now);

    cout << "========== 药品供销管理系统 ==========" << endl
         << endl;
    cout << "      -----    欢迎使用！   -----    " << endl;
    cout << "       " << dt << endl
         << endl;
    cout << "     * 1: 设置及修改密码" << endl;
    cout << "     * 2: 录入药品基本信息" << endl;
    cout << "     * 3: 药品入库管理" << endl;
    cout << "     * 4: 药品销售管理" << endl;
    cout << "     * 5: 修改药品基本信息" << endl;
    cout << "     * 6: 输出全部药品信息" << endl;
    cout << "     * 7: 查询管理" << endl;
    cout << "     * 8: 统计管理" << endl;
    cout << "     * 9: 汇总报表" << endl;
    cout << "     * q: 退出系统" << endl
         << endl;
    cout << "所有功能在执行完毕后，都会自动将当前信息保存进文件" << endl
         << endl;
}

int main()
{

    Hint();

    if (!pwd)
    {
        cout << "请先选1设置密码：";
        char ch;
        ch = getchar(); /* NOLINT */
        getchar();      /* NOLINT */
        while (ch != '1')
        {
            cout << "请先选1设置密码！";
            ch = getchar(); /* NOLINT */
            getchar();
        }
        while (flag)
        {
            login();
        }
    }
    else
    {
        cout << "请先选1登录系统：";
        char ch;
        ch = getchar(); /* NOLINT */
        getchar();
        while (ch != '1')
        {
            cout << "请先选1登录系统！";
            ch = getchar(); /* NOLINT */
            getchar();
        }
        while (flag)
        {
            login();
        }
    }
    if (!flag)
    {
        while (true)
        {
            Hint();
            cout << "请输入您的需求：";
            char ch;
            ch = getchar(); /* NOLINT */
            ch = getchar(); /* NOLINT */
            switch (ch)
            {
            case '1':
            {
                flag = true;
            L3:
                cout << "请输入root密码：";
                string tmp;
                cin >> tmp;
                if (tmp == root)
                {
                    sleep(1);
                    cout << "====== Admin ======" << endl;
                    sleep(1);
                    cout << "尊敬的管理员欢迎您！" << endl;
                    sleep(1);
                    cout << "请输入您想重设的密码：" << endl;
                    cin >> password;
                    pwd = true;
                    flag = false;
                    cout << endl;
                    progressBar();
                    sleep(1);
                    cout << endl
                         << "密码已经重新设置！" << endl
                         << endl;

                    system("clear");
                    //                      system("cls");
                }
                else
                {
                    cout << "root密码错误，若想重设密码请联系管理员" << endl;
                    goto L3;
                }
                break;
            }
            case '2':
            {
                {

                    break;
                }
            }
            case '3':
            {

                break;
            }
            case '4':
            {

                break;
            }
            case '5':
                modify();
                break;
            case '6':
            case '7':
            case '8':
            case '9':
            case 'q':
                cout << endl
                     << "感谢您的使用，再会👋" << endl
                     << endl;
                cout << "============== E O F ==============" << endl;
                return 0;
            default:
                break;
            }
        }
    }

    return 0;
}