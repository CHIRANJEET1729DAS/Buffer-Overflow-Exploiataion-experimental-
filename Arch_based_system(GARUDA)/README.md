## Buffer Overflow Exploit Experiment on Garuda Linux
 
 ## Project Description

This project investigates the potential for buffer overflow exploits on a Garuda Linux system, with a focus on understanding how security mechanisms, such as Address Space Layout Randomization (ASLR), stack canaries, and Data Execution Prevention (DEP), influence the exploit process. Despite using several modern protections, the experiment intentionally disabled some of these protections to demonstrate how buffer overflow exploits can still be carried out in specific circumstances.

 ## Purpose

The goal of this experiment was to test buffer overflow exploitation techniques while understanding the impact of security mechanisms on exploitability. Using GDB to step through the program, I tested how ASLR, stack canaries, and DEP affect the buffer overflow vulnerability in a program that was compiled with critical protections disabled (using flags such as -fno-stack-protector, -z execstack, and -no-pie).

 ## Key Features

1) Buffer Overflow Vulnerability: A vulnerable C program was used in this experiment, leveraging unsafe functions like strcpy() that can overflow a buffer if the input exceeds the allocated space, simulating a typical buffer overflow vulnerability.

2) Compiling with Disabled Protections: The following compilation flags were used to disable key security features:

        -fno-stack-protector: Disables stack canaries, which are used to detect buffer overflows and prevent exploitation by checking for stack corruption.
        -z execstack: Allows execution of code on the stack, which is normally prevented to protect against shellcode injection attacks.
        -no-pie: Disables Position Independent Executable (PIE), which would otherwise randomize the base address of the executable in memory.
        -g: Includes debugging information in the compiled binary, which was useful for debugging with GDB.

3) GDB for Analysis: GDB (GNU Debugger) was used to step through the execution of the program, analyze memory locations, and attempt to locate the vulnerable buffer and the address of the payload function to hijack control flow.

 ## Key Safety Techniques Explained

1) Address Space Layout Randomization (ASLR)

ASLR is a security mechanism that randomizes memory addresses used by the system. Even though we disabled certain protections, ASLR remained active, making it challenging to exploit the vulnerability.
Impact on Exploits: Despite the vulnerability being present, ASLR caused the memory layout to be randomized every time the program ran. This randomness made it difficult to predict the memory address of the vulnerable buffer or the payload_function, preventing us from successfully crafting an exploit.

2)  Stack Canaries (Disabled)

With the -fno-stack-protector flag, stack canaries were disabled, meaning the program did not use any mechanism to detect if the stack was corrupted by a buffer overflow.
Impact on Exploits: Disabling stack canaries made it easier to perform a buffer overflow, as there was no additional check in place to prevent the exploit. However, ASLR still made it difficult to predict where the stack would be located in memory, complicating the exploit.

3) Data Execution Prevention (DEP)

While DEP wasn't explicitly disabled in this experiment, it is still typically enabled by default on modern Linux systems. DEP prevents code execution in certain areas of memory, such as the stack and heap, making it difficult to execute injected shellcode even if the buffer overflow is successful.
Impact on Exploits: If DEP was enabled, it would have prevented the execution of any shellcode injected into the stack during the buffer overflow. However, since we were unable to craft a successful buffer overflow due to ASLR, DEP did not come into play during this experiment.

4) Execution of Code on the Stack (Allowed)
With the -z execstack flag, we allowed execution of code on the stack, meaning that if the exploit was successful and shellcode was injected into the stack, it could potentially be executed.
Impact on Exploits: This flag made it possible to run injected code on the stack, but due to ASLR, it was still difficult to predict where the buffer and the injected payload would reside in memory. Thus, the stack’s address was randomized with each execution of the program, making the exploit nearly impossible to execute successfully.

 ## Observations

1) GDB Analysis: Using GDB, I was able to inspect the memory layout and observe how the program handled input. Despite the vulnerability in the code, the exploit failed because the memory locations were randomized by ASLR. This demonstrated how ASLR can thwart buffer overflow attacks by making key addresses unpredictable.

2) Exploit Difficulty: Even though the buffer overflow vulnerability was present and protections like stack canaries were disabled, the ASLR mechanism prevented the exploit from succeeding. I attempted to exploit the vulnerability by predicting the address of the payload_function, but each time the program ran, the memory addresses were different, making the attack infeasible.

3) Stack Protection: By disabling the stack canaries (-fno-stack-protector), I was able to bypass a typical safeguard against buffer overflows. However, the remaining protections, especially ASLR, still made it difficult to carry out the exploit.

 ## Conclusion

This experiment demonstrates the resilience of modern security mechanisms like ASLR in defending against buffer overflow exploits. While traditional methods of exploiting buffer overflows can work in the absence of these protections, ASLR significantly increases the difficulty of executing such attacks by randomizing memory layouts.

The use of GDB provided valuable insight into how ASLR and other protections impacted the exploit process, ultimately preventing the attack from being successful.

## [Observations](https://github.com/CHIRANJEET1729DAS/Buffer-Overflow-Exploiataion-experimental-/tree/main/Arch_based_system(GARUDA)/GDB)
All images taken during the GDB analysis, as well as other relevant observation data, are available in the GDB folder. These images provide detailed views of memory layout, function addresses, and stack information during the experiment.
