<HTML>
<HEAD>
<TITLE>CS/ECE 354, Assignment 2</TITLE>
<link rel=stylesheet type="text/css" HREF="/csheader/cs.css">
</HEAD>

<BODY>

<center><h1> Assignment 2</h1></center>
<center><h1>CS/ECE 354</h1></center>
<HR>
<h3>Please post all questions to the piazza page</h3>


<H3>Collaboration Policy</H3>
<p>
For this assignment, you may work in pairs (2 people).<br>
<b>This assignment is different with respect to working with partners. Read the following carefully.</b>
</p>
<p>
Since the problems (and answers) for every student is different, each
partner must turn in the answers for his/her problems individually.  You <b>do not need</b> to
submit any extra files to identify your pair. So, effectively, for this
programming assignment, the only difference between working in a pair and
individually is that you can discuss with your partner the techniques to
diffuse the bombs.
</p>

<H2>Purpose</H2>

<P>
There are two main objectives of this project. 
The first is to quickly become familiar with x86 assembly language.
This is a hugely useful skill!
In real life, one is often faced with the task of trying to figure out 
why some code is not working as planned, 
and sometimes this leads to staring at the instructions that are 
executing on the processor to gain understanding. 
The second relates to the first: 
to gain some familiarity with powerful tools that help with this process, 
namely <i>gdb</i> (the debugger) and <i>objdump</i> (the disassembler). 
These tools will also serve you well in your future endeavors.
</P>
<h2>Statement</h2>
<P>
You will be defusing four <i>binary bombs</i>.
The idea is simple: 
each bomb is just an executable program, 
which expects five inputs from you, the bomb defusing expert. 
If you type in the right values, you successfully defuse the bomb. 
If not, the bomb explodes! 
(Don't worry, it just prints that the bomb explodes; 
no real harm is done to you or your computer.)
</p>

<p>The four bombs are located in your assignment 2 directory 
(<code>/p/course/cs354-common/public/spring15.handin/</code><i>login</i><code>/p2</code>, substituting <i>login</i> with your own CS login),
named <code>b1</code> through <code>b4</code>.
Your task is to create four files, 
<code>b1.solution</code> through <code>b4.solution</code>.
Each file contains the five lines of input demanded by its associated bomb.
For example, if the solution to <i>b1</i> was 1, 2, 3, 4, and 5, 
you would create a file (using your text editor) called
<code>b1.solution</code> with the following entries:
</P>
<pre>
    1
    2
    3
    4
    5
</pre>

<p>
The challenge is to figure out the inputs expected by each of the four bombs. 
To do this, use two tools: <i>gdb</i> and <i>objdump</i>. 
Both are incredibly useful for this type of reverse engineering work.
</P>

<p>
Please copy your executable bombs to your own directory, and
work towards finding your solutions in your own directory.
That way, you will have the original executables in your handin directory
if you accidentally overwrite an executable.
</P>
<p id="testing">
To test whether you have figured out a bomb's defusing code correctly,
run the bomb with its input file
<pre>
   ./b1 &lt;b1.solution
</pre>

<p>
<strong>This is how we will grade your assignment.</strong>
It will print a success message if you have figured everything out; 
otherwise it will tell you the bomb exploded.
You can also run each bomb interactively,
and type in your guesses, one at a time.
This will be useful in defusing each bomb with the debugger, 
as described below.
</p>

<p>
This testing also uses another shell skill that you have already used:
redirection of input or output.
This command redirects <code>stdin</code> to come from a file.
The first part of Chapter 7 in K&amp;R has an introduction,
as does this 
<A HREF="http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-3.html">TLDP web page</A>.
</p>

<h2>Notes</h2>
<p>
<b>EACH PERSON HAS A DIFFERENT SET OF BOMBS!</b>
Thus, the answers for <i>b1</i> for you are different than the answers 
for <i>b1</i> for each and every other student in CS/ECE 354. 
Sharing answers will not be useful.
</P>
<p>
Make sure your solution file contains exactly five non-empty lines.
Fewer lines will lead to an infinite loop.
(If that happens, press Ctrl-C to break.)
</p>



<h2> The Tools: gdb and objdump </h2>
<p>
To figure out how to defuse your binary bombs, 
use two powerful tools: <i>gdb</i> and <i>objdump</i>. 
Both are critical in understanding what each binary bomb does.
</p>

<h3>objdump</h3>
With <i>objdump</i>, two important command line options are 
<ul>
<li>
<b>-d</b>, which disassembles a binary
<li>
<b>-s</b>, which displays the full binary contents of the executable
</ul>

<p>
For example, to see the assembly code of bomb b1, you might type:
<pre>
   objdump -d b1
</pre>

<p>
<p>
This will show an assembly listing of each function in the bomb. 
Your first task then might be to look at main() 
and figure out what the code is doing.
</p>

<p>
The -s flag is also quite useful, 
as it shows the contents of each segment of the executable. 
This may be needed when looking for the initial value of a given variable.
</p>

<p>
By redirecting <code>stdout</code>,
you can capture the output of <i>objdump</i> in a file, such
that you can look at this output without having to regenerate
it every time.
And, you can use both command line options at the same
time to create a full dump of the contents of the executable
as well as the disassembled contents. (Hint, hint!)
</p>

<h3>gdb</h3>
<p>
The debugger, <i>gdb</i>, 
is an even more powerful ally in your search for clues as to 
how to defuse each binary bomb. 
To run <i>gdb</i> on a particular bomb (say b1), 
<pre>
   gdb b1
</pre>
which will launch the debugger and ready you for a debugging session. 
The command <i>run</i> causes the debugger to run the program, 
in this case prompting you for input.
</p>

<p>
However, before running the debugger, 
you likely need to first set some <b>breakpoints</b>.
Breakpoints are places in the code where the debugger will 
stop running and let you take control of the debugging session.
For example, 
a common thing to do will be to fire up the debugger, 
and then
<pre>
   break main 
</pre>
to set a breakpoint at the <code>main()</code> routine of the program, 
and then type 
<pre>
   run 
</pre>
to run the program. 
When the debugger enters the <code>main()</code> routine, 
it will then stop running the program and pass control back to you, the user.
</p>

<p>
At this point, you will need to do some work.
One likely command you will use is 
<code>stepi</code>, 
which steps through the code one instruction at a time. 
Another useful command is 
<code>info registers</code>,
which shows you the contents of all of the registers of the system.
Another is 
<code>x/x 0xADDRESS</code>,
which is the examine command.
It shows you the contents at the address <code>ADDRESS</code>, 
and does so in hexadecimal.
The second x determines the format, 
whereas the first x is the examine command.
Finally, you can also have <i>gdb</i> disassemble the code by typing 
the <code>disassemble</code> command.
</p>

<p>
A former TA for the course wrote an excellent tutorial that can
help you learn to use <i>gdb</i>.
Questions for this assignment go to 
<a href="http://www.piazza.com/wisc/fall2015/cs354/">Piazza</a>;
please <b>do not</b> email Chris Feilbach, the author of this tutorial.
<code>prog1.c</code> and <code>prog2.c</code> mentioned in the
<A HREF="a2aux/gdb.pdf">gdb tutorial</A> is moved <a href="a2aux/">here</a>.
And, you might like to refer to 
<A HREF="a2aux/gdb.list.html">Cherin's quick list of useful gdb commands</A>.
A lengthy tutorial that contains way more than you need for this assignment is
the <A HREF="http://web.archive.org/web/20141004195237/http://www.dirac.org/linux/gdb/02a-Memory_Layout_And_The_Stack.php"> Peter Jay Salzman  gdb tutorial</A>.
And, for those that like to watch videos,
here is an excellent 
<A HREF="https://www.youtube.com/watch?v=sCtY--xRUyI"> YouTube video tutorial</A>.
</p>

<p>
Getting good with <i>gdb</i> will make this project go smoothly,
so spend the time and learn! 
One thing to notice: 
using the keyboard's up and down arrows 
(or control-p and control-n for previous and next, respectively) 
allows you to go through your <i>gdb</i>  history and easily 
re-execute old commands; 
getting good at using your history, 
whether in <i>gdb</i> or more generally in the shell you use, is a good idea.
</p>


<h3>Grading</h3>

<p>
Grading will be based entirely on whether you defuse the bombs. 
Each bomb is thus worth 25 percent of the grade for this project.
If you have only part of the five inputs correct, the bomb still explodes.
</p>
<p>To test it by yourself, follow the instructions <a href="#testing">here</a>.
</p>

<h3>Hints</h3>
<ul>
<li><a href="http://pages.cs.wisc.edu/~cs354-1/Handouts/Handout-x86-cheat-sheet.pdf">x86 cheat sheet</a></li>
<li>
Every C program has a <code>main()</code> function.
Figure out how to locate it.
</li>
<li>
A loop in <code>main()</code> iterates five times. 
Remember that each bomb requires five inputs.
</li>
<li>
On a wrong input, function <code>bomb()</code> is called.
This results in an explosion.
</li>
<li>
If all five inputs are correct, function <code>success()</code> is called.
</li>
<li>
Function <code>strtol()</code> corresponds to the use of <code>atoi()</code> in C source code.
</li>
<li>
Function arguments are set up in the call stack just prior 
to the function call.
</li>
<li>
The two parameters to <code>strcmp()</code> are addresses to 2 C strings.
</li>
<li>
The contents of your <code>.solution</code> for a binary bomb must
contain the same sequence of characters as you type at the
keyboard when you run the executable interactively.
Please note that the characters you type include a
newline character after each of the 5 inputs.
</li>
</ul>

<h3>Handing In the Programs</h3>

<p>
<b>
If you work in a pair, each partner will need to submit the solutions to their own bombs!<br>
The bombs provided for each partner is different and therefore the solution files will
also be different. Each partner's solution files should diffuse their own bombs.</p>
</b>

<p>Turn in your 4 files 
<code>b1.solution</code> through <code>b4.solution</code> by copying them to
<code>/p/course/cs354-common/public/spring15.handin/login/p2</code> 
where <code>login</code> is your CS login. 


</BODY>
</HTML>

