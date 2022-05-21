
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

class car {
  private:

  public:
  car (short Duration, short allowed,short Time_Arrival,short Leave,short s1,short s2,short s3,short s4,short s5,short s6);
    short Duration;
    short Allowed;
    short Time_Arrival;
    short Leave;
    short s1;
    short s2;
    short s3;
    short s4;
    short s5;
    short s6;
    
};

car::car(short Duration, short allowed,short Time_Arrival,short Leave,short s1,short s2,short s3,short s4,short s5,short s6)
{
  Duration=Duration;
  Allowed=Allowed;
  Time_Arrival=Time_Arrival;
  Leave=Leave;
  s1=s1;
  s2=s2;
  s3=s3;
  s4=s4;
  s5=s5;
  s6=s6;  
}
car* queue[100];

 car* car1 = new car( 200,2,21,23,11,0,0,0,0,0);
 car car_handler1 = car( 0,0,0,0,0,0,0,0,0,0);
//car* car2 = new car;
//car* car3 = new car;

SemaphoreHandle_t mutex;
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

void listesning();
void rearange();
void checking(car*choosen_car);
void allocate(car*choosen_car);
void reset(car*choosen_car);
void lock(short resource);
void unlock(short resource);

int globalCount = 0;

void setup() {

  Serial.begin(9600);

  mutex = xSemaphoreCreateMutex();
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

  

 


  xTaskCreate(resource_manager, "Task1", 128, 1, 1, NULL);

  queue[0] =car1;

}

void loop() {}
car* choosen_car =new car( 200,2,21,23,11,0,0,0,0,0);
void resource_manager()
{
  for (;;)
  {
    Serial.println("dh masuk dah");
    
    listesning();

    

    
    Serial.println( choosen_car->Duration);
    Serial.println( choosen_car->s1);






    checking(choosen_car);
    allocate(choosen_car);
    reset(choosen_car);
    
  }
  
}


void listesning()
{
  for(; queue[0] == 0;){}
}

void rearange()
{
    //queue[0] =car2;
}



void checking(car *choosen_car)
{
  

    if(choosen_car->s1!=0)
    {
        lock(choosen_car->s1);
    }
    if(choosen_car->s2!=0)
    {
        lock(choosen_car->s2);
    }
    if(choosen_car->s3!=0)
    {
        lock(choosen_car->s3);
    }
    if(choosen_car->s4!=0)
    {
        lock(choosen_car->s4);
    }
    if(choosen_car->s5!=0)
    {
      lock(choosen_car->s5);
    }
    if(choosen_car->s6!=0)
    {
      lock(choosen_car->s6);
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
    case 6 :  while(xSemaphoreTake(mutex6, 10)!= pdTRUE);Serial.println("suksess 66666666666666666666666666666666666"); break;
    case 7 :  while(xSemaphoreTake(mutex7, 10)!= pdTRUE);Serial.println("suksess 7777777777777777777777777777777777"); break;
    case 8 :  while(xSemaphoreTake(mutex8, 10)!= pdTRUE); break;
    case 9 :  while(xSemaphoreTake(mutex9, 10)!= pdTRUE); break;
    case 10 :  while(xSemaphoreTake(mutex10, 10)!= pdTRUE); break;
    case 11 :  while(xSemaphoreTake(mutex11, 10)!= pdTRUE);Serial.println("suksess  11111111111111111111111111111"); break;
    case 12 :  while(xSemaphoreTake(mutex12, 10)!= pdTRUE); break;
  }
}

void allocate(car*choosen_car)
{
  delay(choosen_car->Duration/ portTICK_PERIOD_MS);
}

void reset(car *choosen_car)
{
    if(choosen_car->s1!=0)
    {
        unlock(choosen_car->s1);
    }
    if(choosen_car->s2!=0)
    {
        unlock(choosen_car->s2);
    }
    if(choosen_car->s3!=0)
    {
        unlock(choosen_car->s3);
    }
    if(choosen_car->s4!=0)
    {
        unlock(choosen_car->s4);
    }
    if(choosen_car->s5!=0)
    {
      unlock(choosen_car->s5);
    }
    if(choosen_car->s6!=0)
    {
      unlock(choosen_car->s6);
    }
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
    case 6 :  while(xSemaphoreGive(mutex6)!= pdTRUE);Serial.println("suksess  uuuuuuuuuuuuuuuuuuuuuuuuu 666666666666666666666666666666666"); break;
    case 7 :  while(xSemaphoreGive(mutex7)!= pdTRUE);Serial.println("suksess  uuuuuuuuuuuuuuuuuuu 777777777777777777777777"); break;
    case 8 :  while(xSemaphoreGive(mutex8)!= pdTRUE); break;
    case 9 :  while(xSemaphoreGive(mutex9)!= pdTRUE); break;
    case 10 :  while(xSemaphoreGive(mutex10)!= pdTRUE); break;
    case 11 :  while(xSemaphoreGive(mutex11)!= pdTRUE);Serial.println("suksess uuuuuuuuuuuuuuu 1111111111111111111111111111"); break;
    case 12 :  while(xSemaphoreGive(mutex12)!= pdTRUE); break;

  }
}

