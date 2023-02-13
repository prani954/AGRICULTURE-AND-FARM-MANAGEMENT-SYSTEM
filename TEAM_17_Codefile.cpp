/* AGRICULTURE AND FARMING MANAGEMENT SYSTEM */
//Software used : Dev C++
//used MYSQL 8.0 Command Line Client 
//used MySQL Workbench to extract CSV files
#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<string.h>
#include<conio.h>
#include<cstdlib>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<windows.h>
#include <dos.h>
#include <unistd.h>
#include <algorithm>
#include <getopt.h>


using namespace std;

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "3sandhya@203sha@123";
//enter the password that you have given for mysql connection
// Global variables 

int qstate;

MYSQL* obj;  	
MYSQL_ROW row;
MYSQL_RES* res;

int hflag=0;
// class for database connection 


class database_connection
{
		public :
			
		static void toconnect()
		{
			if(!(obj = mysql_init(0)))
				 {
				 	cout << "ERROR:MySQL object could not be created" << endl;
				 }
			 else
		 		{
		 			if(!mysql_real_connect(obj,HOST,USER,PASS,"crops",3306,NULL,0))
			 		{
			 		cout << "ERROR:DataBase doesn't exist" << endl;
			 		cout << mysql_error(obj) << endl;
					}
					else
					{
						cout << "Database connected .....: "<< endl;
						
					}
				
				}
			
		}
	
};

// for new registration:

class farmerreg
{
	public :
	
	string fuser_id;
	string fpassword;
	string setid;
    string Name;
	string state;
	string Age;
	string Income;
	string contact;
	string willingness;
	string status;
	bool ProgramIsOpened;
	public :
	void freg()
	{
		cout << "please set your user id : "<< endl;
		cin.ignore(100,'\n');
		getline(cin,fuser_id );
		cout << " enter your password : "<< endl;
		getline(cin,fpassword);
		cout << "Enter the Details" << endl;
		cout << "Enter Your Name : "<<endl;
		getline(cin,Name);
		cout << "Enter Your Age : "<<endl;
		getline(cin,Age);
		cout<<"Enter Your Income : "<<endl;
        getline(cin,Income);
        cout << "Enter State :  "<< endl;
      	getline(cin,state);
      	cout << "enter contact details :"<<endl;
      	getline(cin,contact);
      	cout << "Are you willing to do a job :"<<endl;
      	getline(cin,willingness);
      	
      	
      	
		
        //added here
		
		setid="INSERT INTO farmerdb(USERID,PASSWORD,Name,Age,Income,state,contact,willingness,status) VALUES('"+fuser_id+"','"+fpassword+"','"+Name+"','"+Age+"','"+Income+"','"+state+"','"+contact+"','"+willingness+"','unhired')";
		const char* qn = setid.c_str();
		 
		 qstate = mysql_query(obj, qn);

		    if (!qstate)
		    {
		        cout <<  "Successfully registered .." << endl;
		    }
		    else
		    {
		        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
		    }
				
	}	
	void GroceryPrice()
	{
	qstate = mysql_query(obj, "select *from pricelist");
    if (!qstate)
    {
        res = mysql_store_result(obj);
        printf("---------------------------------------------------------\n");
        printf("| %15s | %-15s | %-15s| %15s |\n","ID","Category","Name","Price_per_kg");
        printf("---------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %15s | %-15s| %-15s| %15s |\n",row[0],row[1], row[2],row[3]);
        }
        printf("----------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
    }

		
	}
void AddNewItem()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Variables
	string ID = "";
    string category = "";
    string name = "";
    float price = 0.0;
    char choose;
    // Variables End

    cout << "Welcome To our Store" << endl << endl;
    cout << "Add New Item Menu" << endl << endl;
    
    cin.ignore(1, '\n');
	cout << "Enter ID : ";
	getline(cin,ID);
    cout << "Enter Category: ";
    getline(cin, category);
    cout << "Enter Type: ";
    getline(cin, name);
    cout << "Enter Price: ";
    cin >> price;
    stringstream streamPrice, streamQuan;
    string sprice;
    streamPrice << price;
    streamPrice >> sprice;
 


    string insert_query = "insert into pricelist(ID,Category, Name, price_per_kg) values ('"+ID+"','"+category+"','"+name+"','"+sprice+"')";

    const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

    qstate = mysql_query(obj, q);

    if (!qstate)
    {
        cout << endl << "Successfully added in database." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
    }
    // Exit Code
}

void EditItem()
{
    system("cls");

    // Variables
    string category = "";
    string name = "";
    string items[5000];
    string price = "";
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeid = "";
    string storecategory = "";
    string storename = "";
    string storeprice = "";
    // Variables End

    cout << "Welcome To our Store" << endl << endl;
    cout << "Edit Item Menu" << endl << endl;

    qstate = mysql_query(obj, "select ID, Name from pricelist");
    if (!qstate)
    {
        res = mysql_store_result(obj);
        cout << "ID\tName\n" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << row[0] << "\t" << row[1] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        exit(0);
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from pricelist where ID = '"+strid+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(obj, qi);

            if (!qstate)
            {
                res = mysql_store_result(obj);
                cout << endl;
                while ((row = mysql_fetch_row(res)))
                {
                    cout << "ID: " << row[0] << "\nCategory: " << row[1] << "\nName: " << row[2] << "\nPrice_per_kg: " << row[3] << endl << endl;
                    storeid = row[0];
                    storecategory = row[1];
                    storename = row[2];
                    storeprice = row[3];
                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
            }

            cin.ignore(1, '\n');
            cout << "Enter Category (xN to not change): ";
            getline(cin, category);
            if (category == "xN")
            {
                category = storecategory;
            }
            cout << "Enter Name (xN to not change): ";
            getline(cin, name);
            if (name == "xN")
            {
                name = storename;
            }
            cout << "Enter Price_per_kg (xN to not change): ";
            cin >> price;
            if (price == "xN")
            {
                price = storeprice;
            }


            string update_query = "update pricelist set Category = '"+category+"', Name = '"+name+"',  Price_per_kg = '"+price+"' where ID = '"+strid+"'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(obj, qu);

            if (!qstate)
            {
                cout << endl << "Successfully Saved In Database." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(obj) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }


    
}
void RemoveItem()
{
    system("cls");

    // Variables
    char choose;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    // Variables End

    cout << "Welcome To Store" << endl << endl;
    cout << "Remove Item Menu" << endl << endl;

    qstate = mysql_query(obj, "select ID, Name from pricelist");
    if (!qstate)
    {
        res = mysql_store_result(obj);
        cout << "ID\tName\n" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << row[0] << "\t" << row[1] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
		exit(0); 
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from pricelist where ID = '"+strid+"'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(obj, qd);

            if (!qstate)
            {
                cout << "Successfully Deleted From Database." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(obj) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    // Exit Code


}
	
	
	
	
	
	
	
};



class customerreg : public farmerreg
{
	public :
	
	string cuser_id;
	string cpassword;
	string cust_id;
    string CName;
	string Cstate;
	string Ccontact;
	
	public :
	void creg()
	{
		cout << "Enter the Details" << endl;
		cout << "Please set your user id : "<< endl;
		cin.ignore(100,'\n');
		getline(cin,cuser_id );
		cout << "Enter your password : "<< endl;
		getline(cin,cpassword);
		cout << "Enter Your Name : "<<endl;
		getline(cin,CName);
        cout << "Enter State :  "<< endl;
      	getline(cin,Cstate);
      	cout << "Enter your contact Number : " << endl;
      	getline(cin,Ccontact);
		
        
		
		cust_id="INSERT INTO customerdb(USERID,PASSWORD,Name,state,contact) VALUES('"+cuser_id+"','"+cpassword+"','"+CName+"','"+Cstate+"','"+Ccontact+"')";
		const char* qn = cust_id.c_str();
		 
		 qstate = mysql_query(obj, qn);

		    if (!qstate)
		    {
		        cout <<  "Successfully registered .." << endl;
		    }
		    else
		    {
		        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
		    }
				
	}	
	
	void todisplayprice(string inpname)
	{
		string groc;
		groc=inpname;
		string findbyname_query ="select* from pricelist where Name like '%"+groc+"%'";
	   	const char* qn = findbyname_query.c_str();
	    qstate = mysql_query(obj, qn);
	    
		cout << endl;
	    if (!qstate)
	    {
	        res = mysql_store_result(obj);
	        while ((row = mysql_fetch_row(res)))
	        {
	        	cout << "ID number : " << row[0] << endl;
	            cout << "Category (Fruit/Vegetable) : " << row[1] << endl;
				cout << "Name : " << row[2] << endl;
				cout << "Price per kg : " << row[3] << endl;
				
				
	        }
	    }
	    else
	    {
	        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
	    }
			
			
	}
	
};



class hfarmerreg
{
	public :
	
	string huser_id;
	string hpassword;
	string hsetid;
    string HName;
	string Hstate;
	string HAge;
	string HIncome;
	
	public :
	void hfreg()
	{
		cout << "please set your user id : "<< endl;
		cin.ignore(100,'\n');
		getline(cin,huser_id );
		cout << " enter your password : "<< endl;
		getline(cin,hpassword);
		cout << "Enter the Details" << endl;
		cout << "Enter Your Name : "<<endl;
		getline(cin,HName);
		cout << "Enter Your Age : "<<endl;
		getline(cin,HAge);
		cout<<"Enter Your Income : "<<endl;
        getline(cin,HIncome);
        cout << "Enter State :  "<< endl;
      	getline(cin,Hstate);
		
        
		
		hsetid="INSERT INTO Hfarmerdb(USERID,PASSWORD,Name,Age,Income,state) VALUES('"+huser_id+"','"+hpassword+"','"+HName+"','"+HAge+"','"+HIncome+"','"+Hstate+"')";
		const char* qn = hsetid.c_str();
		 
		 qstate = mysql_query(obj, qn);

		    if (!qstate)
		    {
		        cout <<  "Successfully registered .." << endl;
		    }
		    else
		    {
		        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
		    }
				
	}	
	
	
	
};



class custolog : public customerreg
{
	public:
	string cuse_id;
	int cflag=0;
	string cpasswords;
	public :
	int culogin()
	{
			cout << "enter your USERID :"<< endl;
			cin.ignore(100,'\n');
			getline(cin,cuse_id);
			cout << "enter your password : "<< endl;
			getline(cin,cpasswords);
			string setlogc="select *from customerdb where USERID like '%"+cuse_id+"%' AND PASSWORD like '%"+cpasswords+"%'";
			const char* qu = setlogc.c_str();
			qstate = mysql_query(obj, qu);
		
			if(!qstate)
			{
				res = mysql_store_result(obj);
		        while ((row = mysql_fetch_row(res)))
		        {
		        	cout << "successfully logged in ....."<< endl;
		        	cout << "Name : "<< row[2] << endl;
			    	cout << "State : "<< row[3]<< endl;
			    	cout << "contact : " << row[4] << endl;
					cflag=1;
				}
				
			}
		
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
		}
		return cflag;
	}
	
	
	
};

class farmlog : public farmerreg
{
	public:
	string fuse_id;
	string fpasswords;
	public :
	int fflag=0;
	int farmlogin()
	{
			int fflag=0;
			cout << "enter your USERID :"<< endl;
			cin.ignore(100,'\n');
			getline(cin,fuse_id);
			cout << "enter your password : "<< endl;
			getline(cin,fpasswords);
			string setlog="select *from farmerdb where USERID like '%"+fuse_id+"%' AND PASSWORD like '%"+fpasswords+"%' ";
			const char* quer = setlog.c_str();
			qstate = mysql_query(obj, quer);
		
			if(!qstate)
			{
				res = mysql_store_result(obj);
		        while ((row = mysql_fetch_row(res)))
		        {
		        	cout << "-------------------------------------------------------------------------------------"<<endl;
		        	cout << "successfully logged in ....."<< endl;
		        	cout << "Name : "<< row[2] << endl;
			    	cout << "Age : "<< row[3]<< endl;
			    	cout << "Income : "<< row[4]<< endl;
			    	cout << "State : "<< row[5]<< endl;
			    	cout << "contact : "<< row[6]<<endl;
			    	fflag=1;
			    	cout << "-------------------------------------------------------------------------------------"<<endl;
					
				}
				
			}
		
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
		}
		return fflag;
	}
	
	
	
	
};


class hfarmlog : public hfarmerreg
{
	public:
	string huse_id;
	string hpasswords;
	public :
	int hflag=0;
	int hfarmlogin()
	{
			hflag=0;
			cout << "enter your USERID :"<< endl;
			cin.ignore(100,'\n');
			getline(cin,huse_id);
			cout << "enter your password : "<< endl;
			getline(cin,hpasswords);
			string setlog="select *from Hfarmerdb where USERID like '%"+huse_id+"%' AND PASSWORD like '%"+hpasswords+"%' ";
			const char* quer = setlog.c_str();
			qstate = mysql_query(obj, quer);
			
			if(!qstate)
			{
				res = mysql_store_result(obj);
		        while ((row = mysql_fetch_row(res)))
		        {
		        	cout << "-------------------------------------------------------------------------------------"<<endl;
		        	cout << "successfully logged in ....."<< endl;
		        	cout << "Name : "<< row[2] << endl;
			    	cout << "Age : "<< row[3]<< endl;
			    	cout << "Income : "<< row[4]<< endl;
			    	cout << "State : "<< row[5]<< endl;
			    	cout << "contact : "<< row[6]<<endl;
			    	cout << "-------------------------------------------------------------------------------------"<<endl;
			    	hflag=1;
					
				}
				
			}
		
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
		}
		return hflag;
	}
	
};


class grocery
{
	int cho=0;
	public :
	void ginfo()
	{
	int cho = 0;
	int an = 0;
	char eentry;
	farmerreg frg;
	bool ProgramIsOpened;
	while(cho!=5)
	{
		cout << "------------------------------------------" << endl;
		cout << "1.Grocery-price list : " << endl;
		cout << "2.to Add new Item to the list : " << endl;
		cout << "3.to Edit the items of the list : " << endl;
		cout << "4.To remove the items of the list : " << endl;
		cout << "5.exit " << endl;
	    cout << "------------------------------------------" << endl;

		
		cout << "Enter choice : " << endl;
		cin >> cho;
		
		switch(cho)
		{
			case 1:
				{
				frg.GroceryPrice();
				break;
			}
			case 2:
				{
				frg.AddNewItem();
				break;
			}
		    case 3:
		    	{
		    	frg.EditItem();
		    	break;
		    }
		    case 4:
		    	{
		    	frg.RemoveItem();
		    	break;
		    }
		    case 5:
		    	{
			
			    	cout << "program terminating ... Are you sure ?(y/n) : " << endl;
					cin >> eentry;
	   				if(eentry == 'y' ||eentry=='Y' )
	   				{
	   					//return 0;
	   					cout << "exiting....";
	   					exit(0);
	   				}
					else 
					{
						
						cout << endl << "Another?" << endl;
			            cout << "[1]: Yes" << endl;
			            cout << "[0]: No" << endl;
			            cout << "Answer : ";
			            cin >> an;
	            		cin.ignore(100,'\n');
	            		
						 if(an == 0)
			            {
			            	ProgramIsOpened = false;
						}
						
					}
			}
							
									
		    	
		}
	}
}
	
	
};

class detforlessexp : public farmerreg
{
	public :
	
	// function for displaying soils;
	
	
	void statetosoil() 
	{

    qstate = mysql_query(obj, "select *from statesoil");
    if (!qstate)
    {
        res = mysql_store_result(obj);
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("| %-15s | %-15s|\n", "sno","states");
        printf("-------------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-15s| %-15s|\n", row[0], row[1]);
        }
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
    }

    
	}

	
	
	
	// to display soil types in that state;
	
	void Find_soilby_states_no() 
	{
    int integ ;
     cin.ignore(100, '\n');
    cout << "Enter serial number for the state: ";
    cin >> integ;
    string findbysno_query ="select* from statesoil where sno= ";
    findbysno_query += to_string(integ);
    const char* qn = findbysno_query.c_str();
    qstate = mysql_query(obj, qn);

    cout << endl;
    if (!qstate)
    {
        res = mysql_store_result(obj);
        while ((row = mysql_fetch_row(res)))
        {
        	cout << "--------------------------------------------------------------------"<<endl;
            cout << "sno: " << row[0] << endl;
			cout << "state: " << row[1] << endl;
			cout << "soil types: " << row[2] << endl;
			cout << "-----------------------------------------------------------------------"<<endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
    }

    
    
	}
	
	void takesoil()
	{
		qstate = mysql_query(obj, "select *from soiltocrop");
    	if (!qstate)
    	{
        res = mysql_store_result(obj);
        cout << "---------------------------"<< endl;
        printf("| %-15s | %-15s|\n", "SNO","SOIL");
        cout << "---------------------------"<< endl;
        while ((row = mysql_fetch_row(res)))
        {
        	cout << "------------------------------------------------"<<endl;
            printf("| %-15s| %-15s|\n", row[0], row[1]);
        }
    	}
        else
    	{
        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
    	}

  	}
	
	void todisplaycrop(string inpsoil)
	{
		string fsoil;
		fsoil=inpsoil;
		string findbysoil_query ="select* from soiltocrop where SOIL like '%"+fsoil+"%'";
	   	const char* qn = findbysoil_query.c_str();
	    qstate = mysql_query(obj, qn);
		cout << endl;
	    if (!qstate)
	    {
	        res = mysql_store_result(obj);
	        while ((row = mysql_fetch_row(res)))
	        {
	        	cout << "--------------------------------------------------------------------"<<endl;
	            cout << "sno " << row[0] << endl;
				cout << "soil: " << row[1] << endl;
				cout << "crops : " << row[2] << endl;
				cout << "---------------------------------------------------------------------"<<endl;
	        }
	    }
	    else
	    {
	        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
	    }
			
			
	}
		
	void todispcrops()
	{
		qstate = mysql_query(obj, "select *from croptofertilizers");
    	if (!qstate)
    	{
        res = mysql_store_result(obj);
        cout << "---------------------------"<< endl;
        printf("crops");
        cout << "---------------------------"<< endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << row[0] << endl;
        }
    	}
        else
    	{
        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
    	}

		
	}
	void todisplayfert(string incrop)
	{
		string fcrop;
		fcrop=incrop;
		string findbyfert_query ="select* from croptofertilizers where CROPS like '%"+fcrop+"%'";
	   	const char* qn = findbyfert_query.c_str();
	    qstate = mysql_query(obj, qn);
		cout << endl;
	    if (!qstate)
	    {
	        res = mysql_store_result(obj);
	        while ((row = mysql_fetch_row(res)))
	        {
	        	cout << "--------------------------------------------------------------------"<<endl;
	            cout << "CROPS :" << row[0] << endl;
				cout << "MANURES" << row[1] << endl;
				cout << "SEASON : " << row[2] << endl;
				cout << "--------------------------------------------------------------------"<<endl;
				
	        }
	    }
	    else
	    {
	        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
	    }
			
			
	}
	void todisplayclimate(string incrop)
	{
		string fcrop;
		fcrop=incrop;
		string findbyfert_query ="select* from croptotemp where crops like '%"+fcrop+"%'";
	   	const char* qn = findbyfert_query.c_str();
	    qstate = mysql_query(obj, qn);
		cout << endl;
	    if (!qstate)
	    {
	        res = mysql_store_result(obj);
	        while ((row = mysql_fetch_row(res)))
	        {
	        	cout << "--------------------------------------------------------------------"<<endl;
	            cout << "CROPS :" << row[0] << endl;
				cout << "temperature" << row[1] << endl;
				cout << "AnnualRainfall : " << row[2] << endl;
				cout << "--------------------------------------------------------------------"<<endl;
				
	        }
	    }
	    else
	    {
	        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
	    }
			
			
	}
	
	void todisplaykvkdis()
	{
		string takestate1;
		cout << "Enter state: "<< endl;
		cin.ignore(100,'\n');
		getline(cin,takestate1); 
		string findbystate_query= "select DISTRICT from kvkwithconctacts  where STATE like '%"+takestate1+"%'";   
		const char* qn = findbystate_query.c_str();
		qstate = mysql_query(obj,qn);
		                 	
		cout << "Districts in " << takestate1 << " is/are : " << endl;
		cout <<  "---------------------";
		cout << endl;
		if(!qstate)
			{
		            res= mysql_store_result(obj);
		            			
		            			
		            	while((row = mysql_fetch_row(res)))
		            			{
		            				cout << row[0] << endl;
		            				
								}	
		            			
			}
							if(qstate)
							{
								cout << "Query Execution Problem : "<< mysql_errno(obj)<<endl;
							}
							cout << "---------------------";
							cout << endl;

	}
	
	void todisplaykvkcenter()
	{
		
		string takedistrict = "";
		
		cout << "Enter district: "<< endl;
		getline(cin,takedistrict);
		string findbykvk_query= "select *from kvkwithconctacts where DISTRICT like '%"+takedistrict+"%'";   
		const char* qn = findbykvk_query.c_str();
		qstate = mysql_query(obj,qn);
		                 	
		cout << "you can contact the following for further information  : " << endl;
		
		cout << endl;
		if(!qstate)
			{
		            res= mysql_store_result(obj);
		            			
		            			
		            	while((row = mysql_fetch_row(res)))
		            			{
		            					cout << "--------------------------------------------------------------------"<<endl;
		            					cout << "state : "<< row[1] << endl;
		            					cout << "district :"<<row[2] << endl;
		            					cout << "number of kvk centers in your district : "<< endl << row[3] << endl;
		            					cout << "contact details : "<< row[4] << endl;
		            					cout << "--------------------------------------------------------------------"<<endl;
		            				
		            				
								}	
		            			
			}
							if(qstate)
							{
								cout << "Query Execution Problem : "<< mysql_errno(obj)<<endl;
							}
							cout << "---------------------";
							cout << endl;

		
	}
	
};
bool ProgramIsOpened = true;
char exitentry;
int answer;

class cutintmain
{
	int newchoice=0;
	
	
	public :
	void whileinfo()
	{
		detforlessexp obje;
		cout << "since you are less expertised in farming we provide you the following options : "<<endl;
		cout << "-----------------------------------------------------------------------------------"<< endl;
				while(newchoice!=6)
							{
								cout << "1.Info about soils in India : "<< endl;
				            	cout << "2.Info about crops in particular soil : "<< endl;
				            	cout << "3.Pesticides and Manures for soil : "<< endl;
				            	cout << "4.info about climatic conditions : "<< endl;
				            	cout << "5.info about kvk : "<< endl;
				            	cout << "6.exit "<< endl;
								cin >> newchoice;
							
													
			            		switch(newchoice)
			            	
			            		{
								case 1:
									{

										obje.statetosoil();
										obje.Find_soilby_states_no();
										break;
									
									}
								case 2:
									{
									
										string masoil;
										obje.takesoil();
										cout << "enter soil : "<< endl;
										cin.ignore(100,'\n');
										getline(cin,masoil);
										obje.todisplaycrop(masoil);
										break;
									}
									
								
								case 3 :
									{
										string mcrop;
										obje.todispcrops();
										cout << "please enter crop : "<< endl;
										cin.ignore(100,'\n');
										getline(cin,mcrop);
										obje.todisplayfert(mcrop);
										break;
									}
								case 4 :
									{
										string tcrop;
										obje.todispcrops();
										cout << "please enter crop : "<< endl;
										cin.ignore(100,'\n');
										getline(cin,tcrop);
										obje.todisplayclimate(tcrop);
										break;
										
									}
								case 5 :
									{
										obje.todisplaykvkdis();
										obje.todisplaykvkcenter();
										break;
									}
								case 6:
									{
										cout << "program terminating ... Are you sure ?(y/n) : " << endl;
		       	   						cin >> exitentry;
				       	   				if(exitentry == 'y' ||exitentry=='Y' )
				       	   				{
				       	   					//return 0;
				       	   					cout << "exiting....";
				       	   					exit(0);
				       	   				}
										else 
										{
											
											cout << endl << "Another?" << endl;
								            cout << "[1]: Yes" << endl;
								            cout << "[0]: No" << endl;
								            cout << "Answer : ";
								            cin >> answer;
						            		cin.ignore(100,'\n');
						            		
											 if(answer == 0)
								            {
								            	ProgramIsOpened = false;
											}
											
										}
									}
									
								
									
								}
			            		
							}
		
		}
		
		
			            		
};


// if there are no farmers available it doesn't show anything

class hiringfarmers 
{
	string stateofhir;
	public :
	void hirefarm()
	{
		cout << "Enter state : " << endl;
		cin.ignore(100,'\n');
		getline(cin,stateofhir);
		
		string findque_bystate="select *from farmerdb where state like '%"+stateofhir+"%'";
		const char* query=findque_bystate.c_str();
		qstate = mysql_query(obj,query);
		if (!qstate)
	    {
	        res = mysql_store_result(obj);
	        while ((row = mysql_fetch_row(res)))
	        {
	        	cout << "---------------------------------------------------------------------------------------------"<<endl;
	        	cout << "Info of farmers in your state ........................"<< endl <<endl;
	            cout << " Name :" << row[2] << endl;
				cout << "state :" << row[5] << endl;
				cout << "contact  : " << row[6] << endl;
				cout << "willingness for job : "<< row[7]<<endl;
				cout << "status : "<< row[8]<< endl ;
				cout << "---------------------------------------------------------------------------------------------"<<endl;
			}
			
	    }
	    else
	    {
	    	cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
		}
		
		
		
	}
	//giving review
	public :
	void givingreview()
	{
		string takereview;
		string takestrreview;
		cout << "please give rating from 1-5 : " << endl;
		cin.ignore(100,'\n');
		getline(cin,takereview);
		cout << "pleasa give ur feedback"<< endl;
		getline(cin,takestrreview);
		if(takereview=="5"||takereview=="4")
		{
			cout << "Thank you "<< endl;
		}
		else if(takereview=="3")
		{
			cout << "Thank you ..We will improve "<< endl;
			
		}
		else if(takereview=="2")
		{
			cout << "Thankyou ....we will improve.."<< endl;
		}
		else if(takereview=="1")
		{
			cout << "thank you ....we will improve"<< endl;
		}
		else
		{
			cout << "thanks for your feedback ..... :)" ;
		}
	}
	public :
	void editperson()
	{
		string persedit;
		//cin.ignore(100,'\n');
		getline(cin,persedit);
		
		
		string findbypfert_query ="update farmerdb set status = 'hired' where Name = '%"+persedit+"%'";
	   	const char* qn = findbypfert_query.c_str();
	    qstate = mysql_query(obj, qn);
		cout << endl;
	    if (!qstate)
	    {
	        res = mysql_store_result(obj);
	        while ((row = mysql_fetch_row(res)))
	        {
	        	cout << row[3]<< endl;
	        	cout << row[8]<< endl;
				
	        }
	    }
	    else
	    {
	        cout << "Query Execution Problem!" << mysql_errno(obj) << endl;
	    }
			
		 //update farmerdb set status = 'unhired' where Name = 'trisandhya';
	}

	
};





class cutintmainforh : public hiringfarmers
{
	int hichoi=0;
	char exitentry;
	string hiredname;
	public:
	void while_h_info()
		{
			hiringfarmers hobj;
			cout << "Welcome .." <<endl << "------------------------------------------------------------------"<< endl;
			
			
					while(hichoi!=4)
						{
							cout << "1.Do you want some farmers to work for ur land "<< endl;
							cout << "2.Do you want to give some reviews on crops/soils .."<< endl;
							cout << "3.Do you want some basic details of farming .." << endl;
							cout << "4.exit"<< endl;
								
								cout << "enter your choice" << endl;
								cin >> hichoi ;
								
								switch(hichoi)
								{
									case 1:
										{
											hobj.hirefarm();
											//cout << "mention the name whom you are choosing "<< endl;
											//hobj.editperson();											
											break;	
										}
										
									case 2:
										{
											hobj.givingreview();
											break;
										}
									case 3 :
										{
											cutintmain fobject;
											fobject.whileinfo();
											break;
										}
										
									case 4:
									{
										
										cout << "program terminating ... Are you sure ?(y/n) : " << endl;
		       	   						cin >> exitentry;
				       	   				if(exitentry == 'y' ||exitentry=='Y' )
				       	   				{
				       	   					
				       	   					cout << "exiting....";
				       	   					exit(0);
				       	   				}
										else 
										{
											
											cout << endl << "Another?" << endl;
								            cout << "[1]: Yes" << endl;
								            cout << "[0]: No" << endl;
								            cout << "Answer : ";
								            cin >> answer;
						            		cin.ignore(100,'\n');
						            		
											 if(answer == 0)
								            {
								            	ProgramIsOpened = false;
											}
											
										}
									
									}
										
								}
								
								
								
							}
		}
};


int main(int argc, char *argv[])
{
	
	int basechoice=0;
	int newchoice=0;
	int fchoi; 
	int cuchoi;
	int hichoi;
	int hchoi;
	int basicchoice;
	char* consult;
	string fuse_id;
	char* sentence;
	string sentence_aux;
	string gname;
	char ord,co,en;
		 
		 
		  		database_connection::toconnect();   // static void can be called without using object ..
		  		
		  		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  WELCOME TO FARMING MANAGEMENT SYSTEM    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		  		cout << "					           	"<< "****************************************************************************"<< "																			"<<endl;
		  		cout << endl <<endl <<endl;
		  		
		  
				while(ProgramIsOpened)
				{
					cout << "1.Farmer " <<"  -----    "<< "2.High experienced farmer "<< "     ---------      "<< "3.customer "<< endl;
					cin >> basicchoice;
					if(basicchoice==1)
					
						{
							// farmer login 
							cout << "1.New Registration "<< "        " << "2.Login " << "             " <<  "3.Employment Details for BPL " << endl;
							cin >> fchoi;
							if(fchoi==1)
							{
								farmerreg ob;
								ob.freg();
                                mysql_store_result(obj);
                                cout << "1.check for basic information "<< "----------------------------" << "2.update Grocery details "<< endl;
                                cin >> basechoice; 
                                if(basechoice==1)
                                {
                                newchoice=0;
								cutintmain maino;
								maino.whileinfo();
                                }
                                else if(basechoice==2)
                                {
                                	
                                grocery gr;
								gr.ginfo();
                                }
								
								
							}
							else if(fchoi==2)
							{
								newchoice=0;
								farmlog fob;
								//fob.farmlogin();
								if(fob.farmlogin()==1)
								{
									cout << "1.check for basic information "<< "----------------------------" << "2.update Grocery details "<< endl;
	                                cin >> basechoice; 
	                                if(basechoice==1)
	                                {
	                                newchoice=0;
									cutintmain maino;
									maino.whileinfo();
	                                }
	                                else if(basechoice==2)
	                                {
	                                grocery gr;
									gr.ginfo();
	                                }
								
								}
								else
								{
									cout <<" pls check your password" << endl;
								}
				          			
							}
							else if(fchoi==3)
							{
								string a;
							        int i = 1;
							        //string url =  "https://pmkisan.gov.in/";
							        string url1 = "https://pmkisan.gov.in/RegistrationFormNew.aspx";
							        string url2 = "https://pmkisan.gov.in/";
							
							        

						            for (; i < argc; i++)
									 {
						                url1 = url1 + string(argv[i]);
						                if (i != argc-1) url1 = url1 + string("+");
						            }
                                    
                                     cout << url1 << endl;
						            string op = string("start ").append(url1);
						            system(op.c_str());
						            cout << "Do you want more details?(y/n): ";
						            cin >> a;
						            if(a == "y"){
						                for (; i < argc; i++) {
						                url2 = url2 + string(argv[i]);
						                if (i != argc-1) url2 = url2 + string("+");
						                }
                                 	cout << url2 << endl;
						            string op = string("start ").append(url2);
						            system(op.c_str());
						            }
						            else{
						                cout << "----------"<< endl;
						                cout << "thank you "<< endl;
						                cout << "----------"<< endl;
						            } 

						}
						}
						
						else if(basicchoice==2)
						{
							hfarmerreg ob;
							hfarmlog hobje;
							
							
							cout << "1.New Registration "<< "        " << "2.Login " << endl;
							cin >> hchoi;
							if(hchoi==1)
							{
								
								hichoi=0;
								hobje.hfreg();
								
								cutintmainforh mainh;
								mainh.while_h_info();
							}
							else if(hchoi==2)
							{
								hichoi=0;
								//hobje.hfarmlogin();
								if(hobje.hfarmlogin()==1)
								{
								
								cutintmainforh mainh;
								mainh.while_h_info();
								}
								else
								{
									cout << "pls check your password ..." << endl;
									exit(0);
									
								}
								

							}
							
								
						}
						else if(basicchoice==3)
						{
							cout << "1.New Registration "<< "        " << "2.Login " << endl;
							cin >> cuchoi;
							if(cuchoi==1)
							{
								customerreg cob;
								cob.creg();
								cout << "grocery price list : "<< endl;
								cob.GroceryPrice();
								cout << "please enter grocery Name  : "<< endl;
								//cin.ignore(100,'\n');
								cin >> gname;
								
								cout << "Do you want to place an order (y/n) : " << endl;
								cin >> ord;
		       	   				if(ord == 'y' ||ord=='Y' )
		       	   				{
		       	   					
		       	   					cob.todisplayprice(gname);
									cout << "Do you want to confirm your order (y/n) : " << endl;
									cin >> co;
									if(co == 'y' ||co=='Y' )
		       	   				   {
		       	   				   	 cout << " Your order will be delivered soon! " << endl;
		       	   				   }
										
		       	   				}
		       	   				else
		       	   				{
		       	   					cout << " Thank you " << endl;
		       	   					exit(0);
							    }
								
								mysql_store_result(obj);
								newchoice=0;
								
							}
							else if(cuchoi==2)
							{
								customerreg cg;
								custolog clog;
								if(clog.culogin()==1)
								{
								
								
								cg.GroceryPrice();
								cout << "please enter grocery Name  : "<< endl;
								//cin.ignore(100,'\n');
								getline(cin,gname);
								
								cout << "Do you want to place an order (y/n) : " << endl;
								cin >> ord;
		       	   				if(ord == 'y' ||ord=='Y' )
		       	   				{
		       	   					
		       	   					cg.todisplayprice(gname);
									cout << "Do you want to confirm your order (y/n) : " << endl;
									cin >> co;
									if(co == 'y' ||co=='Y' )
		       	   				   {
		       	   				   	 cout << " Your order will be delivered soon! " << endl;
		       	   				   }
										
		       	   				}
		       	   				else
		       	   				{
		       	   					cout << " Thank you " << endl;
		       	   					exit(0);
							    }
								
								mysql_store_result(obj);
								newchoice=0;
								}
								
				          			
							}
							
							
							
						}
						
				
			
}
}
