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

In this code, I will introduce the application of an example of deadlock avoidance banker's algorithm.
