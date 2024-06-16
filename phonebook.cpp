#include<iostream>
#include<fstream>
using namespace std;
class Phonebook 
{
   public : 
   string name,lname,cn1,cn2,email,label;
   void get()
   {
      cout<<"\n-----Enter Details-----";
      cout<<"\nEnter First Name  : ";
      cin>>name;
      cout<<"\nEnter Last Name : ";
      cin>>lname;
      cout<<"\nEnter Contact Number 1 : ";
      cin>>cn1;
      cout<<"\nEnter Contact Number 2 : ";
      cin>>cn2;
      cout<<"\nEnter Email ID : ";cin>>email;
      cout<<"\nLabel as : (Family/Work/Other) : ";cin>>label;
   }
   void display()
   {
       cout<<"\n-------------------------------------\n";
       cout<<"\nDetails : ";
       cout<<"\nFirst Name : "<<name;
       cout<<"\nLast Name : "<<lname;
       cout<<"\nContact Number 1 : "<<cn1;
       cout<<"\nContact Number 2 : "<<cn2;
       cout<<"\nEmail ID : "<<email;
       cout<<"\nLabel : "<<label;
       cout<<"\n-------------------------------------\n";
   }
};
Phonebook p;
void write()
{
    ofstream fout;
    fout.open("Contact.dat",ios::app|ios::binary);
    p.get();
    fout.write((char*)&p,sizeof(p));
    fout.close();
    cout<<"\nData Added Successfully...";
}
void read()
{
    ifstream fin;
    fin.open("Contact.dat",ios::in|ios::binary);
    while(fin.read((char*)&p,sizeof(p)))
    {
        p.display();
    }
    fin.close();
}
void searchbyname()
{
    fstream fin;
    int flag=0;string cname,slname;
    fin.open("Contact.dat",ios::in|ios::binary);
    cout<<"\nEnter First Name : ";
    cin>>cname;
    cout<<"\nEnter Last Name : ";
    cin>>slname;
    while(fin.read((char*)&p,sizeof(p)))
    {
        if((p.name==cname) && (p.lname==slname))
        {
            flag=1;
            cout<<"\nRecord Found";
            p.display();
            break;
        }
    }
    if(flag==0)
    {
        cout<<"\nRecord Not Found !!!";
    }
    fin.close();
}
void searchbynum()
{
    fstream fin;
    int flag=0;string cnum;
    fin.open("Contact.dat",ios::in|ios::binary);
    cout<<"\nEnter Contact Number : ";
    cin>>cnum;
    while(fin.read((char*)&p,sizeof(p)))
    {
        if((p.cn1==cnum) || (p.cn2==cnum))
        {
            flag=1;
            cout<<"\nRecord Found";
            p.display();
            break;
        }
    }
    if(flag==0)
    {
        cout<<"\nRecord Not Found !!!";
    }
    fin.close();
}
void update()
{
    int fl=0;string cname,uname,ucn1,ucn2,uemail,slname,ulname,ulabel;char ans;
    fstream f;
    f.open("Contact.dat",ios::out|ios::in|ios::binary);
    cout<<"\nEnter the First Name whose details you want to update : ";
    cin>>cname;
    cout<<"\nEnter the Last Name whose details you want to update : ";
    cin>>slname;
    while(f.read((char*)&p,sizeof(p)))
    {
        if((p.name==cname) && (p.lname==slname))
        {
            fl=1;
            cout<<"\nRecord Found";
            cout<<"\nDo you want to Update First Name ? (y/n) : ";cin>>ans;
            if(ans=='y')
            {
            cout<<"\nEnter the Updated First Name: ";cin>>uname;
            int t=f.tellp();
            p.name=uname;
            f.seekp(t-sizeof(p));
            f.write((char*)&p,sizeof(p));
            }
            cout<<"\nDo you want to Update Last Name ? (y/n) : ";cin>>ans;
            if(ans=='y')
            {
            cout<<"\nEnter the Updated Last Name: ";cin>>ulname;
            int t=f.tellp();
            p.lname=ulname;
            f.seekp(t-sizeof(p));
            f.write((char*)&p,sizeof(p));
            }
            cout<<"\nDo you want to Update Contact Number 1 ? (y/n) : ";cin>>ans;
            if(ans=='y')
            {
            cout<<"\nEnter the Updated Contact Number 1 : ";cin>>ucn1;
            int t=f.tellp();
            p.cn1=ucn1;
            f.seekp(t-sizeof(p));
            f.write((char*)&p,sizeof(p));
            }
            cout<<"\nDo you want to Update Contact Number 2 ? (y/n) : ";cin>>ans;
            if(ans=='y')
            {
            cout<<"\nEnter the Updated Contact Number 2 : ";cin>>ucn2;
            int t=f.tellp();
            p.cn2=ucn2;
            f.seekp(t-sizeof(p));
            f.write((char*)&p,sizeof(p));
            }
            cout<<"\nDo you want to Update Email ID ? (y/n) : ";cin>>ans;
            if(ans=='y')
            {
            cout<<"\nEnter the Updated Email ID : ";cin>>uemail;
            int t=f.tellp();
            p.email=uemail;
            f.seekp(t-sizeof(p));
            f.write((char*)&p,sizeof(p));
            }
            cout<<"\nDo you want to Update Label ? (y/n) : ";cin>>ans;
            if(ans=='y')
            {
            cout<<"\nEnter the Updated Label : ";cin>>ulabel;
            int t=f.tellp();
            p.label=ulabel;
            f.seekp(t-sizeof(p));
            f.write((char*)&p,sizeof(p));
            }
            cout<<"\nData Updated Successfully.....";
            break;
        }
    }
    if(fl==0)
    {
        cout<<"\nRecord Not Found !!!";
    }
    f.close();
}
void delete_specific()
{
    int fl=0;string cname,clname;
    fstream f;
    f.open("Contact.dat",ios::in|ios::binary);
    ofstream fout;
    fout.open("new.dat",ios::app|ios::binary);
    cout<<"\nEnter First Name whose contact you want to delete : ";
    cin>>cname;
    cout<<"\nEnter Last Name whose contact you want to delete : ";
    cin>>clname;
    while(f.read((char*)&p,sizeof(p)))
    {
        if((p.name!=cname) && (p.lname!=clname))
        {

            fout.write((char*)&p,sizeof(p));
        }
        else{
            fl=1;
        }
    }
    f.close();
    fout.close();
    remove("Contact.dat");
    rename("new.dat","contact.dat");
    cout<<"\nSuccessful";

}
int main()
{
    int ch;
    remove("Contact.dat");
    while(1)
    {
        cout<<"\nEnter : \n1.Add Contact\n2.Display All Contacts\n3.Search Contacts by Name\n4.Search Contact by Numbers\n5.Update Contact\n6.Delete Contact\n7.EXIT";
        cout<<"\nEnter Your Choice : ";
        cin>>ch;
        switch(ch)
        {
            case 1:write();break;
            case 2:read();break;
            case 3:searchbyname();break;
            case 4:searchbynum();break;
            case 5:update();break;
            case 6:delete_specific();break;      
            case 7:exit(0);
            default:cout<<"\nInvalid Choice";
        }
    }
}