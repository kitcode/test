# Dining Philosophers

## Description

An implementation of a solution to the Dining Philosophers problem
(a classic multi-thread synchronization problem).  This particular
implementation demonstrates the usage of microkernel task groups,
Mutex APIs and timer drivers from multiple (6) tasks.

The philosopher always tries to get the lowest fork first (f1 then f2).
When done, he will give back the forks in the reverse order (f2 then f1).
If he gets two forks, he is EATING.  Otherwise, he is THINKING.

Each philosopher will randomly alternate between the EATING and THINKING
states.

## Sample Output

```
Philosopher 0 EATING
Philosopher 1 THINKING
Philosopher 2 THINKING
Philosopher 3 EATING
Philosopher 4 THINKING
Philosopher 5 THINKING
```

