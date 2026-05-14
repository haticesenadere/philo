*This project has been created as part of the 42 curriculum by hdere.*

# Philosophers (philo)

## Description

`philo` is a concurrency project based on the classic **Dining Philosophers** problem.

The goal of the project is to simulate a group of philosophers sitting around a circular table. Each philosopher repeatedly alternates between three actions:

- **eating**
- **sleeping**
- **thinking**

To eat, a philosopher must take two forks. Since forks are shared between neighboring philosophers, the program must manage access to these shared resources safely.

This project focuses on fundamental concurrency concepts in C, including:

- POSIX threads with `pthread`
- Mutex-based synchronization
- Shared state protection
- Race condition prevention
- Deadlock avoidance
- Starvation awareness
- Precise time management using millisecond-based constraints
- Clean thread lifecycle management

The simulation must respect strict timing rules. If a philosopher does not eat before `time_to_die` expires, the philosopher dies and the simulation stops.

---

## Instructions

### Compilation

To compile the project, use the provided `Makefile`:

```bash
make
```

This will generate the `philo` executable.

---

### Execution

The program is executed with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers and also the number of forks |
| `time_to_die` | Maximum time in milliseconds a philosopher can live without eating |
| `time_to_eat` | Time in milliseconds a philosopher spends eating |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional argument. If provided, the simulation stops when every philosopher has eaten at least this many times |

All time values are given in **milliseconds**.

---

### Examples

Run the simulation with 5 philosophers:

```bash
./philo 5 800 200 200
```

Run the simulation with 5 philosophers where each philosopher must eat 7 times:

```bash
./philo 5 800 200 200 7
```

---

### Cleaning

Remove object files:

```bash
make clean
```

Remove object files and the executable:

```bash
make fclean
```

Rebuild the project from scratch:

```bash
make re
```

---

## Project Behavior

Each philosopher is represented by a separate thread.

During the simulation, philosophers perform actions in a loop:

```text
take forks → eat → sleep → think
```

The program prints each action with a timestamp in milliseconds:

```text
timestamp_in_ms philosopher_id action
```

Example output:

```text
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

If a philosopher dies, the program prints:

```text
timestamp_in_ms philosopher_id died
```

After a death is detected, the simulation must stop cleanly.

---

## Synchronization Strategy

The project uses mutexes to protect shared resources and avoid unsafe memory access between threads.

Typical shared resources include:

- forks
- simulation stop flag
- last meal timestamps

---

## Notes

- This project uses only mandatory POSIX features. Bonus features (processes, semaphores) are not implemented.
- Maximum tested scale: 200 philosophers with no observable issues.
- Timing precision is ±1-2ms depending on OS scheduler behavior.
- No AI assistance was used in code generation; all logic designed and implemented manually.
- meal counters
- printing/output

Mutexes are used to prevent:

- two philosophers taking the same fork at the same time
- multiple threads printing mixed or corrupted output
- data races on shared simulation state
- inconsistent death detection

The implementation is designed to avoid deadlocks by controlling the order in which philosophers take forks and by carefully managing lock/unlock operations.

---

## Important Concepts

This project helped practice and understand:

- how threads share the same process memory
- why shared data must be protected
- how mutexes prevent race conditions
- how deadlocks can happen
- how starvation can occur
- how timing precision affects concurrent programs
- how to stop multiple threads safely
- how to clean allocated memory and destroy mutexes correctly

---

## Resources

### 42 Resources

- 42 Philosophers subject document

### Manual Pages

Useful manual pages for this project:

```bash
man pthread_create
man pthread_join
man pthread_detach
man pthread_mutex_init
man pthread_mutex_destroy
man pthread_mutex_lock
man pthread_mutex_unlock
man gettimeofday
man usleep
```

### Classic References

- Dining Philosophers problem overview
- POSIX threads documentation
- General operating systems resources about processes, threads, synchronization, and scheduling

---

## AI Usage

AI assistance was used during the project for:

- understanding concurrency concepts
- clarifying threads, mutexes, race conditions, starvation, and deadlocks
- brainstorming edge cases and test scenarios
- reviewing possible failure cases
- drafting and formatting this documentation

AI tool used:

- GitHub Copilot Chat, ChatGBT, and Claude (GPT/LLM-bassed assistants)

All final implementation decisions, code changes, debugging steps, and corrections were reviewed, verified, and applied manually.


