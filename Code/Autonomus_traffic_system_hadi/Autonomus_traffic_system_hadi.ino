//
//#include <Arduino_FreeRTOS.h>
//#include <semphr.h>
//#include <queue.h>
//////////////////////////////////////////////////////// dummy object ////////////////////////////////////////////////////
//car class to create dummy car//

class car {
  private:

  public:
  car (short Duration, short allowed,short Time_Arrival,short Leave,short S1,short S2,short S3,short S4,short S5,short S6);
  car();
  void reset(){
    Duration=0;
    Allowed=0;
    Time_Arrival=0;
    Leave=0;
    S1=0;
    S2=0;
    S3=0;
    S4=0;
    S5=0;
    S6=0; 
  }
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
car* car2 = new car( 200,2,21,23,0,0,0,0,7,0);// dummy car


car request_array [100];




//////////////////////////////////////////////////////// the system ////////////////////////////////////////////////////////


//queue for car request
QueueHandle_t car_queue;
int queue_size = 0;


//guard for each critical section in this system
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
void shift_array_left();
void add_request(car *array_name, car car_object);

void setup() {

  Serial.begin(1200);
  request_array[0]= *car1;
  request_array[1]= *car2;

  car_queue = xQueueCreate(100, //Queue length
                          sizeof(short) * 10); //Queue item size
                          
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

  //tasks

  xTaskCreate(task_request_handler,"Handle_Request_From_Car",1280,0,1,0);
  xTaskCreate(resource_manager, "Task1", 1280,0,1,0);
  xTaskCreate(resource_manager, "Task2", 1280,0,1,0);
  

//  queue[0] = car1;//dudi
//  queue[1] = car2;//dudi

}

void loop() {}

//////////////////////////////////////////////////////// car request handler ////////////////////////////////////////////////////////


void task_request_handler(void *pvParameters){
  (void) pvParameters;

  for (;;){
    
    
    if( request_array[0].Duration != 0 ){
//      Serial.print("DURATION IS : ");
//      Serial.println(request_array[0].Duration);
      if(xSemaphoreTake(mutexQueue,0) == pdTRUE){
//      Serial.println("Mutex is free");
      xQueueSendToBack( car_queue,
                         &request_array[0],
                         (TickType_t ) 10 );
      queue_size++;
      shift_array_left();
      xSemaphoreGive(mutexQueue);
      }
    
      else{
//       Serial.println("Mutex is NOT free");
      }
    }
    
    else{
    ;
    }

    vTaskDelay(500 / portTICK_PERIOD_MS);
    
    
  }
  
}

void shift_array_left(){
  request_array[0].reset();
  for(int i = 0; i < 100 ;i++){
    if( request_array[i+1].Duration != 0 ){
      request_array[i] = request_array[i +1];
    }
    else{
      request_array[i].reset();
    }

  }
}

void add_request(car *array_name, car car_object){
  for(int i = 0; i < 100 ;i++){
    if(sizeof(array_name[i]) != 0){
      ;
    }
    else{
      array_name[i] = car_object;
    }
  }
}


//////////////////////////////////////////////////////// resource access manager ////////////////////////////////////////////////////

void resource_manager(void *pvParameters)
{
//  Serial.println("new"); 
  
  car car_handler = car( 0,0,0,0,0,0,0,0,0,0);
  for (;;)
  {
    listesning();//check for requesting car on queue
    choose(&car_handler);//take car to handle
    checking(&car_handler);//lock requested resources
    allocate(&car_handler);// give permission to the car to use the resources
    reset(&car_handler);//unlock requested resources
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  
}


//check for requesting car on queue
void listesning()
{
  for(; uxQueueSpacesAvailable(car_queue) == 100;){vTaskDelay(500 / portTICK_PERIOD_MS);} // Check first element queue kosong ke tak
  
}
//take a car from queue to handle the car
void choose(car *chosen_car)
{
 
  while(xSemaphoreTake(mutexQueue, 10)!= pdTRUE){};
  xQueueReceive( car_queue,chosen_car,( TickType_t ) 10 );
  while(xSemaphoreGive(mutexQueue)!= pdTRUE){};

  
}


//lock requested resources
void checking(car *chosen_car)
{
  

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
