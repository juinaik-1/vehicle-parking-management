
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<fstream>
#include<ctime>
using namespace std;

class EarnedMoney{ 
    private:
    int cartype;
    int two_whtype;
    int bustype;
    int trucktype;
    int total;
    public:
    EarnedMoney(){                               //constructor to initially set prices at 0
        this->cartype=0;
        this->two_whtype=0;
        this->bustype=0;
        this->trucktype=0;
        this->total=0;
    }
    void setEMoney(int cartype,int two_whtype,int bustype,int trucktype,int total){
        this->cartype=cartype;
        this->two_whtype=two_whtype;
        this->bustype=bustype;
        this->trucktype=trucktype;
        this->total=total;
    }
    void showEMoney(){                               //show earned money
        cout<<"\n \t\t EARNED MONEY \n";
        cout<<setw(10)<<"car"<<setw(10)<<"2-wheeler"<<setw(10)<<"bus"<<setw(10)<<"truck"<<setw(10)<<"total\n";
        cout<<setw(9)<<this->cartype<<setw(9)<<this->two_whtype<<setw(9)<<this->bustype<<setw(9)<<this->trucktype<<setw(9)<<this->total<<endl;
    }
    void getallmoney();
    friend void addmoney(EarnedMoney,EarnedMoney&);  //friend function declaration
};

void EarnedMoney:: getallmoney(){           //to know total money earned 
    // open file in read mode
    ifstream fin;
    fin.open("earnedmoney.txt",ios_base::in|ios_base::binary);
    fin.read((char*)this,sizeof(*this)); //read file in read mode 
}
void addmoney(EarnedMoney oldmoney, EarnedMoney &newmoney){
     /* passing two objects of same class as a parameter 
    2nd object needs reference as it stores the calculated value*/
    newmoney.cartype+=oldmoney.cartype;
    newmoney.two_whtype+=oldmoney.two_whtype;
    newmoney.bustype+=oldmoney.bustype;
    newmoney.trucktype+=oldmoney.trucktype;
    newmoney.total+=oldmoney.total;
}

class vehicleType{     //parent class
    private:
    char VehicleTypeName[50];
    public:
    vehicleType(){    //constrctor
        strcpy(VehicleTypeName,"vehicle");
    }
    void SetVehicleType(EarnedMoney &earnedMoney){  //passing object as parameter  (& for reference of object)
        int vehicle_type;
        while(1){                                   //if invalid input: again take input
            cout<<"\nSelect vehicle type: ";
            cout<<"\n1. car  2. two-wheeler  3. bus  4. truck : ";
            cin>>vehicle_type;
            if(vehicle_type==1){                    // set pricing for each vehicle type
                strcpy(VehicleTypeName,"car");
                earnedMoney.setEMoney(100,0,0,0,100);
                break;
            }
            else if(vehicle_type==2){
                strcpy(VehicleTypeName,"2wheeler");
                earnedMoney.setEMoney(0,50,0,0,50);       //setmoney function from EarnedMoney class gets called
                break;
            }
            else if(vehicle_type==3){
                strcpy(VehicleTypeName,"bus");
                earnedMoney.setEMoney(0,0,150,0,150);
                break;
            }
            else if(vehicle_type==4){
                strcpy(VehicleTypeName,"truck");
                earnedMoney.setEMoney(0,0,0,200,200);
                break;
            }
            else{
                cout<<"\ninvalid choice!!";
            }
        }
    }void ShowVehicleType(){
        cout<<VehicleTypeName<<"  ";
    }
};

class vehicle:public vehicleType{                 //inherited class
    private:
    int vehicleNo;
    static int parking_slot;                      //declaring static var for parking slot
    const int max = 20;                           //constant variable for maximum parking limit 
    char model[60];
    char drivername[50];
    char datetime[50];
    EarnedMoney earnedMoney;                     //obj1
    public:
    
    vehicle(){     //constructor
        this->vehicleNo=0;
        this->parking_slot=0;
        strcpy(this->model,"not set");
        strcpy(this->drivername,"default");
        time_t tt;                               // creating an object tt of inbuilt class time_t
        tt=time(NULL);                           // using time() function
        char *tm=ctime(&tt);                    //ctime=asctime(localtime(time))  - storing time in character data type
        strcpy(datetime,tm);
    }
    static int addparkslot(){                 //static function for accessing static variable
        return parking_slot++;
    }
    static int delparkslot(){                 //static function for accessing static variable
        return parking_slot--;
    }
    void setvehicle(){                  //enter a new vehicle
        if(parking_slot>max){
            cout<<"sorry no parking available!!\n";
        }
        else{
            SetVehicleType(earnedMoney);
            cout<<"\nEnter the vehicle number: ";
            cin>>vehicleNo;
            cin.ignore();
            cout<<"\nEnter the model: ";
            cin.getline(model,60);
            cout<<"\nEnter the driver name: ";
            cin.getline(drivername,50);
            time_t tt;
            tt=time(NULL); 
            char *tm=ctime(&tt);
            strcpy(datetime,tm);
            addparkslot();
        }
    }
    
    void showvehicle(){                                 //print entered vehicle
        cout<<"type\tno.\tmodel\tname\tslot\tdate\ttime\tyear\n";
        ShowVehicleType();                              //inherited function
        cout<<"\t"<<vehicleNo<<"\t"<<model<<"\t"<<drivername<<"\t"<<parking_slot<<"\t"<<datetime<<endl;
    }
    void addvehicle();  //to add vehicle into file
    void GetVehicleList();  //to get all vehicles in file 
    void searchvehicle(int vehicleNo); //to search for a vehicle
    void deletevehicle(int vehicleNo);
    void updatevehicle(int vehicleNo);

};
int vehicle:: parking_slot=1;    //initializing the static variable
void vehicle::addvehicle(){
    //this pointer contains address of pointer of current vehicle instance
    ofstream fout;
    fout.open("addvehicle_data.txt",ios_base::app| ios_base::binary);  //opening file in append and binary mode
    fout.write((char*)this,sizeof(*this)); //convert address in char type - type casting
    fout.close();
    EarnedMoney em;                  //obj2 to access EarnedMoney class
    em.getallmoney();
    addmoney(em,this->earnedMoney);         //calling function outside of class
    fout.open("earnedmoney.txt",ios_base::out|ios_base::binary);        //updating "earnedmoney.txt"
    fout.write((char*)(&this->earnedMoney),sizeof(this->earnedMoney));  //passing object with this pointer and coverting values to char and store data in file 
    fout.close();
}
void vehicle::GetVehicleList(){    //info of all vehicles parked
    ifstream fin;
    int records=0;
    fin.open("addvehicle_data.txt",ios_base::in| ios_base::binary);
    if(!fin){
        cout<<" \n file not found!!";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){          //read file until gets to its end
            this->showvehicle();
            cout<<endl;
            records++;
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(records==0){
            cout<<"\nfile has no record!! ";
        }
    }
}
void vehicle::searchvehicle(int vehicleNo){
    /*1) search for given vehicle no. by opening file in read mode
      2) when vehicle no. matches, print the record by showvehicle() function
      3) we use records var as a flag to know whether the record was found or not
    */
    ifstream fin;
    int records=0;
    fin.open("addvehicle_data.txt",ios_base::in| ios_base::binary);
    if(!fin){
        cout<<" \n file not found!!";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){      //read file until gets to its end   eof-end of
            if(this->vehicleNo==vehicleNo){
                this->showvehicle();
                records=1;
                break;
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(records==0){
            cout<<"\nrecord not found!! ";
        }
    }
}
void vehicle::deletevehicle(int vehicleNo){
    /* here the logic we applied is- 
    1) open "addvehicle_data.txt" file in read mode
    2) create a temporary file named as "tempaddvehicle_data.txt" in write mode
    3) copy all the data from 1st file except for which the record has been matched
    4) remove 1st file and rename temp file as the 1st file*/
    ifstream fin;
    ofstream fout;
    int flag=0;
    fin.open("addvehicle_data.txt",ios_base::in| ios_base::binary);
    if(!fin){
        cout<<" \n file not found!!";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        fout.open("tempaddvehicle_data.txt",ios_base::out| ios_base::binary);
        while(!fin.eof()){     //read file until gets to its end
            if(this->vehicleNo==vehicleNo){
                flag=1;
            }
            else{
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        if(flag==0){
            cout<<"\nrecord not found!! cannot delete \n";
            remove("tempaddvehicle_data.txt");
        }
        else{
            cout<<"record deleted!!\n";
            remove("addvehicle_data.txt");
            rename("tempaddvehicle_data.txt","addvehicle_data.txt");
            delparkslot();
            cout<<"Your vehicle has left the parking area!\n";
        }
    }
}
void vehicle::updatevehicle(int vehicleNo){
    fstream foutin;
    int flag=0;
    foutin.open("addvehicle_data.txt",ios_base::in|ios_base::out|ios_base::ate| ios_base::binary);
                                                                //ate mode- used to anvigate to a particular position before end of file
    foutin.seekg(0);     //get pointer at start.. by default it is at last in append mode
    if(!foutin){
        cout<<" \n file not found!!";
    }
    else{
        foutin.read((char*)this,sizeof(*this));
        while(!foutin.eof()){//read file until gets to its end
            if(this->vehicleNo==vehicleNo){
                cout<<" Update the data:- \n";
                cout<<"\nEnter the vehicle number: ";
                cin>>vehicleNo;
                cin.ignore();
                cout<<"\nEnter the model: ";
                cin.getline(model,60);
                cout<<"\nEnter the driver name: ";
                cin.getline(drivername,50);
                time_t tt;
                tt=time(NULL);
                char *tm=ctime(&tt);
                strcpy(datetime,tm);
                foutin.seekp(foutin.tellp()-std::streamoff(sizeof(*this)));         //changes get pointer's location to previous location
                foutin.write((char*)this,sizeof(*this));
                cout<<"\nrecord updated!!";

                flag=1;
                break;
            }
            foutin.read((char*)this,sizeof(*this));
        }
        foutin.close();
        if(flag==0){
            cout<<"\nrecord not found!! ";
        }
    }
}

int menu(){
    int ch;
    printf("\n 1. Add vehicle ");
    printf("\n 2. Search vehicle ");
    printf("\n 3. Delete vehicle ");
    printf("\n 4. Update vehicle ");
    printf("\n 5. List all vehicles ");
    printf("\n 6. Check earned money ");
    printf("\n 7. Exit ");
    printf("\n Enter your choice: ");
    scanf("%d",&ch);
    return(ch);
}

int main(){
    vehicle v;
    EarnedMoney em;
    int breakloop=0,vehicleNo;
    
    while(1){
        switch(menu()){
            case 1:
                v.setvehicle();
                v.addvehicle();
                cout<<"\nYour vehicle has been parked!!"<<endl;
                break;
            case 2:
                cout<<"\nEnter vehicle number to find your vehicle:";
                cin>>vehicleNo;
                v.searchvehicle(vehicleNo);
                break;
            case 3:
                cout<<"\nEnter vehicle number to exit the parking area:";
                cin>>vehicleNo;
                v.deletevehicle(vehicleNo);
                break;
            case 4:
                cout<<"\nEnter vehicle number to update your data:";
                cin>>vehicleNo;
                v.updatevehicle(vehicleNo);
                break;
            case 5:
                v.GetVehicleList();
                break;
            case 6:
                em.getallmoney();
                em.showEMoney();
                break;
            case 7:
                breakloop=1;
                break;
            default:
                cout<<"\nInvalid input";
        }
        if (breakloop==1){
            break;
        }
    }
    return 0;
}
