#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<time.h>


void mainMenu(int sd);
void adminLogin(int sd);
void admin_work(int sd);
void signup(int sd);
void delete_account(int sd);
void admin_changepassword(int sd);
void add_train(int sd);
void search_train(int sd);
void delete_train(int sd);
void userLogin(int sd);
void user_function(int sd);
void change_password(int sd, char uname[]);
void book_ticket(int sd,char uname[]);
void print_bookingdetails(int sd, char uname[]);
void cancel_booking(int sd,char uname[]);
void agentLogin(int sd);
void agent_function(int sd);
void achange_password(int sd, char uname[]);
void abook_ticket(int sd,char uname[]);
void aprint_bookingdetails(int sd, char uname[]);
void acancel_booking(int sd,char uname[]);



void mainMenu(int sd)
{
	int choice;


printf("\e[1;1H\e[2J");  // clear screen.. found out on stackoverflow as an alternative to clrscr()

	 printf("\n ==================================********WELCOME TO ONLINE BANKING SYSTEM********===========================================\n");
	printf("\n1.ADMIN LOGIN\n2.USER LOGIN\n3.AGENT LOGIN\n4.EXIT\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
         char message[100];
	write(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
				
		   case 2: userLogin(sd);
				break;
		case 1: adminLogin(sd);
				break;
		case 3: agentLogin(sd);
				break;
		case 4: 
		           
                             exit(0);
				break;
                 default:
                         read(sd,message,100);
                         printf("%s\n",message);
                         exit(0);
        }
}
	
	
void adminLogin(int sd)
{
	char uname[40], passwrd[30], welcome[100];
	int flag=0;
	
	printf("\nEnter the admin username: ");
	scanf(" %s",uname);
	printf("Enter admin password: ");
	scanf(" %s",passwrd);
	
	write(sd, uname, sizeof(uname));
	write(sd, passwrd, sizeof(passwrd));
	
	
	read(sd, &flag, 100);
	read(sd, welcome, 100 );  // welcome message of admin 
	
	printf("\n%s\n",welcome);
	
	//sleep(3);
	
	if(flag == 1)
		admin_work(sd);
		
	if ( flag == 0 )
		{ 
		  mainMenu(sd);
		}
}

void admin_work(int sd)
{

int choice;
	
     printf("\n1.Add user/Agent Account \n2.Delete user/Agent Account \n3.Search an Account(view details)\n4.Add train\n5.Delete Train\n6.search Train\n7.change password of any user\n8.sign out\nEnter your choice: ");
     scanf("%d", &choice);
	
	char buffer[100], uname[40], pass[30];
	int flagch=0;
	write(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
		case 1:signup(sd);
			break;
		case 2:delete_account(sd);
			break;
                 
                 
        	case 3:
		        printf("\nEnter account holder name to search: ");
			scanf(" %s", uname);
			write(sd, uname, sizeof(uname));
			
			read(sd,&flagch,sizeof(flagch));
			
			//printf("flagch value %d\n",flagch);
			
			if ( flagch == 1)     // to display all the user attributes
			{
			    int id;
			    char uname[40];
			    read(sd, &buffer, sizeof(buffer));
			     printf("%s\n", buffer);
			    
			    read(sd,&id,100);
			    printf("user_id : %d\t",id);
			    
			    read(sd,uname,100);
			    printf("user_name: %s\t",uname);
			    
			    read(sd,uname,100);
			    printf("user_password : %s\n",uname);
			    
			    read(sd,&id,100);
			    printf("user_type:%d\t",id);
			    
			    read(sd,&id,100);
			     printf("user_balance:%d\t",id);
			    
			    read(sd,&id,100);
	                     printf("user_status(0-->inactive 1-->active):%d\t\n",id);		   
			
			
			}
			if( flagch == 0)                      // account holder name not found 
			{
			  read(sd,&buffer,sizeof(buffer));
			  printf("%s\n", buffer);
			 }
			 
			admin_work(sd);
			break;
			
			
	      case 4: add_train(sd);
	               break;
	               
	      case 5: delete_train(sd);
	               break;
	               
	      case 6: search_train(sd);
	                break;	
	      case 7: admin_changepassword(sd);
	               break;
		case 8:
		   read(sd,buffer,100);
		   printf("%s",buffer);
		   sleep(1);
		   mainMenu(sd);
	}
	
}


void signup(int sd)
{
	int account_id,type;
	char uname[40],pass[30], message[100];

	printf("Enter username: ");
	scanf("%s",uname);
	printf("Enter password: ");
	scanf("%s",pass);

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));
	
	read(sd,message,sizeof(message));
	printf("%s",message);
	
	scanf("%d",&type);
	write(sd,&type,100);
        
	read(sd, message, sizeof(message));
	printf("%s", message);
	
	admin_work(sd);
		
}
void admin_changepassword(int sd)
{
    char pass[40],message[40],uvname[40];
    printf("enter username:");
    scanf("%s",uvname);
    
    write(sd,uvname,100);

    printf("Enter New Password:");
    scanf("%s",pass);
    write(sd,pass,100);

    read(sd,message,100);
    printf("%s\n",message);
    
    admin_work(sd);
}

void delete_account(int sd)
{

 char name[40],message[100];
 printf("enter name of the account user:");
 scanf("%s",name);
 write(sd,name,100);

 read(sd,message,sizeof(message));
 printf("===%s====\n",message);
 admin_work(sd);

}

void add_train(int sd)
   {
      char tr_name[40],message[100];
      printf("enter train to be added:");
      scanf("%s",tr_name);
      write(sd,tr_name,100);

      read(sd,message,100);

      printf("++++++++%s+++++++++++++",message);

      admin_work(sd);
    }

 void search_train(int sd)
    {
       char name[40],message[50];
       int flag=0; 
       int t_no;
      
       printf("Enter name of the train:");
      
       scanf("%s",name);
       write(sd,name,100);

       read(sd,&flag,100);
       
       if(flag == 1)
        { 
      
        printf("train details found:=======\n");
      
        read(sd,&t_no,100);
        printf("Train number: %d\t",t_no);
        
        read(sd,name,100);
        printf("train name: %s\t",name);
        
        read(sd,&t_no,100);
        printf("train status: %d\n",t_no);
      }
    
     else
     {
        read(sd,message,100);
        printf("%s\n",message);

     }
     
     admin_work(sd);
  }

void delete_train(int sd)
{

 char name[40],message[100];
 printf("enter name of the train:");
 scanf("%s",name);
 write(sd,name,100);

 read(sd,message,sizeof(message));
 printf("===%s====\n",message);
 
 admin_work(sd);

}



//================================================for normal user ==============================================================================
//==============================================================================================================================================
//==============================================================================================================================================


void userLogin(int sd)
{
	char uname[40], passwrd[30], welcome[50];
	int flag=0;
	
	printf("\nEnter the  username: ");
	scanf(" %s",uname);
	printf("Enter password: ");
	scanf(" %s",passwrd);
	
	write(sd, uname, 100);
	write(sd, passwrd,100);
	
	
	read(sd, &flag, 100);
	read(sd, welcome, 100);
	
	printf("\n%s\n",welcome);
	
	//sleep(3);
	
	if(flag == 1)
		user_function(sd);
		
	if ( flag == 0 )
		{ 
		  mainMenu(sd);
		 
		}
}

void user_function(int sd)
{

int choice;
	
     printf("=======WELCOME USER=======\n1.change password \n2.Book Ticket \n3.search bookings\n4.cancel booking \n5.sign out\nEnter your choice: ");
     scanf("%d", &choice);
	
	char buffer[100], uname[40], pass[30];
	int flagch=0;
	write(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
		case 1:change_password(sd,uname);
			break;
		case 2:book_ticket(sd,uname);
			break;
                 
               case 3:
                       
		       
			print_bookingdetails(sd,uname);
			printf("\n\n");
			break;
               
               case 4:
                        cancel_booking(sd,uname);
                        break;
                        
		case 5:
		    read(sd,buffer,100);
		   printf("%s",buffer);
		   sleep(5);
		   mainMenu(sd);
	}
	
}

void change_password(int sd, char uname[])
{
    char pass[40],message[40],uvname[40];
    printf("enter username:");
    scanf("%s",uvname);
    
    write(sd,uvname,100);

    printf("Enter New Password:");
    scanf("%s",pass);
    write(sd,pass,100);

    read(sd,message,100);
    printf("%s\n",message);
    
    user_function(sd);
}
void book_ticket(int sd,char uname[])
  {
     int train_id;
     int txn_id,flag=0;
     char train_name[40],message[50],uvname[50];
     
     printf("enter name of passenger:");
     scanf("%s",uvname);
     write(sd,uvname,100);
     
     
     printf("enter train id:");
     scanf("%d",&train_id);
     write(sd,&train_id,100);
     
     printf("enter train name:");
     scanf("%s",train_name);
     write(sd,train_name,100);
     
     read(sd,&flag,100);
     
   if(flag == 1)
       {
          read(sd,message,100);
          printf("%s",message);
          read(sd,&txn_id,100);
          printf("%d",txn_id);
       }    
     else
       {
        read(sd,message,100);  // for printinf txn id 
        printf("%s\n",message);
       }

      user_function(sd);

    }
  

void print_bookingdetails(int sd, char uname[])
{
     
     int flag =1,temp,txnid,txd;
     //char uname[50];
     char uvname[40];
     write(sd,uname,100);
     
     printf("enter transaction/Booking id:");
     
     scanf("%d",&txnid);
     txd=txnid;
     write(sd,&txnid,100);
     
    
     char name[40],message[50];
     
     read(sd,&flag,100);
       
     if(flag == 1)
     {
        printf("ticket details are:\n");
        printf("txnid:%d\t",txd);
        
        read(sd,uvname,100);
        printf("passenger name:%s\t",uvname);
        
        read(sd,&temp,100);
        printf("train_number:%d\t",temp);
     
        read(sd,name,100);
        printf("Train name:%s\t",name);
    
        read(sd,&temp,100);
        printf("booking_status(0:cancelled 1:booked::::: %d\n",temp);
     
   
     }
   else
     {
       read(sd,message,100);
       printf("%s\n",message);
       printf("booking details not found:\n");
       
     }
     
     user_function(sd);
} 
       

void cancel_booking(int sd,char* uname)
{
  char tr_name[40],msg[40];
  int txid;
  
  write(sd,uname,100);
  
  printf("enter transaction id:");
  scanf("%d",&txid);
  write(sd,&txid,100);

  read(sd,msg,100);
  printf("%s\n",msg);
 
 user_function(sd);

}

//================================************for agent*******===================================================================================

void agentLogin(int sd)
{
	char uname[40], passwrd[30], welcome[50];
	int flag=0;
	
	printf("\nEnter the  username: ");
	scanf(" %s",uname);
	printf("Enter password: ");
	scanf(" %s",passwrd);
	
	write(sd, uname, 100);
	write(sd, passwrd,100);
	
	
	read(sd, &flag, 100);
	read(sd, welcome, 100);
	
	printf("\n%s\n",welcome);
	
	//sleep(3);
	
	if(flag == 1)
		agent_function(sd);
		
	if ( flag == 0 )
		{ 
		  mainMenu(sd);
		 
		}
}

void agent_function(int sd)
{

int choice;
	
     printf("==========WELCOME AGENT=============\n1.change password \n2.Book Ticket \n3.Look all bookings\n4.cancel booking \n5.sign out\nEnter your choice: ");
     scanf("%d", &choice);
	
	char buffer[100], uname[40], pass[30];
	int flagch=0;
	write(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
		case 1:achange_password(sd,uname);
			break;
		case 2:abook_ticket(sd,uname);
			break;
                 
               case 3:
                       
		       
			aprint_bookingdetails(sd,uname);
			printf("\n\n");
			break;
               
               case 4:
                        acancel_booking(sd,uname);
                        break;
                        
		case 5:
		    read(sd,buffer,100);
		   printf("%s",buffer);
		   sleep(5);
		   mainMenu(sd);
	}
	
}

void achange_password(int sd, char uname[])
{
    char pass[40],message[40];
    write(sd,uname,100);

    printf("Enter New Password:");
    scanf("%s",pass);
    write(sd,pass,100);

    read(sd,message,100);
    printf("%s",message);
    
    agent_function(sd);
}
void abook_ticket(int sd,char uname[])
  {
     int train_id;
     int txn_id,flag=0;
     char train_name[40],message[50],uvname[50];
     
     printf("enter name of passenger:");
     scanf("%s",uvname);
     write(sd,uvname,100);
    
     
     printf("enter train id:");
     scanf("%d",&train_id);
     write(sd,&train_id,100);
     
     printf("enter train name:");
     scanf("%s",train_name);
     write(sd,train_name,100);
     
     read(sd,&flag,100);
     
   if(flag == 1)
       {
          read(sd,message,100);
          printf("%s\n",message);
          
          read(sd,&txn_id,100);
          printf("%d",txn_id);
       }    
     else
       {
        read(sd,message,100);  // for printinf txn id 
        printf("%s\n",message);
       }

      user_function(sd);

    }
  

void aprint_bookingdetails(int sd, char uname[])
{
     
     int flag =1,temp,txnid,txd;
     //char uname[50];
     char uvname[40];
     write(sd,uname,100);
     
     printf("enter transaction/Booking id:");
     
     scanf("%d",&txnid);
     txd=txnid;
     write(sd,&txnid,100);
     
    
     char name[40],message[50];
     
     read(sd,&flag,100);
       
     if(flag == 1)
     {
        printf("ticket details are:\n");
        printf("txnid:%d\t",txd);
        
        read(sd,uvname,100);
        printf("passenger name:%s\t",uvname);
        
        read(sd,&temp,100);
        printf("train_number:%d\t",temp);
     
        read(sd,name,100);
        printf("Train name:%s\t",name);
    
        read(sd,&temp,100);
        printf("booking_status(0:cancelled 1:booked::::: %d\n",temp);
     
   
     }
   else
     {
       read(sd,message,100);
       printf("%s\n",message);
       printf("booking details not found:\n");
       
     }
     
     agent_function(sd);
} 
  

void acancel_booking(int sd,char* uname)
{
  char tr_name[40],msg[40];
  int txid;
  
  write(sd,uname,100);
  
  printf("enter transaction id:");
   scanf("%d",&txid);
   write(sd,&txid,100);

  read(sd,msg,100);
  printf("%s\n",msg);
 
  agent_function(sd);

}







 



