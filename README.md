# oracle
:cd: A 1-up to the Microsoft FAT file system.<br />
<p align="center">
  <img alt="1-up" src="https://user-images.githubusercontent.com/16131737/37385328-c42681cc-2710-11e8-8213-13ce1aa3aafd.gif" />
</p>

## TODO
+ Convert all integer values to Big Endian (`netinit/in.h`)
+ Generate multiple binaries from single source
+ Finish `diskinfo` (PART 1)
  + ...
+ Finish `disklist` (PART 2)
+ Finish `diskget` (PART 3)
+ Finish `diskput` (PART 4)
+ Clean-up repo
+ Test on linux lab machine

## Overview
This project was an assignment for the [Operating Systems](https://github.com/williamgrosset/oracle/blob/master/csc360_p3.pdf) class at the University of Victoria. The file system implementation

## Usage
### Compile
```
make all 
```

### Clean build
```
make clean
```

### Run `diskinfo`
Displays information about the file system. See sample output.
```bash
./diskinfo.o test.img
```

#### Sample output
...

### Run `disklist`
Display content for the given directory. See sample output.
```bash
./disklist.o test.img /sub_dir 
```
#### Sample output
...

### Run `diskget`
Copy a file from the file system to the current directory. If specified file is not found in file system, an error message will be displayed. See sample output.
```bash
./diskget.o test.img /sub_dir/foo2.txt foo.txt 
```

#### Sample output
...

### Run `diskput`
Copy a file from current directory into the given directory of the file system. If specified file is not found in current directory, an error message will be displayed. See sample output.
```bash
./diskput.o test.img foo.txt /sub_dir/foo3.txt 
```

#### Sample output
...
