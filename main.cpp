#include <iostream>
#include <cstdio>
#include <list>
#include <unistd.h>
#include <fstream>
#include <utility>
#include <ctime>
using namespace std;

class Medicine
{
private:
    struct medicineMessage
    {
        string number;
        string name;
        string species;
        string manufacture;
        int price;
        string indate;
        string attentionMatters;
        int stock;

        explicit medicineMessage(int prc = 0, int stk = 0) : price(prc), stock(stk) {}
    };

    list<medicineMessage> medicineList;
    string fileBasePath = "./medicine_base.dat";

public:
    void logMedicineMessageWrite()
    {
        // Open by emptying the source file
        ofstream ofstr(fileBasePath, ios_base::out | ios_base::trunc);
        // Fail to open file
        if (!ofstr.is_open())
        {
            cout << "文件打开失败" << endl;
            return;
        }
        // File opened successfully
        // Copy message from List to the file (Write)
        for (const auto &item : medicineList)
        {
            ofstr << endl
                  << item.number
                  << item.name
                  << item.species
                  << item.manufacture
                  << item.price
                  << item.indate
                  << item.attentionMatters
                  << item.stock;
        }
        // Close file
        ofstr.close();
    }

    // Put file content into List (Read)
    void logMedicineMessageRead()
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
        // Command "clear" in Linux / OSX
        // On Windows can use:
        // system("cls");

        ifstr.open(fileBasePath, ios_base::in);

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
            msg.price = stoi(ch);
            ifstr.getline(ch, sizeof(ch));
            msg.indate = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.attentionMatters = ch;
            ifstr.getline(ch, sizeof(ch));
            msg.stock = stoi(ch);

            medicineList.push_back(msg);
        }
    }

    bool listSearch(const string &Name, const string &Num)
    {
        for (const auto &item : medicineList)
        {
            if (item.name == Name && item.number == Num)
            {
                return true;
            }
        }
        return false;
    }
    // Match the "price" of medicine
    int perPrice(const string &medicineName)
    {
        int perprice;
        for (const auto &item : medicineList)
        {
            if (item.name == medicineName)
            {
                perprice = item.price;
            }
        }
        return perprice;
    }

    // TODO:删改的函数接口，注意变更后的刷新
    friend void modify();

private:
    string fileDealPath = "./medicine_deal.dat";
    struct intoStorageMessage
    {
        string medicineName;
        string medicineNum;
        double intoStoragePerPrice = 0;
        int intoStorageNum = 0;
        double intoStoragePrice = 0; // intoStoragePrice = intoStoragePerPrice * intoStorageNum
        string intoStorageTime;
        string intoStoragePerson;
        string intoStorageType;
    };
    list<intoStorageMessage> intoStorageList;

public:
    void intoStorageMedicineMessageWrite()
    {
        ofstream ofstr(fileDealPath, ios_base::out | ios_base::trunc);
        if (!ofstr.is_open())
        {
            cout << "文件打开失败" << endl;
            return;
        }

        for (const auto &item : intoStorageList)
        {
            ofstr << endl
                  << item.medicineName
                  << item.medicineNum
                  << item.intoStoragePerPrice
                  << item.intoStorageNum
                  << item.intoStoragePrice
                  << item.intoStorageTime
                  << item.intoStoragePerson
                  << item.intoStorageType;
        }
        // Close file
        ofstr.close();
    }

    void intoStorage()
    {
        string medicine_Name;
        string medicine_Num;
        int intoStorage_Num;
        string intoStorage_Person;

        cout << "请输入「入库药品信息」：" << endl;
        cout << "药品名称：";
        cin >> medicine_Name;
        cout << endl;
        cout << "药品编号：";
        cin >> medicine_Num;
        cout << endl;

        if (!listSearch(medicine_Name, medicine_Num))
        {
            cout << "无此药品信息！" << endl;
        }
        else
        {
            cout << "请输入药品入库数量：";
            cin >> intoStorage_Num;
            cout << endl;
            cout << "请输入入库人员姓名：";
            cin >> intoStorage_Person;
            cout << endl;
            // 这里medicine_Name是对应药品名称，medicine_Num对应了药品编号，intoStorage_Num代表入库数量
            struct intoStorageMessage tmp;
            tmp.medicineName = medicine_Name;
            tmp.medicineNum = medicine_Num;
            tmp.intoStoragePerPrice = perPrice(medicine_Name);
            tmp.intoStorageNum = intoStorage_Num;
            tmp.intoStoragePrice = perPrice(medicine_Name) * intoStorage_Num;
            time_t now = time(nullptr);
            string dt = ctime(&now);
            tmp.intoStorageTime = dt;
            tmp.intoStoragePerson = intoStorage_Person;
            tmp.intoStorageType = "采购";

            intoStorageList.push_back(tmp);

            // Refresh the base stock
            for (auto item : medicineList)
            {
                if (item.name == medicine_Name)
                {
                    item.stock += intoStorage_Num;
                    logMedicineMessageWrite();
                    break;
                }
            }
        }
    }

    // TODO:这里需要获取单价库存等药品信息，然后分别更新维护两个文件

private:
    struct outStockMessage
    {
        string medicineName;
        string medicineNum;
        double outStockPerPrice = 0;
        int outStockNum = 0;
        double outStockPrice = 0; // outStockPrice = outStockPerPrice * outStockNum
        string outStockTime;
        string outStockPerson;
        string outStockType;
    };
    list<outStockMessage> outStockList;

public:
    void outStockMedicineMessageWrite()
    {
        ofstream ofstr(fileDealPath, ios_base::out | ios_base::trunc);
        if (!ofstr.is_open())
        {
            cout << "文件打开失败" << endl;
            return;
        }

        for (const auto &item : outStockList)
        {
            ofstr << endl
                  << item.medicineName
                  << item.medicineNum
                  << item.outStockPerPrice
                  << item.outStockNum
                  << item.outStockPrice
                  << item.outStockTime
                  << item.outStockPerson
                  << item.outStockType;
        }
        // Close file
        ofstr.close();
    }

    void outStock()
    {
        string medicine_Name;
        string medicine_Num;
        // 这里medicine_Name是对应药品名称，medicine_Num对应了药品编号，outStock_Num代表入库数量
        int outStock_Num;
        string outStock_Person;

        cout << "请输入「购买药品信息」：" << endl;
        cout << "药品名称：";
        cin >> medicine_Name;
        cout << endl;
        cout << "药品编号：";
        cin >> medicine_Num;
        cout << endl;

        if (!listSearch(medicine_Name, medicine_Num))
        {
            cout << "无此药品信息" << endl;
            // TODO:看一下这里是否有必要return
            return;
        }
        else
        {
            cout << "请输入想要购买的数量：";
            cin >> outStock_Num;
            cout << endl;

            // Compare outStockNumber with baseStockNumber
            for (const auto &item : medicineList)
            {
                if (item.name == medicine_Name && item.number == medicine_Num)
                {
                    if (item.stock >= outStock_Num)
                    {
                        break;
                    }
                    else
                    {
                        cout << "库存不足，请重新输入信息" << endl;
                        // TODO:看一下有无比return更好的解决方法
                        return;
                    }
                }
            }

            cout << "请输入购买者姓名：";
            cin >> outStock_Person;
            cout << endl;

            struct outStockMessage tmp;
            tmp.medicineName = medicine_Name;
            tmp.medicineNum = medicine_Num;
            tmp.outStockPerPrice = perPrice(medicine_Name);
            tmp.outStockNum = outStock_Num;
            tmp.outStockPrice = perPrice(medicine_Name) * outStock_Num;
            time_t now = time(nullptr);
            string dt = ctime(&now);
            tmp.outStockTime = dt;
            tmp.outStockPerson = outStock_Person;
            tmp.outStockType = "销售";

            outStockList.push_back(tmp);

            // Refresh the base stock
            for (auto item : medicineList)
            {
                if (item.name == medicine_Name && item.number == medicine_Num)
                {
                    item.stock -= outStock_Num;
                    logMedicineMessageWrite();
                    break;
                }
            }
        }
    }
};

// Modify or delete the basic information of medicine
void modify()
{
}

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

// Set and reset the password
string password;
bool pwd = false;
bool flag = true;
const static string root = "20105050110";
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
             << "##### 按 l 以输入密码登录系统 ##### 按 r 以重设密码 #####" << endl;
        char ch;
        ch = getchar();
        ch = getchar();
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
                cout << "@@@ 欢迎使用 @@@" << endl
                     << endl;
                flag = false;
                sleep(1);
                system("clear");
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
                cout << "===== Admin =====" << endl;
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
    Medicine medicine;
    Hint();

    if (!pwd)
    {
        cout << "请先选1设置密码：";
        char ch;
        ch = getchar();
        getchar();
        while (ch != '1')
        {
            cout << "请先选1设置密码！";
            ch = getchar();
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
        ch = getchar();
        getchar();
        while (ch != '1')
        {
            cout << "请先选1登录系统！";
            ch = getchar();
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
            getchar();
            ch = getchar();
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
                    cout << "===== Admin =====" << endl;
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
                }
                else
                {
                    cout << "root密码错误，若想重设密码请联系管理员" << endl;
                    goto L3;
                }
                break;
            }
            case '2':
                medicine.logMedicineMessageRead();
                break;
            case '3':
                medicine.intoStorage();
                break;
            case '4':
                medicine.outStock();
                break;
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