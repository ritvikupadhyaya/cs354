<HTML>
<HEAD>
<TITLE>CS/ECE 354, Assignment 4</TITLE>
<link rel=stylesheet type="text/css" HREF="/csheader/cs.css">
</HEAD>

<BODY>

<center><h1> Assignment 4</h1></center>
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
(for example: bad copy of the source code, late, names and sections
are missing, or perhaps not turning in 
portions of the assignment), 
then <i>both</i> of the pair get the same penalty and the same score.
<p>
If working in a pair, the names and sections of <i>both</i> students
must appear as comments at the top of all files of the turned in assignment.

<H2>Overview</H2>

<P>
The purpose of this program is to gain insight into the asynchronous
nature of interrupts, and handling interrupts and traps,
while expanding C programming skills.
By their very definition, interrupts occur
at times not connected to the running program; this makes them <b>asynchronous</b>.
</P>

<H3>Program Description</H3>


<p>
This assignment consists of 2 programs, and each will be
turned in.
</p>

<p>
These programs use specific software interrupts,
requiring you to set up the capture of the interrupts to
be handled, and also provide the handling code.
</p>

<h3> First Program: A Periodic Alarm</h3>

<h3> Periodic Alarm: Step 1</h3>
<p>
Write a C program called <code>intdate.c</code> that is composed of two parts.
One part is the main function, which does <i>absolutely nothing</i>
 in an infinite loop.
Before entering the infinite loop,
the main function will set up what is to happen when an alarm goes off 
3 seconds later.
When the alarm goes off,
this causes a <code>SIGALRM</code> interrupt to signal the program.
This interrupt is to be caught by the program,
and handled by the second part of the program,
an interrupt handler.
This handler function is to print out the current time, in the
same format as the
Unix <i>date</i> command,
re-arm the alarm to go off three seconds later,
and then return back to the main function (which continues
its infinite loop doing nothing).
</p>
<p>
Since the main function is to keep running forever,
the <code>main()</code> function will contain an infinite loop such as
</p>
<pre>
   while (1) {
   }
</pre>
<p>
Before executing the infinite loop, the main() function
needs to set up the alarm. Once it starts executing the infinite loop 
it does nothing useful.
For this partially complete program, output will look
something like
</p>
<pre>
% intdate
Date will be printed every 3 seconds.
Enter ^C to end the program:
current time is Tue Mar  4 13:15:21 2014
current time is Tue Mar  4 13:15:24 2014
current time is Tue Mar  4 13:15:27 2014
^C
</pre>
<p>
Notice that to stop the program from running,
you type in a Control-c.
Remember for the next part of this assignment:
typing Control-c sends a software interrupt (called SIGINT)
to the running program.
</p>
<p>
Like the set of C programs in Assignment 1, you will use library functions to
help you.
Just like Assignment 1,
it is <i>important</i> to check the return values of these functions,
such that your program detects error conditions and acts
in response to those errors.
Reference the man pages of these functions that you will use:
</p>
<ul>
<li>  <code>time()</code> and <code>ctime()</code>
are library calls to help your handler obtain and print the
time in the correct format.
<li>  <code>alarm()</code>
activates the <code>SIGALRM</code> interrupt to occur in a 
specified number of seconds.
<li>  <code>sigaction()</code>  (<i> do not use signal()</i> )
sets up what happens when the specific type of interrupt
(specified as the first parameter) causes a software interrupt.
You are particularly interested in setting the <code>sa_handler</code>
field of the structure that <code>sigaction()</code> needs;
it specifies the handler function to run upon an interrupt.
</ul>
<h3> Periodic Alarm: Step 2</h3>
<p>
Once the periodic printing of the time is working, 
add to the program to do something 
other than exit the program the first time a Control-c is typed.
This extension to program only exits after the user types
Control-c <b>5</b> times.
Set up a <code>SIGINT</code> handler (using <code>sigaction()</code> to set
up the call back function).
The <code>SIGINT</code> handler either prints how many more
times Control-c must be typed before exiting,
or it prints that it caught the 5th one and it calls <code>exit()</code>.
</p>
<p>
Output of the program looked like this on Feb 26:
</p>
<pre>
Date will be printed every 3 seconds.
Enter ^C 5 times to end the program:
^C
Control-c caught. 4 more before program is ended.

current time is Thu Feb 26 15:15:51 2015
^C
Control-c caught. 3 more before program is ended.
^C
Control-c caught. 2 more before program is ended.
^C
Control-c caught. 1 more before program is ended.

current time is Thu Feb 26 15:15:54 2015
^C
Final Control-c caught. Exiting.
</pre>

<p>
The alarm interrupt handler will need to re-arm the
alarm each time it is called.
Since both <code>main()</code> and the alarm handler both need
to know/use the number of seconds in order to arm the alarm,
make this value a <i>global</i> variable.
<b>Interrupt handlers are not invoked by another function
within the program, so they cannot  receive parameters
from another function in the program.</b>
</p>
<p>
You will also need a global variable to keep track of the
number of times a Control-c has been typed.
It is only used by the <code>SIGINT</code> handler,
but it needs to exist (single instantiation) the entire
time that the program runs.
</p>
<!--
Further, the C compiler will make the assumption that the
value of this global variable can go into a register,
since its value will not be changed by the loop within <code>main()</code>.
Yet, the handler will be changing the value asynchronously,
whenever the alarm goes off, 
making <code>main()</code>'s copy within the register stale,
and wrong.  
To make the compiler generate code that reloads the 
variable from memory each time it is accessed, 
use the <code>volatile</code> qualifier in your declaration
of the variable.
Your declaration (and initialization) will appear like:
</p>
<pre>
   volatile int numSignals = 0;
</pre>
-->
<h3> Periodic Alarm: Step 3</h3>
<p>
<br>1. Once you are through with this program, copy /p/course/cs354-common/public/bin/demo.c to your current working folder. Compile the program using the following option -
<br><b>gcc demo.c -o demo -Wall -m32</b>
<br>2. Run the program using -
<br><b>./demo</b>
<br>3. Observe the result. It should be something like this -
<br> Enter ^C to end the program:
<br>
<br>4. Now Press "Ctrl-C" to quit the program. Open the file demo.c and go through the code. Notice the printf statement after the infinite loop. 
<br><b>printf("This should not be printed\n");</b>
<br>
<br>Because the program is <b>stuck in an infinite loop</b>, the above printf statement is not executed. <b>That is, the program does not go forward.</b>
<br>6. Now copy the file /p/course/cs354-common/public/bin/a4questions.txt to your folder and answer the question in the file.
<br>7. Once you are done answering the question, copy this file along with intdate.c in your handin folder for submission of PART 1 of this assignment.
</p>

<p>
<b>VERY IMPORTANT:</b>  Compile the program with a different set
of  options than used in assignment 1.
When grading your programs, we will also use this command.
You are leaving off the <b>-O</b> option which invokes the
optimizer on your code.  If you were to allow the compiler
to optimize your code, it might eliminate necessary code.

<pre>
    % gcc -o intdate intdate.c -Wall -m32
</pre>

<p>
<i>One more note:</i> Even if you have a personal computer with
a C compiler,
you will not be able to work on your own computer,
as the set up and handling of the variety of interrupts is different
on different platforms.
Work on the csl machines to do this assignment.
</p>

<h3> Second Program: Do Some Division</h3>

<p>
Write a simple program that loops (forever) to
<ul>
<li> prompt for and read in one integer value (followed by the newline)
<li> prompt for and read in a second integer value (followed by the newline)
<li> calculate the quotient and remainder of doing the integer division
operation: <code> int1 / int2</code>,
printing these results, and keeping track of how many division
operations were successfully completed.
</ul>
<p> Place this endless loop into <code>main()</code>.
Yes, this is poor style, but do it anyway.
<p> A Control-c will cause this program to stop running.
<p> Use <code>fgets()</code> to read each line of input.
Then, use <code>atoi()</code> to translate that C string to an integer.
<p> Users tend to type in bad inputs occasionally.
For ease of programming, mostly ignore error checking on the input.
If the user enters in a bad integer value,
don't check for a bad integer value, and
don't worry about it.
Just use whatever value  <code>atoi()</code> returns.
<i>If you still don't know what this value is, look it up in the
 <code>atoi()</code> man page!</i>
<p> The count of the number of completed divisions needs to be
a global variable, as it will be needed by
the second program enhancement (described below).
<p> Call the source code for this  program <code>division.c</code>. 
<p>
A sample run of the program might appear as
<pre>
Enter first integer: <b>12</b>
Enter second integer: <b>2</b>
12 / 2 is 6 with a remainder of 0
Enter first integer: <b>100</b>
Enter second integer: <b>-7</b>
100 / -7 is -14 with a remainder of 2
Enter first integer: <b>10</b>
Enter second integer: <b>20</b>
10 / 20 is 0 with a remainder of 10
Enter first integer: <b>ab17</b>
Enter second integer: <b>3</b>
0 / 3 is 0 with a remainder of 0
Enter first integer: <b>^C</b>
</pre>
<p>
Once this program is working,
enhance it in two ways.
<ol>
<li> Try your program on a divide by 0 operation.
What happens?
<p> The hardware traps when this unrecoverable
arithmetic error occurs, and the program crashes,
because it did not (catch and) handle the 
<code>SIGFPE</code> signal.
<p> To make this situation a little bit better, 
set up a handler that will be called if the program
receives the <code>SIGFPE</code> signal.
In the signal handler you write, print a message stating that
a divide by 0 operation was attempted, print the number
of successfully completed division operations,
and then exit the program (gracefully, instead of crashing).
</li>
<li>
You needed to interrupt this program to cause it to stop running.
The second enhancement to this program captures the control-c
just like the <code>intdate</code> program did,
but on the first control-c interrupt,
the handler prints the number
of successfully completed division operations,
and then exits the program (gracefully).
<p> Set up and add a handler for the <code>SIGINT</code> signal.
The handler is to print a little message stating
the number of completed operations,
and then exit the program (gracefully).
</li>
</ol>
<p> Useful functions that you will need to use:
<ul>
<li>  <code>fgets()</code> reads up to a defined maximum number of 
characters into a buffer, 
stopping before that maximum is reached if a newline or
EOF is encountered.
<li>  <code>atoi()</code> converts a C string into the integer
represented by that string.
<li>  <code>sigaction()</code>  (<i> do not use signal()</i> )
sets up what happens when the specific type of interrupt
specified as the first parameter causes a software interrupt.
You will be calling <code>sigaction()</code> twice,
once to set up the handling of <code>SIGFPE</code>, and another time to 
set up the handling of <code>SIGINT</code>.
Implement 2 independent handlers; do not combine the handlers.
<i> Do not place the calls to <code>sigaction()</code> within a loop.
These calls will be completed before
entering the loop that requests and does division on the two integers.</i>
</ul>
<!--
-->

<h3>Handing In the Programs</h3>

<p>To turn in your source code for grading, 
copy both source files (<code>intdate.c</code> and <code>division.c</code>) and <code>a4questions.txt</code>
into your handin directory. 
Your handin directory for this first project is 
<code>/p/course/cs354-common/public/spring15.handin/login/p4</code> where <code>login</code> is your CS login. 
<p> <i>If you are working as part of a pair</i>,
you must turn in an extra file.
This file will contain the names and sections of <b>both</b> students
in the pair.
As an example, if Karen worked with Urmish on this assignment,
the contents of the extra file for both Karen and Urmish would be
<pre>
Karen Miller   section 1
Urmish Thakker  section 2
</pre>
<p> The <i>name</i> of this file is specialized to help the 354 automated
grading tools identify who worked together.
This file name is composed of the <i>CS logins</i> of the partners
separated by a period.
The file name is of the form &lt;login1&gt;.&lt;login2&gt;.
Karen's login is <code>smoler</code>, and Urmish's login is
<code>uthakker</code>.
The file name that both use will be <code>smoler.uthakker</code>;
please have both partners use the same file name.
It does not matter which partner's name is first within this
file name.

<p>Your Handin Folder should have the following files 
<ol>
<li>
intdate.c
</li>
<li>
a4questions.txt
</li>
<li>
division.c
</li>
</ol>
</p>

<H3>Requirements</H3>

<ol>
<li>
Include a comment at the top of the source code of all programs
with your <i>name</i> and <i>section</i> (and your partner's name and section,
if working in a pair).
</li>
<li>
Your program must follow style guidelines as given in
<A HREF="http://www.cs.wisc.edu/~cs354-1/cs354/homeworks/style.html">Style Guidelines</A>.
<p>
See
<A HREF="http://www.cs.wisc.edu/~cs354-1/cs354/handouts/pgrading.html">Guidelines for Programs</A>
to see an indication of point allocation for program grading.
</li>
<li>
Use the <b>galapogos</b> Linux machines for this assignment!
Your programs must compile
on a <b>galapogos</b> Linux machine as indicated in this specification
<i>without warnings or errors</i>.
</li>
</ol>

<h3>About Copying Code and Academic Misconduct</h3>
<p>
For almost any C program that does something useful,
someone has already written this program and
further, has posted it for others to use.
This program does not do much that is useful,
and is not likely posted anywhere.
Still, it is academic misconduct for you to copy or use some or
all of a program
that has been written by someone else.
</p>
<p>
It is academic misconduct to post your solution,
especially to a publicly accessible web site such as GitHub. 
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

