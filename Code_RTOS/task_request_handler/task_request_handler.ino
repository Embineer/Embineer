#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

//Define tasks,queue,variables and functions
class car {
  private:

  public:
    int Duration;
    int Allowed;
    int Time_Arrival;
    int Leave;
    
};

void task_request_handler(void *pvParameters);
void shift_array_left(car *array_name);
void add_request(car *array_name, car car_object);

QueueHandle_t car_queue;
SemaphoreHandle_t mutex_car_queue;


car request_array [100];

int queue_size = 0;




void setup() {
  car_queue = xQueueCreate(100, //Queue length
                          sizeof(short) * 10); //Queue item size

  mutex_car_queue = xSemaphoreCreateMutex();
  if(car_queue == NULL){
    //Error handler for when car queue is not created
    Serial.println("ERROR: Car queue not succesfully created");
  }
  
  xTaskCreate(task_request_handler,
              "Handle_Request_From_Car",
              128,//Stacksize
              NULL,//Parameter
              2,//Priority
              NULL);

}

void loop() {
}


void task_request_handler(void *pvParameters){
  (void) pvParameters;

  for (;;){
    if(xSemaphoreTake(mutex_car_queue,0) == pdTRUE){
      if( sizeof(request_array[0]) != 0 ){
      xQueueSendToBack( car_queue,
                         &request_array[0],
                         (TickType_t ) 10 );
      queue_size++;
      shift_array_left(request_array);
      xSemaphoreGive(mutex_car_queue);
      }
    }
    else{
      Serial.println("Car queue is being accessed by another proccess");
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
