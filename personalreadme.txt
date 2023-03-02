Design Process:
  This was by far the biggest coding project I have completed at Temple. My process began with reading through the project readme and the assigned readings.
After reading the assigned readings I decided to use the getopt while loop that was given. So I wrote the rough draft of it in my main function.  
The next steps were the deliverables. I did fall behind with the deliverables but the warmups were helpful in translating over to coding the actual lab.  
Once I actually got to the myPs coding I started by creating a function for each of the possible cases. I used sprintf to incorprate the pid in the filename before
tokeniseing the actuall /proc/stat and /proc/statm. I then used fopen to read the charstring. I included a fgets if statement to try to fix an earlier 
problem I was running into. It was working well with the new code so I left it in the program as I did not want to mess it up when it while it was working properly.
I then simply tokenised /proc/stat and /proc/statm and printed out the value of where the function variable is found in. The commandline function took 
me a while to figure out. Since it did not have to be tokenised, I thought it would be simple. However, everything I tried kept printing out "[null]". 
After rereading the readme, it mentioned the zero null bytes. So I created a loop to replace them with a space. Then I finished up my main function. I 
kept the original while loop with getopt, and modified it. Because I had functions already created, I was having trouble using the normal orientation from 
the readings. So I created booleans for each of my functions and fliped the value of the function when the flag was called. Then printed out the boolean 
functions that were true at the end of the main method. The only part I did not complete was the pid function. I had trouble understanding what the 
process was for it, and ultimately ran out of time for it. I used getpid() to retrieve the pid values that I encorporated in my program.
  
Testing Process: 
  The testing process was very long and frustrating for the project. Since I could not open the files for /proc/stat, /proc/statm, and /proc/cmndline on 
my clion terminal on my mac I had to test just about everything on the linux server. I started testing when I was creating each of my functions 
mentioned above. I tested retrieving the necessary values from the tokenised /proc file. I did this my copying example stat, statm, and cmndline files
into my program then running the code I had with them. I eventually moved onto the linux server once I was able to successfully open the files with 
the pid. After much testing and coding the output was successful. 
