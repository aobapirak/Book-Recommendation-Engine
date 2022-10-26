
README.txt

Group 	: icutmyhairbecauseyoudontcaremyheart
Members : Kasikan   Wisetkamin   (Mook)  ID: 63070503403
    	  Chayathit Rattanapokil (Peach) ID: 63070503405   
    	  Poonyavee Wongwisetsuk (Pup)   ID: 63070503430
    	  Apirak    Senarak      (Aob)   ID: 63070503458

Book Recommendation Engine
--------------------------
Many websites includes "recommendation engine" in their sites. Basically, recommendation engine is a program that can recommend items 
that the users might be interested in based on their activities on the website. In this program, books are recommended to users 
based on the factors: community and content. The program also stores a large number of book in the database.

User Manual
--------------------------

#How to run the program
 1.1) compile by make on terminal
 1.2) in case makeFile not worked :( 
      ==> gcc -o main main.c chainedHashTable.c dataManagement.c linkedListUtil.c login.c register.c search.c validation.c recommendBook.c purchase.c
 2) './main' to run the program

#Validation on register system
 Name: space, specific, alphabet, start with uppercas
 Username: space, specific, range 6-16, unique
 Password: space, specific, range 8-16, alphanumeric

#How the program works
 1) Run the program using the instructions given above. 

 2) Menu: After running, the system will give you three options to select: 
	
		[1] Create an Account
        [2] Log in
        [3] Exit Program
    
    If you don't have an account, you must select sign up and create an account first.
    If you have an account, you can login using the username and password that you picked.
    Note: You must login before you can continue to any other process*
	      or you can use test user => Username:testuser1 Password:testuser1
	
	Creating an account will give you three space to fill out: username,name, and password.
	Username cannot be previously used and password require a number. For example: user12345

 3) Search: Afterward, the user will be redirected to the search menu. The menu will display 5 attributes which you can select to use for searching. 
	
	Select the desired attribute to search
            [1] Search by Name
            [2] Search by Author
            [3] Search by Genre
            [4] Search by Keyword
			[5] Checkout 
    
	Enter [DONE to exit]: 

    When searching, must enter the full name of the attribute.
	You must search for a book to select a book to purchase.
	When searching with keyword, it only require one of the keywords to match.
	You cannot select Checkout until you have added a book to your cart.
	Typing 'DONE' before checkout will cause the cart to empty and log out of account
	You can exit the search menu and logout by typing 'DONE'
    	Note: Searching is not case-sensitive.
    	

 4) Search Result: If your search is successful, it will display all of the books found. 
	Example:
                   	[All book founds]
	_______________________________________________________

        	[#No.1] Book: Harry Potter and the Philosopher's Stone
        	[#No.2] Book: Percy Jackson & the Olympians: The Lightning Thief
        	[#No.3] Book: Percy Jackson & the Olympians:The Titan's Curse
        	[#No.4] Book: Percy Jackson & the Olympians: The Battle of the Labyrinth
	_______________________________________________________

   	- - - - - - - - - - - - - - - - - - - - - - - - -	

   	If there are multiple books, the user will be given option to select a book that they are interested in.
   	Then, the system will display the information of the selected book.
   	The user will be allows to select a different book or continue with the current selected book.
	Note: You can return without selecting a book by typing 'DONE'

   	- - - - - - - - - - - - - - - - - - - - - - - - -	
	Example:
        	Which book do you interested in?

        	Select [DONE to back]: 1

	          Title Book  : Harry Potter and the Philosopher's Stone
	          Author      : JK Rowling
	          Genre       : Fantasy
	          Page Length : 223

 5) Select Book: The system will ask the user whether they want to add the selected book to cart or return to search for another book.
	
	It will look like this:  

	Would you like to purchase this book? [Y/N]:Y

		[Added to cart!]

	Would you like to search again?
	Else you will return to menu [Y/N]: 

	If you picked yes, the program will add the book to your cart. Afterward, it will ask if you want to search for another book or return to menu.
	else if you picked no, the program will not add anything to cart and you will return to search for another book

	Keep in mind that you can't add a book that you have already purchased before in the cart

 6) Checkout: If you return to menu and picked checkout, the system will register information to the database

	It will look something like this:

					[All books purchased]
	_______________________________________________________

        [#No.1] Book: Harry Potter and the Philosopher's Stone
        [#No.2] Book: Percy Jackson & the Olympians: The Lightning Thief
        [#No.3] Book: Percy Jackson & the Olympians:The Titan's Curse
        [#No.4] Book: Percy Jackson & the Olympians: The Battle of the Labyrinth
	_______________________________________________________

	Once the receipt is printed, the information will be registered into the user's record and the book's record
	All purchases you make can affect the community-based recommendation of other users.
	
 7) Recommend: The system will recommend a list of book. Community-based and Content-based

	For community:	
		The program will randomly pick a book from your receipt. (Specifically book with record)
		if none of the book you purchased has a record, it will shows message that say there is not enough information.

		Afterward, it will go through the picked book's record and randomly pick a user. (Specifically user with record)
		if none of the user has a record, it will show message that say there is not enough information.
	
		Then, it will print all the book from the randomly picked and filtered user's record.

	For content:
		The program will randomly pick a book from the cart of purchased book. 
		Then it will find all the attributes of the book and see which book in the book's database has the most similar attributes
		Books with similar attributes will be given similarity score where the book with highest score is recommend.

	It will look something like this:
	__________________________________________________________
			
			[Recommended by community]

			User 'chayathit00' who purchased 'Harry Potter and the Philosopher's Stone' also bought:

			Book:'Elon Musk'
			Written by Ashlee Vance

			Book:'Simply Raymond'
			Written by Raymond Blanc

			Book:'Weirdo'
			Written by Zadie Smith
	__________________________________________________________

			[Recommended by content]

			A book that is similar to 'Harry Potter and the Philosopher's Stone'

			Book:'Harry Potter and the Chamber of Secrets'
			Written by J. K. Rowling
	__________________________________________________________

        Would you like to make another purchase?
        Else you will log out [Y/N]:

	Afterward, you're given an option to either make another purchase or logout

 8) Next purchase: Purchase more books
	
	If you choose to make another purchase, you will first be given options to buy from the recommended books.

	like this:
                   		[All book founds]
		__________________________________________________________
        		[#No.1] Book: Elon Musk
				[#No.2] Book: Simply Raymond
				[#No.3] Book: Weirdo
				[#No.4] Book: Harry Potter and the Chamber of Secrets
		__________________________________________________________
				Which book are you interested in?
				Select [0 to back]:

	You can select a book and return to menu or you can type '0' to go back and a short menu will be displayed

  		//Next action:
		__________________________________________________________
			
			[1] Search for another book
			[2] Checkout
			[3] Logout
			
			What would you like to do?:

	You can return to search menu, checkout, or logout which will delete your current cart.


FAQ
--------------------------
How recommendation work?
    Content-based: Recommend books based on the attributes of books that the user has purchased.
    Community-based: Recommend books based on the history of users who has purchased the same book

How the books are stored?
    The books are stored in a textfile and informations is separated by '~' and a short description of the content.
    Ex:
        "title:Sapiens:A Brief History of Humankind~author:Yuval Noah Harari~genre:Comic~length in pages:369~keywords:human,history,evolution"

What Hash Function is used?

    The program is currently using 'bitwiseOpHash' which is a function based on code by Sally Goldin. It is a robust hash function that uses bitwise operations to
    modify string values. The program used bitwiseOpHash because during our testing of a few hash functions, this function have the least collision.


List of modified files and functions written by Aj.Sally Goldin 
--------------------------
[FILES]
abstractHashTable.h  
	-> Remove hashTableRemove()

chainedHashTable.c
	-> Remove hashTableRemove()
	-> Modified hashTableLookup() -- <|  
	-> Modified hashTableInsert() -- <|
	-> Modified hashTableInit() --   <| All these function make to work with the new modified variable which is more about attribute to separate data
	-> Modified hashTableFree() --   <|  
	-> Added bitwiseOphash()
	-> Modified variable: table -- become double pointer one for attribute, another one for data
	-> Added freeRecordAndBookList()

linkedListUtil.h
	-> No change

linkedListUtil.c 
	-> No change

[FUNCTION]
bitwiseOpHash
	It is a robust hash function that uses bitwise operations to modify string values, using for return hashValue.
	The program used bitwiseOpHash because during our testing of a few hash functions, this function have the least collision.

Note:
	We research for information about bug malloc.c because sometime we run and find this problem when recommendlist have an odd number return.
	=> malloc.c:2379: sysmalloc: Assertion `(old_top == initial_top (av) 
           && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) 
           && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.	
	
	=> We print and figure out where the bug happen and find it in listInsertEnd() function when allocate pNew

	=> And we found that Problems arise with Ubuntu some version and C library

	Anyway, This problem will occur not too much and on laptop of some member in the team only.