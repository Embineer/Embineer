
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>
//////////////////////////////////////////////////////// dummy object ////////////////////////////////////////////////////
//car class to create dummy car//
class car {
  private:

  public:
  car (short Duration, short allowed,short Time_Arrival,short Leave,short S1,short S2,short S3,short S4,short S5,short S6);
  car(); 
    short Duration;
    short Allowed;
    short Time_Arrival;
    short Leave;
    short S1;
    short S2;
    short S3;
    short S4;
    short S5;
    short S6;
    
};
//car constructor complete
car::car(short duration, short allowed,short time_Arrival,short leave,short s1,short s2,short s3,short s4,short s5,short s6)
{
  Duration=duration;
  Allowed=allowed;
  Time_Arrival=time_Arrival;
  Leave=leave;
  S1=s1;
  S2=s2;
  S3=s3;
  S4=s4;
  S5=s5;
  S6=s6;  
}
car::car()
{

}

//car class to create dummy car//
car* car1 = new car( 150,2,21,23,11,0,6,0,0,0);// dummy car
car car2 = car( 200,2,21,23,0,0,0,0,7,0);// dummy car


car request_array [100];



//////////////////////////////////////////////////////// the system ////////////////////////////////////////////////////////


//queue for car request
QueueHandle_t car_queue = xQueueCreate(100,sizeof(car));
int queue_size = 0;


//guard for each critical section in this system
SemaphoreHandle_t mutex_car_queue;
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

 

//function prototype for resource manager
void listesning();
void choose(car*chosen_car);
void rearange();
void checking(car*chosen_car);
void allocate(car*chosen_car);
void reset(car*chosen_car);
void lock(short resource);
void unlock(short resource);

//function prototype for request handler
void task_request_handler(void *pvParameters);
void shift_array_left(car *array_name);
void add_request(car car_object);

void setup() {

  Serial.begin(1200);

 

  mutex_car_queue = xSemaphoreCreateMutex();
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

  //tasks

  //  xTaskCreate(task_request_handler,"Handle_Request_From_Car",128,NULL,1,NULL);
  xTaskCreate(resource_manager, "Task1", 128,1,1 , NULL);
  xTaskCreate(resource_manager, "Task2", 128,1,1 , NULL);

  xQueueSendToBack( car_queue,(void*)&car1, (TickType_t ) 0 );
  xQueueSendToBack( car_queue,(void*)&car2, (TickType_t ) 0 );
  // add_request(car1);
  // add_request(car2);
//  queue[0] = car1;//dudi
//  queue[1] = car2;//dudi

}

void loop() {}

//////////////////////////////////////////////////////// car request handler ////////////////////////////////////////////////////////


void task_request_handler(void *pvParameters){
  (void) pvParameters;

  for (;;){
    if(xSemaphoreTake(mutex_car_queue,0) == pdTRUE){
      if( sizeof(request_array[0]) != 0 ){
          // Serial.println("masuk task handler");
      xQueueSendToBack( car_queue,
                         &request_array[0],
                         (TickType_t ) 0 );
                     
      queue_size++;
      shift_array_left(request_array);
      xSemaphoreGive(mutex_car_queue);
      }
      // Serial.println(uxQueueMessagesWaiting( car_queue));
    }
    else{Serial.println("Car queue is being accessed by another proccess");
    }
    
  }
  
}

void shift_array_left(car *array_name){
  delete &array_name[0];
  for(int i = 0; i < 100 ;i++){
    if( sizeof(array_name[i+1]) != 0 ){
      array_name[i] = array_name[i +1];
    }
    else{
      break;
    }
    
    
  }
}

void add_request(car car_object){
  for(int i = 0; i < 100 ;i++){
    if(sizeof(request_array[i]) != 0){
      ;
    }
    else{
      request_array[i] = car_object;
    }
  }
}


//////////////////////////////////////////////////////// resource access manager ////////////////////////////////////////////////////

void resource_manager(void *pvParameters)
{
  Serial.println("new"); 
  
  car car_handler = car( 0,0,0,0,0,0,0,0,0,0);
  for (;;)
  {
    Serial.println("list ");
    listesning();//check for requesting car on queue 
    Serial.print(uxQueueMessagesWaiting( car_queue));
    Serial.println("list ");
    // Serial.println(car_handler.Duration);
    choose(&car_handler);//take car to handle
    Serial.println(car_handler.Duration);
    checking(&car_handler);//lock requested resources
    allocate(&car_handler);// give permission to the car to use the resources
    reset(&car_handler);//unlock requested resources
  }
  
}


//check for requesting car on queue
void listesning()
{
  for(;  uxQueueMessagesWaiting( car_queue)==0;){
  }
}
//take a car from queue to handle the car
void choose(car *chosen_car)
{
 
  while(xSemaphoreTake(mutex_car_queue, 10)!= pdTRUE){};
  xQueueReceive( car_queue,&(chosen_car),( TickType_t ) 0 ) ;
  while(xSemaphoreGive(mutex_car_queue)!= pdTRUE){};  
}

//lock requested resources
void checking(car *chosen_car)
{
  
  Serial.println("checking..... ");
    if(chosen_car->S1!=0)
    {
        lock(chosen_car->S1);
    }
    if(chosen_car->S2!=0)
    {
        lock(chosen_car->S2);
    }
    if(chosen_car->S3!=0)
    {
        lock(chosen_car->S3);
    }
    if(chosen_car->S4!=0)
    {
        lock(chosen_car->S4);
    }
    if(chosen_car->S5!=0)
    {
      lock(chosen_car->S5);
    }
    if(chosen_car->S6!=0)
    {
      lock(chosen_car->S6);
    }
}
    

void lock(short resource)
{
  int sumber = int(resource);
  
  switch (resource)
  {
    case 1 :  while(xSemaphoreTake(mutex1, 10)!= pdTRUE); break;
    case 2 :  while(xSemaphoreTake(mutex2, 10)!= pdTRUE); break;
    case 3 :  while(xSemaphoreTake(mutex3, 10)!= pdTRUE); break;
    case 4 :  while(xSemaphoreTake(mutex4, 10)!= pdTRUE); break;
    case 5 :  while(xSemaphoreTake(mutex5, 10)!= pdTRUE); break;
    case 6 :  while(xSemaphoreTake(mutex6, 10)!= pdTRUE);Serial.println("Source 6 locked"); break;
    case 7 :  while(xSemaphoreTake(mutex7, 10)!= pdTRUE);Serial.println("Source 7 locked"); break;
    case 8 :  while(xSemaphoreTake(mutex8, 10)!= pdTRUE); break;
    case 9 :  while(xSemaphoreTake(mutex9, 10)!= pdTRUE); break;
    case 10 :  while(xSemaphoreTake(mutex10, 10)!= pdTRUE); break;
    case 11 :  while(xSemaphoreTake(mutex11, 10)!= pdTRUE);Serial.println("source 11 locked"); break;
    case 12 :  while(xSemaphoreTake(mutex12, 10)!= pdTRUE); break;
  }
}
// give permission to the car to use the resources
void allocate(car*choosen_car)
{
  delay(((choosen_car->Duration)*30)/ portTICK_PERIOD_MS);
}

//unlock requested resources
void reset(car * chosen_car)
{
    if(chosen_car->S1!=0)
    {
        unlock(chosen_car->S1);
    }
    if(chosen_car->S2!=0)
    {
        unlock(chosen_car->S2);
    }
    if(chosen_car->S3!=0)
    {
        unlock(chosen_car->S3);
    }
    if(chosen_car->S4!=0)
    {
        unlock(chosen_car->S4);
    }
    if(chosen_car->S5!=0)
    {
      unlock(chosen_car->S5);
    }
    if(chosen_car->S6!=0)
    {
      unlock(chosen_car->S6);
    }
    chosen_car->Duration =0;
    chosen_car->Allowed =0;
    chosen_car->Time_Arrival =0;
    chosen_car->Leave =0;
    chosen_car->S1 =0;
    chosen_car->S2 =0;
    chosen_car->S3 =0;
    chosen_car->S4 =0;
    chosen_car->S5 =0;
    chosen_car->S6 =0;
}


void unlock(short resource)
{
  switch (int(resource))
  {
    case 1 :  while(xSemaphoreGive(mutex1)!= pdTRUE); break;
    case 2 :  while(xSemaphoreGive(mutex2)!= pdTRUE); break;
    case 3 :  while(xSemaphoreGive(mutex3)!= pdTRUE); break;
    case 4 :  while(xSemaphoreGive(mutex4)!= pdTRUE); break;
    case 5 :  while(xSemaphoreGive(mutex5)!= pdTRUE); break;
    case 6 :  while(xSemaphoreGive(mutex6)!= pdTRUE);Serial.println("source 6 unlocked"); break;
    case 7 :  while(xSemaphoreGive(mutex7)!= pdTRUE);Serial.println("source 7 unlocked"); break;
    case 8 :  while(xSemaphoreGive(mutex8)!= pdTRUE); break;
    case 9 :  while(xSemaphoreGive(mutex9)!= pdTRUE); break;
    case 10 :  while(xSemaphoreGive(mutex10)!= pdTRUE); break;
    case 11 :  while(xSemaphoreGive(mutex11)!= pdTRUE);Serial.println("source 11 unlocked"); break;
    case 12 :  while(xSemaphoreGive(mutex12)!= pdTRUE); break;

  }
}
