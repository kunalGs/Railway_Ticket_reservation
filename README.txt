ONLINE RAILWAY TICKET BOOKING SYSTEM


1. Assignment is uploaded in the format MT2021067.zip


2. Download the file and extract the contents.


3. There will be FOUR  files: client.c, server.c, serverutils.h and clientutils.h +  README.txt.


4. client.c serves as the client side, server.c serves as the server side of the online railway ticket booking system application.clientutils.h contains all the functions required for the client application to run.serverutils.h contains all the functions required for the server application to run.




5. store all the files in a folder.


6. Open two terminals one for running server.c and other for running client.c


7. first compile and run server.c. Then compile and run client.c


8. To compile Server:
                        gcc server.c
   To run Server:
                           ./a.out


           
9. To compile client:
                        gcc client.c
   To run client:
                           ./a.out




10. clientutils.h file need not be compiled or run separately. It is already included in client.c


11. You will be prompted to choose one among the five options: 
          1.ADMIN LOGIN
          2. USER LOGIN
          3. AGENT LOGIN
          4. EXIT






12. This application is based on a single central admin. PRESS 1 AND ENTER FOR THE  LOGIN PROMPT OF THE ADMIN.
       Admin details as follows:
            Admin name         : kunal
           Admin password   : admin
No function to change and add admin is there.!


13. To terminate the server side session press "control + c".




14. Files and their contents:


        -> user.dat => this file stores all the details of the user.
        ->  transaction.dat => this file stores all the details of transactions of single and joint users.
        -> train.dat => this file stores the details of all the trains.
        
        -> server.c   => code for server side of the application.
        -> client.c  => code for client side of the application.
        -> serverutils.h => all functions for Add,, search, delete users and trains etc are included in this file and it will be included in header of server.c
        -> clientutils.h => all formats of the client side is implemented in this file which will be included in the header of client.c
15. Agent user is implemented in the similar way as single user. Here username is unique and account numbers for single account holders start from 1000.


16. For concurrency, Fork() is used on the server side.same structure is used for normal users and Agent users . Three logins are implemented, one for each normal user ,agent user  and admin. Client takes details from the user and sends them to the server. Server then processes the information by calling the respective programs and returns the output to the client. Locks are implemented in the agent user to avoid any race conditions.Multiple logins of the accounts can be done from different terminals.