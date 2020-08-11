#include <WiFi.h>

String ssid ="Iphone11";
String pass ="xai3gdiban";
String ID_Client="IOT47";

unsigned char Connect_packet[14]={0x10, 0xFF, 0x00, 0x04, 0x4D, 0x51, 0x54, 0x54 ,0x04, 0x02, 0x00, 0x3C, 0x00, 0xFF};
int Connect_Packet_Length;

//hàm này có nhiệm vụ gửi 1 lệnh AT đến cho ESP32 và chờ xem nó có phản hồi đúng data về không
bool ESP32_SendCommand(String cmd,String value,int timeout)
{
 String rx_data="";
 while(Serial.available())Serial.read(); //xóa sạch bộ đệm RX

 Serial.print(cmd);       // gửi lệnh AT đi
 unsigned long t=millis();
 while(1)
 {
   if((millis() - t) > timeout)return false; //nếu tới time out thì thoát
   if (Serial.available() > 0)
   {
     char inChar = (char)Serial.read();
     rx_data+=inChar;
     if(rx_data.indexOf(value) != -1)return true;     
   }
 }
}
int ESP32_init()
{
  int i=0;

  while(1)//GỬI LỆNH AT
  {
    if(ESP32_SendCommand("AT\r\n","OK",500) == true)break; // liên tục gửi lệnh AT xem ESP32 có hoạt động không
    i++; if(i==10)return 1; //trả về false báo init thất bài
  }
  
  //1 số setup cơ bản
  delay(100);Serial.print("ATE0\r\n"); //tắt phản hồi
  delay(100);Serial.print("AT+CWMODE=1\r\n"); //chế độ station
  delay(100);Serial.print("AT+CIPMUX=0\r\n"); //chế độ đơn kênh

  delay(100);
  String data_connect = "AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"\r\n";
  if(ESP32_SendCommand(data_connect,"OK",10000) == false)return 2; //kết nối vào wifi, timeout 10 giây
  return 0;
}
void ESP32_pub(String topic,String mess) //max topic length + mess =127
{
  
} 
void ESP32_sub(String topic) //max topic length =255
{                                  //size                    size
  unsigned char Sub_packet[6]={0x82, 0xFF, 0x00, 0x01, 0x00, 0xFF};
  //tính độ dài gói packet
  Sub_packet[5] = topic.length();
  Sub_packet[1] = 4 + Sub_packet[5] + 1;
  
  int Sub_packet_length = Sub_packet[1] + 2;
  String CIPSEN = "AT+CIPSEND=" + String(Sub_packet_length) + "\r\n";
  Serial.print(CIPSEN);
  delay(50);

  //gửi gói tin sub đi
  for(int i=0;i<6;i++)Serial.write(Sub_packet[i]);
  Serial.print(topic);
  Serial.write(0x00);
  ESP32_SendCommand("","SEND OK",3000); //chờ phản hồi SEND OK
}
void MQTT_init()
{
  Connect_packet[13] = ID_Client.length(); //byte 14 ghi độ dài của id
  Connect_packet[1]  = Connect_packet[13] + 12; //byte 1 ghi Packet Length
  Connect_Packet_Length = Connect_packet[1] + 2;
}
int MQTT_broker_connect()
{ 
  MQTT_init();
  int i=10;
  while(i--)
  {
    if(ESP32_SendCommand("AT+CIPSTART=\"TCP\",\"broker.hivemq.com\",1883\r\n","CONNECT",3000) == true) //kết nối tcp tới broker
    {
      String CIPSEN = "AT+CIPSEND=" + String(Connect_Packet_Length) + "\r\n";
      Serial.print(CIPSEN);
      delay(50);
      //gửi gói tin connect đi
      for(int i=0;i<14;i++)Serial.write(Connect_packet[i]);
      Serial.print(ID_Client);
      ESP32_SendCommand("","SEND OK",3000); //chờ phản hồi SEND OK
      return 0;
    }
  }
  return 1; //không thể kết nối tới server
}
void MQTT_reconnect()
{
 
}
void setup() 
{
  pinMode(A0,OUTPUT);digitalWrite(A0,LOW); 
  pinMode(A1,OUTPUT);digitalWrite(A1,LOW); 
  pinMode(A2,OUTPUT);digitalWrite(A2,LOW); 
  pinMode(A3,OUTPUT);digitalWrite(A3,LOW); 
  delay(500);
  Serial.begin(115200);
  
  int err_code = 0;
  err_code=ESP32_init();
  if(err_code != 0)
  {
     /*
      * err_code=1 lỗi kết nối
      * err_code=2 không thể truy cập vào wifi
      */
     Serial.print("Error code=");Serial.println(err_code);
     while(1);
  }
  int err_code_connect=MQTT_broker_connect(); // khởi tạo giao thức MQTT
  if(err_code != 0)
  {
    /*
      * err_code_connect=1 //không thể kết nối tới server
      * 
      */
      Serial.print("err_code_connect=");Serial.println(err_code_connect);
      while(1);
  }
  ESP32_sub("ESP32_read_data"); //đăng kí nhận mess từ topic
}

String inputString="";
void loop() 
{
 if (Serial.available() > 0)  //nhận tin nhắn từ topic 
   {
     delay(100);
     while(Serial.available() > 0) //data bắt đầu từ byte 0x00 , byte tiếp theo chưa độ dài của topic
     {
       char inChar = (char)Serial.read();
       if(inChar == 0) break;
     }
     inputString="";
     while(Serial.available() > 0)
     {
       char inChar = (char)Serial.read();
       inputString+=inChar;      
     }   
     int topic_length = inputString[0];
     String topic = inputString.substring(1,1+topic_length); //lấy được tên topic
     String mess = inputString.substring(1+topic_length);    //lấy được tên mess

     if(mess == "Bat 1")digitalWrite(A0,HIGH); 
     if(mess == "Tat 1")digitalWrite(A0,LOW); 
     if(mess == "Bat 2")digitalWrite(A1,HIGH); 
     if(mess == "Tat 2")digitalWrite(A1,LOW); 
     if(mess == "Bat 3")digitalWrite(A2,HIGH); 
     if(mess == "Tat 3")digitalWrite(A2,LOW); 
     if(mess == "Bat 4")digitalWrite(A3,HIGH); 
     if(mess == "Tat 4")digitalWrite(A3,LOW); 
   }
}
