// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "elevatortest.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 3; num++) {
	    printf("*** thread %d looped %d times\n", which, num); 
        printf("thread name:%s pid:%d uid:%d priority:%d\n", currentThread->getName(), 
            currentThread->getPid(), currentThread->getUid(), currentThread->base_priority);
        printf("\n");
        // 每运行一次当前线程，就让出CPU，让另一个线程继续执行
        currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");
    int num = 3;
    Thread *t[num];
    for(int i = 0; i < num;i++){
        t[i] = new Thread("test thread", i+1);
    }
    for(int i = num-1;i >= 0 ;i--){
        t[i]->Fork(SimpleThread, (void*)t[i]->pid);
    }
    SimpleThread(0);
    // Thread *t = new Thread("forked thread", 1); // 声明一个新的线程
    // if(t->pid != -1){
    //     int id = t->getPid();
    //     printf("this thread pid is id:%d\n", id);
    //     t->Fork(SimpleThread, (void*)1); // 线程创建并调用SimpleThread方法，标识为1
    //     SimpleThread(0);  // 主线程自己调用SimpleThread方法，传入参数为当前执行该方法的线程标识。当前线程为0，新创建的线程为1
    // }
    // else{
    //     printf("the new pid number is %d\n", t->pid);
    // }
}
void ThreadTest2(){
    DEBUG('t', "Entering ThreadTest2");


}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) { // 判断传入的测试线程数
    case 1:
    	ThreadTest1();
    	break;
    case 2:
        ThreadTest2();
        break;
    default: // 不为1的话就打印
    	printf("No test specified.\n");
    	break;
    }
}

