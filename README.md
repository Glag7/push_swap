# From the subject :

__Summary:__  
This project will make you sort data on a stack, with a limited set of instructions, using
the lowest possible number of actions. To succeed you’ll have to manipulate various
types of algorithms and choose the most appropriate solution (out of many) for an
optimized data sorting.  
Version: 7  

You have 2 stacks named a and b.  
• At the beginning:  
◦ The stack a contains a random amount of negative and/or positive numbers
which cannot be duplicated.  
◦ The stack b is empty.  
• The goal is to sort in ascending order numbers into stack a. To do so you have the
following operations at your disposal:  
*sa* (swap a): Swap the first 2 elements at the top of stack a.
Do nothing if there is only one or no elements.  
*sb* (swap b): Swap the first 2 elements at the top of stack b.
Do nothing if there is only one or no elements.  
*ss* : sa and sb at the same time.  
*pa* (push a): Take the first element at the top of b and put it at the top of a.
Do nothing if b is empty.  
*pb* (push b): Take the first element at the top of a and put it at the top of b.
Do nothing if a is empty.  
*ra* (rotate a): Shift up all elements of stack a by 1.
The first element becomes the last one.  
*rb* (rotate b): Shift up all elements of stack b by 1.
The first element becomes the last one.  
*rr* : ra and rb at the same time.  
*rra* (reverse rotate a): Shift down all elements of stack a by 1.
The last element becomes the first one.  
*rrb* (reverse rotate b): Shift down all elements of stack b by 1.
The last element becomes the first one.  
*rrr* : rra and rrb at the same time.  
 
__bonuses:__  
• Write a program named checker that takes as an argument the stack a formatted
as a list of integers. The first argument should be at the top of the stack (be careful
about the order). If no argument is given, it stops and displays nothing.  
• It will then wait and read instructions on the standard input, each instruction will
be followed by ’\n’. Once all the instructions have been read, the program has to
execute them on the stack received as an argument.  

# Usage

`make` to create the binary.  
`./push_swap x y z` or `./push_swap "x y z"`  
`make bonus` to create the checker.  
`./push_swap x y z | ./checker x y z` or `./push_swap "x y z" | ./checker "x y z"`  

Average number of instructions:  
100:   547  
500:   3808  
10000: 115172  
50000: 680574
