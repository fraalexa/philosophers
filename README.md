This project has been created as part of the 42 curriculum by <fraalexa>.

**Problem description**

There are N philosophers sitting around a circular table.
There is an equal number of forks and philosophers. Each philosopher needs two forks to eat: one on their left and one on their right.

Each philosopher must eat within a specified time interval. If a philosopher does not eat before their time limit expires, they die.

The philosophers continuously repeat the following cycle: eat, sleep, and think.

There are two ways to run the simulation: with or without a maximum number of times each philosopher is allowed to eat.

Based on the input parameters, the program must simulate this behavior and determine whether any philosopher dies or whether they all reach the maximum number of allowed meals. If a philosopher dies, the program must immediately stop the simulation.

**Philosophers' routine cycle:**

1 - Pick up two forks.
2 - Eat.
3 - Release the forks and sleep.
4 - Think.

**AI usage**

I requested AI to:
1 - Explain general purpose and usage of mutexes and threads;
2 - Explain some details about the usleep function and oversleeping.
3 - Explain the data race and deadlock problems.

**Build the program:**

make

**The program must be executed as follows:**

./philo [number_of_philosophers time_to_die] [time_to_eat] [time_to_sleep] 
optional - [number_of_times_each_philosopher_must_eat]

Example:

./philo 10 800 200 200 10
