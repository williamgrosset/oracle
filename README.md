# oracle
:cd: A 1-up to the Microsoft FAT file system.<br />
![1-up](https://user-images.githubusercontent.com/16131737/37385328-c42681cc-2710-11e8-8213-13ce1aa3aafd.gif)

## Overview
This project was an assignment for the [Operating Systems](https://github.com/williamgrosset/thomas/blob/master/csc360_p2.pdf) class at the University of Victoria. The multithreaded train scheduler is a simulation of priority-based trains being loaded concurrently and dispatched across a single track. See the [requirements document](https://github.com/williamgrosset/thomas/blob/master/csc360_p2.pdf) and [design document](https://github.com/williamgrosset/thomas/blob/master/csc360_p2_solutions.pdf) for more details.

### Usage
#### Compile
```
make setup
```

#### Run scheduler
```
make run f=trains.txt
# OR
./mts.o trains.txt
```

#### Clean build
```
make clean
```
