# Embedded Event Logger System

An event logging system implemented in C++ for the course "Algorithms, Data Structures and Design Patterns".

## Project Structure

```
event_logger/
├── include/
│   ├── Event.h
│   ├── EventLog.h
│   ├── EventQueue.h
│   ├── SortStrategy.h
│   └── AlarmSet.h
├── src/
│   ├── Event.cpp
│   ├── EventLog.cpp
│   ├── EventQueue.cpp
│   ├── SortStrategy.cpp
│   ├── AlarmSet.cpp
│   └── main.cpp
├── README.md
└── rapport.md
```

## Build and Run (Visual Studio)

### Option 1: Visual Studio GUI
- Clone the repo: `git clone https://github.com/oskar-lsson/EmbeddedEventLogger`
- Open `.sln` in Visual Studio
- Build and run the project



## Example Usage

When the program starts, enter these commands to test the system:

```
> help                    # Show all commands
> tick 20                 # Generate and process 20 events
> print                   # Show all events in log
> shuffle                 # Shuffle order (to test sorting!)
> print                   # See shuffled order
> sort insertion          # Sort log with insertion sort
> print                   # Show sorted log
> status                  # Show system status
> alarms                  # Show active temperature alarms
> find 3                  # Find all events for sensor 3
> set-threshold 25        # Set alarm threshold to 25°C
> tick 10                 # Generate more events
> alarms                  # Show updated alarms
> exit                    # Exit program
```

## Complete Test Run

Here is a complete sequence demonstrating all functions:

```
> tick 15
Tick run 15 iterations:
  Produced: 15 events
  Consumed: 15 events
  Size of queue 0/10
  Size of logg: 15

> print
=== Event Log (15 events) ===
[0] Sensor 2 - TEMP: 45
[1] Sensor 1 - BUTTON: 0
[2] Sensor 4 - MOTION: 67
... (sorted by timestamp)

> shuffle
Logg is now shuffled
Logg is now sorted: No

> print
=== Event Log (15 events) ===
[5] Sensor 3 - TEMP: 32
[0] Sensor 2 - TEMP: 45
[12] Sensor 1 - MOTION: 88
... (shuffled order!)

> sort insertion
Sorted with Insertion Sort
Logg is now sorted: Yes

> print
=== Event Log (15 events) ===
[0] Sensor 2 - TEMP: 45
[1] Sensor 1 - BUTTON: 0
[2] Sensor 4 - MOTION: 67
... (back in order!)

> find 2
=== Events for Sensor 2 ===
[0] Sensor 2 - TEMP: 45
[5] Sensor 2 - BUTTON: 1
Total 2 events was found

> alarms
=== Active Alarms (2) ===
Threshold: 30°C
 Sensor 2
 Sensor 4

> status
=== System status ===
Queue: 0/10 events
Logg: 15 events
Active alarm: 2
Alarm threshold: 30°C
Logg sorted by timestamp: Yes
```
## Features

### Commands
- `tick <n>` - Run n iterations of event loop
- `print` - Display all events in log
- `shuffle` - Shuffle log order (to test sorting)
- `sort <algorithm>` - Sort log (insertion/selection)
- `find <sensorId>` - Find all events for a sensor
- `alarms` - Show active alarms
- `set-threshold <n>` - Set temperature threshold
- `status` - Show system status
- `help` - Show help
- `exit` - Exit program

### Sorting Algorithms
- `insertion` - Insertion Sort
- `selection` - Selection Sort
