# oracle
:cd: A 1-up to the Microsoft FAT file system.<br />
<p align="center">
  <img alt="1-up" src="https://user-images.githubusercontent.com/16131737/37385328-c42681cc-2710-11e8-8213-13ce1aa3aafd.gif" />
</p>

## TODO
+ Generate multiple binaries from single source
+ Finish `diskinfo` (PART 1)

## Overview
This project was an assignment for the [Operating Systems](https://github.com/williamgrosset/thomas/blob/master/csc360_p2.pdf) class at the University of Victoria. The multithreaded train scheduler is a simulation of priority-based trains being loaded concurrently and dispatched across a single track. See the [requirements document](https://github.com/williamgrosset/thomas/blob/master/csc360_p2.pdf) and [design document](https://github.com/williamgrosset/thomas/blob/master/csc360_p2_solutions.pdf) for more details.

### Usage
#### Compile
```
make all 
```

#### Run `diskinfo` 
```
./diskinfo.o test.img
```

#### Run `disklist` 
```
./disklist.o test.img /sub_dir 
```

#### Run `diskget` 
```
./diskget.o test.img /sub_dir/foo2.txt foo.txt 
```

#### Run `diskput` 
```
./diskput.o test.img foo.txt /sub_dir/foo3.txt 
```

#### Clean build
```
make clean
```
