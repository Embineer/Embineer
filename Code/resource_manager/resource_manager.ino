#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#define QUEUE_SIZE 100
#define STACK_SIZE 128
#define BUTTON 13

// car class to create dummy car
class car {
  private:
  public:
  car (short Duration, short allowed,short Time_Arrival,short Leave,short S1,short S2,short S3,short S4,short S5,short S6);
    short ID;
    short Duration;
    short Time_Arrival;
    short Leave;
    short S1;
    short S2;
    short S3;
    short S4;
    short S5;
    short S6; 
};
// car constructor complete
car::car(short id, short duration,short time_Arrival,short leave,short s1,short s2,short s3,short s4,short s5,short s6)
{
  ID = id;
  Duration=duration;
  Time_Arrival=time_Arrival;
  Leave=leave;
  S1=s1;
  S2=s2;
  S3=s3;
  S4=s4;
  S5=s5;
  S6=s6;  
}

// car class to create dummy car
car* car1 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
car* car2 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car
car* car3 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
car* car4 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car
car* car5 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
car* car6 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car
car* car7 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
car* car8 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car
car* car9 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
car* car10 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car
car* car11 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
car* car12 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car
car* car13 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
car* car14 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car
car* car15 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
car* car16 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car

// car queue
QueueHandle_t car_queue;

// guard for car queue and each critical section in this system
SemaphoreHandle_t mutexQueue;
SemaphoreHandle_t mutex1;
SemaphoreHandle_t mutex2;
SemaphoreHandle_t mutex3;
SemaphoreHandle_t mutex4;
SemaphoreHandle_t mutex5;
SemaphoreHandle_t mutex6;
SemaphoreHandle_t mutex7;
SemaphoreHandle_t mutex8;
SemaphoreHandle_t mutex9;
SemaphoreHandle_t mutex10;
SemaphoreHandle_t mutex11;
SemaphoreHandle_t mutex12;

// function prototype 
void listesning();
void choose(car*chosen_car);
void checking(car*chosen_car);
void allocate(car*chosen_car);
void reset(car*chosen_car);
void lock(short resource);
void unlock(short resource);


void setup() {

  Serial.begin(1200);
  
  // guard for queue and each resources
  mutexQueue = xSemaphoreCreateMutex();
  mutex1 = xSemaphoreCreateMutex();
  mutex2 = xSemaphoreCreateMutex();
  mutex3 = xSemaphoreCreateMutex();
  mutex4 = xSemaphoreCreateMutex();
  mutex5 = xSemaphoreCreateMutex();
  mutex6 = xSemaphoreCreateMutex();
  mutex7 = xSemaphoreCreateMutex();
  mutex8 = xSemaphoreCreateMutex();
  mutex9 = xSemaphoreCreateMutex();
  mutex10 = xSemaphoreCreateMutex();
  mutex11 = xSemaphoreCreateMutex();
  mutex12 = xSemaphoreCreateMutex();

  // initialize car queue  
  car_queue = xQueueCreate(QUEUE_SIZE, sizeof(car*));  

  // tasks
  xTaskCreate(resource_manager, "Task1", STACK_SIZE,1,1 , 0);
  xTaskCreate(resource_manager, "Task2", STACK_SIZE,1,1 , 0);
  xTaskCreate(resource_manager, "Task3", STACK_SIZE,1,1 , 0);
  xTaskCreate(resource_manager, "Task4", STACK_SIZE,1,1 , 0);

  // put dummy car in queue
  xQueueSendToBack(car_queue, (void*)&car2, 1);
  xQueueSendToBack(car_queue, (void*)&car1, 1);
  xQueueSendToBack(car_queue, (void*)&car3, 1);
  xQueueSendToBack(car_queue, (void*)&car4, 1);
  xQueueSendToBack(car_queue, (void*)&car5, 1);
  xQueueSendToBack(car_queue, (void*)&car6, 1);
  xQueueSendToBack(car_queue, (void*)&car7, 1);
  xQueueSendToBack(car_queue, (void*)&car8, 1);
  xQueueSendToBack(car_queue, (void*)&car9, 1);
  xQueueSendToBack(car_queue, (void*)&car10, 1);
  xQueueSendToBack(car_queue, (void*)&car11, 1);
  xQueueSendToBack(car_queue, (void*)&car12, 1);
  xQueueSendToBack(car_queue, (void*)&car13, 1);
  xQueueSendToBack(car_queue, (void*)&car14, 1);
  xQueueSendToBack(car_queue, (void*)&car15, 1);
  xQueueSendToBack(car_queue, (void*)&car16, 1);

  // guard to add more car into queue
  pinMode(BUTTON,INPUT);
}

void loop() {
  if(digitalRead(BUTTON) == 1){
    xQueueSendToBack(car_queue, (void*)&car2, 1);
    xQueueSendToBack(car_queue, (void*)&car1, 1);
    xQueueSendToBack(car_queue, (void*)&car3, 1);
    xQueueSendToBack(car_queue, (void*)&car4, 1);
    xQueueSendToBack(car_queue, (void*)&car5, 1);
    xQueueSendToBack(car_queue, (void*)&car6, 1);
    xQueueSendToBack(car_queue, (void*)&car7, 1);
    xQueueSendToBack(car_queue, (void*)&car8, 1);
    xQueueSendToBack(car_queue, (void*)&car9, 1);
    xQueueSendToBack(car_queue, (void*)&car10, 1);
    xQueueSendToBack(car_queue, (void*)&car11, 1);
    xQueueSendToBack(car_queue, (void*)&car12, 1);
    xQueueSendToBack(car_queue, (void*)&car13, 1);
    xQueueSendToBack(car_queue, (void*)&car14, 1);
    xQueueSendToBack(car_queue, (void*)&car15, 1);
    xQueueSendToBack(car_queue, (void*)&car16, 1);
  }
}


void resource_manager(void *pvParameters){
  Serial.println("new"); 
  car car_handler = car( 0,0,0,0,0,0,0,0,0,0);
  for (;;)
  {
    listesning();// check for requesting car on queue
    choose(&car_handler);// take car to handle
    
  Serial.println(car_handler.Duration); 
    checking(&car_handler);// lock requested resources
    allocate(&car_handler);// give permission to the car to use the resources
    reset(&car_handler);// unlock requested resources
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// check for requesting car on queue
void listesning(){
  for(; uxQueueSpacesAvailable(car_queue) == QUEUE_SIZE;){
  } // Check first element 
}

// take a car from queue to handle the car
void choose(car *chosen_car){
  car* choosing_car;
  while(xSemaphoreTake(mutexQueue, 10)!= pdTRUE){};
  xQueueReceive( car_queue,&(choosing_car), ( TickType_t ) 10 );
  while(xSemaphoreGive(mutexQueue)!= pdTRUE){}; 
  *chosen_car=*choosing_car;

}

// lock requested resources
void checking(car *chosen_car){
    if(chosen_car->S1!=0){
        lock(chosen_car->S1);
    }
    if(chosen_car->S2!=0){
        lock(chosen_car->S2);
    }
    if(chosen_car->S3!=0){
        lock(chosen_car->S3);
    }
    if(chosen_car->S4!=0){
        lock(chosen_car->S4);
    }
    if(chosen_car->S5!=0){
      lock(chosen_car->S5);
    }
    if(chosen_car->S6!=0){
      lock(chosen_car->S6);
    }
}
  
void lock(short resource){
  switch (resource){
    case 1 :  while(xSemaphoreTake(mutex1, 10)!= pdTRUE);Serial.println("Source 1 locked"); break;
    case 2 :  while(xSemaphoreTake(mutex2, 10)!= pdTRUE);Serial.println("Source 2 locked"); break;
    case 3 :  while(xSemaphoreTake(mutex3, 10)!= pdTRUE);Serial.println("Source 3 locked"); break;
    case 4 :  while(xSemaphoreTake(mutex4, 10)!= pdTRUE);Serial.println("Source 4 locked"); break;
    case 5 :  while(xSemaphoreTake(mutex5, 10)!= pdTRUE);Serial.println("Source 5 locked"); break;
    case 6 :  while(xSemaphoreTake(mutex6, 10)!= pdTRUE);Serial.println("Source 6 locked"); break;
    case 7 :  while(xSemaphoreTake(mutex7, 10)!= pdTRUE);Serial.println("Source 7 locked"); break;
    case 8 :  while(xSemaphoreTake(mutex8, 10)!= pdTRUE);Serial.println("Source 8 locked"); break;
    case 9 :  while(xSemaphoreTake(mutex9, 10)!= pdTRUE);Serial.println("Source 9 locked"); break;
    case 10 :  while(xSemaphoreTake(mutex10, 10)!= pdTRUE)Serial.println("Source 10 locked"); break;
    case 11 :  while(xSemaphoreTake(mutex11, 10)!= pdTRUE);Serial.println("source 11 locked"); break;
    case 12 :  while(xSemaphoreTake(mutex12, 10)!= pdTRUE);Serial.println("Source 12 locked"); break;
  }
}
// give permission to the car to use the resources
void allocate(car*choosen_car){
  vTaskDelay(((choosen_car->Duration)*30)/ portTICK_PERIOD_MS);
}

// unlock requested resources
void reset(car * chosen_car){
    if(chosen_car->S1!=0){
        unlock(chosen_car->S1);
    }
    if(chosen_car->S2!=0){
        unlock(chosen_car->S2);
    }
    if(chosen_car->S3!=0){
        unlock(chosen_car->S3);
    }
    if(chosen_car->S4!=0){
        unlock(chosen_car->S4);
    }
    if(chosen_car->S5!=0){
      unlock(chosen_car->S5);
    }
    if(chosen_car->S6!=0){
      unlock(chosen_car->S6);
    }
    // reser car attribute to copy new car artibute
    chosen_car->ID =0;
    chosen_car->Duration =0;
    chosen_car->Time_Arrival =0;
    chosen_car->Leave =0;
    chosen_car->S1 =0;
    chosen_car->S2 =0;
    chosen_car->S3 =0;
    chosen_car->S4 =0;
    chosen_car->S5 =0;
    chosen_car->S6 =0;
}

void unlock(short resource){
  switch (int(resource)){
    case 1 :  while(xSemaphoreGive(mutex1)!= pdTRUE);Serial.println("source 1 unlocked"); break;
    case 2 :  while(xSemaphoreGive(mutex2)!= pdTRUE);Serial.println("source 2 unlocked"); break;
    case 3 :  while(xSemaphoreGive(mutex3)!= pdTRUE);Serial.println("source 3 unlocked"); break;
    case 4 :  while(xSemaphoreGive(mutex4)!= pdTRUE);Serial.println("source 4 unlocked"); break;
    case 5 :  while(xSemaphoreGive(mutex5)!= pdTRUE);Serial.println("source 5 unlocked"); break;
    case 6 :  while(xSemaphoreGive(mutex6)!= pdTRUE);Serial.println("source 6 unlocked"); break;
    case 7 :  while(xSemaphoreGive(mutex7)!= pdTRUE);Serial.println("source 7 unlocked"); break;
    case 8 :  while(xSemaphoreGive(mutex8)!= pdTRUE);Serial.println("source 8 unlocked"); break;
    case 9 :  while(xSemaphoreGive(mutex9)!= pdTRUE);Serial.println("source 9 unlocked"); break;
    case 10 :  while(xSemaphoreGive(mutex10)!= pdTRUE);Serial.println("source 10 unlocked"); break;
    case 11 :  while(xSemaphoreGive(mutex11)!= pdTRUE);Serial.println("source 11 unlocked"); break;
    case 12 :  while(xSemaphoreGive(mutex12)!= pdTRUE);Serial.println("source 12 unlocked"); break;
  }
}
