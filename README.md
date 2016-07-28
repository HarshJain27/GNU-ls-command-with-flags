# GNU-ls-command-with-flags
Implementation of GNU ls command with flags. Details can be referred from README.

Flags implemented:
R: Recursive listing of files and directories 
l : Long listing format 
a : All 
t : Sort by modification time 
S: Sort by size 
i:  Print the index number of each file 


Some of the usages: 
$ ./a.out -l -a -t
$ ./a.out -lat
$ ./a.out l dir1/dir2 (can be relative or absolute) 
$ ./a.out latSi path1 path2 path3 
$ ./a.out  path1 path2 path3 -l -a -tS -i 
$ ./a.out  abc.txt -l -a -i abc.pdf dir1
