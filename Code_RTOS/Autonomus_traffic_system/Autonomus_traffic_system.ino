#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#define QUEUE_SIZE 100
#define STACK_SIZE_128 128
#define STACK_SIZE_1280 1280
#define BUTTON 12


/////////////////////////////////////////////////////////////// dummy car //////////////////////////////////////////////////////////////////////
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
  car();
  void reset(); 
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

car::car(){
}

void car::reset(){
    ID=0;
    Duration=0;
    Time_Arrival=0;
    Leave=0;
    S1=0;
    S2=0;
    S3=0;
    S4=0;
    S5=0;
    S6=0; 
  }

// car class to create dummy car
const car* car1 = new car( 1,2,21,23,11,0,6,0,0,0);// dummy car
const car* car2 = new car( 2,3,21,23,0,0,8,0,7,10);// dummy car
const car* car3 = new car( 3,2,21,23,11,0,6,0,0,0);// dummy car
const car* car4 = new car( 4,3,21,23,0,0,8,0,7,10);// dummy car
const car* car5 = new car( 5,2,21,23,11,0,6,0,0,0);// dummy car
const car* car6 = new car( 6,3,21,23,0,0,8,0,7,10);// dummy car
const car* car7 = new car( 7,2,21,23,11,0,6,0,0,0);// dummy car
const car* car8 = new car( 8,3,21,23,0,0,8,0,7,10);// dummy car
const car* car9 = new car( 9,2,21,23,11,0,6,0,0,0);// dummy car
const car* car10 = new car( 10,3,21,23,0,0,8,0,7,10);// dummy car
const car* car11 = new car( 11,2,21,23,11,0,6,0,0,0);// dummy car
const car* car12 = new car( 12,3,21,23,0,0,8,0,7,10);// dummy car
const car* car13 = new car( 13,2,21,23,11,0,6,0,0,0);// dummy car
const car* car14 = new car( 14,3,21,23,0,0,8,0,7,10);// dummy car
const car* car15 = new car( 15,2,21,23,11,0,6,0,0,0);// dummy car
const car* car16 = new car( 16,3,21,23,0,0,8,0,7,10);// dummy car
const car* car0 = new car( 0,0,0,0,0,0,0,0,0,0);// null car use for reset request array element

// array for simulating requesting car
car* request_array[100];



/////////////////////////////////////////////////////////////// system setup //////////////////////////////////////////////////////////////////////

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
SemaphoreHandle_t mutexRequest;

// function prototype for resource manager
void listesning();
void choose(car*chosen_car);
void checking(car*chosen_car);
void allocate(car*chosen_car);
void reset(car*chosen_car);
void lock(short resource);
void unlock(short resource);
void resource_manager(void *pvParameters);

//function prototype for request handler
void task_request_handler(void *pvParameters);
void shift_array_left();
void add_request(car *array_name, car car_object);


void setup() {
  Serial.begin(1200);
  Serial.println(" "); 
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
  mutexRequest = xSemaphoreCreateMutex();

  // initialize car queue  
  car_queue = xQueueCreate(QUEUE_SIZE, sizeof(car*));  

  // tasks
  xTaskCreate(addRequest, "addRequest", STACK_SIZE_1280,1,1 , 0);
  xTaskCreate(task_request_handler,"Handle_Request_From_Car",STACK_SIZE_128,0,1,0);
  xTaskCreate(resource_manager, "Task1", STACK_SIZE_128,1,1 , 0);
  xTaskCreate(resource_manager, "Task2", STACK_SIZE_128,1,1 , 0);
  xTaskCreate(resource_manager, "Task3", STACK_SIZE_128,1,1 , 0);
  xTaskCreate(resource_manager, "Task4", STACK_SIZE_128,1,1 , 0);

  // guard to add more car into queue
  pinMode(BUTTON,INPUT);

  Serial.println("Starting..."); 
  
}

/////////////////////////////////////////////////////////////// add dummy request ////////////////////////////////////////////////////////////////////

// add new request
void addRequest(void *pvParameters){
  (void) pvParameters;
  
  for(;;){
    while(!digitalRead(BUTTON)){
    }
    if(xSemaphoreTake(mutexRequest,0) == pdTRUE){
      Serial.println("adding new set of requesting car");
      request_array[0]= car1;
      request_array[1]= car2;
      request_array[2]= car3;
      request_array[3]= car4;
      request_array[4]= car5;
      request_array[5]= car6;
      request_array[6]= car7;
      request_array[7]= car8;
      request_array[8]= car9;
      request_array[9]= car10;
      request_array[10]= car11;
      request_array[11]= car12;
      request_array[12]= car13;
      request_array[13]= car14;
      request_array[14]= car15;
      request_array[15]= car16;
      xSemaphoreGive(mutexRequest);
      vTaskDelay( 1000/ portTICK_PERIOD_MS);
      Serial.println(uxQueueSpacesAvailable(car_queue));
    }
  
  }
}


/////////////////////////////////////////////////////////////// request handler //////////////////////////////////////////////////////////////////////
void task_request_handler(void *pvParameters){
  (void) pvParameters;
  Serial.println("handler"); 
  for (;;){
    if(xSemaphoreTake(mutexRequest,0) == pdTRUE){
      if( request_array[0]->ID != 0 ){
        
        if(xSemaphoreTake(mutexQueue,0) == pdTRUE){
        xQueueSendToBack( car_queue,&request_array[0],(TickType_t ) 10 );
        shift_array_left();
        xSemaphoreGive(mutexQueue);
        }
        else{
        }
      }
      else{
      }
      xSemaphoreGive(mutexRequest);
    }
    
    vTaskDelay(500 / portTICK_PERIOD_MS);    
  }
}

void shift_array_left(){
  if( request_array[0]->ID != 0 ){
      for(int i = 0; i < 100 ;i++){
        if( request_array[i+1]->ID != 0 ){
          request_array[i] = request_array[i +1];
        }
        else{
          request_array[i] = car0 ;
        }
      }
  }
}

/////////////////////////////////////////////////////////////// resource manager //////////////////////////////////////////////////////////////////////
void resource_manager(void *pvParameters){
  Serial.println("manager"); 
  car car_handler = car( 0,0,0,0,0,0,0,0,0,0);
  for (;;)
  {
    listesning();// check for requesting car on queue
    choose(&car_handler);// take car to handle
    Serial.println(car_handler.ID); 
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
  chosen_car->reset();
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

void loop(){
}
