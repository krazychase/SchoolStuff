#include <iostream>

using namespace std;

typedef void (*funPtr)(int);

int numThreads=0;

long regs0[10],regs1[10],regs2[10]; // struct with all registered named
long *stack0,*stack1,*stack2;

void saveRegs(long *regsLocation) {
	asm(//"pushq %rdi\n"
	    "mov %rax,(%rdi)\n" 
	    "mov %rbx,8(%rdi)\n"
	    "mov %rsp,16(%rdi)\n"); //...
}

void loadRegs(long *regsLocation) {  // similar to the book
	asm(//"popq %rdi\n"
	    "mov (%rdi),%rax\n" 
	    "mov 8(%rdi),%rbx\n"
	    /*"mov 16(%rdi),%rsp\n"*/);	//....
}

int currentThread;

void setStack(long *stack) {
	asm("mov %rdi,%rsp\n");
}

void setStackAndRun(long *stack,funPtr ptr) {
	asm("mov %rdi,%rsp\n");
	ptr(currentThread);
}

void getStack(long **stack) {
	asm("mov %rsp,(%rdi)");
}
 
void startThread(funPtr ptr) {
	numThreads++;
	currentThread=numThreads;
	if (numThreads==1) {
		stack1=((long *)malloc(sizeof(long)*64000))+64000;
		saveRegs(regs0);
		getStack(&stack0);
		loadRegs(regs1);
		setStackAndRun(stack1,ptr);
	}
	else if (numThreads==2) {
		stack2=((long *)malloc(sizeof(long)*64000))+64000;
		saveRegs(regs0);
		getStack(&stack0);
		loadRegs(regs2);
		setStackAndRun(stack2,ptr);
	}
	//ptr(numThreads);
}

void shareCPU(int thread) {
  if (numThreads==1) {
	  saveRegs(regs1); // Save out created thread registers
	  loadRegs(regs0); // Load the main thread registers
	  setStack(stack0);
	  // do "opposite" of what we did on lines 36-39
  }
  // Switch stacks back and swap registers
}

void main1(int whoami) {
    while(true) {
        cout << "Main 1 says Hello" << endl;
        shareCPU(whoami);
    }
}

void main2(int whoami) {
    while(true) {
        cout << "Main 2 says Hello" << endl;
        shareCPU(whoami);
    }
}

int main() {
    startThread(main1);
    startThread(main2);
    while(true) {
		shareCPU(0);
	};
    return 0;
}
