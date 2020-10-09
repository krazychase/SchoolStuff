1. Segmentation Fault
2. Note: I have peda installed, so some output may be different. GDB shows me the registers, code, stack, and line when it segfaulted.
3. "Invalid read of size 4 at 0x109167: main (null.c:6) Address 0x0 is not stack'd, malloc'd or (recently) free'd" followed by more troubleshooting information. I think I understand most of the information, it's pretty much telling me the address is inaccessable, and 4 bytes were lost since they weren't properly free'd.
4. It runs fine. gdb also run fine. Valgrind shows the 36,000 bytes were lost and shows an error.
5. It runs fine. Valgrind shows that 4 bytes were written after the allocated amount, and the bytes were lost since I didn't free them. The program is incorrect, we wrote outside the allowed space, but didn't segfault.
6. It runs fine, doesn't print anything. Valgrind has an error, saying read happened insode a free'd block. 
7. It runs fine. Valgrind errors about " Conditional jump or move depends on uninitialised value(s) " and the lost 400 bytes, but nothing else.