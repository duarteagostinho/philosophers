# 🍝 Philosophers
> A simulation of the classic **Dining Philosophers Problem**, implemented in C using POSIX threads and mutexes.
This project is part of the **42 School** curriculum and focuses on concurrency, synchronization, and race condition prevention.
---
## 📖 About
The **Dining Philosophers Problem** is a classic computer science concurrency problem formulated by Edsger Dijkstra. It models a scenario where a number of philosophers sit around a circular table with a fork between each pair of adjacent philosophers. A philosopher must hold both their left and right forks to eat. The challenge is to coordinate access to the shared forks without causing **deadlock** or **starvation**.
This implementation uses:
- **POSIX threads (`pthreads`)** — one thread per philosopher plus a dedicated monitor thread.
- **Mutexes** — one per fork, plus additional mutexes for shared state and output synchronization.
- An **even/odd fork-pickup strategy** to prevent deadlock.
---
## 🗂️ Project Structure
```
philosophers/
├── philo/
│   ├── philo.h          # Data structures and function prototypes
│   ├── Makefile
│   ├── src/
│   │   ├── main.c       # Entry point and single-philosopher edge case
│   │   ├── init.c       # Data, fork and philosopher initialization
│   │   ├── actions.c    # Fork-picking, eating, and meal tracking
│   │   ├── mods.c       # Philosopher routine, monitor thread, thread management
│   │   └── check.c      # Argument validation
│   └── utils/
│       ├── utils.c      # ft_atoi, ft_putstr
│       └── utils2.c     # get_time, ft_usleep, print_message, ft_exit, ft_free
└── count_eats           # Helper script to count how many times each philosopher ate
```
---
## ⚙️ Compilation
```bash
cd philo
make
```
To remove object files:
```bash
make clean
```
To remove object files and the binary:
```bash
make fclean
```
To recompile from scratch:
```bash
make re
```
---
## 🚀 Usage
```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```
| Argument                  | Description                                                                 |
|---------------------------|-----------------------------------------------------------------------------|
| `number_of_philosophers`  | Number of philosophers (and forks) at the table. Maximum: **200**.         |
| `time_to_die` (ms)        | Time in milliseconds before a philosopher dies if they haven't started eating. |
| `time_to_eat` (ms)        | Time in milliseconds a philosopher spends eating.                           |
| `time_to_sleep` (ms)      | Time in milliseconds a philosopher spends sleeping.                         |
| `number_of_meals` *(opt)* | If specified, the simulation stops when every philosopher has eaten at least this many times. |
### Examples
```bash
# 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200
# Same as above, but stop after each philosopher eats 7 times
./philo 5 800 200 200 7
# Edge case: a single philosopher (will always die)
./philo 1 800 200 200
```
---
## 📋 Output Format
Each state change is printed in the following format:
```
<timestamp_ms> <philosopher_id> <state>
```
Possible states:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`
Example:
```
0      1 has taken a fork
0      1 has taken a fork
0      1 is eating
200    1 is sleeping
400    1 is thinking
...
800    2 died
```
> No message is printed after a philosopher dies.
---
## 🛠️ Implementation Details
### Threads & Synchronization
- Each philosopher runs in its own **thread**.
- A separate **monitor thread** continuously checks whether any philosopher has exceeded `time_to_die` since their last meal, and signals termination when all meals are completed.
- Each fork is protected by a **mutex**.
- Shared state (`dead`, `finished`) is protected by a dedicated **data mutex**.
- Console output is serialized using a **write mutex** to prevent interleaved messages.
### Deadlock Prevention
- **Even-numbered** philosophers pick up their left fork first, then their right.
- **Odd-numbered** philosophers pick up their right fork first, then their left.
- This asymmetry breaks the circular wait condition.
### Single Philosopher Edge Case
- With only one philosopher, there is only one fork. The philosopher picks it up, waits `time_to_die` milliseconds, and dies — handled explicitly in `main.c`.
---
## 🧪 Testing Helper
A convenience script is included to verify that meal counts are balanced across philosophers:
```bash
# Usage: ./count_eats <philo_nr> <time_to_die> <time_to_eat> <time_to_sleep> [meals]
./count_eats 5 800 200 200 7
```
Output:
```
Philo 1: 7 meals
Philo 2: 7 meals
Philo 3: 7 meals
Philo 4: 7 meals
Philo 5: 7 meals
```
---
## 📚 Concepts Covered
- **Concurrency** and **multithreading** with `pthread`
- **Mutex** creation, locking, and destruction
- **Race condition** prevention
- **Deadlock** and **starvation** avoidance
- Precise timing with `gettimeofday`
- Memory management and proper cleanup
---
## 👤 Author
**Duarte Agostinho** — [duandrad@student.42lisboa.com](mailto:duandrad@student.42lisboa.com)  
*42 Lisboa*
