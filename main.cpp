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
    cout << "* Loading" << endl;
    sleep(2);
    cout << "[##########        ]  "
         << "(1/2)" << endl;
    sleep(1);
    cout << "[##################]  "
         << "(2/2)" << endl;
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
        ifstream ifstr(fileBasePath, ios::in);
        // Just in case
        if (!ifstr.is_open())
        {
            ofstream tmp(fileBasePath, ios::out);
            if (!tmp.is_open())
            {
                cout << "文件创建失败，退出程序" << endl;
                exit(-1);
            }
            tmp.close();
        }

        system("clear");
        // system("cls");

        // Open successfully
        cout << "******** 欢迎使用药品供销系统 ********" << endl;
        sleep(1);
        progressBar();
        cout << endl;

        ifstream ifst(fileBasePath, ios::in);
        char ch[30];
        medicineMessage msg;

        // Read the empty first line
        ifst.getline(ch, sizeof(ch));

        while (!ifst.eof())
        {
            ifst.getline(ch, sizeof(ch));
            msg.number = ch;
            ifst.getline(ch, sizeof(ch));
            msg.name = ch;
            ifst.getline(ch, sizeof(ch));
            msg.species = ch;
            ifst.getline(ch, sizeof(ch));
            msg.manufacture = ch;
            ifst.getline(ch, sizeof(ch));
            msg.price = ch;
            ifst.getline(ch, sizeof(ch));
            msg.indate = ch;
            ifst.getline(ch, sizeof(ch));
            msg.attentionMatters = ch;
            ifst.getline(ch, sizeof(ch));
            msg.stock = ch;

            ioMedicineList.push_back(msg);
        }

        cout << "文件读取完成" << endl;
        sleep(1);
        cout << endl;
        system("clear");
        // system("cls");
    }

    bool logMedicineMessage()
    {
        medicineMessage message;
        cout << endl
             << "========= 药品信息录入 =========" << endl;
        cout << "@@@ 若想退出录入请输入\'q\' @@@" << endl
             << endl;
    L1:
        cout << "请输入药品编号：";
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
        int size = str.size();
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
        int size = str.size();
        for (int i = 0; i < size; ++i)
        {
            res = res * 10 + (str[i] - '0');
        }
        return res;
    }

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
        double perPrice = stringToDouble(iSM.intoStoragePerPrice);
        int intoNum = stringToInteger(iSM.intoStorageNum);
        iSM.intoStoragePrice = to_string(static_cast<double>(perPrice * intoNum));
        cout.precision(3);
        cout << "入库药品金额：" << iSM.intoStoragePrice << endl;

        time_t now = time(nullptr);
        string dt = ctime(&now);
        cout << "时间（UTC + 800）：" << dt << endl;
        cout << "请输入药品入库日期：";
        cin >> iSM.intoStorageTime;
        if (iSM.intoStorageTime == "q")
        {
            return false;
        }

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

        // Refresh ioMedicineList.stockNum
        for (auto &item : ioMedicineList)
        {
            if (item.number == iSM.medicineNum)
            {
                int Stk = stringToInteger(item.stock);
                Stk += intoNum;
                item.stock = to_string(Stk);
            }
        }

        // Write into file

        ofstream ofstr(fileDealPath, ios_base::app);
        ofstr << endl
              << iSM.medicineName << endl
              << iSM.medicineNum << endl
              << iSM.intoStoragePerPrice << endl
              << iSM.intoStorageNum << endl
              << iSM.intoStoragePrice << endl
              << iSM.intoStorageTime
              << iSM.intoStoragePerson << endl
              << iSM.intoStorageType;

        ofstr.close();
        cout << endl;
        progressBar();
        sleep(1);
        cout << endl
             << endl;
        system("clear");
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
        string buyer;
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
        if (oSM.medicineNum == "q")
        {
            return false;
        }
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
        if (oSM.outStockNum == "q")
        {
            return false;
        }
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

            oSM.outStockPrice = to_string(static_cast<double>(stringToDouble(oSM.outStockPerPrice) * outNum));
            cout.precision(3);
            cout << "交易金额：" << oSM.outStockPrice << endl;

            time_t now = time(nullptr);
            string dt = ctime(&now);
            cout << "时间（UTC + 800）：" << dt << endl;
            cout << "请输入药品交易日期：";
            cin >> oSM.outStockTime;
            if (oSM.outStockTime == "q")
            {
                return false;
            }

            cout << "请输入购买者姓名：";
            cin >> oSM.buyer;
            if (oSM.buyer == "q")
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
                  << oSM.outStockTime
                  << oSM.buyer << endl
                  << oSM.outStockType;

            ofstr.close();
            return true;
        }
    }

    // Func.5 Modify or delete the basic information of medicine
    bool modify()
    {
        Medicine medicine;
        // species, manufacture, price, intdate, attentionMatters can be modified
        // medicineNum, medicineName, medicineStock can not be modified!
        // And the medicine information can not be modified if the medicine have been dealt!

    L0:
        cout << "---------- 修改药品基本信息 ----------" << endl
             << endl;
        cout << "请选择想要进行的操作（修改信息/删除信息）" << endl;
        cout << "     *1 修改药品信息" << endl;
        cout << "     *2 删除药品信息" << endl;
        cout << endl
             << "请输入想要进行的操作（1 / 2）如果想退出请输入\'q\'" << endl;
        char ops;
        cin >> ops;
        if (ops == '1')
        {
        // Modify
        L1:
            cout << "请输入您想要修改信息的药品编号：" << endl;
            string medicineNumber;
            cin >> medicineNumber;
            bool flag = true;
            for (auto &item : ioMedicineList)
            {
                if (item.number == medicineNumber)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                cout << "未找到此药品信息，请检查输入" << endl;
                goto L1;
            }
            else
            {
                cout << endl
                     << "请选择您想要修改的药品信息：" << endl
                     << endl;
                cout << "     *1 药品种类" << endl;
                cout << "     *2 生产厂家" << endl;
                cout << "     *3 药品价格" << endl;
                cout << "     *4 有效日期" << endl;
                cout << "     *5 注意事项" << endl;
            L2:
                cout << "请输入您想要修改的药品信息，如果想退出请输入\'q\'" << endl;
                char choice;
                cin >> choice;

                if (choice == '1')
                {
                    cout << "请输入您想修改成的药品种类：" << endl;
                    string newMedicineSpecies;
                    cin >> newMedicineSpecies;
                    for (auto &item : ioMedicineList)
                    {
                        if (item.number == medicineNumber)
                        {
                            item.species = newMedicineSpecies;
                        }
                    }
                }
                else if (choice == '2')
                {
                    cout << "请输入您想修改成的药品生产厂家：" << endl;
                    string newMedicineManufacture;
                    cin >> newMedicineManufacture;
                    for (auto &item : ioMedicineList)
                    {
                        if (item.number == medicineNumber)
                        {
                            item.manufacture = newMedicineManufacture;
                        }
                    }
                }
                else if (choice == '3')
                {
                    cout << "请输入您想修改成的药品价格：" << endl;
                    string newMedicinePrice;
                    cin >> newMedicinePrice;
                    for (auto &item : ioMedicineList)
                    {
                        if (item.number == medicineNumber)
                        {
                            item.price = newMedicinePrice;
                        }
                    }
                }
                else if (choice == '4')
                {
                    cout << "请输入您想修改成的药品有效日期：" << endl;
                    string newMedicineIndate;
                    cin >> newMedicineIndate;
                    for (auto &item : ioMedicineList)
                    {
                        if (item.number == medicineNumber)
                        {
                            item.indate = newMedicineIndate;
                        }
                    }
                }
                else if (choice == '5')
                {
                    cout << "请输入您想修改成的注意事项：" << endl;
                    string newMedicineAttentions;
                    cin >> newMedicineAttentions;
                    for (auto &item : ioMedicineList)
                    {
                        if (item.number == medicineNumber)
                        {
                            item.attentionMatters = newMedicineAttentions;
                        }
                    }
                }
                else if (choice == 'q')
                {
                    cout << "** 正在退出 **" << endl;
                    sleep(1);
                    goto L0;
                }
                else
                {
                    cout << "输入有误，请检查输入" << endl;
                    goto L2;
                }
            }

            // Modify file
            ofstream ofstr(fileBasePath, ios::out | ios::trunc);
            ofstr << endl;
            for (auto &item : ioMedicineList)
            {
                ofstr << item.number << endl
                      << item.name << endl
                      << item.species << endl
                      << item.manufacture << endl
                      << item.price << endl
                      << item.indate << endl
                      << item.attentionMatters << endl
                      << item.stock << endl;
            }

            ofstr.close();
            cout << "药品信息修改完成！" << endl;
        }

        else if (ops == '2')
        {
        // TODO: Delete!
        L3:
            cout << "请输入您想要删除药品的编号：";
            bool flag = true;
            string medicineNumber;
            cin >> medicineNumber;

            // Check whether the medicineNumber has been entered
            for (auto &item : ioMedicineList)
            {
                if (item.number == medicineNumber)
                {
                    flag = false;
                    // Check whether the medicine has not been dealt
                    ifstream ifstr(fileDealPath, ios::in);
                    string ss;
                    while (getline(ifstr, ss))
                    {
                        if (ss == item.number)
                        {
                            flag = true;
                            break;
                        }
                    }

                    break;
                }
            }

            // If flag is true, either the medicine has not been entered or has been dealt
            if (flag)
            {
                cout << "未找到药品信息或药品存在交易记录无法删除，请检查输入" << endl;
                goto L3;
            }
            else
            {
                auto itr = ioMedicineList.begin();
                while (itr->number != medicineNumber)
                {
                    ++itr;
                }
                // itr -> number = medicineNumber
                ioMedicineList.erase(itr);

                // Refresh the base file now!
                ofstream ofstr(fileBasePath, ios::out | ios::trunc);
                ofstr << endl;
                for (auto &item : ioMedicineList)
                {
                    ofstr << item.number << endl
                          << item.name << endl
                          << item.species << endl
                          << item.manufacture << endl
                          << item.price << endl
                          << item.indate << endl
                          << item.attentionMatters << endl
                          << item.stock;
                }

                ofstr.close();
                cout << "药品删除完成！" << endl;
            }
        }
        else if (ops == 'q')
        {
            cout << "* 正在更新修改" << endl;
            sleep(1);
            return false;
        }

        return true;
    }

    // Func.6 Output all messages
    void outputAllMessages()
    {
        // Output medicine basic messages
        cout << "---------- 药品基本信息 ----------" << endl
             << endl;
        for (auto &item : ioMedicineList)
        {
            cout << "药品编号：       " << item.number << endl;
            cout << "药品名称：       " << item.name << endl;
            cout << "药品种类：       " << item.species << endl;
            cout << "生产厂家：       " << item.manufacture << endl;
            cout << "药品价格：       " << item.price << endl;
            cout << "药品有效期：     " << item.indate << endl;
            cout << "药品注意事项：    " << item.attentionMatters << endl;
            cout << "药品库存量：      " << item.stock << endl
                 << endl;
        }

        cout << "---------- 药品交易信息 ----------" << endl
             << endl;
        ifstream ifstrs(fileDealPath, ios::in);
        string strs;
        cout << "药品名称    药品编号    交易单价  交易数量  交易金额    交易时间    交易人员    交易方式" << endl
             << endl;
        int i = 0;
        cout.precision(3);
        getline(ifstrs, strs);
        while (getline(ifstrs, strs))
        {
            ++i;
            cout << strs << "    ";
            if (i == 8)
            {
                cout << endl;
                i = 0;
            }
        }
    }
};

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
                cout << "@@@@@@@@ 欢 迎 使 用 @@@@@@@@" << endl
                     << endl;
                flag = false;
                sleep(1);
                system("clear");
                //system("cls");
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
                cout << "======= Admin =======" << endl;
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

    // Clarify a Medicine Class
    Medicine medicine; /* NOLINT */

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
                    cout << "======= Admin =======" << endl;
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
                    //system("cls");
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
                    while (medicine.logMedicineMessage())
                        ;
                    cout << "药品信息录入完成" << endl;
                    sleep(1);
                    cout << "谢谢使用！" << endl;
                    break;
                }
            }
            case '3':
            {
                {
                    while (medicine.intoStorageMedicine())
                        ;
                    cout << "药品入库完成" << endl;
                    sleep(1);
                    cout << "谢谢使用！" << endl;
                    break;
                }
            }
            case '4':
            {
                {
                    while (medicine.outStockMedicine())
                        ;
                    cout << "药品出库完成" << endl;
                    sleep(1);
                    cout << "谢谢使用！" << endl;
                    break;
                }
            }
            case '5':
                while (medicine.modify())
                    ;
                break;
            case '6':
            {
                medicine.outputAllMessages();
                sleep(3);
                cout << endl
                     << "输入\'q\'继续" << endl;
                char q;
            L4:
                cin.get(q);
                if (q == 'q')
                {
                    break;
                }
                else
                {
                    goto L4;
                }
            }
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