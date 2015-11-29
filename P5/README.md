<HTML>
<HEAD>
<TITLE>CS/ECE 354, Assignment 5</TITLE>
<link rel=stylesheet type="text/css" HREF="/csheader/cs.css">
</HEAD>

<BODY>

<center><h1> Assignment 5</h1></center>
<center><h1>CS/ECE 354</h1></center>
<HR>
<H3>Please post all questions to the piazza page

<p>

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
must appear as comments at the top of all source code
files of the turned in assignment.
<p>In addition, students who work in a pair must turn in an extra file that identifies the pair.  Details are given in the section on Handing In the Assignment.</p>
<HR> <!-- ----------------------------------------------------- -->

<H2>Overview</H2>

<P>
The purpose of this program is to help you understand the nuances of building a memory allocator,
to further increase your C programming skills by
working a lot more with pointers and to get familiar with using Makefiles.
</P>
<P>
Please read this entire assignment specification before starting
on the first step.
</P>

<H3>Program Description</H3>


<p>
For this assignment, you will be given the structure for
a simple shared library that implements 
the memory allocation functions
<code>malloc()</code> and <code>free()</code>.
Everything is present, except for the definitions of those
two functions, called <code>Mem_Alloc()</code> and <code>Mem_Free()</code>
in this library.
</p>

<h3> Step One: Understand the Code</h3>

<p>
Memory allocators have two distinct tasks. 
First, the memory allocator asks the operating system to expand the heap 
portion of the process's address space by calling either <code>sbrk()</code> or <code
>mmap()</code>. 
Second, the memory allocator doles out this memory to the calling process. 
This involves managing a free list of memory and finding a contiguous chunk of 
memory that is large enough for the user's request; 
when the user later frees memory, it is added back to this list.
</p>
<p>
This memory allocator is usually provided as part of a standard library,
and it is not part of the OS. 
To be clear, the memory allocator operates entirely within 
the virtual address space
of a single process and knows nothing about which physical pages have been 
allocated to this process or the mapping from logical addresses 
to physical addresses.
</p>
<p>
Classic <code>malloc()</code> and <code>free()</code> are defined as follows:
</p>
<ul>
<li>
<code>void *malloc(size_t size)</code>: 
<code>malloc()</code> allocates <code>size</code> bytes and returns 
a pointer to the allocated memory. 
The memory is not cleared.
</li>
<li>
<code>void free(void *ptr)</code>: 
<code>free()</code> frees the memory space pointed to by <code>ptr</code>, 
which must have been returned by a previous call to <code>malloc()</code> (or <code>calloc()</code> or <code>realloc()</code>). 
Otherwise, or if <code>free(ptr)</code> has already been called before, 
undefined behavior occurs. 
If <code>ptr</code> is <code>NULL</code>, no operation is performed.
</li>
</ul>

<p>
</p>
<p>
Create a directory for this assignment.
The source code files you will need are in the directory:
</p>
<pre>
   /p/course/cs354-common/public/html/alloc.program/
</pre>

<p>
Copy the files <code>Makefile</code>, <code>mem.c</code> and <code>mem.h</code>
to your own directory.
You will probably copy more files for Step 3, but these 3 files
 are sufficient for Step 2.
In <code>mem.c</code> is fully working code for two functions:
<b><code>Mem_Init(int sizeOfRegion)</code></b> and <b><code>Mem_Dump()</code></b>.
Look at them, and understand what they do, as well as how they accomplish
their task. Also note the global block header pointer <b><code>list_head</code></b> which is the head of our free linked list of memory chunks. Read the header comments for the block header structure provided <b>very carefully</b> to understand the convention used.
</p>

<ul>
<li>
<p>
<b><code>Mem_Init(int sizeOfRegion)</code>:</b><br> 
This sets up and initializes the heap space that the
module manages. <code>sizeOfRegion</code> is the number of bytes that are requested to be initialized on the heap. <br>

This function should be called once at the start of any program before calling any of the other three functions. When testing your code you should call this function first to initialize enough space so that subsequent calls to allocate space via <code>Mem_Alloc()</code> can be served successfully. The test files we provide (as mentioned below) do the same.<br> 

Note that <code>Mem_Init(int sizeOfRegion)</code> rounds up the amount memory requested in units of the page size. <br>
Because of rounding up, the amount of memory initialized may be more than <code>sizeOfRegion</code>. You may use all of this initialized space for allocating memory to the user.<br>
Once <code>Mem_Init(int sizeOfRegion)</code> has been successfully called, <code>list_head</code> will be initialized as the first and only header in the free list which points to a single free chunk of memory. You will use this list to allocate space to the user via <code>Mem_Alloc()</code> calls<br>

<code>Mem_Init(int sizeOfRegion)</code> uses the <code>mmap()</code> system call to initialize space on the heap. If you are interested, read the man pages to see how that works.

</p>
</li>

<p>
<li>
<b><code>Mem_Dump()</code>:</b><br> 
This is used for debugging; it prints a list of
all the memory blocks (both free and allocated).
It will be incredibly useful when you are trying to determine if
your code works properly.
As a future programming note: take notice of this function.
When you are working on implementing a complex program,
a function like this that produces lots of useful information about a
data structure can be well worth the time you might spend implementing it.
</p>
</li>
</ul>

<h3> Step Two: Write the Code</h3>
<p> 
<b>Note: Do <i>not</i> change the interface.  Do not change anything within
file <code>mem.h</code>.  Do not change any part of functions <code>Mem_Init()</code> 
or <code>Mem_Dump()</code>.</b>
</p>
<p> 
Write the code to implement <code>Mem_Alloc()</code>  and <code>Mem_Free()</code>.
Use a <b>best fit</b> algorithm when allocating blocks with <code>Mem_Alloc()</code>.
When freeing memory, always <b>coalesce</b> with the adjacent memory blocks if they are free.
<code>list_head</code> is the free list structure as defined and described in <code>mem.c</code>
<b>It is based on the model described in your textbook in section 9.9.6 ( except
our implementation has an additional next pointer in the header in order to make it easier to
traverse through the free list structure).</b>
Here are definitions for the functions:
</p>
<ul>
<li>
<b><code>void *Mem_Alloc(int size)</code>:</b> 
<br><code>Mem_Alloc()</code> is similar to the library function 
<code>malloc()</code>. 
<code>Mem_Alloc</code> takes as an input parameter the 
<code>size</code> in bytes of the memory space to be allocated,
and it returns a pointer to the start of that memory space.
The function returns <code>NULL</code> if there is not enough 
contiguous free space 
within <code>sizeOfRegion</code> allocated by <code>Mem_Init</code> 
to satisfy this request. 
For better performance, 
<code>Mem_Alloc()</code> is to return 4-byte aligned chunks of memory. 
For example if a user requests 1 byte of memory, 
the <code>Mem_Alloc()</code> implementation should return 4 bytes of memory,
so that the next free block will also be 4-byte aligned.
To debug whether you return 4-byte aligned pointers, 
you could print the pointer this way:
<code><pre>
   printf("%08x", ptr) .
</pre></code>
The last digit should be a multiple of 4 (that is, 0, 4, 8, or C).
For example, b7b2c04c is okay, and b7b2c043 is <i>not</i> okay.

<p> Once the best fit free block is located we could use the entire block for the allocation. The disadvantage is that it causes internal fragmentation and wastes space. So we will split the block into two. The first part becomes the allocated block, and the
remainder becomes a new free block. Before splitting the block there should be enough space left over for a new free block i.e the header and its minimum payload of 4 bytes, otherwise we don't split the block.
</p>

</li>
<li>
<b><code>int Mem_Free(void *ptr)</code>:</b>
<br><code>Mem_Free()</code> frees the memory object that <code>ptr</code> points to. 
Just like with the standard <code>free()</code>, 
if <code>ptr</code> is <code>NULL</code>, then no operation is performed. 
The function returns 0 on success and -1 if 
the <code>ptr</code> was not allocated by <code>Mem_Alloc()</code>. 
If <code>ptr</code> is <code>NULL</code>, also return -1. For the block being freed, always coalesce with its adjacent blocks if either or both of them are free.
</li>
</ul>

<h3> Step Three: Test the Code</code></h3>
<p>
You have a provided <code>Makefile</code> that compiles your
code in <code>mem.c</code> and <code>mem.h</code> into a shared library
called <code>libmem.so</code>.
To do the compilation, the command is
<pre>
   make mem
</pre>
</p>
<p>
With this shared library, it is time to test if your <code>Mem_Alloc()</code>
and <code>Mem_Free()</code> implementations work.
This implies that you will need to write a separate program that 
links in your shared library, and makes
calls to the functions within this shared library.
We've already written a bunch of small programs that do this, 
to help you get started.
Our programs and a second Makefile are in
</p>
<pre>
   /p/course/cs354-common/public/html/alloc.program/tests/
</pre>
<p>
Copy all the files within this directory into a
new directory within the one containing your shared library.
Name your new directory <code>tests</code>.
</p>
<p>
In this directory, file <code>testlist.txt</code> contains a list
of the tests we are giving you to help you start testing your code.
The tests are ordered by difficulty. 
<b>Please note that these tests are not sufficient or complete for
testing your code;</b> 
they are meant to help you get started.
</p>
<p>
When you run <i>make</i> within the <code>tests</code> directory,
it will make executables of all the C programs in this directory.
</p>
<!--
The makefile specifies the base name of the library with 
the option <code>-lmem</code> and the path, 
so that the linker can find the library "-L.".
<pre>
gcc mymain.c -lmem -L. -o myprogram -m32
</pre>
-->

The linking step needs to use your library, <code>libmem.so</code>.
So, you need to tell the linker where to find this file.
Before you run any of the created dynamically linked executables,
you will need to set the environment variable, <code>LD_LIBRARY_PATH</code>,
so that the system can find your library at run time.
Assuming you always run a testing executable from (your copy of) 
this same <code>tests/</code> directory, 
and the dynamically linked library (<code>libmem.so</code>) is
one level up,
that directory (to a Linux shell) is '../', so you can use the command:
<pre>
export LD_LIBRARY_PATH=../
</pre>

Or, if you use a *csh shell:
<pre>
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:../
</pre>

If the setenv command returns an error "LD_LIBRARY_PATH: Undefined variable", 
do not panic. 
The error implies that your shell has not defined the environment variable. 
In this case, run:

<pre>
setenv LD_LIBRARY_PATH ../
</pre>

</p>
<h3> Step Four: Design a New Test</code></h3>
<p>
Create a new C program that tests whether simple <code>Mem_Free()</code> 
calls work.
The test should determine if a single allocation, followed
by a call to <code>Mem_Free()</code> does the right thing.
After you have debugged enough to know that it works correctly,
add to this same C program a test case to make sure that <code>Mem_Free()</code>
does the right thing if passed a bad pointer.
A bad pointer is one with the <code>NULL</code> value
or an address of memory space <i>not</i> allocated by <code>Mem_Alloc()</code>.
Name this testing program <code>freetests.c</code>.
</p>

<h3>Hints</h3>
<ul>
	<li>Always keep in mind that the value of <code>size_status</code> excludes the space for the header block. Make use of <code>sizeof(block_header)</code> to set the apporpriate size of requested block.</li>
	<li>It is highly recommended that you write small helper functions(test them first) for common operations and checks such as: isFree, setFree, setAllocated etc.</li>
	<li>Double check your pointer arithmetic. (int*)+1 changes the address by 4, (void*)+1 or (char*)+1 changes it by 1. What does (block_header*)+1 change it by?</li>
	<li>For any tests that you write, make sure you call <code>Mem_init()</code> first to allocate sufficient space.</li>
	<li>Check return values for all function calls to make sure you don't get unexpected behaviour.</li>
</ul>

<h3>Handing In the Assignment</h3>

<p>Turn in files <code>mem.c</code> and <code>freetests.c</code>.
Copy these files into your handin directory. 
Your handin directory for this project is 
<br><code>/p/course/cs354-common/public/spring15.handin/&lt;yourloginID&gt;/p5/</code> 
<p><code>&lt;yourloginID&gt;</code> is the username of your CS account.</p> 

<p>Your Handin Folder should have the following files:
<ol>
<li>mem.c</li>
<li>freetests.c</li>
</ol>
</p>

<p><i>If you are working as part of a pair</i>, you must turn in an extra file. This file will contain the names and sections of <b>both</b> students in the pair. As an example, if Kevin worked with Urmish on this assignment, the contents of the extra file for both Kevin and Urmish would be</p>
          <pre>Kevin Zhang     section 1
Urmish Thakker  section 2</pre>
          <p>The name of this file is specialized to help the 354 automated grading tools identify who worked together. This file name is composed of the CS logins of the partners separated by a period. The file name is of the form &lt;login1&gt;.&lt;login2&gt;. Kevin&#39;s login is kzhang, and Urmish&#39;s login is uthakker. The file name that both use will be kzhang.uthakker. Please have both partners use the same file name. It does not matter which partner's name is first within this file name.</p>


<!--
<p>
If you are working with a partner, follow the directions
given in Assignment 3 for the extra file that identifies
partners.
</p>
-->

<H3>Requirements</H3>

<ol>
<li>
Within the comment block at the top of <code>mem.c</code>,
add a new line of the form: 
<pre>
  * MODIFIED BY:  name, section#, partnername, section#
</pre>
</li>
<li>
Your program is to continue the style of the code
already in the file.
Use the same types of comments, and use tabs/spaces as the existing
code does. 
</li>
<li>
Document your added functions with inline comments!
</li>
<!--
<li>
Use the <b>galapagos</b> Linux machines for this assignment!
A penalty will be imposed for any program that was obviously edited
on a Windows machine and transferred to the Unix machines
for turning in.
Text files in Windows have different line endings (^M) at the
end of every line, so check you code on the Linux machines to make sure its in order.
</li>
-->
<li>
Your programs must compile
on the CS Linux lab machines as indicated in this specification
<i>without warnings or errors</i>.
</li>
<li>
<b>
Do <i>not</i> use any <code>stdlib</code> allocate or free functions 
in this program!
</b>
The penalty for using <code>malloc()</code> (or friends) will be
no credit for this assignment.
</li>
</ol>

<h3>About Copying Code and Academic Misconduct</h3>
<p> <a href="http://pages.cs.wisc.edu/~cs354-2/dontcheat.html">Don't cheat. Read this link carefully</a></p>
<p>
For almost any C program that does something useful,
someone has already written this program and
further, has posted it for others to use.
This program does not do much that is useful,
and is not likely posted anywhere.
Still, it is academic misconduct for you to copy or use some or
all of a program
that has been written by someone else.
Just as you may not copy someone else's code,
you may not provide your code to anyone else; that is also
academic misconduct.
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
<p>
<i> Do <b>not</b> post your assignment solution (or drafts) on any publicly 
accessible web sites. 
This specifically includes GitHub. 
It is academic misconduct to post your solution.</i>

</BODY>
</HTML>

