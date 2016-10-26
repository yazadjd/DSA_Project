Name: Yazad Jamshed Davur
MIS: 111503072
Project topic: Grep Command

Grep Function returns the whole lines matching a specific entered pattern from given input of files prior to the options entered by the user.
Grep stands for Global Regular Expression Print.

Command:
	grep [Options] [Pattern] [Filenames]
Exit Satus:
	Exit status is 0 if match is found and 1 if not found. 2, if an error occurs.

Options:

-A NUM :
	Prints NUM number of lines after each pattern match.
-b:
	Prints the number of bytes read in the file before the output line, where match is found.
-B NUM:
	Prints NUM number of lines before each pattern match.
-C NUM:
	Prints NUM number of lines before and after each pattern match.
-c:
	Prints the number of lines which has the pattern.
-f FILE:
	Compares first file with the rest of the files and prints matching lines.
-H:
	Prints the filename for each match.
-h:
	Does not print the file names even when multiple files are searched.
-i:
	Ignores the case and matches pattern.
-L:
	Prints names of those files from which no matches are found.
-l:
	Prints names of those files from which matches are found.
-m NUM: 
	Prints matches found in the first NUM number of lines in each file.
-n:
	Prints the line number for corresponding matches.
-o:
	Prints only the matching pattern from each line.
-q:
	Exit immediately whether match is found or error as well with zero status.
-R/-r:
	Reads all files from the directory recursively and prints matches. Same as using -d recurse.
-s:
	Supresses error messages about non existent or un readable files.
-T:
	Keeps a tab space when used with -H, -n and -b.
-V:
	Prints the version number and copyright details.
-v:
	Prints all non matching lines
-w:
	Prints only those matches where the whole word is matched. Must be separated by a non word constituent, i.e other than letters, words or digits.
-x:
	Selects only those lines where the entire line matches the substring.
-y:
	Same as -i.
