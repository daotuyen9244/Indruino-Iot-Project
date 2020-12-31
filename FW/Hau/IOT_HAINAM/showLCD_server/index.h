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
          .bt_login {height:20px; width:50px; margin:10px 0;background-color:#00FF00;border-radius:5px;}
          .bt_write {height:30px; width:70px; margin:10px 0;background-color:#00FF00;border-radius:5px;}
          .bt_restart {height:30px; width:70px; margin:10px 0;background-color:#FF6600;border-radius:5px;}
          .bt_clear {height:30px; width:70px; margin:10px 0;background-color:#00FF00;border-radius:5px;}
       </style>
       <meta name="vieport" content="width=device-width,user-scalable=0" charset="UTF-8">
   </head>
   <body> 
      <h1>ESP32 Web Server</h1> 
      <div id ="homecontrol" >
        <div> <h2>Vui lòng đăng nhập trước khi sử dụng </h2> </div>
        <div> 
          <form method="post"> 
            <div><label>User Name </label></div>
            <div><input type="text" name="username" id="user"/> </div>
            <div><label>Password </label></div>
            <div><input type="password" name="password" id="password"/> </div>
            <div><input type="button" class="bt_login" value="Login" onclick="checklogin()"/> </div>  
          </form> 
        </div>   
        <div>IP connected: <b><pan id="ipconnected"></pan></b></div>
      </div>
      
      <div id="setup">
        <div>Username WiFi </div>
        <div><input id="ssid"/></div>
        <div>Password WiFi </div>
        <div><input id="pass"/></div>
        <div>ID board </div>
        <div><input id="id_board"/></div>
        <div>
        <button class="bt_write" onclick="writeEEPROM()">WRITE</button>
        <button class="bt_restart" onclick="restartESP()">RESTART</button>
        <button class="bt_clear" onclick="clearEEPROM()">CLEAR</button> 
      </div>
        <div id="reponsetext"></div>
      </div>
      <script>
        //-----------Tạo đối tượng request----------------
        function create_obj()
        {
          td = navigator.appName;
          if(td == "Microsoft Internet Explorer")
          {
            obj = new ActiveXObject("Microsoft.XMLHTTP");
          }else
          {
            obj = new XMLHttpRequest();
          }
          return obj;
        }
        var xhttp = create_obj();

        //===================Khởi tạo ban đầu khi load trang=============
        window.onload = function()
        {
          document.getElementById("homecontrol").style.display = "block";
          document.getElementById("setup").style.display = "none";
          getIPconnect();
        }
        //------------------------------------------------
        function getIPconnect()
        {
          xhttp.open("GET","/getIP",true);
          xhttp.onreadystatechange = process_ip;//nhận reponse 
          xhttp.send();
        }
        //-----------Kiểm tra response IP------------------
        function process_ip()
        {
          if(xhttp.readyState == 4 && xhttp.status == 200){
            //------Updat data sử dụng javascript----------
            ketqua = xhttp.responseText; 
            document.getElementById("ipconnected").innerHTML=ketqua;       
          }
        }    
        //===============================================================
        //-----------Thiết lập dữ liệu và gửi request ssid,password, server và port ---

        function checklogin()
        {
          if(Empty(document.getElementById("user"), "Please enter ssid!")&&Empty(document.getElementById("password"), "Please enter password"))
          {
            var user = document.getElementById("user").value;
            var password = document.getElementById("password").value;
            if (user == "admin" && password == "indruino2020" )
            {
              alert ("Login successfully"); 
              document.getElementById("homecontrol").style.display = "none";
              document.getElementById("setup").style.display = "block";
              //getIPconnect();
            }
            else 
            {
              alert("Invalid username or password");
              document.getElementById("homecontrol").style.display = "block";
              document.getElementById("setup").style.display = "none";
            }
          }
        }
        function writeEEPROM()
        {
          //if(Empty(document.getElementById("ssid"), "Please enter ssid!")&&Empty(document.getElementById("pass"), "Please enter password"))
          {
            var ssid = document.getElementById("ssid").value;
            var pass = document.getElementById("pass").value;
            var idboard = document.getElementById("id_board").value;
            xhttp.open("GET","/writeEEPROM?ssid="+ssid+"&pass="+pass+"&id_board="+idboard,true);
            xhttp.onreadystatechange = process;//nhận reponse 
            xhttp.send();
          }
        }
        function clearEEPROM()
        {
          if(confirm("Do you want to delete all saved wifi configurations?"))
          {
                xhttp.open("GET","/clearEEPROM",true);
                xhttp.onreadystatechange = process;//nhận reponse 
                xhttp.send();
          }
        }
        function restartESP()
        {
          if(confirm("Do you want to reboot the device?"))
          {
                xhttp.open("GET","/restartESP",true);
                xhttp.send();
                alert("Device is restarting! If no wifi is found please press reset!"); 
          }
        }
        //-----------Kiểm tra response ------------------
        function process()
        {
          if(xhttp.readyState == 4 && xhttp.status == 200)
          {
            //------Updat data sử dụng javascript----------
            ketqua = xhttp.responseText; 
            document.getElementById("reponsetext").innerHTML=ketqua;       
          }
        }

        //----------------------------CHECK EMPTY--------------------------------
       function Empty(element, AlertMessage)
       {
          if(element.value.trim()== "")
          {
            alert(AlertMessage);
            element.focus();
            return false;
          }else
          {
            return true;
          }
       }
      </script>
   </body> 
  </html>
)=====";
