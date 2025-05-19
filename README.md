# 🧠 Philosophers

## 📘 Description
This project is an implementation of the classic **Dining Philosophers Problem**, a fundamental exercise in concurrent programming. It illustrates the challenges of managing shared resources, avoiding deadlocks, and preventing starvation in multithreaded systems.

---

## 🧩 Problem Statement

- N philosophers sit at a round table.
- There are N forks, one placed between each pair of philosophers.
- Philosophers alternate between **thinking**, **eating**, and **sleeping**.
- A philosopher needs **two forks** (left and right) to eat.
- A philosopher dies if they do not start eating within `time_to_die` milliseconds.
- The simulation must prevent:
  - **Deadlocks** (no circular wait on forks)
  - **Starvation** (no philosopher can be permanently blocked from eating)

---

## ✅ Requirements

- Language: **C**
- Must follow the **42 School Norm**.
- Must use only **POSIX threads** (`pthread`).
- The program must handle the following command-line arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


## 🖥️ Usage Example

```bash
./philo 5 800 200 200
```

This will run the simulation with:
- 5 philosophers
- Each philosopher must eat within 800ms or they die
- Eating takes 200ms
- Sleeping takes 200ms

## 🧾 Output Format

The program will print state changes in the following format:

```
[timestamp_in_ms] X has taken a fork
[timestamp_in_ms] X is eating
[timestamp_in_ms] X is sleeping
[timestamp_in_ms] X is thinking
[timestamp_in_ms] X died
```

Where:
- `timestamp_in_ms`: Time elapsed since the start of the simulation
- `X`: Philosopher number (starting from 1)

## 📁 Project Structure

```
philo/
├── Makefile
├── README.md
├── inc/
│   └── philo.h
└── src/
    ├── main.c
    ├── philo.c
    ├── actions.c
    ├── monitor.c
    └── utils.c
```

## 👤 Author
Izan Segura

## 📄 License
This project is part of the 42 School Curriculum and follows its academic and license policies.

