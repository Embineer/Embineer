#include <Arduino_FreeRTOS.h>
#include <queue.h>

//Define tasks,queue,variables and functions
void task_request_handler(void *pvParameters);
void shift_array_left(car* array_name)

QueueHandle_t car_queue;

car request_array [100];

int queue_size = 0;


void setup() {
  car_queue = xQueueCreate(100, //Queue length
                          sizeof(short) * 10); //Queue item size
  if(car_queue == NULL){
    //Error handler for when car queue is not created
    Serial.println("ERROR: Car queue not succesfully created");
  }
  
  xTaskCreate(task_request_handler,
              "Handle_Request_From_Car",
              ?,//Stacksize
              NULL,//Parameter
              ?,//Priority
              NULL);

}

void loop() {
}

void task_request_handler(void *pvParameters){
  (void) pvParameters;

  for (;;){
    if( request_array[0] != 0 ){
      xQueueSendToFront( task_request_handler,
                         ( void * ) &request_array[0],
                         (TickType_t ) 10 )
      queue_size++;
      shift_array_left(request_array);
    }
  }
  
}

void shift_array_left(car* array_name){
  array_name[0] = 0;
  for(i = 0; i < 100 ;i++){
    if( array_name[i+1] != 0 ){
      array_name[i] = array_name[i +1];
    }
    else{
      break;
    }
    
    
  }
}

void add_request(car* array_name, car car_object){
  for(i = 0; i < 100 ;i++){
    if(array_name[i] != 0){
      ;
    }
    else{
      array_name[i] = car_object;
    }
}