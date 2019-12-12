# Ascii-to-Array

Made to make life eaier when converting ascii art to use in arrays in C

## What it does

This will get a text file by command line, read it and write at the end of the file the copy-ready version of the text to string initialization

## If you didn't understand the setence above

No worries, I'll give an example (because my english is bad):

textFile.txt:
```
  1| Example text
  2|
  3| X X
  4|  o
```

After the program:
```
  1|Example text
  2|
  3|X X
  4| o
 ...
 15|{'E','x','a','m','p','l','e',' ','t','e','x','t'},
 16|
 17|{'X',' ','X'},
 18|{' ','o'},
```

After this, copy the lines and put in your code, easy peasy :D
Remember, the text file should be passed by argument

## Future plans

This code is good, but not complete. There's still thing to do:
  - Support wchar: non-ascii characters aren't supported
  - Better coma usage: there's always comma after ```}```. In the last ```}``` it shouldn't be there, also the space after the comma inside the brackets
  - Complete array support: It just puts the brackets in the line, it needs to put one extra open bracket in the start line and a close bracket at the end of the groups.
  PS: line groups are separeted by a empty line
  - Support array assignment: so you'll have just to change the variable name
