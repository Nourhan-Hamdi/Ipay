#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#define IOS                     \
  ios_base::sync_with_stdio(0); \
  cin.tie(NULL);                \
  cout.tie(NULL);
using namespace std;
class user
{
private:
    string user_name, password;
    int phone_number, card, balance;
public:
    void set(string u, string p)
    {
        user_name = u;
        password = p;
    }
    void set(int n, int c, int b = 0)
    {
        phone_number = n;
        card = c;
        balance = b;
    }
    string get_password()
    {
        return password;
    }
    string get_username()
    {
        return user_name;
    }
    int get_phone()
    {
        return phone_number;
    }
    int get_card()
    {
        return card;
    }
    int get_balance()
    {
        return balance;
    }
    void change_balance(int credit)
    {
        balance = credit;
    }
    void change_balance(int x, char s)
    {
        balance += x;
    }
};
vector<user>list;
vector<user>fav;
class Ipayment
{
protected:
    int credit;
public:
    virtual void pay(user me) = 0;
    virtual void set_balance(user me) = 0;
};
void select_from_fav(int x)
{
    cout << "enter\n1- to select from favourite list\n2- to type payment address\n";
    int s;
    cin >> s;
    if (s == 1)
    {
        if (fav.size() == 0)
        {
            cout << "ther is no users in the list,type the payment address\n";
        }
        else
        {
            for (int i = 0; i < fav.size(); i++)
            {
                cout << i + 1 << fav[i].get_username() << '\n';
            }
            cout << "enter the user number\n";
            cin >> s;
            s--;
            if (s >= 0 && s <= fav.size())
            {
                fav[s].change_balance(x, '+');
            }
        }
    }
    else
    {
        string address;
        cin >> address;
        bool exist = 0;
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < list.size(); i++)
            {
                if (address == list[i].get_username())
                {
                    exist = 1;
                    list[i].change_balance(x, '+');
                    cout << "do you want to add this user to favourite list?\n1-yes\n2-no\n";
                    int a;
                    cin >> a;
                    if (a == 1)
                    {
                        fav.push_back(list[i]);
                    }
                    break;
                }
            }
            if (!exist)
            {
                cout << "user_name does not exist, try again\n";
                cin >> address;
            }
            else { break; }
        }
        if (!exist)
        {
            //menu(me);
            return;
        }
    }

}
class pay_by_payment_address :public Ipayment
{
public:
    pay_by_payment_address(user me)
    {
        credit = me.get_balance();
    }
    void pay(user me)
    {
        cout << "enter the amount you want to send\n";
        int x;
        cin >> x;
        if (credit < x + 2)
        {
            cout << "your balance is not enough\n";
        }
        else
        {
            //cout << "enter payment address\n";
            select_from_fav(x);
            credit -= x + 2;
            me.change_balance(x, '+');
        }
    }
    void set_balance(user me)
    {
        me.change_balance(credit);
    }
};
class pay_by_phone_number :public Ipayment
{
public:
    pay_by_phone_number(user me)
    {
        credit = me.get_balance();
    }
    void pay(user me)
    {
        cout << "enter the amount you want to send\n";
        int x;
        cin >> x;
        if (credit < x + 5)
        {
            cout << "your balance is not enough\n";
        }
        else
        {
            int phone;
            cout << "enter phone number\n";
            cin >> phone;
            credit -= x + 5;
            me.change_balance(x, '+');
        }
    }
    void set_balance(user me)
    {
        me.change_balance(credit);
    }
};
class pay_by_credit_card :public Ipayment
{
public:
    pay_by_credit_card(user me)
    {
        credit = me.get_balance();
    }
    void pay(user me)
    {
        cout << "enter the amount you want to send\n";
        int x;
        cin >> x;
        if (credit < x + 5)
        {
            cout << "your balance is not enough\n";
        }
        else
        {
            int card;
            cout << "enter the credit card number \n";
            cin >> card;
            credit -= x + 5;
            me.change_balance(x, '+');
        }
    }
    void set_balance(user me)
    {
        me.change_balance(credit);
    }
};
user login();
user sign_up()
{
    string username, pass;
    int phone, credit, balan;
    cout << "enter ur phone number\n";
    cin >> phone;
    cout << "create a user_name\n";
    cin >> username;
    cout << "enter bank card number\n";
    cin >> credit;
    cout << "enter ur balance\n";
    cin >> balan;
    cout << "create a password \n";
    cin >> pass;
    user me;
    me.set(username, pass);
    me.set(phone, credit, balan);
    list.push_back(me);
    return me;
}
user sign_in()
{
    string un;
    cout << "enter ur user_name\n";
    cin >> un;
    bool exist = 0;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (un == list[i].get_username())
            {
                exist = 1;
                break;
            }
        }
        if (!exist)
        {
            cout << "user_name does not exist, try again\n";
            cin >> un;
        }
        else { break; }
    }
    if (!exist)
    {
        login();
        //return;
    }
    string pass;
    cout << "enter ur password\n";
    cin >> pass;
    user me;
    exist = 0;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (pass == list[i].get_password())
            {
                exist = 1;
                me = list[i];
                break;
            }
        }
        if (!exist)
        {
            cout << "wrong password, try again\n";
            cin >> pass;
        }
        else { break; }
    }
    if (!exist)
    {
        login();
        //return;
    }
    else
    {
        return me;
    }
}
user login()
{
    int x;
    cout << "press:\n1 to login\n2 to register\n";
    cin >> x;
    user me;
    if (x == 1)
    {
        me = sign_in();
    }
    else if (x == 2)
    {
        me = sign_up();
    }
    else
    {
        login();
        // return;
    }
    return me;
}
void menu()
{
    cout << "\n1-send money\n2-Inquire about your balance\n3-list the users\n4-log out\n";
}
int main()
{
    IOS;
    user me = login();
    while (1)
    {
        menu();
        int choice;
        cout << "enter a number to select from the menu\n";
        cin >> choice;
        if (choice == 1)
        {
            Ipayment* ob = NULL;
            cout << "choose how to pay\n";
            cout << "1-payment adress\n2-phone number\n3-credit card\n";
            cin >> choice;
            if (choice == 1)
            {
                ob = new pay_by_payment_address(me);
                ob->pay(me);
                ob->set_balance(me);
            }
            else if (choice == 2)
            {
                ob = new pay_by_phone_number(me);
                ob->pay(me);
                ob->set_balance(me);
            }
            else if (choice == 3)
            {
                ob = new pay_by_credit_card(me);
                ob->pay(me);
                ob->set_balance(me);
            }
        }
        else if (choice == 2)
        {
            cout << me.get_balance();
        }
        else if (choice == 3)
        {
            for (int i = 0; i < list.size(); i++)
            {
                cout << i + 1 << "- " << list[i].get_username() << '\n';
            }
        }
        else if (choice == 4)
        {
            me = login();
        }
    }
    return 0;
}