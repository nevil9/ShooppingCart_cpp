#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<fstream>
using namespace std;

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
	while(fin.read((char*)this, sizeof(*this)))
	{
		cout<<"User name: \n"<<username;
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
		if(strcmp(username,un)==0)
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



int main()
{
char n[100],p[100];
int choice;
//clrscr();
user u;
	do
	{
	   cout<<endl<<"Press 1 for sign up\nPress 2 for login\nPress 3 to display\nPress 4 for exit"<<endl;
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
		case 3: u.display();
			break;
		case 4: break;
	   }
	   }while(choice!=4);

getch();
}
