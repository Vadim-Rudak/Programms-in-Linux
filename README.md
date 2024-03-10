# Programms-in-Linux

You must install the compiler

```
sudo apt-get install gcc
```
# hello linux

Compiling a program in C is done using the following code

```
gcc hello_linux.c -o hello_linux.exe
```

Running a compiled program

```
./hello_linux.exe
```

# write in file

Compiling and then running a compiled program

```
./write_in_file.exe name_your_file
```

To close the program you must enter the @ symbol

```
text@
```

# get text from file

Compiling and then running a compiled program. You must specify the file name and the number of lines to be output.

```
./get_text_from_file.exe name_your_file num_read_lines
```
# copy file

Compiling and then running a compiled program. Enter the copied file and the new one

```
./copy_file.exe name_copied_file name_new_file
```

# see all files in catalog

```
./see_all_files_in_catalogs.exe your_path num_min_size num_max_size result_file.txt
```

# see all files in catalog with find by size and date

```
./see_all_files_with_params.exe your_path name_file num_min_size num_max_size 01/01/2024 10/02/2024
```

# two child processes and info

```
./two_child_processes.exe
```

# find for identical files

N - max number of concurrent processes

```
./find_for_identical_files.exe path1 path2 N
```

# parent and child processes with info

```
./parent_and_child_processes.exe
```

# process with Tailor

A program for finding an array of K consecutive values ​​of the function y[i]=sin(2*PI*i/N) ( i=0,1,2…K-1) using the Taylor series. The user specifies the values ​​of K, N and the number n of terms of the Taylor series. A separate thread is launched to calculate each term of the Taylor series. Each thread displays its id and the calculated value of the series. The main process waits for all threads to complete and sums all terms of the Taylor series. He writes the resulting value y[i] to the result file.

Edit InPath and OuPath

```
./process_with_Tailor.exe
```

