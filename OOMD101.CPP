#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
int admin=1;
class user
{
	char username[100];
	char password[100];
	public:
	void getdata(char*, char*);
	void writedata();
	void display();
	void check(char*, char*);
};
void user::getdata(char *un,char *pass)
{
	strcpy(username,un);
	strcpy(password,pass);
	writedata();
}
void user::writedata()
{
	ofstream fout;
	fout.open("Userdetails1.txt",ios::binary | ios::app);
	fout.write((char*)this,sizeof(*this));
	fout.close();
}
void user::display()
{
	ifstream fin;
	fin.open("Userdetails1.txt",ios::binary);
	while(fin.read((char*)this,sizeof(*this)))
	{
		cout<<"User name: "<<username<<endl;
		cout<<"Password: "<<password<<endl;

	}
	fin.close();
}
void user::check(char *un,char *pass)
{
	ifstream fin;
	int f=0;
	fin.open("Userdetails1.txt",ios::binary);
	while(fin.read((char*)this,sizeof(*this)))
	{

		if((strcmp(username,"admin"))==0)
		{
		f=1;
			if((strcmp(password,"admin"))==0)
			{
				cout<<endl<<"You have successfully logged in as admin";
				admin=1;
			}
			else
			{
				cout<<endl<<"Sorry password is incorrect";
			}
			break;
		}
		else if(strcmp(username,un)==0)
		{
			f=1;
			if(strcmp(password,pass)==0)
			{
				cout<<endl<<"You have successfully logged in";
			}
			else
			{
				cout<<endl<<"Sorry password is incorrect";
			}
			break;
		}
	}
	if(f==0)
	{
		cout<<endl<<"No such username exist";
	}
}

class authenticated_user
{
	char cat_name[50], pro_name[50],item_name[50];
	int item_id,price,quantity;
	public:
	/*authenticated_user()
	{
		strcpy(cat_name,"Nil");
		strcpy(pro_name,"Nil");
		strcpy(item_name,"Nil");
		item_id=0;
		price=0;
		quantity=0;
	}*/
	void create_cat(char[]);
	void create_pro(char[]);
	void create_item(char[]);
	void add(char[]);
	void update();
	void List(char[],int);
};

void authenticated_user::create_cat(char fcn[])
{
	strcpy(cat_name,fcn);
	fstream fout;
	fout.open("category.txt",ios::binary|ios::app);
	fout.write((char*)this,sizeof(*this));
	fout.close();
}
void authenticated_user::create_pro(char fpn[])
{
	char cn[50];
	List("category",1);
	cout<<endl<<"Enter category to add product in: ";
	cin>>cn;
	strcpy(cat_name,cn);
	strcpy(pro_name,fpn);
	add(cat_name);
}
void authenticated_user::create_item(char itm[])
{
	int q,id,p;
	char cn[50],pn[50];

	List("category",1);
	cout<<endl<<"Enter category to add product in: ";
	gets(cn);
	strcpy(cat_name,cn);

	List(cat_name,2);
	cout<<endl<<"Enter product to add item in: ";
	gets(pn);
	strcpy(pro_name,pn);

	cout<<endl<<"Enter item id: ";
	cin>>id;
	cout<<endl<<"Enter price of item: ";
	cin>>p;
	cout<<"Enter the available quantity: ";
	cin>>q;

	item_id=id;
	quantity=q;
	price=p;

	strcpy(item_name,itm);
	add(pro_name);


}

void authenticated_user::add(char val[])
{
	char temp[50];
	strcpy(temp,val);

	strcat(temp,".txt");

	ofstream fout;
	fout.open(temp,ios::binary|ios::app);
	fout.write((char*)this,sizeof(*this));
	fout<<"\n";
	fout.close();
}
void authenticated_user::update()
{
	char cn[50],pn[50];
	int id,n,p,q;
	List("category",1);
	cout<<endl<<"\nEnter category to update: ";
	cin>>cn;
	List(cn,2);
	cout<<"\nEnter product name : ";
	cin>>pn;
	cout<<" ";
	List(pn,3);
	cout<<"\nEnter item no.: ";
	cin>>id;
	strcat(pn,".txt");
     /*	item_id=this->item_id;
	price=this->price;
	quantity=this->quantity;    */
	cout<<cat_name<<endl<<pro_name<<endl<<price<<quantity<<item_id;
	ifstream fin;
	ofstream fout;
	fin.open(pn,ios::binary);
	fout.open("temp.txt",ios::binary|ios::app);
	while(fin.read((char*)this,sizeof(*this)))
	{
		if(item_id!=id)
		{
		    fout.write((char*)this,sizeof(*this));
		}
		else
		{
		    cout<<"\nPress 1 to update price\nPress 2 to update stock";
		    cin>>n;
		    if(n==1)
		    {
			cout<<"Enter updated price";
			cin>>p;
			price=p;
			cout<<"called";
			fout.write((char*)this,sizeof(*this));
		    }
		    if(n==2)
		    {
			cout<<"Enter updated stock quantity: ";
			cin>>q;
			quantity=q;
		    }
		    List(pn,2);

		}
	}
	fout.close();
	fin.close();
	remove(pn);
	rename("temp.txt",pn);

}
void authenticated_user::List(char fn[],int f)
{
	int c=1;
	char temp[50];
	strcpy(temp,fn);

	ifstream fin;
	strcat(temp,".txt");
	fin.open(temp,ios::binary);
	while(fin.read((char*)this,sizeof(*this)))
	{
		if(f==1)
		cout<<endl<<c++<<". "<<cat_name;
		if(f==2)
		cout<<endl<<c++<<". "<<pro_name;
		if(f==3)
		{
			cout<<endl<<c++<<". "<<cat_name<<endl<<"--> "<<pro_name<<endl;
			cout<<endl<<"--> "<<item_name<<endl<<"--> "<<item_id;
			cout<<endl<<"--> "<<price;
			cout<<endl<<"--> "<<quantity;
		}

	}
	fin.close();
}

class Order
{

public:
    char fname[20],email[20];
    int ShipmentDate;

    long int MobNum;
    float totalprice;

    void getinfo()
    {
        cout<<endl<<"Enter Full Name  : ";
        cin>>fname;
        cout<<"Enter Mobile No. : ";
        cout<<"Enter Email ID   : ";
        cout<<"\nYour Order has been placed.Please enter the following details:"<<endl;
        cout<<"\nEnter Shipping address:";
        cin>>ShippingAddress;
        cout<<endl;

    }
    void ShowOrder()
    {
        int dd,mm,yy,dd1,mm1,yy1;
        time_t now = time(0);
        tm* timePtr = localtime(&now);
        char* dt = ctime(&now);

        dd=(timePtr->tm_mday);
        mm=(timePtr->tm_mon)+1;
        yy=(timePtr->tm_year)+1900;
        if(mm==2)
        {
            if(dd>21)
               {
                 dd1=dd-21;
                 mm1=mm+1;
               }
            else
            {
                dd1=dd+7;
                mm1=mm;
            }
        }
        else if( (mm==4) || (mm==6) || (mm==9) || (mm==11))
        {
            if(dd>23)
               {
                 dd1=dd-23;
                 mm1=mm+1;
                }
            else
                {
                 dd1=dd+7;
                 mm1=mm;
                }
        }
        else
        {
            if(dd>24)
                {
                 dd1=dd-24;
                 mm1=mm+1;
                }
            else
            {
                dd1=dd+7;
                mm1=mm;
            }
        }

        cout<<"\nThese are the details you entered:"<<endl;
        cout<<"Name:"<<fname<<endl;
        cout<<"Shipping address:"<<ShippingAddress<<endl;
        cout<<"Mobile Num:"<<phone<<endl;
        cout<<"The Date of order is:"<<dd<<"/"<< mm <<"/"<< yy<< endl;
        cout<<"Date of delivery:"<<dd1<<"/"<< mm1 <<"/"<< yy<< endl;
        cout<<"Delivery may take "<<dd1-dd<<" or less.\n";
        cout<<"\nDelivery Boy name: Ashil Shah\n";
        cout<<"\nDelivery Boy contact no.: 9237426387";

    }

};
void main()
{
char n[100],p[100],c_n[50],p_n[25],i_n[25];
int choice;
clrscr();
user u;
authenticated_user au;

	do
	{
	   cout<<endl<<"Press 1 for sign up\nPress 2 for login as admin\nPress 3 to login as user\nPress 4 to display\nPress 5 for exit"<<endl;
	   cin>>choice;
	   switch(choice)
	   {
		case 1: cout<<"Enter username: ";
			gets(n);
			cout<<"Enter password: ";
			gets(p);
			u.getdata(n,p);
			break;
		case 2: cout<<"Enter username: ";
			gets(n);
			cout<<"Enter password: ";
			gets(p);
			u.check(n,p);
			break;
		case 3: cout<<"Enter username: ";
			gets(n);
			cout<<"Enter password: ";
			gets(p);
			u.check(n,p);
			break;
		case 4: u.display();
			break;
		case 5: break;
	   }
	}while(choice!=5);

	 int update;
	if(admin==1)
	{
	   do
	   {

		cout<<endl<<endl<<"----------------ADMIN-------------------";
		cout<<endl<<"Press 1 to add a category\nPress 2 to add a product\nPress 3 to add a item\Press 4 to display\nPress 5 to update \nPress 6 to exit\n";
		cin>>update;
		switch(update)
		{
			case 1: //make a file category and append one category there.
				cout<<endl<<"Enter category name: ";
				cin>>c_n;
				au.create_cat(c_n);
				break;
			case 2: //ask for the category to add item in (** ask for subcategory if any)
				cout<<endl<<"Enter product to add: ";
				cin>>p_n;
				cout<<endl<<"called";
				au.create_pro(p_n);
				break;
				//ask for rice of itm append both in the file of that category.
			case 3: //ask for the category,open file ,find item and update price.
				cout<<endl<<"Enter item to add: ";
				cin>>i_n;
				au.create_item(i_n);
				break;
			case 4: au.List("category",1);
				cout<<endl<<"Enter category name: ";
				cin>>i_n;
				au.List(i_n,2);
				cout<<endl<<"Enter product name: ";
				cin>>i_n;
				au.List(i_n,3);
				break;
			case 5: au.update();
			case 6: break;
		}
	 }while(update!=6);
	}
	   // we will make a class for after login i.e. authenticated users
	   // it will contain data members and functions for update for admin
	   // and other functions for customers.
	   else  // when not admin or is customer
	   {
		int choose;
		cout<<"------Customer------"; //to be set by iomanip
		cout<<"Press 1 to see catalouge\nPress 2 to see previous records\nPress 3";
	   }
	   /*
	   clrscr();
	 //  au.create_cat("Elec");
	 //  au.create_cat("Food");
	   au.List("category",1);
	   au.create_pro("pun");
	   au.create_pro("guju");

	   au.List("Food",2);*/
getch();
}
