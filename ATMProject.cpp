#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

const string FileName = "Client2.txt";

enum enTransection { eQuickWithdraw = 1, eWithdraw = 2, eDeposit = 3, eTotalBalances = 4, eMainMenue = 5 };
enum enQuickWithdraw { Twenty=1, Fifty=2, OneHunderd=3, TwoHundred=4, FourHundred=5, SixHundred=6, EightHundred=7, Thousand=8, Exit=9 };

void BackToMainMenue();

string ReadString(string Message)
{
    string S1;
    cout << Message;
    getline(cin >> ws, S1);
    return S1;
}

short GetAPositiveNumber(string Message)
{
    short Number;
    do 
    {
        cout << Message;
        cin >> Number;
    } while (Number < 0);
    
    return Number;
}

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool MarkToChange = false;
};

stClient CurrentClient;

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{
    string LineData;
    LineData += Client.AccountNumber + Seperator;
    LineData += Client.PinCode + Seperator;
    LineData += Client.Name + Seperator;
    LineData += Client.Phone + Seperator;
    LineData += to_string(Client.Balance);

    return LineData;
}

vector <string> SplitString(string  DataLine, string delim = "#//#")
{
    vector <string> vString;
    short pos = 0;
    string sWord;

    while ((pos = DataLine.find(delim)) != std::string::npos)
    {
        sWord = DataLine.substr(0, pos);

        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        DataLine.erase(0, pos + delim.length());
    }
    if (DataLine != "")
    {
        vString.push_back(DataLine);
    }

    return vString;
}

stClient ConvertLineToRecord(string DataLine)
{
    vector <string> vString = SplitString(DataLine);

    stClient Client;
    Client.AccountNumber = vString.at(0);
    Client.PinCode = vString.at(1);
    Client.Name = vString.at(2);
    Client.Phone = vString.at(3);
    Client.Balance = stod(vString.at(4));

    return Client;
}

vector <stClient> LoadDataFromFile(string ClientstFileName)
{
    vector <stClient> vClient;
    stClient Client;

    fstream MyFile;

    MyFile.open(ClientstFileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClient.push_back(Client);
        }

    }

    MyFile.close();

    return vClient;
}

bool FindClientByAccountNumber(vector <stClient> &vClient, stClient& Client, string AccountNumber)
{
    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

vector <stClient> SaveDataToFile(vector <stClient> vClient, string ClientstFileName)
{
    fstream MyFile;
    MyFile.open(ClientstFileName, ios::out);

    if (MyFile.is_open())
    {
        string Line;
        for (stClient& Client : vClient)
        {
            Line = ConvertRecordToLine(Client);
            MyFile << Line << endl;
        }

    }
    MyFile.close();

    return vClient;
}

void ShowTransactionScreen();
void BackToTransectionMenue()
{
    cout << "\n\nPress any key to go back to Transection Menue...";
    system("pause>0");
    ShowTransactionScreen();
}

void ClinetBalanceScreen()
{
    system("cls");
    cout << "\n============================================================\n";
    cout << "\t\t      Check Balance Screen";
    cout << "\n============================================================\n";
}

void ShowClientsBalance(string Message = "Your Balance is : ")
{
    vector <stClient> vClient = LoadDataFromFile(FileName);
    for(stClient &C : vClient)
    {
        if(C.AccountNumber == CurrentClient.AccountNumber)
        {
            cout << Message << C.Balance << endl;
            break;
        }
    }

}

void ClientBalance()
{
    ClinetBalanceScreen();
    ShowClientsBalance();
}

void Deposit()
{

    cout << "\n============================================================\n";
    cout << "\t\t      Deposit Screen";
    cout << "\n============================================================\n";


    ShowClientsBalance();
    vector <stClient> vClient = LoadDataFromFile(FileName);

    char Answer = 'N';

    for (stClient& C : vClient)
    {

        if (C.AccountNumber == CurrentClient.AccountNumber)
        {
            
            int deposit = GetAPositiveNumber("\n\nPlease Enter Deposit Amount: ");
            
            cout << "\nAre you sure you want perform this transection [Y/N] ? ";
            cin >> Answer;

            if (toupper(Answer) == 'Y')
            {
                C.Balance += deposit;
            
                SaveDataToFile(vClient, FileName);
                vClient = LoadDataFromFile(FileName);
            }
            break;
        }
    }
    
}

void NormalWithdrawScreen()
{    
    cout << "\n============================================================\n";
    cout << "\t\t      Normal Withdraw Screen";
    cout << "\n============================================================\n";
}

int ShowQuickWithdrawScreen();
void GoBackToQuichWithdrawScreen()
{
    cout << "Press to any key to go back transection menue...";
    system("puase>0");
    ShowQuickWithdrawScreen();
}

short PerformQuickWithdraw(enQuickWithdraw Choice)
{
    switch(Choice)
    {
        case enQuickWithdraw::Twenty:
            return 20;
        case enQuickWithdraw::Fifty:
            return 50;
        case enQuickWithdraw::OneHunderd:
            return 100;
        case enQuickWithdraw::TwoHundred:
            return 200;
        case enQuickWithdraw::FourHundred:
            return 400;
        case enQuickWithdraw::SixHundred:
            return 600;
        case enQuickWithdraw::EightHundred:
            return 800;
        case enQuickWithdraw::Thousand:
            return 1000;
        case enQuickWithdraw::Exit:
            return 0;
    }
    return 0;
}

enQuickWithdraw GetQuickWithdrawChioces()
{
    short Choice;
    cout << "Enter what to withdraw [1 - 8] : ";
    cin >> Choice;
    return enQuickWithdraw(Choice);    
}

int ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "\n============================================================\n";
    cout << "\t\t      Withdraw Menue Screen";
    cout << "\n============================================================\n";
    cout << "\t" << "[1] 20  \t [2] 50" << endl;
    cout << "\t" << "[3] 100 \t [4] 200" << endl;
    cout << "\t" << "[5] 400 \t [6] 600" << endl;
    cout << "\t" << "[7] 800 \t [8] 1000" << endl;
    cout << "\t" << "[9] Exit" << endl;
    cout << "\n============================================================\n";
    ShowClientsBalance();
    return PerformQuickWithdraw(GetQuickWithdrawChioces());
}

void QuickWithdraw()
{
    vector <stClient> vClient = LoadDataFromFile(FileName);

    for (stClient& C : vClient)
    {

        if(C.AccountNumber == CurrentClient.AccountNumber)
        {
            short withdraw = ShowQuickWithdrawScreen();

        if(withdraw==0)
        {
            ShowTransactionScreen();
        }

        char Answer='N';
            
            while (withdraw > C.Balance)
            {
                cout << "\nAmount Exceeds The Balance, Make another choice  \n";
                cout << "Press Any Key To continue... ";
                system("pause>0");
                short withdraw = ShowQuickWithdrawScreen();
            }

            cout << "\nAre you sure you want perform this transection [Y/N] ? ";
            cin >> Answer;

            if (toupper(Answer) == 'Y')
            {
                C.Balance -= withdraw;

                SaveDataToFile(vClient, FileName);
                vClient = LoadDataFromFile(FileName);
            };
            break;
        }
    }
}

void NormalWithdraw()
{
    NormalWithdrawScreen();

    vector <stClient> vClient = LoadDataFromFile(FileName);

    ShowClientsBalance();

    for (stClient& C : vClient)
    {   
        int withdraw;
        
        char Answer='N';

        if (C.AccountNumber == CurrentClient.AccountNumber)
        {
            withdraw = GetAPositiveNumber("\n\nEnter amount multiple of 5's : ");
            while ( withdraw > C.Balance || withdraw % 5!=0 || withdraw==0)
            {
                if(withdraw > C.Balance)
                {
                    cout << "\nAmount Exceeds The Balance, Make another choice  \n";
                    cout << "Press Any Key To continue... ";
                    system("pause>0");
                    system("cls");
                    NormalWithdrawScreen();
                    ShowClientsBalance();
                    withdraw = GetAPositiveNumber("\n\nEnter amount multiple of 5's : ");
                }
                else if(withdraw % 5!=0 || withdraw==0)
                {
                    system("cls");
                    NormalWithdrawScreen();
                    ShowClientsBalance();
                    withdraw = GetAPositiveNumber("\n\nEnter amount multiple of 5's : ");
                }
                    
            }

            cout << "\nAre you sure you want perform this transection [Y/N] ? ";
            cin >> Answer;

            if (toupper(Answer) == 'Y')
            {
                C.Balance -= withdraw;

                SaveDataToFile(vClient, FileName);
                vClient = LoadDataFromFile(FileName);
            };

            cout << "Done Successfully. New balance is : "; ShowClientsBalance(" ");
            break;
        }
    }
}

enTransection GetTransectionChoices()
{
    short Choice;
    do
    {
        cout << "\nChoose what do you want to do [1 to 8] : ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 5);
    return enTransection(Choice);
}

void Login();
void PerFromTransection(enTransection Choice)
{
    switch (Choice)
    {
        case enTransection::eQuickWithdraw:
        {
            system("cls");
            QuickWithdraw();
            BackToTransectionMenue();
            break;
        }
        case enTransection::eWithdraw:
        {
            system("cls");
            NormalWithdraw();
            BackToTransectionMenue();
            break;
        }
        case enTransection::eDeposit:
        {
            system("cls");
            Deposit();
            BackToTransectionMenue();
            break;
        }
        case enTransection::eTotalBalances:
        {
            system("cls");
            ShowClientsBalance();
            BackToTransectionMenue();
            break;

        }
        case enTransection::eMainMenue:
        {
            system("cls");
            Login();
            break;

        }
    }
}

void ShowTransactionScreen()
{
    system("cls");
    cout << "\n============================================================\n";
    cout << "\t\t      ATM Main Menue Screen";
    cout << "\n============================================================\n";
    cout << "\t" << "[1] Quick Withdraw." << endl;
    cout << "\t" << "[2] Withdraw." << endl;
    cout << "\t" << "[3] Deposit." << endl;
    cout << "\t" << "[4] Check Balance." << endl;
    cout << "\t" << "[5] Logout." << endl;
    cout << "\n============================================================\n";
    PerFromTransection(GetTransectionChoices());
}

bool CheckToAccountNumberAndPinCode(string AccountNumber, string PinCode, stClient &CurrentClient)
{
    vector <stClient> vClinet = LoadDataFromFile(FileName);
    for(stClient &C : vClinet)
    {
        if(C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            CurrentClient = C;
            return true;
        }
    }
    return false;
}

void EnterToATMSystem()
{
    string AccountNumber, PinCode;
    stClient Client;
    AccountNumber = ReadString("Enter Account Number: ");
    PinCode = ReadString("Enter Pine Code: ");

    while(!CheckToAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
    {
        cout << "Invlaid Username/PinCode!\n";
        system("pause>0");
        Login();
        
        AccountNumber = ReadString("Enter Account Number: ");
        PinCode = ReadString("Enter Pine Code: ");

    }
    system("cls");

}
void Login()
{

    system("cls");
    cout << "\n============================================================\n";
    cout << "\t\t      Login Screen";
    cout << "\n============================================================\n";
    EnterToATMSystem();
    ShowTransactionScreen();


}

int main()
{
    Login();
    system("pause>0");
}
