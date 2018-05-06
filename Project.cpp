#include<iostream>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<vector>
#include <string>
using namespace std;

class product
{
	char cat_name[50], pro_name[50],item_name[50];
	int item_id,price,quantity;
	public:
	/*product()
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
	void del_cat(char[]);
	void del_pro(char[],char []);
	void del_item(char[],char []);
	void update();
	void List(char[],int);
	char * getiname();
	char * getcname();
	char * getpname();
	int getid();
	int getprice();
	int getquant();
	int upd_quant(int);
	void buyitem(int);
	void upd_stk(int,int);
	void readstkdet(char [],char [],char[],int);
};
void product::create_cat(char fcn[])
{
	strcpy(cat_name,fcn);
	fstream fout;
	fout.open("category.txt",ios::binary|ios::app);
	fout.write((char*)this,sizeof(*this));
	fout.close();
}
void product::create_pro(char fpn[])
{
	char cn[50];
	List("category",1);
	cout<<endl<<"Enter category to add product in: ";
	cin>>cn;
	strcpy(cat_name,cn);
	strcpy(pro_name,fpn);
	add(cat_name);
}
void product::create_item(char itm[])
{
	int q,id,p;
	char cn[50],pn[50];

	List("category",1);
	cout<<endl<<"Enter category to add product in: ";
	cin>>cn;
	strcpy(cat_name,cn);

	List(cat_name,2);
	cout<<endl<<"Enter product to add item in: ";
	cin>>pn;
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

	//cout<<endl<<item_id<<"\t"<<price<<"\t"<<quantity;

	add(pro_name);

	/*cout<<endl<<cat_name<<" "<<cn;
	cout<<endl<<pro_name<<" "<<pn;
	cout<<endl<<item_name<<" "<<itm;

	cout<<endl<<"-->"<<cat_name<<endl<<"--> "<<pro_name<<endl;
	cout<<endl<<"--> "<<item_name<<endl<<"--> "<<item_id;
	cout<<endl<<"--> "<<price;
	cout<<endl<<"--> "<<quantity;*/
}
void product::add(char val[])
{
	char temp[50];
	strcpy(temp,val);
	strcat(temp,".txt");

	ofstream fout;
	fout.open(temp,ios::binary|ios::app);
	fout.write((char*)this,sizeof(*this));
	fout.close();
}
void product::List(char fn[],int f)
{
	int cnt=1;
	char temp[50];
	strcpy(temp,fn);

	ifstream fin;
	strcat(temp,".txt");
	fin.open(temp,ios::binary);

	if(f==1)
	cout<<endl<<"The categories of products available are: ";
	if(f==2)
	cout<<endl<<"The types of products available in this category are: ";
	if(f==3)
	{	cout<<endl<<"The items available in this type of products are: ";
		cout<<endl<<"SrNo\tItemId\tItemName\tPrice\tStockQuantity";
	}

	while(fin.read((char*)this,sizeof(*this)))
	{
		if(f==1)
		cout<<endl<<cnt++<<". "<<cat_name;
		if(f==2)
		cout<<endl<<cnt++<<". "<<pro_name;
		if(f==3)
		{
			cout<<endl<<"-->"<<cnt++<<"\t"<<item_id<<"\t"<<item_name<<"\t"<<price<<"\t"<<quantity;
		}
	}
	fin.close();
}
void product::update()
{
	char cn[50],pn[50];
	int id,n,p,q;
	List("category",1);
	cout<<endl<<"\nEnter category to update: ";
	cin>>cn;
	List(cn,2);
	cout<<"\nEnter product name : ";
	cin>>pn;
	//cout<<" ";
	List(pn,3);

	cout<<"\nEnter id of item to be updated.: ";
	cin>>id;
	strcat(pn,".txt");

    /*	item_id=this->item_id;
	price=this->price;
	quantity=this->quantity;    */

	//cout<<cat_name<<endl<<pro_name<<endl<<price<<quantity<<item_id;

	ifstream fin;
	ofstream fout;
	fin.open(pn,ios::binary);
	fout.open("temp1.txt",ios::binary|ios::app);
	while(fin.read((char*)this,sizeof(*this)))
	{
		if(item_id!=id)
		{
		    fout.write((char*)this,sizeof(*this));
		}
		else
		{
		    cout<<"\n1) update price\n2) update stock";
		    cin>>n;
		    if(n==1)
		    {
			cout<<"Enter updated price";
			cin>>p;
			price=p;
			cout<<"called";
		    }
		    if(n==2)
		    {
			cout<<"Enter updated stock quantity: ";
			cin>>q;
			quantity=q;
		    }
			fout.write((char*)this,sizeof(*this));
		    List(pn,2);
		}
	}
	fout.close();
	fin.close();
	remove(pn);
	rename("temp1.txt",pn);
}
void product::del_cat(char fn[])
{
	char temp[50];
	//remove items from the product
	strcpy(temp,fn);
	strcat(temp,".txt");
	ifstream fin;
	fin.open(temp,ios::binary);
	while(fin.read((char*)this,sizeof(*this)))
	{
		char prod[50];
		strcpy(prod,pro_name);
		strcat(prod,".txt");
	    remove(prod);
	}
	fin.close();
	remove(temp);

	//char catnm[50];
	//fstream fin;
	ofstream fout;
	fin.open("category.txt",ios::binary);
	fout.open("updat.txt",ios::binary|ios::app);
	while(fin.read((char*)this,sizeof(*this)))
	{
		if(strcmp(cat_name,fn)==0)
			continue;
		fout.write((char*)this,sizeof(*this));
	}
	fout.close();
	fin.close();
	//rewrite updated contents to file
	remove("category.txt");
	rename("updat.txt","category.txt");
}
void product::del_pro(char pn[],char ct[])
{
	char temp[50];
	//remove items from the product
	strcpy(temp,pn);
	strcat(temp,".txt");
	remove(temp);

	//update cat file
	strcpy(temp,ct);
	strcat(temp,".txt");

	ifstream fin;
	fin.open(temp,ios::binary);

	ofstream fout;
	fout.open("updpro.txt",ios::binary|ios::app);

	while(fin.read((char*)this,sizeof(*this)))
	{
		if(strcmp(pro_name,pn)==0)
			continue;
		fout.write((char*)this,sizeof(*this));
	}
	fout.close();
	fin.close();
	//rewrite updated contents to file
	remove(temp);
	rename("updpro.txt",temp);
}
void product::del_item(char itm[],char pn[])
{
	//prev file
	char temp[50];
	strcpy(temp,pn);
	strcat(temp,".txt");

	ifstream fin;
	fin.open(temp,ios::binary);
	ofstream fout;
	fout.open("upditm.txt",ios::binary|ios::app);
	while(fin.read((char*)this,sizeof(*this)))
	{
		if(strcmp(item_name,itm)==0)
			continue;
		fout.write((char*)this,sizeof(*this));
	}
	fout.close();
	fin.close();
	//rewrite updated contents to file
	remove(temp);
	rename("upditm.txt",temp);
}
char * product::getiname()
{	return item_name;
}
char * product::getcname()
{	return cat_name;
}
char * product::getpname()
{	return pro_name;
}
int product::getquant()
{	return quantity;
}
int product::getprice()
{	return price;
}
int product::getid()
{	return item_id;
}
int product::upd_quant(int x)
{   if(  (x>0 && (quantity-x)>=0) || x<0 )
	{
		quantity-=x;
		upd_stk(item_id,quantity);
		return x;
	}
	else if( x>0 && (quantity-x)<=0 && quantity>0)
	{	int z=quantity;
		quantity=0;
		upd_stk(item_id,quantity);
		return (z);
	}
	else if(quantity==0)
	{
		cout<<"\nItem is out of stock.Plz come back after 2 days.Sorry for the inconvinience.";
		return -999;
	}
}
void product::upd_stk(int idn,int qtn)
{
	char tempr[50];
	strcpy(tempr,pro_name);
	strcat(tempr,".txt");

	ifstream fin;
	ofstream fout;
	fin.open(tempr,ios::binary);
	fout.open("updstk1.txt",ios::binary|ios::app);
	while(fin.read((char*)this,sizeof(*this)))
	{
		if(item_id==idn)
		{
		    this->quantity=qtn;
		}
		fout.write((char*)this,sizeof(*this));
	}
	fout.close();
	fin.close();
	remove(tempr);
	rename("updstk1.txt",tempr);
	//might have to store values of the obj prior to calling this function,
	//at the start of this func by storing values in temp variables
}
void product::buyitem(int x)
{
    quantity=x;
}
void product::readstkdet(char *cnm,char *pnm,char *inm,int tid)
{
	char tmp[50];
	int qt,pric;
	strcpy(cat_name,cnm);
	strcpy(pro_name,pnm);
	strcpy(item_name,inm);

	strcpy(tmp,pnm);
	strcat(tmp,".txt");

	ifstream fin;
	fin.open(tmp,ios::binary);
	while(fin.read((char*)this,sizeof(*this)))
	{
		if(item_id==tid)
		{
		    qt=quantity;
			pric=price;
			break;
		}
	}
	fin.close();

	strcpy(cat_name,cnm);
	strcpy(pro_name,pnm);
	strcpy(item_name,inm);
	item_id=tid;
	quantity=qt;
	price=pric;

}


class user;
class consumer;
class admin;
class cart;
class order;
class shipping;

class cart
{
	vector <product> lst;
	float totalp;

	public:
	void writecart(int);
	void readcart(int);
	void addtocart(product,int);
	void updatecart(int,int,int);
	void delfromcart(int,int);
	void displaycart();
	void comptot();
	void disptot();
	product *getpdet(int);
};
void cart::addtocart(product tp,int id)
{
	lst.push_back(tp);
	writecart(id);
	cout<<"\nCart Updated";
	displaycart();
}
void cart::readcart(int id)
{
	string tmp;
    product *pt;

	tmp="scart";
	tmp+=char(id);
	tmp+=".txt";

    const char *tmpid = tmp.c_str();

	ifstream fin;
	fin.open(tmpid,ios::binary);
	while( fin.read( (char *) pt, sizeof(*pt) ))
	{
		lst.push_back(*pt);
	}
	fin.close();
	cout<<"\nYour Cart :";
	displaycart();
}
void cart::writecart(int id)
{
	string tmp;
    //product *pt;

	tmp="scart";
	tmp+=char(id);
	tmp+=".txt";

    const char *tmpid = tmp.c_str();

	ofstream fout;
	fout.open(tmpid,ios::binary);
	for(int i=0;i<lst.size();i++)
	{
	    //fout.write((char *) lst[i] , sizeof(*lst[i]) );
		fout.write((char *) this , sizeof(*this) );
	}
	fout.close();
}
void cart::displaycart()
{
	int cnt=0;
	cout<<"Your Cart details are: ";
	cout<<endl<<"SrNo\tItemId\tItemName\tPrice\tQuantity";
	int i;
	for(i=0;i<lst.size();i++)
	{
		cout<<endl<<"-->"<<cnt++<<"\t"<<lst[i].getid()<<"\t"<<lst[i].getiname()<<"\t"<<lst[i].getprice()<<"\t"<<lst[i].getquant();
	}
	comptot();
	disptot();
}
void cart::comptot()
{
	totalp=0;
	int i;
	for(i=0;i<lst.size();i++)
	{
		totalp+= (lst[i].getquant())*(lst[i].getprice());
	}
}
void cart::disptot()
{	cout<<"\nYour total is : Rs. "<<totalp;
}
void cart::delfromcart(int itemid,int id)
{
	int i,cnt=0;
	for(i=0;i<lst.size();i++)
	{
		if(lst[i].getid()==itemid)
			break;
		cnt++;
	}
	lst.erase(lst.begin()+cnt);
	writecart(id);
	cout<<"\nCart Updated";
	displaycart();
}
void cart::updatecart(int id1,int qt1,int id)
{
	int i,cnt=0;
	for(i=0;i<lst.size();i++)
	{
		if(lst[i].getid()==id1)
			break;
		cnt++;
	}
	lst[cnt].buyitem(qt1);
	writecart(id);
	cout<<"\nUpdated Cart:";
	displaycart();
}
product * cart::getpdet(int ids)
{
	int i;
	product *ptmp;
	for(i=0;i<lst.size();i++)
	{
		if(lst[i].getid()==ids)
			ptmp=&lst[i];
	}
	return ptmp;
}


class order
{
    //shippinginfo sid;
	//consumer *cid;//Product *prid[10];
	int num;

	public:
	/*Order(shippinginfo *shid)//,consumer *custid,Product *prodid[10],int n)
	{
		 num=n;
		oid=ord;sid=shid;cid=custid;
	}*/
	/*void printdetails()
	{
		cout<<"\nconsumer Details:";cid.printdisplay();
		cout<<"\nOrder Details:";   oid.printdisplay();
		cout<<"\nShippingDetails:"; sid.printdisplay();
	}*/
	void placeorder(int id)
	{
		string tmp;
		tmp="scart";
		tmp+=char(id);
		tmp+=".txt";
		const char *tmpid = tmp.c_str();

		string tmp2;
		tmp2="order";
		tmp2+=char(id);
		tmp2+=".txt";
		const char *tmpid2 = tmp2.c_str();

		ifstream fin;
		ofstream fout;
		fin.open(tmpid,ios::binary);
		fout.open(tmpid2,ios::binary | ios::app);

		while(fin.read((char *)this, sizeof(*this)))
		{
			fout.write((char *)this , sizeof(* this));
		}
		fin.close();
		fout.close();
	}
	/*~Order()
	{	cout<<"\n Order with ID "<<oid.orderid<<" deleted";
		delete cid;
		delete oid;
		delete cid;
	}*/
};
/*
class OrderDetails
{
	float unitcost,amt;
	int orderid,quantity;

	public:
	OrderDetails(Product proid)
	{
		orderid=00001+(int)(rand()%100000);
		getunitcost(this,proid);
		inp();
	}
	void getunitcost(OrderDetails oid,Product proid);
	void inp()
	{       cout<<"\nenter the number of units to be ordered:";
		cin>>quantity;
		amt=unitcost*quantity;
	}
	void printdetails()
	{	cout<<"\n";
	}
       	void calcprice()
	{       amt=unitcost*quantity;
	}
};
friend void getunitcost(Orderdetails oid,Product proid)
{
		oid.unitcost=proid.price;
}
*/

class shipping
{
	int sid,days;
	char dest[50],addr[100];
	long int pincode;
	static int sidcnt;
	float scost;//shipping n total cost

	public:
	/*ShippingInfo(float amt)
	{
		scost=0.1*amt;
		tcost=amt+scost;
		sid=00001+(int)(rand()%100000);
	}*/
	void input(int price)
	{
		++sidcnt;
		sid=sidcnt;

		cout<<"\nEnter the Address   :";
		cin>>addr;
		cout<<"Enter the Destination :";
		cin>>dest;
		cout<<"Enter the Pincode     :";
		cin>>pincode;

		days=4;
		scost=200;
		if(price>=6000)
		{
			days=2;
			scost=150;
		}
	}
	int getscost(){return scost;}
	void printdetails()
	{
		cout<<"\n\t\t\tShippingId   : "<<sid;
		cout<<"\n\t\t\tShippingCost : "<<scost;
		cout<<"\n\t\t\tAddress      : "<<addr;
		cout<<"\n\t\t\tDestination  : "<<dest;
		//cout<<"\n"<<sid<<"\t"<<scost<<"\t"<<addr<<"\t"<<dest<<
		cout<<"\nOrder will arrive in "<<days<<" days";
	}
	void writeship()
	{
        string tmp;
		tmp="ship";
		tmp+=char(sid);
		tmp+=".txt";
		const char *tmpid = tmp.c_str();

        ifstream fin;
        ofstream fout;
	    fin.open(tmpid,ios::binary|ios::app);
        while(fin.read((char *)this,sizeof(*this)) )
        {
            fout.write((char *)this,sizeof(*this));
        }
        fout.close();
        fin.close();
	}
};
int shipping::sidcnt=0;

class user
{
	protected:
	char username[100];
	char password[100];
	char email[100];

	public:
	void signup1(char*, char*,char *);
	void SignIn(char*, char*,int);
	//virtual void writedata();
	//virtual void dispdet();
};
void user::signup1(char *un,char *pass,char *eml)
{	strcpy(username,un);
	strcpy(password,pass);
	strcpy(email,eml);
}
void user::SignIn(char *usrnm,char *pass,int typ)
{
	ifstream fin;
	int cnt=0,f=1;
	char temp[100];
	int id,pinn;
	char crdno[16];

	if(typ==0)
	{   strcpy(temp,"custdet.txt");
        fin.open(temp,ios::binary);
        while(!fin.eof())
        {
            fin>>id>>username>>password>>email>>crdno>>pinn;
            // cnt=0;
            if((strcmp(username,usrnm))==0)
            {	f=1;
                    if(strcmp(password,pass)==0)
                    {
                        cout<<endl<<"You have successfully logged in";
                        break;
                    }
                    else
                    {
						cout<<endl<<"Sorry password is incorrect!please enter carefully!";
						break;
                    }
            }
		}
	}
	else if(typ==1)
    {
			if((strcmpi("admin",usrnm))==0)
            {	f=1;
                    if(strcmpi("admin",pass)==0)
                    {
                        cout<<endl<<"You have successfully logged in as admin";
                    }
                    else
                    {
					cout<<endl<<"Sorry password is incorrect!";
                    }
            }
    }
	if(f==0)
	{
		cout<<endl<<"No such username exists";
	}
}


class consumer:public user
{
	char card[16];
	int pin,cid;
	static int custid;
	product *pr;
	cart sc;
	order ord;

	public:
	void signup(char*, char*,char *,char *,int);
	void writedata();
	void dispdet();
	void getcatalogue(product &p1){pr=&p1;}
	void usecatalogue();
	void shopper();
	void cartudp();

};
int consumer::custid=0;
void consumer::signup(char *un,char *pass,char *eml,char *crd,int pinno)
{	signup1(un,pass,eml);
	strcpy(card,crd);
	pin=pinno;
	++cid;
	cid=custid;
	writedata();
}
void consumer::writedata()//left to see what details are stored
{
	ofstream fout;
	fout.open("custdet.txt",ios::binary | ios::app);
	fout<<"\n"<<cid<<username<<"\t"<<password<<"\t"<<email<<"\t"<<card<<"\t"<<pin;
	fout.close();
}
void consumer::dispdet()
{
		cout<<"\nYour Details are as follows:\n ";
		cout<<"CustId    : "<<cid<<endl;
		cout<<"Username  : "<<username<<endl;
		cout<<"Password  : "<<password<<endl;
		cout<<"Email     : "<<email<<endl;
		cout<<"CreditCard: "<<card<<endl;
		cout<<"Pin       : "<<pin<<endl;
}
void consumer::usecatalogue()
{
	char c_n[50],p_n[25],i_n[25];
	int update=0;

	do
	{

		cout<<"------consumer------"; //to be set by iomanip
		cout<<"1. See the Catalouge\n2. Shopping\n3. View your cart \n4. Update your cart";
		cout<<"\n5. Place Order\n6. Order History\n7. Logout";
		cin>>update;
		//or should there be a special key which adds item to cart while seeing catalogue
		switch(update)
		{
			case 1: pr->List("category",1);
					cout<<endl<<"Enter category name: ";
					cin>>c_n;
					pr->List(c_n,2);
					cout<<endl<<"Enter product name: ";
					cin>>p_n;
					pr->List(p_n,3);
					break;
			case 2: shopper();
					break;

			case 3: sc.displaycart();
					break;

			case 4: cartudp();
					break;

			case 5: ord.placeorder(cid);
					break;
			case 6:
					break;
			case 7:
					break;
		}
	}while(update!=7);
}
void consumer::shopper()
{
	int k,ids,qnt;
	char c_n[50],p_n[25];
	product tmp;

	tmp.List("category",1);
	cout<<endl<<"Enter category name: ";
	cin>>c_n;
	tmp.List(c_n,2);
	cout<<endl<<"Enter product name: ";
	cin>>p_n;
	tmp.List(p_n,3);
	cout<<"\nDo you want to add any item to your cart?(1=yes,0=no)";
	cin>>k;
	if(k==1)
	{
		do
		{	cout<<"\nEnter the id of the item you want to purchase(-1 to stop)";
			cin>>ids;
			if(ids==-1)
				break;
			cout<<"\nEnter the no. of these items you want to purchase(less than stock)";
			cin>>qnt;
			//tmp=temp;//temp????
			tmp.buyitem(qnt);
			sc.addtocart(tmp,cid);
		}while(ids!=-1);
	}
	else
			cout<<"please surf some other category";
}
void consumer::cartudp()
{
	int k,ids,qnt,x;
	product *tmp;
	do
	{
		sc.displaycart();
		cout<<"\nDo you want to update your cart?(1 to update quantity,0 to delete item,-1 to exit)";
		cin>>k;

		if(k==-1)
			break;
		else if(k==1)
		{
			do
			{	cout<<"\nEnter the id of the item you want to update the quantity(-1 to stop)";
				cin>>ids;
				if(ids==-1)
					break;

				tmp=sc.getpdet(ids);

				cout<<"\nEnter the updated quantity ";
				cin>>qnt;
				x=tmp->getquant();
				x=qnt-x;//pass it directly into stock and negate and pass in product
				//x is extra no. req by the consumer

				pr->readstkdet(tmp->getcname(),tmp->getpname(),tmp->getiname(),ids);//read stock details

				int stats=pr->upd_quant(-x);//update stock

				/*if(stats==-x)
				{	cout<<x<<" extra number of items have been added to your cart";
					tmp.buyitem(qnt+x);
					sc.updatecart(ids,stats,cid);
				}				else*/
				if(stats==x)
				{	cout<<x<<" extra number of items have been removed from your cart";
					sc.updatecart(ids,qnt-stats,cid);
				}
				else if(stats==-999)
				{	cout<<"Extra requested items are out of stock";
				}
				else
				{
					cout<<stats<<" extra number of available items have been added to your cart";
					sc.updatecart(ids,qnt+stats,cid);
				}
			}while(ids!=-1);
		}
		else if(k==0)
		{
			do
			{	cout<<"\nEnter the id of the item you want to delete from your cart(-1 to stop)";
				cin>>ids;
				if(ids==-1)
					break;
				tmp=sc.getpdet(ids);
				x=tmp->getquant();
				pr->readstkdet(tmp->getcname(),tmp->getpname(),tmp->getiname(),ids);//read stock details
				pr->upd_quant(-x);//update stock
				sc.delfromcart(ids,cid);
			}while(ids!=-1);
		}
	}while(k!=-1);
}


class admin:public user
{
	int aid;
	static int admid;
	product *pr;

	public:
	void signup(char*,char*,char *);
	void writedata();
	void dispdet();
	void setcatalogue(product &p1){pr=&p1;}
	void updatecatalogue();
};
int admin::admid=0;
void admin::signup(char *un,char *pass,char *eml)
{	signup1(un,pass,eml);
	admid++;
	aid=admid;
	writedata();
}
void admin::writedata()//check all what will b stored in file
{
	ofstream fout;
	fout.open("admindet.txt",ios::binary | ios::app);
	fout.write((char*)this,sizeof(*this));
	fout.close();
}
void admin::dispdet()
{
		cout<<"\nYour Details are as follows:\n ";
		cout<<"AdminId   : "<<aid<<endl;
		cout<<"Username  : "<<username<<endl;
		cout<<"Password  : "<<password<<endl;
		cout<<"Email     : "<<email<<endl;
}
void admin::updatecatalogue()
{
	char c_n[50],p_n[25],i_n[25];
	int update;

	do
	{
		cout<<endl<<endl<<"\t\t----------------ADMIN MODE-------------------\n";
		cout<<endl<<"\n\t\t\t1) Add a category\n\t\t\t2) Add a product\n\t\t\t3) Add a item\n\t\t\t4) Display Item Details\n";
		cout<<"\t\t\t5. Update Item Details\n\t\t\t6. Delete a category\n\t\t\t7. delete a product\n\t\t\t8. Delete a item\n";
		cout<<"\t\t\t9. LogOut\n";
		cin>>update;
		switch(update)
		{
			case 1: cout<<endl<<"Enter category name: ";
					cin>>c_n;
					pr->create_cat(c_n);
					break;
			case 2: cout<<endl<<"Enter product to add: ";
					cin>>p_n;
					//cout<<endl<<"called";
					pr->create_pro(p_n);
					break;
			case 3: cout<<endl<<"Enter item to add: ";
					cin>>i_n;
					pr->create_item(i_n);
					break;
			case 4: pr->List("category",1);
					cout<<endl<<"Enter category name: ";
					cin>>c_n;
					pr->List(c_n,2);
					cout<<endl<<"Enter product name: ";
					cin>>p_n;
					pr->List(p_n,3);
					break;
			case 5: pr->update();
					break;
			case 6:	pr->List("category",1);
					cout<<endl<<"Enter category to be deleted: ";
					cin>>c_n;
					//present
					//pr->List("category",1);
					pr->del_cat(c_n);
					//updated category
					//pr->List("category",1);
					break;
			case 7:  pr->List("category",1);
					cout<<endl<<"Enter category name: ";
					cin>>c_n;
					pr->List(c_n,2);
					cout<<endl<<"Enter product name: ";
					cin>>p_n;
					//prev file cont
					//pr->List(c_n,2);
					pr->del_pro(p_n,c_n);
					//updated category
					//pr->List(c_n,2);
					break;
			case 8: pr->List("category",1);
					cout<<endl<<"Enter category name: ";
					cin>>c_n;
					pr->List(c_n,2);
					cout<<endl<<"Enter product name: ";
					cin>>p_n;


					pr->List(p_n,3);
					cout<<endl<<"Enter item name: ";
					cin>>i_n;
					//original cont
					//pr->List(p_n,3);
					pr->del_item(i_n,p_n);
					//updated
					//pr->List(p_n,3);
					break;
			case 9: break;
		}
	}while(update!=9);
}



int main()
{
	char c_n[50],p_n[25],i_n[25];
	char usnm[100],pass[100],crd[16],eml[100];
	int pinno,choice;
	int typ=-1;
	consumer c1;
    admin a1;
	product au;
    cout<<"\t----------------WELCOME TO ONLINE SHOPPING CENTER-----------------";
	do
	{
	   typ=-1;
	   cout<<endl<<"\n\t\t\t1. Admin Sign up\n\t\t\t2. Admin Login\n\t\t\t3. Customer Sign up\n";
	   cout<<"\t\t\t4. Customer Login\n\t\t\t5. Exit";//\n5. Display Admin Details
	   cin>>choice;
	   switch(choice)
	   {
		case 1: cout<<"Enter username: ";
				cin>>usnm;
				cout<<"Enter password: ";
				cin>>pass;
				cout<<"Enter email id: ";
				cin>>eml;
				a1.signup(usnm,pass,eml);
				typ=1;
				break;
		case 2: cout<<"Enter username: ";
				cin>>usnm;
				cout<<"Enter password: ";
				cin>>pass;
				a1.SignIn(usnm,pass,1);
				typ=1;
				break;
		case 3: cout<<"Enter username: ";
				cin>>usnm;
				cout<<"Enter password: ";
				cin>>pass;
				cout<<"Enter email id: ";
				cin>>eml;
				cout<<"Enter credit card number: ";
				cin>>crd;
				cout<<"Enter pin: ";
				cin>>pinno;
				c1.signup(usnm,pass,eml,crd,pinno);
				typ=0;
				break;
		case 4: cout<<"Enter username: ";
				cin>>usnm;
				cout<<"Enter password: ";
				cin>>pass;
				c1.SignIn(usnm,pass,0);
				typ=0;
				break;
		/*case 5: u.display();
				break;*/
		case 6: break;
	   }
	}while(choice==1 ||choice==3);
    /*
	int jkl;
	cout<<"\nenter valuee";
	cin>>jkl;
	int update;
    */
	//a1.setcatalogue(au);

	if(typ==1)
	{
		a1.updatecatalogue();
	}
	else if(typ==0)  // when  consumer
	{
		c1.usecatalogue();
	}
	else if(typ==-1)
	{	cout<<"\nPlz sign in first";

	}

	return 0;
}

