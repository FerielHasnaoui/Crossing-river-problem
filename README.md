# Crossing-river-problem 

Two types of characters (processes), Hackers and Windows developers, try to cross a river with a boat that can hold only 4 passengers. The following patterns must be avoided to guarantee a trip in the right conditions: 1 hacker and 3 Windows, 1 Windows and 3 hackers. Any other schema is "safe" for example 4 W or 4 H or 2/2. The boat will only start once all 4 seats are occupied.
Theoretical solution of the problem:
You need 3 programs: creat.c in which you create and initialize all the variables, and necessary semaphores. The creat.c program will be the first to launch. Below is the theoretical solution for the hacker's program. The windows processes program is the same with modification of variables and semaphores by windows ones.

//The hacker's code (hacker.c)
P(mutex)
hackers += 1
if hackers == 4{
for(i=0;i<3;i++) V(hackerQueue)
hackers = 0
isCaptain = True 
//add a display here where the captain process presents itself as captain (with its pid and type h or w )
} 
else if( hackers == 2 and windows >= 2){
V(hackerQueue)
V(windowsQueue)
V(windowsQueue)
windows -= 2
hackers = 0
isCaptain = True
//add a display here where the captain process presents itself (with its pid and type h or w )
} else{
V(mutex)
P(hackerQueue) ;
}
board () //function that just displays a message "I'm a (hacker or windows) process of pid x, I'm boarding the boat"
barriere(4) // call of a barrier function for 4 processes
if isCaptain{
rowBoat () //display of the captain that the boat has sailed
V(mutex)
}

CHALLENGES :
1- Set up a reusable barrier to add to the library "semaphores.h".
2- implement the two Windows and hacker programs and perform a functional test with 2 Windows and two hackers.
3- Perform a test with 3 hackers and 1 Windows (or vice versa).
4-What will happen if we send a kill 2 (signal SIGINT) to the captain process (before it executes the rowboat function (add sleep before the rowboat() function to both types of processes to slow them down ) Use ipcs –s –i semid to check the status of used semaphores.
5-Now we are going to send a kill 2 signal to another process which is not the captain (after executing the board() function but before the barrier), what happens? What is the status of other processes, use ipcs –s –i semid.
6-To solve the problems occurring in 5 and 4, implement a handler function for the SIGINT signal in which if it is the captain who receives the signal, he will start the boat and above all release the mutex before ending. Does this solve the problem?
7-Now propose a similar handler-based solution for the case of stopping another non-captain process before getting to the barrier.
8-Modify the program in a way that If ever the 4 places are not filled after a certain waiting time, the trip is canceled (each process will display "trip canceled") to get out of the blockage and the processes will end thereafter without executing the board() function
Hint: use the semtimedop function instead of semop in the call to P(hackerQueue) or P(windowsQueue), and implement a function Ptimed to call instead of P which calls semtimedop instead of semop.
