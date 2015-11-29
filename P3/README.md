<HTML>
<HEAD>
<TITLE>CS/ECE 354, Assignment 3</TITLE>
<link rel=stylesheet type="text/css" HREF="/csheader/cs.css">
</HEAD>

<BODY>

<center><h1> Assignment 3</h1></center>
<center><h1>CS/ECE 354</h1></center>
<HR>
<h3>Please post all questions to the piazza page</h3>


<H3>Collaboration Policy</H3>
<p>
For this assignment,
you may work in pairs (2 people).
All students (whether working in a pair or not) must individually
turn in the assignment.
Therefore, 2 copies of the assignment will be turned in
for those working as a pair.
The grader will choose to grade only one copy of a pair's work,
and assign the same score to both students.
<p>
If one member of a pair does something unexpected with respect to turning 
in the assignment 
(for example: bad copy of the source code, late,  or perhaps not turning in 
portions of the assignment), 
then <i>both</i> of the pair get the same penalty and the same score.
<p>
If working in a pair, the names and sections of <i>both</i> students
must appear as comments at the top of all files that will be turned in.


<H2>Overview</H2>

<P>
The purpose of this assignment is to understand more about how caches work,
learning a bit about simulation along the way,
and picking up introductory skills in generating a Makefile.
</P>
<P>
Please read this entire assignment specification before starting
on the first step.
</P>

<H2>Description</H2>


<p>
For this assignment, you will use a program called <i>pin</i>
that produces cache performance statistics, 
given cache parameters and an executable.
</p>

<p>
<i>pin</i> runs the executable to internally produce a series of
<b>address traces</b>.
These are the ordered set of addresses that a program generates
as it runs.  
They represent the addresses read from or written to as the program runs.
Each address may represent a read for the instruction fetch 
or a read or write to a variable stored in memory.
</p>
<p>
The address traces are then used internally with a <b>cache simulator</b>.
The cache simulator is a program that acts as if it is a cache,
and for each trace, does a look up to determine if that address
causes a cache hit or a cache miss.
The simulator tallies the hits/misses, and when it has completed
simulation of all the traces, it prints these statistics for
you.
</p>
<p>
To run a simulation, use a command line similar to
<pre>
/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 64 -ds 16384 -da 1 -db 64 -- yourexe
</pre>
In this command, you would need to replace "yourexe" with the name of your executable file.
The first time you run this command, you should <b>copy, 
paste, and then alter this command,
instead of typing it in</b>, to reduce errors.
The arrow keys on your keyboard can be your friend here,
before you generate a Makefile.
Once you put a target for this command line into your Makefile,
your life gets easy!
</p>
<p>
6 of these command line arguments specify cache parameters to <i>pin</i>.
The simulator presumes separate I-cache and D-cache.
The I-cache holds only the machine code instructions, 
as read when doing an instruction fetch.
The D-cache holds all other data read or written while a program runs.
<p>
For the I-cache, specify
<ul>
<li>
<u><code>-ia 1</code></u>
<br>This causes the set associativity of the cache to be 1,
or direct mapped.  This is the only value we will use in this assignment.
</li>
<li>
<u><code>-is N</code></u>
<br>Substitute a power of 2 for N.
This sets the capacity for this cache.
For all our simulations, use a 16KB (16384) size.
</li>
<li>
<u><code>-ib N</code></u>
<br>Substitute a power of 2 for N.
N is the number of bytes per block.
<b>You will be changing this parameter in this assignment.</b>
</li>
</ul>
<p>
For the D-cache, specify
<ul>
<li>
<u><code>-da 1</code></u>
<br>This causes the set associativity of the cache to be 1,
or direct mapped.  This is the only value we will use in this assignment.
</li>
<li>
<u><code>-ds N</code></u>
<br>Substitute a power of 2 for N.
This sets the capacity for this cache.
For all our simulations, use a  16KB (16384) size.
</li>
<li>
<u><code>-db N</code></u>
<br>Substitute a power of 2 for N.
N is the number of bytes per block.
<b>You will be changing this parameter in this assignment.</b>
</li>
</ul>
</p>
<p>
As you work your way through this assignment, you will be
answering questions that are in the file:
</p>
<pre>
   /p/course/cs354-common/public/html/handouts/a3questions
</pre>
<p>
Copy this file to your own directory, and add your answers to this file. 
The file will be turned in.
</p>

<u><h3> Step One: 1-dimensional array code</h3></u>

<p>
Write a very small C program called <code>cache1D.c</code>
that sets each element
of an array of 100,000 integers to the value of its index.
The statement that sets a single array element will be something like
<pre>
  arr[i] = i;
</pre>
The resulting executable program will be used with <i>pin</i>
to generate statistics about cache usage for your analysis.
To make the analysis easier, the C program is required to
</p>
<ul>
<li>
Declare the array as a global variable,  so the declaration will
be outside of <code>main()</code> (and prior to  <code>main()</code> 
within the source code file).  
This requirement will cause the array to be within the global data segment, 
and <i>not</i> on the stack.
</li>
<li>
Place a <code>for loop</code> inside <code>main()</code>
to set each element of the array.
One array element is set during each iteration of the for loop. 
</li>
</ul>

<p>
Compile your program with
</p>
<pre>
  gcc -o cache1D cache1D.c -Wall -m32
</pre>
<p> Notice that this command differs slightly from the compilation
that we did for assignment 1 this semester.  
It does <b>NOT</b> have the <code>-O</code> option, so
the compiler is not going to do optimizations. It is important that you <b>do not</b> use the <code>-O</code> option.
Use these same compiler options for all the programs in <i>this</i> assignment.
</p>

<p>
Before you go any further, it is time to figure out how to do
this compilation using 
<i>make</i>: a powerful tool that helps us to automate our
compilation, as well as automate many other sets of commands.
</p>
<p> To help you put together a Makefile, try one or more of
<ul>
<li>
<a HREF="http://mrbook.org/tutorials/make/">
A brief tutorial about make</A> 
by Hector Urtubia can start you on your way.
</li>
<li>
Within the online textbook written by our own Arpaci-Dusseau professors,
see the 
<a HREF="http://pages.cs.wisc.edu/~remzi/OSTEP/lab-tutorial.pdf">
Laboratory: Tutorial</A>. 
You'll benefit from pages 1-8 of this tutorial, although pages 5-8 specifically
discuss <i>make</i>.
</li>
<li>
University of Maryland has a nice 
<a HREF="https://www.cs.umd.edu/class/fall2002/cmsc214/Tutorial/makefile.html">
introduction to make</A>; 
especially helpful will be to look at the topic of dummy targets.
You will want to add a dummy target for each of your simulations.
</li>
<li>
UW-Madison alumni Professor Newhall explains 
<a HREF="http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html">
using make</A> in helpful and concise prose. 
</ul>
<p>
Make sure that you have a single target to make the <i>cache1D</i>
executable. 
(And for each 2 subsequent programa, add a new target, and then
use <i>make</i>. You will be turning in your Makefile.
Please name your target with the name of the executable,
which should be the same as your source code, but without
the <code>.c</code> file name extension.)
<u><h3> Step Two: 1-dimensional array code analysis</h3></u>
<p>
Run the 3 simulations needed to answer the questions in the
<code>a3questions</code> file.
Then, answer the questions.
<b>Running the simulations will be amazingly easy, if you
put a target for each block size simulation into your Makefile!
So, do it!</b>
</p>

<u><h3> Step Three: 2-dimensional arrays, two ways</h3></u>
<p> Repeat what you did for the 1 dimensional array with two
programs that set elements of a 2-dimensional array.
Many students will not have used 2-dimensional arrays in C before;
the K&R book, section 5.7-5.9, starting on page 110 will be a 
good reference for declaring and using 2D arrays.
</p>
<p> 
First, write a C program called <code>cache2Drows.c</code> that
sets each element of a 3000 row by 500 column array of
integers to the sum of the row index and the column index.
The statement that sets an element will be something like
<pre>
  arr2d[row][col] = row + col;
</pre>
Use a set of nested <code>for loops</code>,
where the <b>inner loop works its way through the elements of single row of
the array, and the outer loop iterates through the rows</b>.
</p>
<p> 
Run the cache analysis requested in the  
<code>a3questions</code> file.
</p>
<p> 
Second, write another C program called <code>cache2Dcols.c</code> that
does the same thing as <code>cache2Drows.c</code> did, 
<i>but in a different order.</i>  
This program has the <b>inner loop work its way through the elements of a single column
of the array, and the outer loop iterates through the columns</b>. 
If you truly understand your code, it should be close to trivial
to copy <code>cache2Drows.c</code> and modify it to become
<code>cache2Dcols.c</code>.
</p>
</p>
Last step will be to figure out, understand, and explain
why these 2 programs (that accomplish exactly the same thing)
result in different cache performance.
<p> 

<H2>Handing In the Assignment</H2>
You will be turning in 5 files in total:
<li>3 source code files
(<code>cache1D.c</code>, <code>cache2Drows.c</code>, and
<code>cache2Dcols.c</code>)</li>
<li>your <code>Makefile</code> and</li> 
<li>your question answers within
file <code>a3questions</code> for grading.</li> 
<p>We will use your <code>Makefile</code> to compile.
We will compile the 3 source files using following commands:
<pre>
make cache1D
make cache2Drows
make cache2Dcols
</pre>
<b> Make sure the targets in your makefile are named appropriately so
that the 3 make commands work.</b>
Copy all these files into your handin directory. 
Your handin directory for this project is 
<br><code>/p/course/cs354-common/public/spring15.handin/login/p3</code> 
<br>where <code>login</code> is your login. 
</p>
<p> <i>If you are working as part of a pair</i>,
you must turn in an extra file.
This file will contain the names and sections of <b>both</b> students
in the pair.
As an example, if Kevin worked with Haseeb on this assignment,
the contents of the extra file for both Kevin and Haseeb would be
<pre>
Kevin Zhang   section 1
Haseeb Tariq  section 2
</pre>
<p> The name of this file is specialized to help the 354 automated
grading tools identify who worked together.
This file name is composed of the CS logins of the partners
separated by a period.
The file name is of the form &lt;login1&gt;.&lt;login2&gt;.
Kevin's login is <code>kzhang</code>, and Haseeb's login is
<code>haseeb</code>.
The file name that both use will be <code>kzhang.haseeb </code>;
please have both partners use the same file name.
It does not matter which partner's name is first within this
file name.

<u><H3>Requirements</H3></u>

<ol>
<li>
Include a comment at the top of the source code of both programs with your 
<i>name</i> and <i>section</i> 
(and your partner's name and section, if working in a pair). 
</li>
<li>
Use the instructional Linux machines for this assignment!
A penalty will be imposed for any program that was obviously edited
on a Windows machine and transferred to the Unix machines
for turning in.
It is annoying to see Windows line endings (^M) at the
end of every line. Points will be taken off for such mistakes.
</li>
<li>
Your programs must compile
on an instructional Linux machine as indicated in this specification
<i>without warnings or errors</i>.
When grading, we will use your Makefile, so make sure that it works!
</li>
</ol>
  <H2>About Copying Code and Academic Misconduct</H2>
          <p><a href="http://pages.cs.wisc.edu/~cs354-2/dontcheat.html">Don't cheat</a>. Read this link carefully.</p>
<p>
  <i>
    Do <b>not</b> post your assignment solutions (or drafts) on any
    publicly accessible web sites.
    This specifically includes GitHub.
    It is academic misconduct to post your solution.
  </i>
</p>
<p>
  For almost any C program that does something useful,
  someone has already written this program and
  further, has posted it for others to use.
  These programs do not do much that is useful,
  and are not likely posted anywhere.
  Still, it is academic misconduct for you to copy or use some or
  all of a program
  that has been written by someone else.
</p>
<p>
  The penalty for academic misconduct on this assignment
  (and all CS/ECE 354 assignments)
  will be a failing grade in the course.
  This penalty is significantly more harsh than if you simply do not
  do the assignment.
  You will gain much more by doing the assignment
  than by copying, possibly modifying,
  and turning in someone else's effort.

</p>

</BODY>
</HTML>

