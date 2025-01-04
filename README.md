# Philosophers  

The Philosophers project is part of the 42 School curriculum and involves solving the classic "Dining Philosophers" problem. This project focuses on understanding and implementing concurrency, thread synchronization, and resource management in C.  

---  

## The Problem  

The Dining Philosophers problem is a conceptual exercise where:  
1. Five philosophers sit at a circular table, alternating between eating and thinking.  
2. Each philosopher has a fork to their left and right, but they must hold both forks to eat.  
3. Philosophers must avoid starving while ensuring forks are shared without deadlock or data races.  

The challenge is to implement a simulation that respects these rules using threads and synchronization primitives.  

---  

## Features  

- **Simulation of Philosophers**:  
  - Each philosopher alternates between thinking, eating, and sleeping.  
  - Eating requires two forks (shared resources).  

- **Thread-Based Concurrency**:  
  - Each philosopher is represented by a thread.  

- **Synchronization**:  
  - Mutexes or semaphores to manage access to shared resources (forks).  

- **Avoid Deadlock**:  
  - Implements strategies to avoid deadlock scenarios.  

- **Simulation Options**:  
  - Configurable parameters for the number of philosophers, time to die, eat, and sleep.  

---  

## Installation  

1. Clone the repository:  
2. got ot philo dir and simply run `make`

---

## Usage
the programme takes the following arguments :

[number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
1. number_of_philosophers: The number of philosophers and also the numberof forks.
2. time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
3. time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
4. time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
5. number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least [number_of_times_each_philosopher_must_eat]
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

**e.g.**:

./philo 5 800 200 200 : No philosopher should die

./philo 5 800 200 200 7 : No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.

./philo 4 310 200 100 : One philosopher should die
