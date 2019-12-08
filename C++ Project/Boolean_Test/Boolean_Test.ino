boolean route=false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println(route);
  route=(route==0);
  delay(2000);
}
