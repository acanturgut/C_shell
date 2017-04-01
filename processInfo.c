
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

int processPID =0;
int processPrio =0;

module_param(processPID,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
module_param(processPrio,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

MODULE_PARM_DESC(processPID, "Integer which holds process PID");
MODULE_PARM_DESC(processPrio, "Integer which holds process priority value");

int processInfo_init(void){
  printk("HO HO");
  struct task_struct *process;
  struct task_struct *children;
  struct task_struct *thread_group;
  struct list_head *child;
  struct list_head *thread;
  //struct list_head *thread_node;

  //printk("ENTERS ID \n");
  printk(KERN_INFO "Module is loading...\n");

  for_each_process(process){
    if(process->pid==processPID){
      printk(KERN_INFO "Module is loading...\n");
      printk(KERN_INFO "PID: %d\nPARENT'S ID: %d\nEXECUTABLE  NAME: %s\n",process->pid,process->parent->pid,process->comm);
      int childNo=0;
      list_for_each(child, &process->children){
        children=list_entry(child, struct task_struct, children);
        printk(KERN_INFO "CHILD #%d: PID: %d, NAME: %s\n",childNo,children->pid,children->comm);
        childNo++;
      }
      int threadNo=0;
      list_for_each(thread,&process->thread_group){
        printk(KERN_INFO "THREAD #%d: ID: %d, NAME: %s\n",threadNo,thread_group->pid,thread_group->comm);
        threadNo++;
      }
      printk(KERN_INFO "USER ID: %d\nPROCESS VOLUNTARY CONTEXT SWITCH COUNT: %d\nPROCESS INVOLUNTARY CONTEXT SWITCH COUNT: %d\nNICE: %d\nVRUNTIME: %d\n",process->real_cred->uid,process->nvcsw,process->nivcsw,process->prio,process->se.vruntime);
    }
  }
  return 0;
}



void processInfo_exit(void){
  printk(KERN_INFO "Module is removed\n");
}

module_init(processInfo_init);
module_exit(processInfo_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Comp 304 Project #1: Part IV");
MODULE_AUTHOR("A. Can Turgut & Damla Övek");
