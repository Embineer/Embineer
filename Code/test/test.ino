#include <Vector.h>

void setup() {
  Serial.begin(9600);
  delay(2000);
  const int ELEMENT_COUNT_MAX = 2;
  int testing1[ELEMENT_COUNT_MAX];
  Vector<int> testing(testing1);
  testing.push_back(1);
  testing.push_back(2);
  testing.push_back(3);
  testing.push_back(4);

  for (int i = 0; i < testing.size(); i++){
    Serial.print("I = ");
    Serial.print(testing[i]);
    Serial.print(", ");
  }

  Serial.println("");

   testing.remove(0);
   
  for (int i = 0; i < testing.size(); i++){
    Serial.print("I = ");
    Serial.print(testing[i]);
    Serial.print(", ");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
