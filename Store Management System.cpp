#include<iostream>
#include<string.h>
#include<conio.h>
#include<math.h>
#include<fstream>
#include<chrono>
#define ll long long int
using namespace std;
ll i,n;
ifstream fin;
ofstream fout,fout1;
fstream fio;
void disp();
class stock
{
public:
	string name;//pass[15];
	float pr; ll quant;
	void get(); 
	void get2(); 
	void show(); 
    ll stchk(string nm); 
    void withd(ll qty); 
    void refil(ll qty); 
}st;
void stock::withd(ll qty)
{
	if(quant>=qty)
	{
		auto timenow1 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		fout1.open("sales.csv",ios::out|ios::app|ios::ate);
		fout1 << endl;
		string temp(ctime(&timenow1));
		fout1 << st.name << " , " << qty << " , " << st.pr << " , " << qty*st.pr << " , " << temp.substr(0,temp.length()-1);
		quant-=qty;
		fout1.close();
		cout << "\n\nStock updated.\n";
		cout << "\n\nTotal price to be paid:" << pr*qty;
    }
	else 
		cout << "\n\nInsufficient stock";
	getch();
}

void stock::refil(ll qty)
{
	quant+=qty;
	cout << "\n\nStock updated.";
    getch();	
}

ll stock::stchk(string nm)
{
	if(nm==name)
		return 0;
	else 
		return 1;
}
void stock::get()
{
	cin >> name >> pr >> quant;
}
void stock::get2()
{
	cin >> name >> quant;
}

void stock::show()
{
	ll a = name.length();
	cout << "\n" << name ;
	for(ll i=0;i<25-a;i++)
		cout << " ";
	cout << quant;
	ll b = to_string(quant).length();
	for(ll i=0;i<25-b;i++)
		cout << " ";
	cout << pr;
}
void addnew()
{
    system("cls");
	disp();
	getch();
	system("cls");
	cout << "\nEnter the No. of Products that you wish to add: ";
    cin >> n;
    if (n!=0)
    {
		ll j,l,sum=0;
		fout.open("project.csv",ios::out|ios::app|ios::ate);
		fout << endl;
		for(i=0;i<n;i++)
		{
			cout << "\n\nInput the name, price and the quantity of item respectively\n\n";
		    st.get();
		    fout << st.name << " , " << st.quant << " , " << st.pr;
		    if(i!=n-1)
		    	fout << endl;
	        cout << "\n\nitem updated";
			cin.get();
	    }
	    cout << "\n\nStock Updated!!";
	    fout.close();
	    cin.get();
	    system("cls");
	    disp();
	}
	else
	{
		fout.close();
		cin.get();
		system("cls");
		cout << "\n\nNo items to be added";
	}
}

void withdraw()
{
	system("cls");
	string temp;ll qty;
	ll i=0;
	disp();
	cout << "\n\nEnter the product's name \n" << endl;
	cin >> temp;
	cout << "\n\nEnter quantity: \n" << endl;
	cin >> qty;
	char ch;
	fin.open("project.csv",ios::in);
	fout.open("temp.csv",ios::out);
	string a,b,c;
	fin >> a;
//	fin >> a >> ch >> b >> ch >> c;
//	fout << a << " , " << b << " , " << c;
	fout << a;
	if(fin.tellg()!=-1)
		fout << endl;
    while(!fin.eof())
    {
		fin >> st.name >> ch >> st.quant >> ch >>  st.pr;
	    if(st.stchk(temp)==0)
	    {
			st.withd(qty);
			fout << st.name << " , " << st.quant << " , " << st.pr;
			if(fin.tellg()!=-1)
				fout << endl;
			i++;continue;
	    }
	    fout << st.name << " , " << st.quant << " , " << st.pr;
		if(fin.tellg()!=-1)
			fout << endl;
    }
    if(i==0)
    	cout << "\n\n!!Record not found!!";
    fin.close();
    fout.close();
    remove("project.csv");
    rename("temp.csv","project.csv");
    cin.get();
    system("cls");
	disp(); 
	getch();
}
void disp()
{
	ll i=0;
	cout << "\n==================================================================";
	cout << "\n\n=================\tTHE STOCK ITEMS ARE\t==================";
	cout << "\n\n==================================================================\n";
	cout << "\n\nPARTICULARS\tSTOCK AVAILABLE\t\t\t PRICE";
	cout << "\n\n============================================================\n";	
	fin.open("project.csv",ios::in);
	string a;
	fin >> a;
	ll count = 0 ;
	char ch;
    while(!fin.eof())
    {
    	if(fin.tellg()<0)
			break;
	    fin >> st.name >> ch >> st.quant >> ch >>  st.pr;
	    count++;
		st.show();
    }
    if(count==0)
    {	
		cout << "\n\n\t\t\t!!Empty record room!!";
		getch();
	}
	fin.close();    
}
void refill()
{
	system("cls");
	string temp;ll qty;
	ll i=0;
	disp();
	cout << "\n\nEnter the products name \n" << endl;
	cin >> temp;
	cout << "\n\nEnter quantity: \n" << endl;
	cin >> qty;
	char ch;
	fin.open("project.csv",ios::in);
	fout.open("temp.csv",ios::out);
	string a,b,c;
	fin >> a;
//	fin >> a >> ch >>  b >> ch >> c;
//	fout << a << " , " << b << " , " << c;
	fout << a;
	if(fin.tellg()!=-1)
		fout << endl;
    while(!fin.eof())
    {
		fin >> st.name >> ch >> st.quant >> ch >>  st.pr;
	    if(st.stchk(temp)==0)
	    {
			st.refil(qty);
			fout << st.name << " , " << st.quant << " , " << st.pr;
			if(fin.tellg()!=-1)
				fout << endl;
			i++;
			continue;
	    }
	    fout << st.name << " , " << st.quant << " , " << st.pr;
	    if(fin.tellg()!=-1)
			fout << endl;
    }
    if(i!=1)
    	cout << "\n\n!!Record not found!!";
    fin.close();
    fout.close();
    remove("project.csv");
    rename("temp.csv","project.csv");
    system("cls");
    cin.get();
	disp();
	cin.get();
}

void remove()
{
	system("cls");	
	ll i=0;
	string temp;
    cout << "\n\t\t\t\tDelete Record";
    cout << "\n\nEnter the name of the product:";
    char ch;
    cin >> temp;
	fin.open("project.csv",ios::in);
	fout.open("temp.csv",ios::out);
	string a,b,c;
//	fin >> a >> ch >>  b >> ch >> c;
	fin >> a;
//	fout << a << "," << b << "," << c;
	fout << a;
	if(fin.tellg()!=-1)
		fout << endl;
    while(!fin.eof())
    {	
		fin >> st.name >> ch >> st.quant >> ch >>  st.pr;
	    if(st.stchk(temp)==0)
	    {
			st.show();
			cout << "\n\n\t\tRecord deleted";
			i++;
	    }
	    else
	    {
			fout << st.name << " , " << st.quant << " , " << st.pr;
			if(fin.tellg()!=-1)
				fout << endl;
		}
    }
    if(i==0)
    	cout << "\n\n!!Record not found!!";
    fin.close();
    fout.close();
    remove("project.csv");
    rename("temp.csv","project.csv");
}
int main()
{
	ll i,j;
	cout << "\n\n\n\n\n\n\n\n\n\n\n \t\t\t|============ WELCOME TO STORE MANAGEMENT SYSTEM ============|";
	getch();
	system("cls");
	mainmenu:
	string pass,pass2;
	system("cls");
	cout << "\n\t\t   STORE MANAGEMENT SYSTEM\n";	
	cout << "=============================================================";
	cout << "\n\n\t\t   1. Dealer Menu\n\n\t\t   2. Customer Menu\n\n\t\t   3. Employee Menu";
	cout << "\n\n=============================================================\n";
	cout << "\n\nEnter Your Choice:";
	cin >> j;
	if(j==1)
	{
		system("cls");
	    system("cls");
	    cout << "\n\n\n\n\n\n\n\t\t\t\t\tPlease enter the password: ";
		for(ll z=0;z<7;z++)
		{
			pass.push_back(getch());
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tPlease enter the password: ";
			for(i=1;i<=(z+1);i++)
			{
				cout << "*";
			}
		}
		if(pass=="ironman")
		{
			system("cls");
			dealermenu:
			system("cls");
			cout << "=================================================================";
			cout << "\n\n\t\t\t    DEALER MENU\n1. Add new product\n2. Display stock\n3. Refill\n4. Remove an item\n5. Exit:";
			cout << "\n\n\n==========================END OF MENU=============================";
			cout << "\n\n Enter your Choice :\t";
			cin >> i;
			if(i==1)
			{
				addnew();getch();
				goto dealermenu;
			}
			else if(i==2)
			{
				system("cls");
				disp();
				getch();
				goto dealermenu;
			}
			else if(i==3)
			{
				refill();
				goto dealermenu;
			}
			else if(i==4)
			{
				remove();
				getch();
				goto dealermenu;
			}
			else 
			{
				goto mainmenu;
			}
		}
		else
		{
			cout << "\n\n\nINPUT CORRECT PASSWORD!!!\n\n";
			getch();
			goto mainmenu;
		}	
	}	
	if(j==2)
	{
		custmenu:
		system("cls");
		cout << "=================================================================";
		cout << "\n\n\t\t\t    CUSTOMER MENU\n1. Purchase\n2. Display stock\n3. Exit:";
		cout << "\n\n\n==========================END OF MENU=============================";
		cout << "\n\n Enter your Choice :\t";
		cin >> i;
		if (i==1)
		{
			withdraw();
			getch();
			goto custmenu;
		}
		else if(i==2)
		{
			system("cls");
			disp();
			getch();
			goto custmenu;
		}
		else 
		{
			system("cls");
			goto mainmenu;
		}
	}
	if(j==3)
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\t\t\t\t\tPlease enter the password: ";
		for(ll z=0;z<7;z++)
		{
			pass2.push_back(getch());
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tPlease enter the password : ";
			for(i=1;i<=(z+1);i++)
			{
				cout << "*";
			}
		}
		if(pass2=="ironman")
		{
			empmenu:
			system("cls");
			cout << "=================================================================";
			cout << "\n\n\t\t\tEMPLOYEE MENU\n1. Display stock\n2. Refill\n3. Exit";
			cout << "\n\n\n==========================END OF MENU=============================";
			cout << "\n\n Enter your Choice :\t";
			cin >> i;
			if(i==1)
			{
				system("cls");
				disp();
				getch();
				goto empmenu;
			}
			else if(i==2)
			{
				refill();
				goto empmenu;
			}
			else 
			{
				system("cls");
				cout << "\n\n\n\t\t\tThank You!!";
				getch();
				goto mainmenu;
			}
		}
		else
		{
			cout << "\n\nSorry!! Please Provide Valid Password..\n\n";
			getch();
			goto mainmenu;
		}
	}	
	getch();
}
