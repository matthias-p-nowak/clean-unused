# clean-unused
A program that removes unused files and broken symlinks.

# Inner workings
The program goes recursively through the supplied directories. 
The arguments might provide an initial cut-off date, hence only considering older files.
The cut-off date is reduced during the program, when the amount of kept files has become too large (twice the considered amount if specified).

* For each recorded file, a structure is created with a shared_ptr link to the next one.
* There exists a global array representing a histogram for the file ages.
* The available memory is requested once for each directory or for each x files, whatever comes first.
* The cleanup determines a new cut-off date, goes through the records and creates a new histogram. 
* Records that are above the cut-off are skipped (memory automatically freed).
