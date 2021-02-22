# Coding Journal
## Name: Stephen Richardson 
## Lab: Module 10
## Entries:
### Lab Warmup -- November 5th, 2020
I just finished up the lab warmup and it was surprising simple, once the syntax is down. reading from a well formated CSV seems simple and effective, which is why they are used I suppose. I wonder how data is read and saved more dynamically though. How do JSON files work, and how would I read from a database using C? Different problems for another day. 

### Lab Activity -- November 9th, 2020
I still don't quite understand how the qsort thing works, and would like some further explanation. I did have a huge issue trying to make the grow array function work. I could get it to grow once, but the second time, I would run into a double free fault. I couldn't figure it out, so I moved on and finished the project and ran valgrind to see how bad the memory leaks were, but there weren't any! I thought about it, and I realized that I didn't need to free the student structs each time I grew the array. Rather, I only need to copy and past the addresses. I'm not reallocating memory for the students each time, just allocating for a new array. Fun stuff.