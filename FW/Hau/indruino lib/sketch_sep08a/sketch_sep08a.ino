void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 while(!Serial);
int a = 1;
int *b = &a;

 b = (int*)calloc(1, sizeof(int));
 b = (int*)realloc(b, 2*sizeof(int));
 *b = 1;
 b = (int*)realloc(b,3*sizeof(int));
 Serial.println(*b, DEC);
}

void loop() {
  // put your main code here, to run repeatedly:

}
