# Ascii-to-Array

Made to make life eaier when converting ascii art to use in arrays in C

## What it does

This will get a text file by command line, read it and write at the end of the file the copy-ready version of the text to string initialization or assignement

## If you didn't understand the setence above

No worries, I'll give an example (because my english is bad):

textFile.txt:
```
  1| Ex
  2|
  3| X X
  4|  o
```

After the program:
```
  1|Ex
  2|
  3|X X
  4| o
 ...
 15|{'E','x'},
 16|
 17|{'X',' ','X'},
 18|{' ','o'},
```
or: 
```
  1|Ex
  2|
  3|X X
  4| o
 ...
 15|array_0[0][0] = 'E';
 16|array_0[0][1] = 'x';
 17|
 18|array_1[0][0] = 'X';
 19|array_1[0][1] = ' ';
 20|array_1[0][2] = 'X';
 21|array_1[1][0] = ' ';
 22|array_1[1][0] = 'o';
```

After this, copy the lines and put in your code, easy peasy :D

This "or" is there because the program has two mode: the first to initialize an array and the second to assign each element of an array

The text file should be passed by argument. The mode can be passed by argument (being 0 or 1) but it isn't necessary, if you don't put, the program will prompt which mode you want

The default input file in the project is in "D:\test_file.txt"

## Future plans

This code is good, but not complete. There's still thing to do:
  - Support wchar: non-ascii characters aren't supported
  - Use malloc to not have the file line limit
