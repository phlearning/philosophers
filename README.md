# Philosophers

- [Philosophers](#philosophers)
	- [Concepts to understand](#concepts-to-understand)
	- [How to use ?](#how-to-use-)
	- [What to expect ?](#what-to-expect-)
	- [What is a thread ?](#what-is-a-thread-)
		- [What are the differences between process and thread? ](#what-are-the-differences-between-process-and-thread)
		- [Why Multithreading?](#why-multithreading)
		- [Threads operate faster than processes due to following reasons: ](#threads-operate-faster-than-processes-due-to-following-reasons)
	- [Ref](#ref)


## Concepts to understand
	The use of threads, race condition, mutex

## How to use ?
> ./philo [nb_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] ([nb_of_meals_needed]) 

## What to expect ?
| [nb_of_philo] | [time_to_die] | [time_to_eat] | [time_to_sleep] | [nb_of_meals_needed] |  [expectations]  |
| :-----------: | :-----------: | :-----------: | :-------------: | :------------------: | :--------------: |
|       4       |      800      |      200      |       200       |          0           | Philo never die  |
|       4       |      200      |      200      |       200       |          0           | Philo should die |

## What is a thread ?
	A thread is a single sequence stream within a process. Because threads have some of the properties of processes, they are sometimes called lightweight processes.

### What are the differences between process and thread? 

	Threads are not independent from each other unlike processes. As a result, threads shares with other threads their code section, data section and OS resources like open files and signals. But, like processes, a thread has its own program counter (PC), a register set, and a stack space.

### Why Multithreading? 
	Threads are popular way to improve application through parallelism. For example, in a browser, multiple tabs can be different threads. MS word uses multiple threads, one thread to format the text, other thread to process inputs, etc. 

### Threads operate faster than processes due to following reasons: 

   1. Thread creation is much faster. 
   2. Context switching between threads is much faster. 
   3. Threads can be terminated easily.
   4. Communication between threads is faster.


## Ref
- [Codevault Threads Course](https://code-vault.net/course/6q6s9eerd0:1609007479575)
- [Markdown](https://marketplace.visualstudio.com/items?itemName=yzhang.markdown-all-in-one)
- [What is a thread ?](https://www.iitk.ac.in/esc101/05Aug/tutorial/essential/threads/definition.html)