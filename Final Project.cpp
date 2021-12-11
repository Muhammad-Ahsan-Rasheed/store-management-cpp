#include<iostream>
#include<string.h>
#include<conio.h>
#include<math.h>
#include<fstream>
#include<iomanip>
using namespace std;
int i,n;
ifstream fin;
ofstream fout;
fstream fio;
void disp();
class stock
{
	char name[20],pass[15];
	float pr; int quant;

public:
	void get();
	void get2();
	void show();
    int stchk(char nm[30]);    
    void withd(int qty, int &tem);
    void refil(int qty);
}st;
class order
{
	char cus_name[20],conNo[11],time[9],date[12];
	public:
	int bill;
	void get_order();
	void showOrder();
	void cal_order();
}ordn;
void stock::withd(int qty,int &temp)
{
	if(quant>=qty)
	{
		quant-=qty;
		if(temp!=0)
			temp+=(pr*qty);
		else
			temp = (pr*qty);
		cout<<"\n\nStock updated.\n";
		
    }
	else 
		cout<<"\n\nInsufficient stock";
		
	return;
}
void stock::refil(int qty)
{
	quant+=qty;
	cout<<"\n\nStock updated.";
	getch();	
}
int stock::stchk(char nm[30])
{
	if(strcmp(nm,name)==0)
		return 0;
	else 
		return 1;
}
void stock::get()
{
	cin>>name>>pr>>quant;		
}
void stock::get2()
{
	cin>>name>>quant;	
}
void stock::show()
{
	cout<<"\n  "<<setw(18)<<left<<name<<"\t\t"<<setw(15)<<quant<<"\t\t"<<setw(6)<<pr;
}
void addnew()
{
    system("cls");
	disp();
	getch();
	system("cls");
	cout<<"\nEnter the No. of Products that you wish to add: ";
    cin>>n;	
    
    if (n!=0)
    {	
		int j,l,sum=0;
		fout.open("shop.dat",ios::binary|ios::app);
		for(i=0;i<n;i++)
		
		{
			cout<<"\n\nInput the name, price and the quantity of item respectively\n\n";
		    st.get();
		    fout.write((char*)&st,sizeof(st));
	        cout<<"\n\nitem updated";
			cin.get();
	    }
	    cout<<"\n\nStock Updated!!";   
	
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
		cout<<"\n\nNo items to be added";
	}
}
void withdraw()
{
	system("cls");
	char temp[20];int qty, total=0;
	int i=0;
	long pos=0;
			
	iter:
		
		fio.open("shop.dat",ios::binary|ios::out|ios::in);
		fstream ord;
		ord.open("order.dat",ios::app|ios::binary);
		
		system("cls");
		disp();
		cout<<"\n\nEnter q to Quit , Enter the product's name :";
		cin>>temp;
		if(strcmp(temp,"quit")==0 || strcmp(temp,"Quit")==0)
		{
			ordn.get_order();
			ord.write((char*)&ordn,sizeof(ordn));
			return;
		}			
		else
		{
			cout<<"\n\nEnter quantity: :";
			cin>>qty;
			while(fio)
		    {
			    pos=fio.tellp();
			    fio.read((char*)&st,sizeof(st));
			    if(st.stchk(temp)==0)
			    {		  
				  st.withd(qty,total);
				  fio.seekp(pos);
				  fio.write((char*)&st,sizeof(st));
				  i++;break;
			    }
		    }
		    cout<<"Total Price to be Paid :"<<total;
		    ordn.bill = total;
		    getch();		    
		    
		    if(i!=1)
		    	cout<<"\n\n!!Record not found!!";
		    fio.close();
		    ord.close();
		    goto iter;
		}		
}
void disp()
{
	int i=1;
	cout<<"\n|====================================================================|";
	cout<<"\n|====================THE STOCK ITEMS ARE=============================|";	
	cout<<"\n|====================================================================|";
	cout<<"\n\n| PRODUCT NAME\t\tSTOCK AVAILABLE\t\t\tPRICE\t     |";
	cout<<"\n|====================================================================|";
	fin.open("shop.dat",ios::binary);
    while(!fin.eof())
    {
	    fin.read((char*)&st,sizeof(st));
	    if(!fin.eof())
		{
		    if(fin.tellg()<0)
		    {	i=0; break;	}
		    st.show();
		}
    }
    cout<<"\n|====================================================================|";
    if(i==0)
    {	
		cout<<"\n\n\t\t\t!!Empty record room!!";
		getch();
    }
    fin.close();    
}
void refill()
{
	system("cls");
	char temp[100];int qty;
	int i=0;
	long pos=0;
	disp();
	cout<<"\n\nEnter the products name :";
	cin>>temp;
	cout<<"\n\nEnter quantity: ";
	cin>>qty;
	fio.open("shop.dat",ios::binary|ios::out|ios::in);
    while(fio)
    {
	   pos=fio.tellp();
	   fio.read((char*)&st,sizeof(st));
	   if(st.stchk(temp)==0)
	   {		  
		    st.refil(qty);
			fio.seekp(pos);
			fio.write((char*)&st,sizeof(st));
			i++;break;
	   }
    }
    if(i!=1)
    cout<<"\n\n!!Record not found!!";
    fio.close();
    system("cls");
    cin.get();
	disp(); 
	cin.get();
}
void remove()
{
	system("cls");	
	int i=0;
    char temp[30];
    cout<<"\n\t\t\t\tDelete Record";
    cout<<"\n\nEnter the name of the product:";
    cin>>temp;
    fout.open("temp.dat",ios::binary);
    fin.open("shop.dat",ios::binary);
    while(!fin.eof())
    {
		fin.read((char*)&st,sizeof(st));
	    if(!fin.eof())
	    if(st.stchk(temp)==0)
		    {
			  st.show();
			  cout<<"\n\n\t\tRecord deleted";
			  i++;
		    }
	    else
		    fout.write((char*)&st,sizeof(st));
    }
    if(i==0)
    	cout<<"\n\n!!Record not found!!";
    fin.close();
    fout.close();
    remove("shop.dat");
    rename("temp.dat","shop.dat");
}
void order::get_order()
{
	fflush(stdin);
	cout<<"\n\nEnter the Customer's Name :";
	fflush(stdin);
	cin.getline(cus_name,20);
	fflush(stdin);
	strcpy(time,__TIME__);
	fflush(stdin);
	strcpy(date,__DATE__);
	fflush(stdin);
	return;
}
void order::cal_order()
{
	system("cls");
	char name[20];
	int cont,sum=0,pri,quan;
	cout<<"\n\n\tTOTAL PRODUCTS :";
	cin>>cont;
	for(int i=0;i<cont;i++)
	{
		system("cls");
		cout<<"\n\nEnter "<<i+1<<" Product NAME :";
		fflush(stdin);
		gets(name);
		cout<<"\nEnter "<<i+1<<" Product QUANTITY :";
		fflush(stdin);
		cin>>quan;
		cout<<"\nEnter "<<i+1<<" Product PRICE :";
		fflush(stdin);
		cin>>pri;
		cout<<"\nPRICE of this Product is :"<<quan*pri;
		fflush(stdin);
		sum+=(pri*quan);
	}
	cout<<"\n\n\tTotal PRICE to Pay :"<<sum;
	return;
}
void order::showOrder()
{
	cout<<"\n"<<setw(2)<<" "<<setw(20)<<left<<cus_name<<setw(11)<<left<<conNo<<"  "<<setw(9)<<left<<time<<" "<<setw(12)<<left<<date<<" "<<setw(7)<<left<<bill;
	return;
}
void tot_order()
{
	int i=1;
	system("cls");
	cout<<"\n|==============================================================================|";
	cout<<"\n|====================THE TOTAL ORDERS ARE======================================|";	
	cout<<"\n|==============================================================================|";
	cout<<"\n\n|"<<setw(1)<<setw(20)<<left<<" CUSTOMER NAME "<<setw(11)<<left<<" CONTACT NO. "<<setw(9)<<left<<" TIME "<<setw(12)<<left<<"  DATE "<<setw(7)<<left<<"   BILL ";
	cout<<"\n|==============================================================================|";
	fin.open("order.dat",ios::binary);
    while(!fin.eof())
    {
	 fin.read((char*)&ordn,sizeof(ordn));
	 if(!fin.eof())
	 {
	    if(fin.tellg()<0)
	    {	i=0; break;}
	    ordn.showOrder();
	 }
    }
    cout<<"\n|==============================================================================|";
    if(i==0)
    {	cout<<"\n\n\t\t\t!!Empty record room!!";
		getch();
    }
    fin.close();
    return;
}
void set()
{
	cout<<"\n\n\n\t\t\t|=========================|\n";
	cout<<"\t\t\t|==========LOGIN==========|\n";
	cout<<"\t\t\t|=========================|\n";
	cout<<"\t\t\t|			  |\n";
	cout<<"\t\t\t| Enter Password: ";
	return;
}
bool login(const char a[])
{
	set();
	char pass2[strlen(a)];
	for(int z=0;z<strlen(a);z++)
	{
		pass2[z]=getch();
		system("cls");
		set();
		for(int i=1;i<=(z+1);i++)
		{
			cout<<"*";
		}
	}
	if(strcmp(pass2,a)==0)
		return true;

	return false;
}
int main()
{
	char pass2[10];
	char i,j;
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\t|============ WELCOME TO SK STORE MANAGEMENT ============|";
	getch();
	main_menu:
	system("cls");
	cout<<"\n\t|=============================================|";
	cout<<"\n\t|======== SK  STORE MANAGEMENT SYSTEM ========|";	
	cout<<"\n\t|=============================================|";
	cout<<"\n\t|================= Main Menu =================|";
	cout<<"\n\t|=============================================|";
	cout<<"\n\n\t\t   1. Dealer Menu\n\t\t   2. Customer Menu\n\t\t   3. Employee Menu\n\t\t   4. Exit\n";
	cout<<"\n\t|=============================================|";
	cout<<"\n\nEnter Your Choice :";
	j = getch();
	if(j=='1')
	{
		system("cls");	
		fflush(stdin);
		if(login("admin"))
		{
			dealermenu:
			system("cls");
			cout<<"\n\t|=============================================|";
			cout<<"\n\t|=================DEALER MENU=================|";
			cout<<"\n\t|=============================================|";
			cout<<"\n\n\t\t1. Add new product\n\t\t2. Display stock\n\t\t3. Refill\n\t\t4. Remove an item\n\t\t5. Customer Order  \n\t\t6. Back To Main Menu  \n\t\t7. Exit\n";
			cout<<"\n\t|=================END OF MENU=================|";
			cout<<"\n\n Enter your Choice :\t";
			i = getch();
			if(i=='1')
			{
				addnew();getch();
				goto dealermenu;
			}	
			else if(i=='2')
			{
				system("cls");
				disp();getch();goto dealermenu;
			}
			else if(i=='3')
			{
				refill();goto dealermenu;
			}
			else if(i=='4')
			{
				remove();getch();goto dealermenu;
			}
			else if(i=='5')
			{
				cus_item:
				system("cls");
				cout<<"\n\t|=============================================|";
				cout<<"\n\t|================RECORD ORDER=================|";
				cout<<"\n\t|=============================================|";
				cout<<"\n\n\t\t1.Record Order\n\t\t2.Total Order \n\t\t3.Back To Main Menu \n\t\t4.Open Price Calculator \n\t\t5.Exit";
				cout<<"\n\t|=================END OF MENU=================|";
				cout<<"\n\nEnter your Choice :";
				i = getch();				
				if (i=='1')
				{
					withdraw();getch();
					goto cus_item;
				}
				else if(i=='2')
				{
					tot_order();getch();
					goto cus_item;
				}
				else if(i=='3')
				{
					goto dealermenu;
				}
				else if(i=='4')
				{
					ordn.cal_order();getch();
					goto cus_item;
				}
				else
				{
					system("cls");
					cout<<"\n\n\n\n\n\n\n\n\t\t\t    Thank You!!\n\n";
					cout<<"\n\t|============ Developed by SILENT KING ============|\n\n\n";
					exit(0);
				}
			}else if(i == '6')
			{
				goto main_menu;
			}else
			{
				system("cls");
				cout<<"\n\n\n\n\n\n\n\n\t\t\t    Thank You!!\n\n";
				cout<<"\n\t|============ Developed by SILENT KING ============|\n\n\n";
				exit(0);
			}
		}
		else
		{
			system("cls");
			cout<<"\n\n\n\n\n\n\n\n\n\n\n\t|============ WRONG PASSWORD!!! ============|\n\n\n\a";
			getch();
			goto main_menu;
		}
	}
	if(j=='2')
	{
		custmenu:
		system("cls");
		cout<<"\n\t|=============================================|";
		cout<<"\n\t|================CUSTOMER MENU================|";
		cout<<"\n\t|=============================================|";
		cout<<"\n\n\t1. Purchase\n\t2. Display stock\n\t3. Open Price Calculator:\n\t4. Exit:\n";
		cout<<"\n\t|=================END OF MENU=================|";
		cout<<"\n\n\tEnter your Choice :";
		i = getch()		;
		
		if (i=='1')
		{
			withdraw();getch();goto custmenu;
		}
		else if(i=='2')
		{
			system("cls");
			disp();getch();goto custmenu;
		}
		else if(i=='3')
		{
			ordn.cal_order();getch();
			goto cus_item;
		}	
		else 
		{
			goto main_menu;
		}	
	}
	if(j=='3')
	{
		system("cls");
		if(login("emp"))
		{
			empmenu:
			system("cls");
			cout<<"\n\t|=============================================|";
			cout<<"\n\t|================EMPLOYEE MENU================|";
			cout<<"\n\t|=============================================|";
			cout<<"\n\n\t\t1. Display stock\n\t\t2. Refill\n\t\t3. Back To Main Menu\n\t\t4. Exit";
			cout<<"\n\t|=================END OF MENU=================|";
			cout<<"\n\n\t\tEnter your Choice :";
			i = getch();
			if(i=='1')
			{
				system("cls");
			disp();getch();goto empmenu;
			}
			else if(i=='2')
			{
				refill();goto empmenu;
			}
			else if(i=='3')
			{
				goto main_menu;
			}
			else
			{
				system("cls");
				cout<<"\n\n\n\n\n\n\n\n\t\t\t    Thank You!!\n\n";
				cout<<"\n\t|============ Developed by SILENT KING ============|\n\n\n";
				getch();
				exit(0);
			}
		}
		else
		{
			cout<<"\n\n\n\n\n\n\n\n\n\n\n\t|============ WRONG PASSWORD!!! ============|\n\n\n\a";
			getch();
			goto main_menu;
		}
	}
	else 
	{
		system("cls");
		cout<<"\n\n\n\n\n\n\n\n\t\t\t    Thank You!!\n\n";
		cout<<"\n\t|============ Developed by SILENT KING ============|\n\n\n";
		exit(0);
	}
	return 0;
}
