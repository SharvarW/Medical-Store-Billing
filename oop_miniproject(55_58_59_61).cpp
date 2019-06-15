/*
---------------OOP MINIPROJECT--------------
--------------------------------------------
TOPIC: MEDICAL STORE MANAGEMENT
--------------------------------------------

PROJECT BY:
	NAMRATA SONAWANE SE-A(55)
	YASHASHREE SURYAWANSHI SE-A(58)
	OJASWINI TANK SE-A(59)
	SHARVARI WAGH SE-A(61)
---------------------------------------------
*/


#include<iostream>				//header files
#include<fstream>
#include<string.h>

using namespace std;

class Medicine
{
    public:
        int medicine_no;
        int rack_no;
	char name[20];
	int stock;
	int quantity;
	float cost;
	int dde,mme,yye;

	Medicine()
	{
		medicine_no=0;
		rack_no=0;
		strcpy(name," ");
		stock=0;
		quantity=0;
		dde=mme=yye=0;
	}
	int return_medicine()
	{
		return medicine_no;
	}

        void getdata()
        {
            l:cout<<"\nEnter Medicine ID :";
            cin>>medicine_no;
            fstream f;
            Medicine M;
            int medid,pos;
            char found = 'f';
            f.open("Medical.dat",ios::in|ios::binary);
            medid=medicine_no;
            f.seekg(0);
            while(!f.eof())
            {
                pos=f.tellg();
                f.read((char *)&M, sizeof(M));
                if(M.medicine_no == medid)
                {
                    found = 'y';
                    break;
                }
            }
            if(found == 'y')
            {
                cout<<"\nEntered medicine ID already exist!!\n";
                goto l;
            }
            f.close();

            cout<<"\nEnter Rack Number :";
			cin>>rack_no;
			cout<<"\nEnter Name of medicine :";
			cin>>name;
			cout<<"\nEnter cost :";
			cin>>cost;
			cout<<"\nEnter quantity available :";
			cin>>stock;
			cout<<"\nEnter expiry date :"<<endl;
			cout<<"Date : "; cin>>dde;
            cout<<"Month: "; cin>>mme;
            cout<<"Year : "; cin>>yye;

        }
//------------------------------------------------------------------------------------     
        void get_data()
        {
        	cout<<"\nEnter Medicine ID :";
            cin>>medicine_no;
            cout<<"\nEnter Rack Number :";
			cin>>rack_no;
			cout<<"\nEnter Name of medicine :";
			cin>>name;
			cout<<"\nEnter cost :";
			cin>>cost;
			cout<<"\nEnter quantity available :";
			cin>>stock;
			cout<<"\nEnter expiry date :"<<endl;
			cout<<"Date : "; cin>>dde;
            cout<<"Month: "; cin>>mme;
            cout<<"Year : "; cin>>yye;
        }
//------------------------------------------------------------------------------------
        void putdata()
        {
            cout<<"\n"<<medicine_no<<"\t"<<rack_no<<"\t"<<name<<"\t"<<stock<<"\t"<<cost<<"\t"<<dde<<"/"<<mme<<"/"<<yye;

        }
//------------------------------------------------------------------------------------
        void AddRecord()
        {

            fstream f;
            Medicine M;
            f.open("Medical.dat",ios::app|ios::binary);
            M.getdata();
            f.write( (char *) &M, sizeof(M) );
            f.close();
        }
//------------------------------------------------------------------------------------
        void Display()
        {
            fstream f;
            Medicine M;
            f.open("Medical.dat",ios::in|ios::binary);
            cout<<"\nID\tRN\tname\tst\tcost\tdate\n";
            while( (f.read((char*)&M,sizeof(M))) != NULL )
                M.putdata();
            f.close();
        }
//------------------------------------------------------------------------------------
       void searchID()
        {
            fstream f;
            Medicine M;
            int medid,pos;
            char found = 'f';
            f.open("Medical.dat",ios::in|ios::binary);
            cout<<"\nEnter Medicine ID to search :";
            cin>>medid;
            f.seekg(0);
            while(!f.eof())
            {
                pos=f.tellg();
                f.read((char *)&M, sizeof(M));
                if(M.medicine_no == medid)
                {
                    cout<<"\nID\tRN\tname\tst\tdate\n";
                    M.putdata();
                    f.seekg(pos);
                    found = 'y';
                    break;
                }
            }
            if(found == 'f')
            {
                cout<<"\nRecord not found in the file..!!\n";
            }
            f.close();
        }
//-------------------------------------------------------------------------------------------

      	void deleteMedID()
        {
            fstream f1,f2;
            Medicine M1,M2;
            int medid,pos;
            char found = 'f';
            f1.open("Medical.dat",ios::binary | ios::in);
            f2.open("temp.dat",ios::out|ios::binary);
            cout<<"\nEnter Medicine ID to delete :";
            cin>>medid;
            while(f1.read((char*)&M1, sizeof(M1)))
            {
                if( M1.return_medicine() != medid)
                {

                    f2.write((char*)&M1, sizeof(M1));
                    found='y';
                }
            }
            f1.close();
            f2.close();
            remove("Medical.dat");
            rename("temp.dat", "Medical.dat");
        }
//---------------------------------------------------------------------------------------------
        void modify_record()
        {
            fstream f;
            f.open("Medical.dat",ios::in | ios::out);
            Medicine M;
            int medid,pos;
            cout<<"\nEnter Medicine ID to modify :";
            cin>>medid;
            while(!f.eof())
            {
                pos=f.tellg();
                f.read((char*)&M, sizeof(M));
                if(M.medicine_no == medid)
                {
                    f.seekg(pos);
                    cout << "\nEnter the new details of medicine";
                    M.get_data();
                    f.write((char*)&M, sizeof(M));
                    break;
                }
            }

            f.close();
        }
//-------------------------------------------------------------------------------------------
        void update(int x,int y)
        {
            fstream f;
            f.open("Medical.dat",ios::in | ios::out);
            Medicine M;
            int medid,pos;
            while(!f.eof())
            {
                pos=f.tellg();
                f.read((char*)&M, sizeof(M));
                if(M.medicine_no == x)
                {
                    M.stock = M.stock - y;
                    f.seekp(pos);
                    f.write((char*)&M, sizeof(M));
                    break;
                }
            }

            f.close();
        }
//----------------------------------------------------------------------------------------------
         void bill()
         {
         	fstream f;
         	int i=0,j,qty,sum=0;
         	char ans;
            Medicine M;
            Medicine M1[100];
            int medid,pos;
            char found = 'f';
            f.open("Medical.dat",ios::in|ios::binary);
            do
            {

                cout<<"\nEnter Medicine ID to add in bill :";
                cin>>medid;
                f.seekg(0);
                while(!f.eof())
                {
                    pos=f.tellg();
                    f.read((char *)&M, sizeof(M));
                    if(M.medicine_no == medid)
                    {
                        f.seekg(pos);
                        found = 'y';
                        break;
                    }
                }
	        if(found == 'f')
	        {
	                cout<<"\nNo such medicine.!!\n";
	        }
	        else
	        {
	           cout<<"\nEnter quantity";
	           cin>>qty;
	           if(qty>M.stock)
	           {
	            	cout<<"Sorry quantity is "<<M.stock;
                   }
                   else
                   {
                   	M1[i]=M;
                        M1[i].quantity=qty;
                        update(medid,qty);
                   	
                   }
                }
	        cout<<"Do you want to add more?(y/n)";
	        cin>>ans;
	         i++;
            	}while(ans=='y');
	        f.close();
	        cout<<"\n Do you want to print the bill?(y/n)";
	        cin>>ans;
	         if(ans=='y')
	         {
	          	cout<<"\n___________________________________________";
			cout<<"\n         XXXXXXX Medical Store";
	          	cout<<"\n___________________________________________";
	            	cout<<"\nSr.No.  	Medicine	   Price	  Quantity	  Total ";
	            	cout<<"\n___________________________________________";
	            	for(j=0;j<i;j++)
	            	{
	            	    	cout<<"\n  "<<j+1<<"\t\t"<<M1[j].name<<"\t\t"<<M1[j].cost<<"\t\t"<<M1[j].quantity<<"\t\t"<<M1[j].cost*M1[j].quantity;
	            	        sum=sum+M1[j].cost*M1[j].quantity;
                        }
			cout<<"\n___________________________________________";
			cout<<"\n                         Total: "<<sum;
			cout<<"\n___________________________________________";
                }
                else
                   	return;

	}

};//endofclas

int main()
{
    Medicine Med;
    int choice;
    do
    {	cout<<"\n---------------------MENU--------------------------";
        cout<<"\n1.Insert";
        cout<<"\n2.Display";
        cout<<"\n3.Search";
        cout<<"\n4.Delete";
        cout<<"\n5.Modify";
        cout<<"\n6.Bill";
        cout<<"\n7.Exit";
        cout<<"\nEnter your choice :";
        cin>>choice;
        switch(choice)
        {
            case 1:
                    Med.AddRecord();
                    break;

            case 2:
                    Med.Display();
                    break;
            case 3:
                    Med.searchID();
                    break;
            case 4:
            	   Med.Display();
                    Med.deleteMedID();
                    break;
            case 5:
                   Med.Display();
                    Med.modify_record();
                    break;
            case 6:
                   Med.Display();
                    Med.bill();
                    break;
        }
    } while(choice<7);
}
