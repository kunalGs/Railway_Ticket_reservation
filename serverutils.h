#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void mainMenu(int sd);
void admin_functions( int sd);
void adminLogin(int sd);
void signup(int sd);
int check_in_account(char uname[]);
void admin_changepassword(int sd);
void addaccount(char uname[], char pass[],int type,int sd);
void deleteaccount(int sd);
void add_train(int sd);
void delete_train(int sd);
void search_train(int sd);
void userLogin(int sd);
void user_function( int sd);
void change_password(int sd);
int check_train(char tr_nm[]);
void book_ticket(int sd);
void print_bookingdetails(int sd);
void cancel_booking(int sd);

void agentLogin(int sd);
void agent_function( int sd);
void achange_password(int sd);
void abook_ticket(int sd);
void aprint_bookingdetails(int sd);
void acancel_booking(int sd);
struct user  
     {

       int userid;
       int usertype;  // 1 for admin  2 for normal  3 for agent
       char name[40];
       char password[30];
       int current_bal;
       int status;

     };
     
  struct transaction
  {
     int txnid;
     char username[40];
     int trainno;
     char train_name[30];
     int booking_status;   //1 for booked ticket ...    0 for cancelled ticket // if ticket is cancelled  booking status is cancelled 
    
  };
  
  struct train
  {
    int train_no;
    char train_name[20];
    int status;
  
  };


void mainMenu(int sd)
{
	int choice,fd;
	read(sd, &choice, sizeof(choice));

	switch(choice)
	{
				
		case 2: userLogin(sd);
				break;
		case 1: adminLogin(sd);
				break;
		case 3: agentLogin(sd);
				break;
		case 4: exit(0);
				break;
                default: 
                       write(sd,"no any choice found:sorry",100);
	}
}
	
  void adminLogin(int sd)
	{
	       char uname[40], pass[30];
	       int flag=0;
	       read(sd, uname, sizeof(uname));
	       read(sd, pass, sizeof(pass));
	      if(!strcmp(uname,"kunal") && !strcmp(pass,"admin"))
	       {
			flag = 1;
		       
	       }
	      else
	       {
	          flag =0;
	       }
	       write(sd,&flag,100);
	       
	       if(flag ==1 )	
	       {
	        write(sd,"=========================Welcome_Admin:Kunal==========================",100);
		admin_functions(sd);
	       }
	       else
	       {
		
		write(sd,"Invalid_Credentials_of_Admin: Redirecting to main menu:", 100);
		mainMenu(sd);
	       }
	
	}
	
	
	
void admin_functions( int sd)
{
	int choice;
	char uname[40], pass[40], uname1[40];
	int flagch=0;
	read(sd, &choice, sizeof(choice));
	switch(choice)
	{
		case 1:signup(sd);
			break;
		case 2:deleteaccount(sd);
			break;
		
		
		case 3:
		         // for details of the account user 
		         
		         read(sd, uname1, sizeof(uname1));
			  struct user user2;

	                 int fd2 = open("user.dat", O_RDWR, 0666);
	
	                 while(read(fd2, (char *)&user2, sizeof(struct user))) // it will also move seek pointer to the last
	                      {

		                 if(!strcmp(user2.name, uname1))
			             {
			 	        close(fd2);
			 	        flagch = 1;
				          break;
			             }
	                      }
	                    
	            
	             
	                  write(sd,&flagch,sizeof(flagch));	
			if(flagch == 1)
			{
			  
			    write(sd,"Account_found__:",100);
			    write(sd,&user2.userid,100);
			    write(sd,user2.name,100);
			    write(sd,user2.password,100);
			    
			    write(sd,&user2.usertype,100);
			    write(sd,&user2.current_bal,100);
			    write(sd,&user2.status,100);
			 close(fd2);
			
			}
			else
			{
				write(sd, "Account does not exist with the given Username", 100);
				 close(fd2);
			}
			
			
			
			admin_functions(sd);
			break;
		
		
			
		case 4: add_train(sd);
		         break;
		         
		case 5: delete_train(sd);
		           break;
		
		case 6: search_train(sd);
		           break;
		case 7: 
		      admin_changepassword(sd);
		                 break;    
		case 8: 
		    write(sd,"signing off Admin: Kunal",100);
		    mainMenu(sd);
         }
	
}


void signup(int sd)
{
	char uname[40], pass[30];
	int type;

	read(sd, uname, sizeof(uname));
	read(sd, pass, sizeof(pass));
	write(sd,"type of user:normal_account-->2_____agent_account-->3:::::",100);
	
        read(sd,&type,100);
        
	if(!check_in_account(uname)) // to check if username is already present
	{
		addaccount(uname, pass,type,sd);
		admin_functions(sd);
	}
	else
	{
		write(sd, "Username already exist\n", 100);
		admin_functions(sd);
	}	

}

int check_in_account(char uname[])   // to check if the user details present already in the account
{
	struct user user1;

	int fd1 = open("user.dat", O_RDWR , 0666);
	
	while(read(fd1, (char *)&user1, sizeof(struct user))) // it will also move seek pointer to the last
	{

		if(!strcmp(user1.name, uname))
			{
				close(fd1);
				return 1;
			}
	}
	close(fd1);
	return 0;	
	
}
void addaccount(char uname[], char pass[],int type,int sd)
{
	srand(time(0));

	int fd1 = open("user.dat", O_RDWR , 0666);

	struct user user1;

	strcpy(user1.name, uname);
	strcpy(user1.password, pass);

        user1.usertype = type;
	user1.current_bal=11111;
        user1.status=1;
	user1.userid=(rand()%1001)+3000;

	write(fd1,(char *)&user1, sizeof(struct user));      // seek pointer moved to last by check_in_account

	write(sd, "-------Account Created successfully -------", 100);
	
	close(fd1);
}




void deleteaccount(int sd)
{
   char name[100],message[100];
 
   read(sd,name,100);

   int flag=0;
		struct user user1;
                int fd1 = open("user.dat", O_RDWR , 0666);
                
	        while(read(fd1, (char *)&user1, sizeof(struct user)))
	          {
                     
                     
                     
		     if(!strcmp(user1.name,name))
			{
				user1.status=0;
				lseek(fd1,-1 * sizeof(struct user),SEEK_CUR);
		               write(fd1,(char*)&user1,sizeof(struct user));
		               flag =1;
				break;
			}
	          }
		
		
		if(flag)
		{
		  write(sd,"user deleted successfully:status made 0",100);
		  close(fd1);
		   admin_functions(sd);
		}
	
	     else
	         {
		write(sd, "Username does not exist", 100);
		close(fd1);
		admin_functions(sd);
	        }	


}
void admin_changepassword(int sd)
{
  char uname[40],pass[40];
  read(sd,uname,100);
  struct user userm;
  int flag =0;
  int pos=0;
  int fd1 = open("user.dat", O_RDWR , 0666);
//  int fd2 = open("user.dat",O_CREAT | O_APPEND | O_WR , 0666);
  read(sd,pass,100);
               
                  //lseek(fd1,0,SEEK_SET);
	          while(read(fd1, &userm , sizeof(struct user))) 
	         {      

		   if(!strcmp(userm.name,uname))
			{
			  
			  strcpy(userm.password,pass);
			  lseek(fd1,-1* sizeof(struct user),SEEK_CUR);
			  write(fd1,(char *)&userm,sizeof(struct user));
			  //lseek(fd1,0,SEEK_CUR); 
			  fsync(fd1);
			  flag =1;	
			  break;
			}
	           }
	         if(flag == 1)
	         write(sd,"password changed successfully",100);
	         
	         else 
	         write(sd,"password not changed\n",100);  
	         
  fsync(fd1);	         
  close(fd1);
  admin_functions(sd);

}

/*struct train
  {
    int train_no;
    char train_name[20];
    int status;
  
  };*/
  
void add_train(int sd)
{
           
            srand(time(0));
         char tname[40];
         read(sd, tname, sizeof(tname));
       if(!check_train(tname)) // to check if trainname is already present
	{
            int fdt = open("train.dat", O_CREAT | O_APPEND | O_RDWR , 0666);

	     struct train trainx;

	     strcpy(trainx.train_name, tname);
	     trainx.status=1;
	     trainx.train_no =(rand()%100001)+3000;

	     write(fdt,(char *)&trainx, sizeof(struct train));      

	    write(sd, "-------Train Addeded successfully -------", 100);
	     
	     close(fdt);
	     admin_functions(sd);
	}
	else
	{
		write(sd, "Train_name already exist\n", 100);
		admin_functions(sd);
	}	

}
void search_train(int sd)   
{
	struct train train1;
	int flag=0;
	char tr_nm[40];
        read(sd,tr_nm,100);
	int fd1 = open("train.dat", O_CREAT | O_APPEND | O_RDWR , 0666);
	
	while(read(fd1, (char *)&train1, sizeof(struct train))) // it will also move seek pointer to the last
	{

		if( !strcmp(train1.train_name,tr_nm) )
			{       
				flag=1;
				break;
				
			}
	}
                            	
           write(sd,&flag,100);
			        if(flag == 1)
			        {
				write(sd,&train1.train_no,100);
				write(sd,train1.train_name,100);
				write(sd,&train1.status,100);
				}
				else 
				write(sd,"===train name not found====",100);
	fsync(fd1);
	close(fd1);
	
	admin_functions(sd);	

}


void delete_train(int sd)
{
   char name[100],message[100];
 
   read(sd,name,100);

   int flag=0;
		struct train train1;
                int fd1 = open("train.dat", O_RDWR | O_CREAT | O_APPEND , 0666);
                
	        while(read(fd1, (char *)&train1, sizeof(struct train)))
	          {
                     
                     
                     
		     if(!strcmp(train1.train_name,name))
			{
				train1.status=0;
				lseek(fd1,-1 * sizeof(struct train),SEEK_CUR);
		               write(fd1,(char*)&train1,sizeof(struct train));
		               flag =1;
				break;
			}
	          }
		
		
		if(flag)
		{
		  write(sd,"train deleted successfully:status made 0",100);
		  close(fd1);
		   admin_functions(sd);
		}
	
	     else
	         {
		write(sd, "train_name does not exist", 100);
		close(fd1);
		admin_functions(sd);
	        }	


}



//==========================================for normal users ====================================================================


void userLogin(int sd)
	{
	       char uname[100], pass[100];
	       int flag=0;
	       
	       
	       read(sd, uname,100);
	       read(sd, pass,100);
	      
	      
	      // checking from the file 
	       struct user user1;
              int fd1 = open("user.dat", O_RDWR , 0666);
	
	          while(read(fd1,&user1, sizeof(struct user)) ) 
	         {

		    if(!strcmp(user1.name,uname) && !strcmp(user1.password,pass) )
			{
				
				flag=1;
				break;
			}
	         }
	         close(fd1);
	       
	        if(flag == 1)
	           {
		
		     write(sd, &flag, 100);
		     write(sd,"=========================Welcome_User==========================",100);
		     user_function(sd);
	           }
	      else
	       {	
		flag=0;
		write(sd, &flag, 100);
		write(sd,"Invalid_Credentials_of_User", 100);
		
		//sleep(8);
		mainMenu(sd);
	       }
	
	}
	
	
	
void user_function( int sd)
{
	int choice;
	char uname[40], pass[40], uname1[40];
	int flagch=0;
	read(sd, &choice, sizeof(choice));
	switch(choice)
	{
		case 1:change_password(sd);
			break;
		case 2:book_ticket(sd);
			break;
		
		
		case 3:
		        print_bookingdetails(sd);
			break;
		  case 4: 
		          cancel_booking(sd);
		          break;
		          
		case 5: 
		    write(sd,"signing off user",100);
		    mainMenu(sd);
         }
	
}

void change_password(int sd)
{
  char uname[40],pass[40];
  read(sd,uname,100);
  struct user userm;
  int flag =0;
  int pos=0;
  int fd1 = open("user.dat", O_RDWR , 0666);

  read(sd,pass,100);
               
                  //lseek(fd1,0,SEEK_SET);
	          while(read(fd1, &userm , sizeof(struct user))) 
	         {      

		   if(!strcmp(userm.name,uname))
			{
			  
			  strcpy(userm.password,pass);
			  lseek(fd1,-1* sizeof(struct user),SEEK_CUR);
			  write(fd1,(char *)&userm,sizeof(struct user));
			  //lseek(fd1,0,SEEK_CUR); 
			  fsync(fd1);
			  flag =1;	
			  break;
			}
	           }
	         if(flag == 1)
	         write(sd,"password changed successfully",100);
	         
	         else 
	         write(sd,"password not changed\n",100);  
	         
	         
close(fd1);
user_function(sd);

}



int check_train(char* tr_nm)   // to check if the train details present already in the account
{
	struct train train1;

	int fd1 = open("train.dat", O_RDWR , 0666);
	
	while(read(fd1, (char *)&train1, sizeof(struct train))) // it will also move seek pointer to the last
	{

		if( !strcmp(train1.train_name,tr_nm) )
			{
				fsync(fd1);
				close(fd1);
				return 1;
			}
	}
	fsync(fd1);
	close(fd1);
	return 0;	

}



void book_ticket(int sd)
{
  /*  
  struct transaction
  
     int txnid;
     char username[40];
     int trainno;
     char train_name[30];
     int booking_status;   //1 for booked ticket ...    0 for cancelled ticket // if ticket is cancelled  booking status is cancelled 
     
  
  */
  char trainname[100],uname[100];
  int train_id;
  read(sd,uname,100);
  struct transaction tx1;
  struct user userm;
  int flag =0;
  int txid;
  read(sd,&train_id,100);
  
  read(sd,trainname,100);
 int fdtr = open("transaction.dat", O_CREAT | O_APPEND | O_RDWR , 0666);

 srand(time(0));	
	if(check_train(trainname) )
			{
			  tx1.txnid=(rand()%100001)+6000;
			  txid = tx1.txnid;
			  strcpy(tx1.username,uname);
			  tx1.trainno = train_id;
			  strcpy(tx1.train_name,trainname);
			  tx1.booking_status=1;
			  write(fdtr,(char *)&tx1,sizeof(struct transaction));
			  close(fdtr);
			  flag =1;	
			}
		write(sd,&flag,100);
			if(flag == 1)
			{
			      write(sd,"Ticket Booked TXN ID IS:",100);
			      write(sd,&txid,100);
			}
	  else
	  write(sd,"train name does not exist",100);
	  
	  
	  
 fsync(fdtr);
 close(fdtr);	  
	  
	  
 user_function(sd);
}


void print_bookingdetails(int sd)
{
     char uname[100];
     struct transaction tx2;
     int flag=0,txnid;

      read(sd,uname,100);
      read(sd,&txnid,100);

      int fdtr = open("transaction.dat", O_RDWR , 0666);

       while(read(fdtr,(char*)&tx2,sizeof(struct transaction)))
       {
         if((tx2.txnid == txnid) )
           {  
               flag=1;
               break;
           }
       
       }
     write(sd,&flag,100);
       if(flag == 1)
       {
               write(sd,tx2.username,100);
               write(sd,&tx2.trainno,100);
               write(sd,tx2.train_name,100);
               write(sd,&tx2.booking_status,100);
               
       }
       if(flag ==0)
       {
         write(sd,"INVALID BOOKING DETAILS",100);
       }
       fsync(fdtr);
       close(fdtr);
       
       user_function(sd);

}


void cancel_booking(int sd)
{
  char uname[40];
  int tr_id;
  read(sd,uname,100);
  int flag =0;
  
  read(sd,&tr_id,100);
  
  struct transaction tx2;
  int fdtr = open("transaction.dat", O_RDWR , 0666);

       while(read(fdtr,(char*)&tx2,sizeof(struct transaction)))
       {
        if((tx2.txnid == tr_id))
           { 
               tx2.booking_status=0;  // ticket cancelled
               lseek(fdtr,-1 * sizeof(struct transaction) ,SEEK_CUR); 
               write(fdtr,(char *)&tx2,sizeof(struct transaction));
               flag=1;
               break;
           } 
       }
   fsync(fdtr);    
   close(fdtr);     
   if(flag == 1)
   write(sd,"(((((((((((......ticket cancelled.........)))))))))",100);
   else 
   write(sd,"user has not booked any ticket in the given train",100);

user_function(sd);
}

// ==================================================****for agent *******=====================================================================
//============================================================================================================================================
//===============================================================================================================================================

void agentLogin(int sd)
	{
	       char uname[100], pass[100];
	       int flag=0;
	       
	       
	       read(sd, uname,100);
	       read(sd, pass,100);
	      
	      
	      // checking from the file 
	       struct user user1;
              int fd1 = open("user.dat", O_RDWR , 0666);
	
	          while(read(fd1,&user1, sizeof(struct user)) ) // it will also move seek pointer to the last
	         {

		    if(!strcmp(user1.name,uname) && !strcmp(user1.password,pass) )
			{
				
				flag=1;
				break;
			}
	         }
	         close(fd1);
	       
	        if(flag == 1)
	           {
		
		     write(sd, &flag, 100);
		     write(sd,"=========================Welcome_AGENT==========================",100);
		     agent_function(sd);
	           }
	      else
	       {	
		flag=0;
		write(sd, &flag, 100);
		write(sd,"Invalid_Credentials_of_User", 100);
		
		//sleep(8);
		mainMenu(sd);
	       }
	
	}
	
	
	
void agent_function( int sd)
{
	int choice;
	char uname[40], pass[40], uname1[40];
	int flagch=0;
	read(sd, &choice, sizeof(choice));
	switch(choice)
	{
		case 1:achange_password(sd);
			break;
		case 2:abook_ticket(sd);
			break;
		
		
		case 3:
		        aprint_bookingdetails(sd);
			break;
		  case 4: 
		          acancel_booking(sd);
		          break;
		          
		case 5: 
		    write(sd,"signing off user",100);
		    mainMenu(sd);
         }
	
}

void achange_password(int sd)
{
  char uname[40],pass[40];
  read(sd,uname,100);
  struct user userm;
  int flag =0;
  int pos=0;
  int fd1 = open("user.dat", O_RDWR , 0666);
//  int fd2 = open("user.dat",O_CREAT | O_APPEND | O_WR , 0666);
  read(sd,pass,100);
               
                  //lseek(fd1,0,SEEK_SET);
	    while(read(fd1, &userm , sizeof(struct user))) 
	         {      

		   if(!strcmp(userm.name,uname))
			{  
			   strcpy(userm.password,pass);
			   
			    struct flock lock;
                           lock.l_pid = getpid();
                           lock.l_start = lseek(fd1,-1* sizeof(struct user),SEEK_CUR);  // WRITING TO THE LAST OF THE FILE 
                           lock.l_len = sizeof(struct transaction);
                
		           lock.l_type = F_WRLCK;	
		           lock.l_whence = SEEK_CUR;
		           fcntl(fd1, F_SETLKW, &lock);
			  
			  
			   write(fd1,(char *)&userm,sizeof(struct user));
			  
			   lock.l_type = F_UNLCK;	         // unlocking.
                          fcntl(fd1, F_SETLK, &lock);		// unlocking. 
			 
			  fsync(fd1);	                  
                          close(fd1);
			  
			  flag =1;	
			  break;
			}
			
			
	           }
	         if(flag == 1)
	         write(sd,"password changed successfully",100);
	         
	         else 
	         write(sd,"password not changed\n",100);  
	         

agent_function(sd);

}



void abook_ticket(int sd)
{
  /*  
  struct transaction
  
     int txnid;
     char username[40];
     int trainno;
     char train_name[30];
     int booking_status;   //1 for booked ticket ...    0 for cancelled ticket // if ticket is cancelled  booking status is cancelled 
     
  
  */
  char trainname[100],uname[100];
  int train_id;
  read(sd,uname,100);
  struct transaction tx1;
  struct user userm;
  int flag =0;
  int txid;
  read(sd,&train_id,100);
  
  read(sd,trainname,100);
 int fdtr = open("transaction.dat", O_RDWR , 0666);
 
 srand(time(0));	
	if(check_train(trainname) )
			{
			  tx1.txnid=(rand()%100001)+6000;
			  txid = tx1.txnid;
			  strcpy(tx1.username,uname);
			  tx1.trainno = train_id;
			  strcpy(tx1.train_name,trainname);
			  tx1.booking_status=1;
			  
			   struct flock lock;
                          lock.l_pid = getpid();
                          lock.l_start = lseek(fdtr,0,SEEK_END);   // WRITING TO THE LAST OF THE FILE 
                          lock.l_len = sizeof(struct transaction);
                
		           lock.l_type = F_WRLCK;	
		           lock.l_whence = SEEK_CUR;
		           fcntl(fdtr, F_SETLKW, &lock);		// locking.  -> here on critical section for agent user.
               
			  write(fdtr,(char *)&tx1,sizeof(struct transaction));
			  close(fdtr);
			  
			  lock.l_type = F_UNLCK;	                // unlocking.
                         fcntl(fdtr, F_SETLK, &lock);		// unlocking. 
			  flag =1;	
			}
		write(sd,&flag,100);
			if(flag == 1)
			{
			      write(sd,"Ticket Booked TXN ID IS:",100);
			      write(sd,&txid,100);
			}
	  else
	  write(sd,"train name does not exist",100);
	  
	  
	  
 fsync(fdtr);
 close(fdtr);	  
	  
	  
 agent_function(sd);
}


void aprint_bookingdetails(int sd)
{
     char uname[100];
     struct transaction tx2;
     int flag=0,txnid;

      read(sd,uname,100);
      read(sd,&txnid,100);

      int fdtr = open("transaction.dat", O_RDWR , 0666);
        struct flock fl;
        fl.l_type   = F_RDLCK;  
        fl.l_whence = SEEK_SET; 
        fl.l_start  = 0;        
        fl.l_len    = 0;           // basically read locking the whole file
        fl.l_pid    = getpid(); 
        fcntl(fdtr, F_SETLKW, &fl);

       while(read(fdtr,(char*)&tx2,sizeof(struct transaction)))
       {
         if((tx2.txnid == txnid) )
           {  
               flag=1;
               break;
           }
       
       }
       
      fl.l_type = F_UNLCK;	         // unlocking.
      fcntl(fdtr, F_SETLK, &fl);		// unlocking. 
      fsync(fdtr);
      close(fdtr);
       
   
     write(sd,&flag,100);
       if(flag == 1)
       {
               write(sd,tx2.username,100);
               write(sd,&tx2.trainno,100);
               write(sd,tx2.train_name,100);
               write(sd,&tx2.booking_status,100);
               
       }
       if(flag ==0)
       {
         write(sd,"INVALID BOOKING DETAILS",100);
       }
       
       agent_function(sd);

}

void acancel_booking(int sd)
{
  
  char uname[40];
  int tr_id;
  read(sd,uname,100);
  int flag =0;
  
  read(sd,&tr_id,100);
  
  struct transaction tx2;
  int fdtr = open("transaction.dat", O_RDWR , 0666);

             
		
		
	
		
  while(read(fdtr,(char*)&tx2,sizeof(struct transaction)))
       {
        if((tx2.txnid == tr_id))
           { 
               
		
               tx2.booking_status=0;  // ticket cancelled
               struct flock lock;
               lock.l_pid = getpid();
               lock.l_start = lseek(fdtr,-1 * sizeof(struct transaction),SEEK_CUR); 
               lock.l_len = sizeof(struct transaction);
                
		lock.l_type = F_WRLCK;	
		lock.l_whence = SEEK_CUR;
		fcntl(fdtr, F_SETLKW, &lock);		// locking.  -> here on critical section for agent user.
               
               write(fdtr,(char *)&tx2,sizeof(struct transaction));
               
               flag=1;
               break;
               
               lock.l_type = F_UNLCK;	         // unlocking.
               fcntl(fdtr, F_SETLK, &lock);		// unlocking. 
           } 
       }
       
   
   
   
   fsync(fdtr);   
   close(fdtr); 
   
   if(flag == 1)
   write(sd,"(((((((((((......ticket cancelled.........)))))))))",100);
   else 
   write(sd,"agent has not booked any ticket in the given train",100);

agent_function(sd);
}

	

