//********************************************************************************* */
//*                                                                                 */
//*                           BANK SYSTEM                                           */
//*                                                                                 */
//********************************************************************************* */



#include <iostream>
#include <fstream> // file handling
#include <conio.h> // For _getch()
#include <string>
#include<windows.h>
using namespace std;



//********************************************************************************* */
//*                                                                                 */
//*                           Files file handling file                              */
//*                                                                                 */
//********************************************************************************* */


const string FILE_ACCOUNTS = "accounts.txt";
const string FILE_TRANSACTIONS = "transactions.txt";

const string USER_PASSWORD = "1234";
const string ADMIN_PASSWORD = "6221";



//********************************************************************************* */
//*                                                                                 */
//*                           Making struct for node                                */
//*                                                                                 */
//********************************************************************************* */


struct trans
{
    string detail;
    trans *next;
};

struct node
{
    int AccNum;
    string Aname;
    double bal;
    trans *transaction;
    node *next;
};



//********************************************************************************* */
//*                                                                                 */
//*                                BACK Class                                       */
//*                                                                                 */
//********************************************************************************* */



class Bank
{
private:
    node *head;
    int num;

    void add(trans *&head, const string &detail)
    {
        trans *Tptr = new trans;
        Tptr->detail = detail;
        Tptr->next = head;
        head = Tptr;
    }


//********************************************************************************* */
//*                                                                                 */
//*                           FUNCTIONS FOR File Handling                           */
//*                                                                                 */
//********************************************************************************* */



    void saveAccountToFile(const node *account)
    {
        ofstream file(FILE_ACCOUNTS, ios::app);
        if (file.is_open())
        {
            file << account->AccNum << " " << account->Aname << " " << account->bal << "\n";
            file.close();
        }
    }




    void saveTransactionToFile(const trans *transaction)
    {
        ofstream file(FILE_TRANSACTIONS, ios::app);
        if (file.is_open())
        {
            while (transaction)
            {
                file << transaction->detail << "\n";
                transaction = transaction->next;
            }
            file.close();
        }
    }




    void loadAccountsFromFile()
    {
        ifstream file(FILE_ACCOUNTS);
        if (file.is_open())
        {
            string name;
            double balance;
            while (file >> num >> name >> balance)
            {
                node *ptr = new node;
                ptr->Aname = name;
                ptr->AccNum = num;
                ptr->bal = balance;
                ptr->transaction = NULL;
                ptr->next = head;
                head = ptr;
            }
            file.close();
        }
    }



public:
    Bank()
    {
        head = NULL;
        num = 0;
        loadAccountsFromFile();
    }



//********************************************************************************* */
//*                                                                                 */
//*                           FUNCTION FOR NEW MAKING ACCOUNT                       */
//*                                                                                 */
//********************************************************************************* */


    void newAcc(string name, double deposite)
    {
        // system("cls");
        if (deposite < 0)
            return;
        node *ptr = new node;
        ptr->Aname = name;
        ptr->AccNum = num + 1;
        ptr->bal = deposite;
        ptr->transaction = NULL;
        ptr->next = NULL;
        add(ptr->transaction, "\t\t----->  Account created with deposit = $" + to_string(deposite));
        ptr->next = head;
        head = ptr;
        num++;
        saveAccountToFile(ptr);
        saveTransactionToFile(ptr->transaction);
        cout << "\t\t----->  Account created successfully. Account Number = " << ptr->AccNum << endl;
        // system("cls");
    }



//********************************************************************************* */
//*                                                                                 */
//*                       DISPLAY ACCOUNT INFO WITH ACCOUNT NUMBER                 */
//*                                                                                 */
//********************************************************************************* */



    void display(int accNumber)
    {
        // system("cls");
        node *curent = head;
        while (curent)
        {
            if (curent->AccNum == accNumber)
            {
                cout << "\t\t----->  Account Holder = " << curent->Aname << endl;
                cout << "\t\t----->  Account Number = " << curent->AccNum << endl;
                cout << "\t\t----->  Balance = $" << curent->bal << endl;
                return;
            }
            curent = curent->next;
        }
        cout << "\t\t----->  Account not found" << endl;
        // system("cls");
    }



//********************************************************************************* */
//*                                                                                 */
//*                           DEPOSITE Amount in ACCOUNT                            */
//*                                                                                 */
//********************************************************************************* */



    void deposit(int accNumber, double amount)
    {
        // system("cls");
        node *curent = head;
        while (curent)
        {
            if (curent->AccNum == accNumber)
            {
                if (amount > 0)
                {
                    curent->bal += amount;
                    add(curent->transaction, "Deposited = $" + to_string(amount));
                    saveTransactionToFile(curent->transaction);
                    cout << "\t\t----->  Deposit successful. Updated Balance = $" << curent->bal << endl;
                }
                else
                {
                    cout << "\t\t----->  Invalid amount" << endl;
                }
                return;
            }
            curent = curent->next;
        }
        cout << "\t\t----->  Account not found" << endl;
        // system("cls");
    }




//********************************************************************************* */
//*                                                                                 */
//*                           Withdraw Amount in ACCOUNT                            */
//*                                                                                 */
//********************************************************************************* */



    void withdraw(int accNumber, double amount)
    {
        // system("cls");
        node *curent = head;
        while (curent)
        {
            if (curent->AccNum == accNumber)
            {
                if (amount > 0 && curent->bal >= amount)
                {
                    curent->bal -= amount;
                    add(curent->transaction, "Withdrawn = $" + to_string(amount));
                    saveTransactionToFile(curent->transaction);
                    cout << "\t\t----->  Withdrawal successful. Remaining Balance = $" << curent->bal << endl;
                }
                else
                {
                    cout << "\t\t----->  Insufficient funds or invalid amount" << endl;
                }
                return;
            }
            curent = curent->next;
        }
        cout << "\t\t----->  Account not found" << endl;
        // system("cls");
    }


//********************************************************************************* */
//*                                                                                 */
//*                          Search ACCOUNT with ACCOUNT Number                     */
//*                                                                                 */
//********************************************************************************* */



    void searchAcc(string name)
    {
        // system("cls");
        node *curent = head;
        while (curent)
        {
            if (curent->Aname == name)
            {
                cout << "\t\t----->  Account Found...." << endl;
                cout << "\t\t----->  Account Holder = " << curent->Aname << endl;
                cout << "\t\t----->  Account Number = " << curent->AccNum << endl;
                cout << "\t\t----->  Balance = $" << curent->bal << endl;
                return;
            }
            curent = curent->next;
        }
        cout << "\t\t----->  No account found for the name: " << name << endl;
        // system("cls");
    }



//********************************************************************************* */
//*                                                                                 */
//*                           DELETE ACCOUNT with ACCOUNT Number                    */
//*                                                                                 */
//********************************************************************************* */


    void delAcc(int accNumber)
    {
        // system("cls");
        node *curent = head;
        node *prev = NULL;
        while (curent)
        {
            if (curent->AccNum == accNumber)
            {
                if (prev)
                {
                    prev->next = curent->next;
                }
                else
                {
                    head = curent->next;
                }
                trans *Ttemp = curent->transaction;
                while (Ttemp)
                {
                    trans *del1 = Ttemp;
                    Ttemp = Ttemp->next;
                    delete del1;
                }
                cout << "\t\t----->  Account " << accNumber << " deleted successfully." << endl;
                delete curent;
                return;
            }
            prev = curent;
            curent = curent->next;
        }
        cout << "\t\t----->  Account not found" << endl;
        // system("cls");
    }



//********************************************************************************* */
//*                                                                                 */
//*                           Display Accounts                                      */
//*                                                                                 */
//********************************************************************************* */



    void displayAcc()
    {
        
        // system("cls");
        node *curent = head;
        if (curent == NULL)
        {
            cout << "\t\t----->  No accounts to display." << endl;
            return;
        }
        while (curent)
        {
            cout << "\t\t----->  Account Holder = " << curent->Aname << endl;
            cout << "\t\t----->  Account Number = " << curent->AccNum << endl;
            cout << "\t\t----->  Balance = $" << curent->bal << endl;
            cout << "-----------------------------" << endl;
            curent = curent->next; // Move to the next account
        }
        // system("cls");
    }


//********************************************************************************* */
//*                                                                                 */
//*                           Update ACCOUNT with ACCOUNT Number                    */
//*                                                                                 */
//********************************************************************************* */


    void updateAcc(int accNumber, string newName)
    {
        
        // system("cls");
        node *curent = head;
        while (curent)
        {
            if (curent->AccNum == accNumber)
            {
                curent->Aname = newName;
                cout << "\t\t----->  Account details updated successfully." << endl;
                return;
            }
            curent = curent->next;
        }
        cout << "\t\t----->  Account not found" << endl;
        // system("cls");
    }


//********************************************************************************* */
//*                                                                                 */
//*                           Display Transaction with ACCOUNT Number               */
//*                                                                                 */
//********************************************************************************* */


    void dispTrans(int accNumber)
    {
        // system("cls");
        node *curent = head;
        while (curent)
        {
            if (curent->AccNum == accNumber)
            {
                cout << "\t\t----->  Transaction History for Account " << accNumber << ":" << endl;
                trans *Ttemp = curent->transaction;
                while (Ttemp)
                {
                    cout << "- " << Ttemp->detail << endl;
                    Ttemp = Ttemp->next;
                }
                return;
            }
            curent = curent->next;
        }
        cout << "\t\t----->  Account not found" << endl;
        // system("cls");
        
    }



    ~Bank()
    {
        while (head)
        {
            node *temp = head;
            head = head->next;
            trans *Ttemp = temp->transaction;
            while (Ttemp)
            {
                trans *del1 = Ttemp;
                Ttemp = Ttemp->next;
                delete del1;
            }
            delete temp;
        }
    }
};



//********************************************************************************* */
//*                                                                                 */
//*                           Function for password convert into (*)                */
//*                                                                                 */
//********************************************************************************* */


string getPassword()
{
    string password;
    char ch;

    while ((ch = _getch()) != '\r')
    { 
        if (ch == '\b')
        { 
            if (!password.empty())
            {
                cout << "\b \b"; 
                password.pop_back();
            }
        }
        else
        {
            password += ch;
            cout << '*'; // Mask input
        }
    }
    cout << endl;
    return password;
}


//********************************************************************************* */
//*                                                                                 */
//*                      Function for Display Name & Loading in Main                */
//*                                                                                 */
//********************************************************************************* */


void start() 
{
    system("cls");
    system("Color 40");

    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\tBANK MANAGMENT SYSTEM\n\n";
    cout << "\t\t\t\t\t\tLOADING ";
    char x = 219;
    for (int i = 0; i < 35; i++) {
        cout << x;
        if (i < 10)
            Sleep(100);
        if (i >= 10 && i < 20)
            Sleep(100);
        if (i >= 20)
            Sleep(25);
    }
    system("cls");
}





void Menu() 
{
    
    cout << "\t\t\t\t\t==========================++++=======================\n";
    cout << "\t\t\t\t\t|*                                                  *|\n";
    cout << "\t\t\t\t\t|*                                                  *|\n";
    cout << "\t\t\t\t\t|*                                                  *|\n";
    cout << "\t\t\t\t\t|*            ----------------------------------    *|\n";
    cout << "\t\t\t\t\t|*           |     BANK MANAGMENT SYSTEM        |   *|\n";
    cout << "\t\t\t\t\t|*            ----------------------------------    *|\n";
    cout << "\t\t\t\t\t|*                                                  *|\n";
    cout << "\t\t\t\t\t|*                       MADE  BY :                 *|\n";
    cout << "\t\t\t\t\t|*                      -----------                 *|\n";
    cout << "\t\t\t\t\t|*                       USMAN ALI                  *|\n";
    cout << "\t\t\t\t\t|*                                                  *|\n";
    cout << "\t\t\t\t\t|*                                                  *|\n";
    cout << "\t\t\t\t\t|*                                                  *|\n";
    cout << "\t\t\t\t\t=================================================\n\n\n";
}


int main()
{
    start();
    Menu();
    Bank bank;
    int choice, accNumber;
    string name;
    double amount;


    do
    {   
        cout<<"\n\n";
        cout << "\t\t\t|*****************************************************************************************|" << endl;
        cout << "\t\t\t|------------------------------------->    1. User    <-----------------------------------|" << endl;
        cout << "\t\t\t|------------------------------------->    2. Admin   <-----------------------------------|" << endl;
        cout << "\t\t\t|------------------------------------->    3. Exit    <-----------------------------------|" << endl;
        cout << "\t\t\t|*****************************************************************************************|" << endl;
        cout << "\n\n\t\t----->  Choose = ";
        cin >> choice;
        

        if (choice == 1)
        { // User Menu
            cout << "\t\t----->  Enter user password = ";
            string password = getPassword();

            if (password == USER_PASSWORD)
            {
                int userChoice;

                {   
                    cout<<"\n\n";
                    cout << "\t\t\t|********************************************************************************************|" << endl;
                    cout << "\t\t\t|------------------------------------->    1. Deposit    <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    2. Withdraw   <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    3. Exit       <-----------------------------------|" << endl;
                    cout << "\t\t\t|********************************************************************************************|" << endl;
                    cout << "\n\n  -----> Choose = ";
                    cin >> userChoice;
                    

                    switch (userChoice)
                    {
                    case 1:
                        cout << "\t\t----->  Enter account number = ";
                        cin >> accNumber;
                        cout << "\t\t----->  Enter amount to deposit = ";
                        cin >> amount;
                        bank.deposit(accNumber, amount);
                        break;
                    case 2:
                        cout << "\t\t----->  Enter account number = ";
                        cin >> accNumber;
                        cout << "\t\t----->  Enter amount to withdraw = ";
                        cin >> amount;
                        bank.withdraw(accNumber, amount);
                        break;
                    case 3:
                        cout << "\t\t----->  Returning to main menu......" << endl;
                        break;
                    default:
                        cout << "\t\t----->  Invalid option. Try again............." << endl;
                    }
                } while (userChoice != 3);
            }
            else
            {
                cout << "\t\t----->  Incorrect password......" << endl;
            }
        }
        else if (choice == 2)
        { // Admin Menu
            cout << "\t\t----->  Enter admin password = ";
            string password = getPassword();

            if (password == ADMIN_PASSWORD)
            {
                int adminChoice;
                do
                {   
                cout<<"\n\n";
                    cout << "\t\t\t|***********************************************************************************************************|" << endl;
                    cout << "\t\t\t|------------------------------------->    1. Add Account               <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    2. Show Account Details      <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    3. Deposit                   <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    4. Withdraw                  <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    5. Search Account            <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    6. Delete Account            <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    7. View All Accounts         <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    8. Update Account Details    <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    9. View Transaction History  <-----------------------------------|" << endl;
                    cout << "\t\t\t|------------------------------------->    10. Exit                     <-----------------------------------|" << endl;
                    cout << "\t\t\t|***********************************************************************************************************|" << endl;
                    cout << "\n\n --->  Choose = ";
                    cin >> adminChoice;
        

                    switch (adminChoice)
                    {
                    case 1:
                        cout << "\t\t----->  Enter name = ";
                        cin >> name;
                        cout << "\t\t----->  Enter initial deposit = ";
                        cin >> amount;
                        bank.newAcc(name, amount);
                        break;
                    case 2:
                        cout << "\t\t----->  Enter account number = ";
                        cin >> accNumber;
                        bank.display(accNumber);
                        break;
                    case 3:
                        cout << "\t\t----->  Enter account number = ";
                        cin >> accNumber;
                        cout << "\t\t----->  Enter amount to deposit = ";
                        cin >> amount;
                        bank.deposit(accNumber, amount);
                        break;

                    case 4:
                        cout << "\t\t----->  Enter account number = ";
                        cin >> accNumber;
                        cout << "\t\t----->  Enter amount to withdraw =  ";
                        cin >> amount;
                        bank.withdraw(accNumber, amount);
                        break;

                    case 5:
                        cout << "\t\t----->  Enter name to search = ";
                        cin >> name;
                        bank.searchAcc(name);
                        break;

                    case 6:
                        cout << "\t\t----->  Enter account number to delete = ";
                        cin >> accNumber;
                        bank.delAcc(accNumber);
                        break;

                    case 7:
                        bank.displayAcc();
                        break;

                    case 8:
                        cout << "\t\t----->  Enter account number to update = ";
                        cin >> accNumber;
                        cout << "\t\t----->  Enter new name = ";
                        cin >> name;
                        bank.updateAcc(accNumber, name);
                        break;

                    case 9:
                        cout << "\t\t----->  Enter account number to view transactions = ";
                        cin >> accNumber;
                        bank.dispTrans(accNumber);
                        break;

                    case 10:
                        cout << "\t\t ...... Exiting..........." << endl;
                        break;
                    default:
                        cout << "\t\t----->  Invalid option. Try again!.............." << endl;
                    }
                } while (adminChoice != 10);
            }
            else
            {
                cout << "\t\t----->  Incorrect password!......................" << endl;
            }
        }

        else if (choice == 3){
            cout << "............. Exiting program ............" << endl;
        }

        else{
            cout << "\t\t----->  Invalid option. Try again!" << endl;
        }
    } while (choice != 3);

    return 0;
}
