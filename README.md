# Junhao Zheng
# 200372760
# Deadlock avoidance (banker's algorithm)

# Introduction
Deadlock is a situation where a set of processes are blocked because each process is holding a resource and waiting for another resource acquired by some other process. It may occur when a process or thread enters a waiting state. When it occurs, it may cause harm to operating system. Therefore, it is neccessary to handle deadlock.

There are four main idea for deadlock handling:
- Deadlock prevention
- Deadlock avoidance
- Deadlock detection
- Deadlock relief

In this code, I will introduce the application of an example of deadlock avoidance banker's algorithm. In the method of avoiding deadlock, the limited condition is weak, and it is possible to obtain satisfactory system performance. In this method, the system state is divided into safe state and unsafe state. As long as the system is always in safe state, deadlock can be avoided.
The basic idea of banker algorithm is to judge whether the system is safe before allocating resources; if so, allocate. It is the most representative algorithm to avoid deadlock.

# Challenge
The challenge is to find the algorithm and implement it with c language. To find the appropriate algorithm, a lot of resources are needed and select to the appropriate one.

# Instruction

If you want to use built-in data, enter 0  
Then the system will show you safety sequence  
Enter the process which you want to allocate, such as 1
Enter the resource which you want to allocate to process, such as 1 0 2  
then the program will analysis safe or not  
for more instruction, please check test.log file  

If the process cusneed requests REQUEST  [i], the banker algorithm will judge according to the following rules.

(1) If REQUEST  [cusneed] [i] < = NEED [cusneed] [i], turn to (2); otherwise, an error occurs.  
(2) If REQUEST [cusneed] [i] < = available [i], turn to (3); otherwise, wait.   
(3) The system tries to allocate resources and modify relevant data:  
AVAILABLE[i]-=REQUEST[cusneed][i];  
ALLOCATION[cusneed][i]+=REQUEST[cusneed][i];  
NEED[cusneed][i]-=REQUEST[cusneed][i];  
(4) The system performs security check, if it is safe, the allocation is established; otherwise, the exploratory allocation is invalid, the system is restored to its original state, and the process is waiting.  
Security checking algorithm  
(1) Set two working vectors Work = AVAILABLE;  FINISH  
(2) Find a process from the process set that meets the following conditions,  
FINISH==false;  
NEED<=Work;  
If found, execute (3); otherwise, execute (4)  
(3) Set the process to obtain resources, which can be executed smoothly until completion, so as to release resources.  
Work=Work+ALLOCATION;  
Finish=true;  
