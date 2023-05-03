# Data Hiding with NTFS Alternative Data Streams

#### So basically the idea is to use simple data hiding that is available in NTFS file system running on Windows. It is called Alternative Data Streams and can be accessed in the command line:

```bat
-- create empty file
C:\Users\jhgrz\Documents> type nul > file.txt

-- echo the data to the stream, which is being created
C:\Users\jhgrz\Documents> echo I'm hidin here > file.txt:hidden

-- to access the stream we type more command
C:\Users\jhgrz\Documents> more < file.txt:hidden
I'm hidin here
```
