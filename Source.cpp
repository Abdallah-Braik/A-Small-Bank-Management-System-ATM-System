#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

struct stClient {
    string Name;
    string Phone;
    string AcountNumber;
    string PinCode;
   float AcountBalance;
};

struct stUser {
    string username;
    string password;
    short UserPermmesion;
    short ClientPermmesion;
};

vector<string> SplitString(string s1, string delim = "#//#")
{
    vector<string> vS1;
    short pos;
    string line;

    while ((pos = s1.find(delim)) != std::string::npos)
    {
        line = s1.substr(0, pos);
        vS1.push_back(line);
        s1.erase(0, pos + delim.length());
    }
    vS1.push_back(s1);
    return vS1;
}

stClient LineToClient(vector<string> parts)
{
    stClient client1;
    if (parts.size() >= 5) {
        client1.Name = parts[0];
        client1.Phone = parts[1];
        client1.AcountNumber = parts[2];
        client1.PinCode = parts[3];
        client1.AcountBalance = stof(parts[4]);
    }
    return client1;
}

stUser LineToUser(vector<string> parts)
{
    stUser User1;
    if (parts.size() >= 4) {
        User1.username = parts[0];
        User1.password = parts[1];
        User1.UserPermmesion = stoi(parts[2]);
        User1.ClientPermmesion = stoi(parts[3]);
    }
    return User1;
}

vector <stClient> SaveDataToStructClients(string filename = "data.txt")
{
    fstream file;
    string line;
    vector<stClient> clients;
    file.open(filename, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            clients.push_back(LineToClient(SplitString(line)));
        }
        file.close();
    }
    return clients;
}

vector <stUser> SaveDataToStructUsers(string filename = "users.txt")
{
    fstream file;
    string line;
    vector<stUser> users;
    file.open(filename, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            users.push_back(LineToUser(SplitString(line,"#//#")));
        }
        file.close();
    }
    return users;
}

void SaveClientsData(vector<stClient> &clients)
{
    fstream file;
    file.open("data.txt", ios::out);
    if (file.is_open())
    {

        for (stClient& client : clients)
        {
            file << client.Name << "#//#" << client.Phone << "#//#" << client.AcountNumber <<
                "#//#" << client.PinCode << "#//#" << client.AcountBalance << "#//#\n";
        }
        file.close();
    }
}

void SaveUsersData(vector<stUser>& users)
{
    fstream file;
    file.open("users.txt", ios::out);
    if (file.is_open())
    {

        for (stUser& user : users)
        {
            file << user.username << "#//#" << user.password << "#//#" << user.UserPermmesion <<"#//#" 
                << user.ClientPermmesion << endl;
        }
        file.close();
    }
}

short FindClient(vector <stClient>& client,  string msg="Enter the acount number : ")
{
    string acount;
    cout << msg;
    cin >> acount;
    for (int i = 0;i < client.size();i++)
    {
        if (client[i].AcountNumber == acount)
            return i;
    }
    return -2;

}

short FindUser(vector <stUser>& users, string msg = "Enter the user name : ")
{
    string UserName;
    cout << msg;
    cin >> UserName;
    for (int i = 0;i < users.size();i++)
    {
        if (users[i].username == UserName)
            return i;
    }
    return -1;

}

void Printclient(vector<stClient>& client, int index)
{
    if (index != -1)
    {
        cout << "Name : " << client[index].Name;
        cout << "\nPhone Number : " << client[index].Phone;
        cout << "\nAcount number : " << client[index].AcountNumber;
        cout << "\nPIN CODE : " << client[index].PinCode;
        cout << "\nBalance : " << client[index].AcountBalance<<endl;
    }
    else
        cout << "\nNo client was found with such an acount number.\n";
}

void ShowClients( vector<stClient>& clients)
{
    cout << " ========================================================================================\n";
    cout << "\t\t\tClients list\n";
    cout << " ========================================================================================\n";
    cout << left << setw(18) << "|Name" << "|"
        << setw(17) << "Phone Number" << "|"
        << setw(17) << "Account Number" << "|"
        << setw(17) << "PinCode" << "|"
        << "Account Balance\n" << "|";
    cout << "----------------------------------------------------------------------------------------\n";

    for ( stClient & c : clients)
    {
        cout <<  "|"<< setw(17) << c.Name << "|"
            << setw(17) << c.Phone << "|"
            << setw(17) << c.AcountNumber << "|"
            << setw(17) << c.PinCode << "|"
            << c.AcountBalance << "\n";
        cout << "|----------------------------------------------------------------------------------------\n";
    }
   
}

void ShowUser(vector<stUser> users, short i)
{
    cout << "\nUser name : " << users[i].username;
    cout << "\nPassword : " << users[i].password;
    cout << "\nUsers Access : " << users[i].UserPermmesion;
    cout << "\nClients Access : " << users[i].ClientPermmesion;
}

void AddNewClient(vector<stClient>& clients)
{
    cout << "ADD A NEW CLIENT : \n";
    stClient client;
    cout << "Your name : ";
    cin.ignore();
  getline(cin , client.Name);
    cout << "Your phone number : ";
    cin >> client.Phone;
    cout << "Acount number : ";
    cin >> client.AcountNumber;
    cout << "PIN CODE : ";
    cin >> client.PinCode;
    cout << "Your acount balance : ";
    cin >> client.AcountBalance;
    cout << "\nClient was added successfully.";

    clients.push_back(client);

    SaveClientsData(clients);

}

void DeleteClient(vector<stClient>& clients, int index)
{
    cout << "DELETE A CLIENT : \n";
    if (index == -2)
    {
        cout << "No client was found with such an acount number.";
        return;
    }
    Printclient(clients, index);
    char answer;
    cout << "Are you sure you want to delete this clietn ? (Y/N) : ";
    cin >> answer;

    if (tolower(answer) == 'y')
    {
            fstream file;
            file.open("data.txt", ios::out);
            if (file.is_open())
            {
                for (int i = 0;i < clients.size();i++)
                {
                    if (i == index)
                        continue;
                    else
                    {
                        file << clients[i].Name << "#//#" << clients[i].Phone << "#//#" << clients[i].AcountNumber <<
                            "#//#" << clients[i].PinCode << "#//#" << clients[i].AcountBalance << "#//#\n";
                    }
                }
                file.close();
                  cout << "Client was deleted successfully.";
            }
        
    }
}

void UpdateClient(vector<stClient>& clients, int index)
{
    cout << "UPDATE A CLIENT : \n";
    Printclient(clients, index);
    char answer;
    cout << "Are you sure you want to update this client ? (Y/N)";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        cout << "Name : ";
        cin.ignore();
        getline(cin, clients[index].Name);
        cout << "\nPhone Number : ";
        cin >> clients[index].Phone;
        cout << "\nAcount number : ";
        cin >> clients[index].AcountNumber;
        cout << "\nBalance : ";
        cin >> clients[index].AcountBalance;
        cout << "Client was updated successfully!\n";
    }
    SaveClientsData(clients);
    
}

void deposit(vector<stClient> &clients, int i)
{
    cout << "Deposit : \n\n";
    if (i == -2)
    {
        cout << "\nNo client was found with such an acount number.\n";
        return;
    }
    Printclient(clients, i);
    int amount = 0;
    cout << "Enter the amount you want to Deposit : ";
    cin >> amount;
    clients[i].AcountBalance = clients[i].AcountBalance + amount;
    SaveClientsData(clients);
}

void withdraw(vector<stClient>& clients, int i)
{
    cout << "With draw : \n\n";
    if (i == -2)
    {
        cout << "\nNo client was found with such an acount number.\n";
        return;
    }
    Printclient(clients, i);
    int amount = 0;
    cout << "Enter the amount you want to Withdraw : ";
    cin >> amount;
    if (clients[i].AcountBalance >= amount)
    {
        clients[i].AcountBalance = clients[i].AcountBalance - amount;
        SaveClientsData(clients);
    }
    else
        cout << "the amount is more than what you have ( "<< clients[i].AcountBalance<<" )"<< endl;

    }

void PrintAllBalances(vector<stClient>&clients)
{
    cout << " ========================================================================================\n";
    cout << "\t\t\tClients Balances\n";
    cout << " ========================================================================================\n";
    cout << left << setw(18) << "|Name" << "|"
        << setw(17) << "Account Number" << "|"
        << "Account Balance\n" << "|";
    cout << "----------------------------------------------------------------------------------------\n";

    float sum = 0;

    for (stClient& c : clients)
    {
        cout << "|" << setw(17) << c.Name << "|"
            << setw(17) << c.AcountNumber << "|"
            << c.AcountBalance << "\n";
        cout << "|----------------------------------------------------------------------------------------\n";
        sum += c.AcountBalance;
    }
    cout << setw(18) << "\n\nTotal Balances : " << sum;

}

void transactions(vector<stClient> &clients)
{
    cout << "TRANSACION MENU : \n\n";
    short choise;
    char answer = ' ';


    do {
    cout << "(1). Deposit.\n";
    cout<<"(2). Withdraw.\n";
    cout << "(3). Show all Balances.\n";
    cout << "(4). Return.\n";
    
 cout << "Your choise : ";
            cin >> choise;
            int f = 0;
        switch (choise)
        {
        case 1:
            system("cls");
            f = FindClient(clients);
            deposit(clients, f);
            break;
        case 2:
            system("cls");
            f = FindClient(clients);
            withdraw(clients, f);
            break;

        case 3:
            system("cls");
            PrintAllBalances(clients);
            break;
        case 4:
            return;
        };
        cout << "Do you want to make any more transitions ? (Y/N)";
        cin >> answer;
        system("cls");
    } while (tolower(answer) == 'y');

}

void UsersAccess(stUser &user)
{
    char answer;
    cout << "1.Do you want to allow the user to SHOW USERS LIST ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.UserPermmesion = (user.UserPermmesion | 1);
    cout << "\n2.Do you want to allow the user to ADD NEW USER ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.UserPermmesion = (user.UserPermmesion | 2);
    cout << "3.Do you want to allow the user to DELETE A USER ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.UserPermmesion = (user.UserPermmesion | 4);
    cout << "4.Do you want to allow the user to UPDATE A USER ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.UserPermmesion = (user.UserPermmesion | 8);

    cout << "5.Do you want to allow the user to FIND A USER ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.UserPermmesion = (user.UserPermmesion | 16);
}

void ClientsAccess(stUser& user)
{
    char answer;
    cout << "1.Do you want to allow the user to SHOW CLIENTS LIST ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.ClientPermmesion = (user.ClientPermmesion | 1);
    cout << "\n2.Do you want to allow the user to ADD A NEW CLIENT ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.ClientPermmesion = (user.ClientPermmesion | 2);
    cout << "3.Do you want to allow the user to DELETE A CLIENT ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.ClientPermmesion = (user.ClientPermmesion | 4);
    cout << "4.Do you want to allow the user to FIND A CLIENT ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.ClientPermmesion = (user.ClientPermmesion | 8);

    cout << "5.Do you want to allow the user to UPDATE A CLIENT ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.ClientPermmesion = (user.ClientPermmesion | 16);

    cout << "6.Do you want to allow the user for TRANSACTION MENU ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.ClientPermmesion = (user.ClientPermmesion | 32);

    cout << "7.Do you want to allow the user to MANAGE USERS ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.ClientPermmesion = (user.ClientPermmesion | 64);
}

void ShowUsers(vector<stUser>& user)
{
    cout << " ====================================================================\n";
    cout << "\t\t\tUsers list\n";
    cout << " ====================================================================\n\n\n";
    cout << left << setw(18) << "|User Name" << "|"
        << setw(17) << "PassWord" << "|"
        << setw(17) << "Users Access"<<setw(17) << "Clients Access";
    cout << "\n---------------------------------------------------------------------\n";

    for (stUser& c : user)
    {
        cout << "|" << setw(17) << c.username << "|"
            << setw(17) << c.password << "|"
            << setw(17) << c.UserPermmesion << "|" << setw(17) << c.ClientPermmesion << "|";
        cout << "\n|--------------------------------------------------------------------\n";
    }
}

void AddUser(vector<stUser> &users)
{
    stUser user;
    user.UserPermmesion = 0;
    char answer;
    cin.ignore();
    cout << "Enter user name : \n";
    getline(cin,user.username);
    cout << "Enter user password : \n";
    cin >> user.password;
    cout << "\nWould you like to give that user full access on Clients ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.ClientPermmesion = -1;
    else
        ClientsAccess(user);
   
    cout << "\nWould you like to give that user full access on Managing Users ? (Y/N)\n";
    cin >> answer;
    if (tolower(answer) == 'y')
        user.UserPermmesion = -1;
    else 
    UsersAccess(user);
    users.push_back(user);
    SaveUsersData(users);
    cout << "User was added successfully.\n";

}

void DeleteUser(vector<stUser>& users, short index)
{
    if (index == -1)
    {
        cout << "No user was found!\n";
        return;
    }
    if (users[index].username == "Abdallah")
    {
        cout << "\nThe Great Abdallah can't be deleted\n\n";
        return;
    }

    ShowUser(users, index);
      char answer=' ';

while (tolower(answer) != 'y' && tolower(answer) != 'n')
      {
        cout<< "Are you sure you want to delete this user ? (Y/N)\n";
        cin >> answer;
        } 

if (tolower(answer) == 'n')
return;

fstream file;
file.open("users.txt", ios::out);
if (file.is_open())
{
    for (short i=0;i<users.size();i++)
    {
        if (i == index)
            continue;
        else;
        file << users[i].username << "#//#" << users[i].password << "#//#" << users[i].UserPermmesion << endl;
    }
    file.close();
}
cout << "User was deleted successfully.\n";
}

void UpdateUser(vector<stUser> &users, short index)
{
    ShowUser(users, index);
    cout << "\n\nEnter the new password : ";
   cin>> users[index].password;
   UsersAccess(users[index]);
   cout << "User was updated successfully.\n";
   SaveUsersData(users);
}

bool UserSignIn(vector<stUser> &users,stUser &user)
{

    stUser user1;
    while (true)
    {    
        cout << "Enter your user name : \n";
        cin >> user1.username;
        cout << "\nEnter your Password : \n";
        cin >> user1.password;
        for (short i = 0;i < users.size();i++)
        {
            if (user1.username == users[i].username && user1.password == users[i].password)
            {
                user1.UserPermmesion = users[i].UserPermmesion;
                user1.ClientPermmesion = users[i].ClientPermmesion;
                user = user1;
                return true;
            }
        }
 system("cls");
        cout << "\nWrong User name/Password.\n\n";
    }
}

int ClientSignIn(vector<stClient> clients)
{
    stClient client;
    cout << "\nEnter your Acount number : ";
    cin >> client.AcountNumber;
    cout << "\nEnter you password : "; 
    cin >> client.PinCode;
    for (short i=0; i<clients.size(); i++)
    {
        if (clients[i].AcountNumber == client.AcountNumber && clients[i].PinCode == client.PinCode)
        {
            client = clients[i];
            return i;
        }
    }
    cout << "Invalid Acount number / password, try again : \n";
    ClientSignIn(clients);
}

void PrintClientBalance(vector<stClient> clients, int order)
{
    cout << "Your balance is : " << clients[order].AcountBalance << endl;
}

void QuickWithDraw(vector<stClient> &clients, int ClientOrder)
{
    short choise =0;
    cout << "Chose the amount you want to withdraw : \n";
    cout << "(1).100\n(2).200\n(3).300\n(4).500\n(5).600\n(6).800\n(7).900\n(8).1000\n";
    do {
        cout << "\nYour choise : ";
        cin >> choise;
    } while (choise > 8 || choise < 1);
    switch (choise)
    {
    case 1:
        if (clients[ClientOrder].AcountBalance >= 100)
            clients[ClientOrder].AcountBalance -= 100;
        else
            cout << "Out of order amount.";
        break;
    case 2:
        if (clients[ClientOrder].AcountBalance >= 200)
        clients[ClientOrder].AcountBalance -= 200;
        else
            cout << "Out of order amount.";
        break;

    case 3:
        if (clients[ClientOrder].AcountBalance >= 300)
        clients[ClientOrder].AcountBalance -= 300;
        else
            cout << "Out of order amount.";
        break;

    case 4 : 
        if (clients[ClientOrder].AcountBalance >= 500)
        clients[ClientOrder].AcountBalance -= 500;
        else
            cout << "Out of order amount.";
        break;

    case 5:
        if (clients[ClientOrder].AcountBalance >= 600)
        clients[ClientOrder].AcountBalance -= 600;
        else
            cout << "Out of order amount.";
        break;
    case 6:
        if (clients[ClientOrder].AcountBalance >= 800)
        clients[ClientOrder].AcountBalance -= 800;
        else
            cout << "Out of order amount.";
        break;

    case 7:
        if (clients[ClientOrder].AcountBalance >= 900)
        clients[ClientOrder].AcountBalance -= 900;
        else
            cout << "Out of order amount.";
        break;

    case 8:
        if (clients[ClientOrder].AcountBalance >= 1000)
        clients[ClientOrder].AcountBalance -= 1000;
        else
            cout << "Out of order amount.";
        break;
    }
    cout << "\n\nTransaction was done successfully. \n\nYour new balance is : " << clients[ClientOrder].AcountBalance;
    SaveClientsData(clients);
}

void WithDraw(vector <stClient>& clients, int clientorder)
{
    int amount = 0;
    do {
        cout << "\nYour acount balance is : " << clients[clientorder].AcountBalance;
        cout << "\nEnter the amount you want to withdraw : ";
        cin >> amount;
    } while (amount > clients[clientorder].AcountBalance);
    clients[clientorder].AcountBalance - amount;
    cout << "\nWithdraw was done successfully.\n your new Acount Balance is : " << clients[clientorder].AcountBalance;
    SaveClientsData(clients);
}

void Deposit(vector<stClient>& clients, int clientorder)
{
    int amount=0;
    cout << "\nYour acount balance is : " << clients[clientorder].AcountBalance;
    cout << "\nEnter the amount you want to withdraw : ";
    cin >> amount;
    clients[clientorder].AcountBalance += amount;
    SaveClientsData(clients);
}

void AccessDenied()
{
    system("cls");
    cout << "\n-------------------------------------------------------------\n";
    cout << "\t\tYou don't have the access to do this !\n\n\n\n";
    cout << "\n-------------------------------------------------------------\n";
}

void ATM(vector<stClient>&clients)
{  
    char again = 'y';
    system("cls");
    int order = ClientSignIn(clients);
do 
{ 
    short choise = 0;

cout << "(1).Show your balance.\n(2).Quick Withdraw\n(3).Withdraw\n(4).Deposit\n(5).Exit\n";
do { cin >> choise; } while (choise > 5 || choise < 1);

switch (choise)
{
case 1:
    system("cls");
    PrintClientBalance(clients, order);
    break;

case 2:
    system("cls");
    QuickWithDraw(clients, order);
    break;

case 3 :
    system("cls");
    WithDraw(clients, order);
    break;

case 4:
    system("cls");
    Deposit(clients, order);
    break;
case 5:
    return;
}
cout << "\n\nDo you want any more services ? (Y/N)\n";
cin >> again;
system("cls");
} while (tolower(again) == 'y');

}

void ManageUsers(vector<stUser> &users, stUser& user)
{
    
    char answer;
    
    do {
        system("cls");
        cout << "==========================================================\n";
        cout << "\t\tWelcome to Manage clients list\n";
        cout << "==========================================================\n";
        cout << "(1).Show users list.\n";
        cout << "(2).Add a new user.\n";
        cout << "(3).Delete a user.\n";
        cout << "(4).Update a user.\n";
        cout << "(5).Find a user.\n";
        cout << "(6).Back to main menu.\n";
        short choise = 0;
        do {
            cout << "\nYour choise (1:6) :\n";
            cin >> choise;
        } while (choise > 6 || choise < 1);

        switch (choise)
        {

            //If (X & Y) == X, then all bits set in X are also set in Y (Y includes X)
        case 1:
            system("cls");
            if (( user.UserPermmesion & 1) == 1 ||user.UserPermmesion==-1||user.UserPermmesion==31)

            {
                ShowUsers(users);
                break;
            }
            else
            {
                system("cls");
                AccessDenied();
                break;
            }

        case 2:
            if ((  user.UserPermmesion & 2) ==2 || user.UserPermmesion == -1 || user.UserPermmesion == 31)
            {
                system("cls");
                AddUser(users);
                break;
            }
            else
            {
                system("cls");
                AccessDenied();
                break;
            }

        case 3:
            if ( ( user.UserPermmesion & 4) == 4 || user.UserPermmesion == -1 || user.UserPermmesion == 31)
            {
                system("cls");
               DeleteUser(users, FindUser(users));  
                break;
            }
            else
            {
                system("cls");
                AccessDenied();
                break;
            }

        case 4:
            if ((user.UserPermmesion&8) == 8 || user.UserPermmesion == -1 || user.UserPermmesion == 31)
            {
                system("cls");
               UpdateUser(users, FindUser(users));  
                break;
            }
            else
            {
                system("cls");
                AccessDenied();
                break;
            }
  
        case 5:
            if ( (user.UserPermmesion & 16 )== 16 || user.UserPermmesion == -1 || user.UserPermmesion == 31)
            {
                system("cls");
              ShowUser(users, FindUser(users));    
                break;
            }
            else
            {
                system("cls");
                AccessDenied();
                break;
            }

        case 6:
            system("cls");
            return;
        }
        do {
            cout << "\nDo you want any more users services ? (Y/N)  ";
            cin >> answer;
        } while (tolower(answer) != 'y' && tolower(answer) != 'n');

      } while (tolower(answer) == 'y');

    

}

void Bank(vector <stClient> &clients,vector <stUser> &users)
{
    short choise=0;
    char answer = ' ';
    stUser user;
    if (UserSignIn(users, user))
    {
        cout << "WELCOME TO OUR BANK!!\n";
        do
        {
            system("cls");
            cout << "(1). Show all clients.\n";
            cout << "(2). Add a new client.\n";
            cout << "(3). Delete a client.\n";
            cout << "(4). Find a client.\n";
            cout << "(5). Update a client.\n";
            cout << "(6). Transactions.\n";
            cout << "(7). Manage users\n";
            cout << "(8). Log out.\n\nYour choise : ";
            cin >> choise;

            switch (choise)
            {
            case 1:
                if((user.ClientPermmesion & 1)==1 || user.ClientPermmesion == -1)
                { 
                system("cls");
                ShowClients(clients);
                }
                else
                {
                    AccessDenied();
                }
                break;

            case 2:
                if ((user.ClientPermmesion & 2) == 2 || user.ClientPermmesion == -1)
                {
                    system("cls");
                    AddNewClient(clients);
                }
                else
                    AccessDenied();
                break;

            case 3:
                if ((user.ClientPermmesion & 4) == 4 || user.ClientPermmesion == -1)
                {
                    system("cls");
                    DeleteClient(clients, FindClient(clients, "Enter the account number : "));
                }
                else
                    AccessDenied();
                break;

            case 4:
                if ((user.ClientPermmesion & 8) == 8 || user.ClientPermmesion == -1)
                {
                    system("cls");
                    cout << "FIND A CLIENT : \n";
                    Printclient(clients, FindClient(clients, "Enter the account number : "));
                }
                else
                    AccessDenied();
                break;

            case 5:  if ((user.ClientPermmesion & 16) == 16 || user.ClientPermmesion == -1)
            {
                system("cls");
                UpdateClient(clients, FindClient(clients, "Enter the account number : "));
            }
                  else
                AccessDenied();
                break;

            case 6:
                if ((user.ClientPermmesion & 32) == 32 || user.ClientPermmesion == -1)
                {
                    system("cls");
                    transactions(clients);
                }
                else
                    AccessDenied();
                break;

            case 7:
                if ((user.ClientPermmesion & 64) == 64 || user.ClientPermmesion==-1 )
                {
                    system("cls");
                    ManageUsers(users, user);
                }
                else
                    AccessDenied();
                break;

            case 8:
                return;
            }

            cout << "\nDo you want any more services ? (Y/N)  ";
            cin >> answer;
        } while (tolower(answer) == 'y');
    }

}

int main()
{
    vector<stClient> clients = SaveDataToStructClients(); 
     vector <stUser> users= SaveDataToStructUsers();
     short choise = 0;
     do {
         cout << "Client : (1)\nUser : (2)\nEnter : ";
         cin >> choise;
     } while (choise != 1 && choise != 2);

     if(choise==1)
     ATM(clients);

     else
    Bank(clients,users);
 
   return 0;
}