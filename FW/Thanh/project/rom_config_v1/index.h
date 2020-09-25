//=========Biến chứa mã HTLM Website==//
const char MainPage[] PROGMEM = R"=====(
  <!DOCTYPE html> 
  <html>
   <head> 
       <title>HOME PAGE</title> 
       <style> 
          body {text-align:center;}
          h1 {color:#003399;}
          a {text-decoration: none;color:#FFFFFF;}
          .bt_write {height:30px; width:70px; margin:10px 0;background-color:#00FF00;border-radius:5px;}
          .bt_restart {height:30px; width:70px; margin:10px 0;background-color:#FF6600;border-radius:5px;}
          .bt_clear {height:30px; width:70px; margin:10px 0;background-color:#00FF00;border-radius:5px;}
       </style>
       <meta name="viewport" content="width=device-width,user-scalable=0" charset="UTF-8">
   </head>
   <body> 
      <h1>ESP32 Web Server</h1> 
      <div>User: </div>
      <div><input id="ssid"/></div>
      <div>Password: </div>
      <div><input id="pass"/></div>
      <div>MQTT Server: </div>
      <div><input id="server"/></div>
      <div>MQTT Port: </div>
      <div><input id="port"/></div>
      <div>
        <button class="bt_write" onclick="writeEEPROM()">WRITE</button>
        <button class="bt_restart" onclick="restartESP()">RESTART</button>
        <button class="bt_clear" onclick="clearEEPROM()">CLEAR</button>
      </div>
      <div id>IP connected: <pan id="ipconnected"></pan></div>
      <div id="reponsetext"></div>
      <script>
        //-----------Tạo đối tượng request----------------
        function create_obj(){
          td = navigator.appName;
          if(td == "Microsoft Internet Explorer"){
            obj = new ActiveXObject("Microsoft.XMLHTTP");
          }else{
            obj = new XMLHttpRequest();
          }
          return obj;
        }
        var xhttp = create_obj();
        //------------------------------------------------
        window.onload = function(){
          xhttp.open("GET","/getIP",true);
          xhttp.onreadystatechange = process_ip;//nhận reponse 
          xhttp.send();
        }
        //-----------Kiểm tra response IP------------------
        function process_ip(){
          if(xhttp.readyState == 4 && xhttp.status == 200){
            //------Updat data sử dụng javascript----------
            ketqua = xhttp.responseText; 
            document.getElementById("ipconnected").innerHTML=ketqua;       
          }
        }
        
        //===============================================================
        //-----------Thiết lập dữ liệu và gửi request ssid,password, server và port ---
        function writeEEPROM(){
          var ssid = document.getElementById("ssid").value;
          var pass = document.getElementById("pass").value;
          var server = document.getElementById("server").value;
          var port = document.getElementById("port").value;
          xhttp.open("GET","/writeEEPROM?ssid="+ssid+"&pass="+pass+"&server="+server+"&port="+port,true);
          xhttp.onreadystatechange = process;//nhận reponse 
          xhttp.send();
        }
        function clearEEPROM(){
          xhttp.open("GET","/clearEEPROM",true);
          xhttp.onreadystatechange = process;//nhận reponse 
          xhttp.send();
        }
        function restartESP(){
          xhttp.open("GET","/restartESP",true);
          xhttp.onreadystatechange = process;//nhận reponse 
          xhttp.send();
        }
        //-----------Kiểm tra response ------------------
        function process(){
          if(xhttp.readyState == 4 && xhttp.status == 200){
            //------Updat data sử dụng javascript----------
            ketqua = xhttp.responseText; 
            document.getElementById("reponsetext").innerHTML=ketqua;       
          }
        }
      </script>
   </body> 
  </html>
)=====";
//=========================================//
