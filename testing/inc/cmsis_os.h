#ifndef CMSIS_OS_H_FAKE
#define CMSIS_OS_H_FAKE

#include <stdint.h>
#include <stddef.h>

#define osWaitForever     0xFFFFFFFFU

/* Priority used for thread control. */
typedef enum  {
  osPriorityIdle          = -3,         
  osPriorityLow           = -2,          
  osPriorityBelowNormal   = -1,          
  osPriorityNormal        =  0,          
  osPriorityAboveNormal   = +1,         
  osPriorityHigh          = +2,          
  osPriorityRealtime      = +3,         
  osPriorityError         =  0x84,       
  os_priority_reserved    =  0x7FFFFFFF  
} osPriority;

/* Entry point of a thread. */
typedef void (*os_pthread) (void const *argument);

/* Thread ID identifies the thread (pointer to a thread control block). */
typedef struct os_thread_cb *osThreadId;

/* Message ID identifies the message queue (pointer to a message queue control block). */
typedef struct os_messageQ_cb *osMessageQId;

/* Pool ID identifies the memory pool (pointer to a memory pool control block). */
typedef struct os_pool_cb *osPoolId;

/* Mail ID identifies the mail queue (pointer to a mail queue control block). */
typedef struct os_mailQ_cb *osMailQId;


/* Definition structure for message queue. */
typedef struct os_messageQ_def  {
  uint32_t                queue_sz;    /*< number of elements in the queue */
  void                       *pool;    /*< memory array for messages */
} osMessageQDef_t;

/* Definition structure for memory block allocation. */
typedef struct os_pool_def  {
  uint32_t                 pool_sz;    /*< number of items (elements) in the pool */
  uint32_t                 item_sz;    /*< size of an item */
  void                       *pool;    /*< pointer to memory for pool */
} osPoolDef_t;

/* Thread Definition structure contains startup information of a thread. */
typedef struct os_thread_def  {
  os_pthread               pthread;    /*< start address of thread function */
  osPriority             tpriority;    /*< initial thread priority */
  uint32_t               instances;    /*< maximum number of instances of that thread function */
  uint32_t               stacksize;    /*< stack size requirements in bytes; 0 is default stack size */
} osThreadDef_t;

/* Status code values returned by CMSIS-RTOS functions. */
typedef enum  {
  osOK                    =     0,       
  osEventSignal           =  0x08,       
  osEventMessage          =  0x10,       
  osEventMail             =  0x20,       
  osEventTimeout          =  0x40,       
  osErrorParameter        =  0x80,       
  osErrorResource         =  0x81,       
  osErrorTimeoutResource  =  0xC1,        
  osErrorISR              =  0x82,       
  osErrorISRRecursive     =  0x83,       
  osErrorPriority         =  0x84,       
  osErrorNoMemory         =  0x85,       
  osErrorValue            =  0x86,       
  osErrorOS               =  0xFF,       
  os_status_reserved      =  0x7FFFFFFF  
} osStatus;


/* Event structure contains detailed information about an event. */
typedef struct  {
  osStatus                 status;     
  union  {
    uint32_t                    v;     
    void                       *p;     
    int32_t               signals;     
  } value;                            
  union  {
    osMailQId             mail_id;     
    osMessageQId       message_id;    
  } def;                               
} osEvent;


#define osMessageQDef(name, queue_sz, type)   \
uint32_t os_messageQ_q_##name[4+(queue_sz)] = { 0 }; \
const osMessageQDef_t os_messageQ_def_##name = \
{ (queue_sz), (os_messageQ_q_##name) }

#define osPoolDef(name, no, type)   \
uint32_t os_pool_m_##name[3+((sizeof(type)+3)/4)*(no)]; \
const osPoolDef_t os_pool_def_##name = \
{ (no), sizeof(type), (os_pool_m_##name) }

#define osThreadDef(name, priority, instances, stacksz)  \
const osThreadDef_t os_thread_def_##name = \
{ (name), (priority), (instances), (stacksz)  }

#define osMessageQ(name) \
&os_messageQ_def_##name

#define osThread(name)  \
&os_thread_def_##name

#define osPool(name) \
&os_pool_def_##name


/* prototypes */

osMessageQId osMessageCreate (const osMessageQDef_t *queue_def, osThreadId thread_id);
osThreadId osThreadCreate (const osThreadDef_t *thread_def, void *argument);
osPoolId osPoolCreate (const osPoolDef_t *pool_def);
osEvent osMessageGet (osMessageQId queue_id, uint32_t millisec);
osStatus osPoolFree (osPoolId pool_id, void *block);
osStatus osThreadYield (void);

#endif