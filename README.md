# mscd-file-format
Description:
There are four different symbols that this format can use, each taking up 2 bits.

00 = EMPTY

01 = DOT

10 = DASH

11 = SPACE


Empty symbols are only used for padding out the file so that the number of bits is divisible by 8.
Dots represent a morse code dot.
Dashes represent a morse code dash. 
Spaces are used to separate individual letters.

Files in this format do not have a starting header, nor does they have a footer.
