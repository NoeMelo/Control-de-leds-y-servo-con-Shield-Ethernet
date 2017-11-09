#include <Servo.h>
Servo myservo; 
#include <SPI.h> //Aqui incluimos la libreria SPI
#include <Ethernet.h> //Aqui incluimos la libreria Ethernet
byte mac[]={0xDE,0xAD,0xBE,0xEF,0xFE,0xED}; //Declaracion de la direccion MAC 
IPAddress ip(172, 43, 1, 37); //Declaracion de la IP 
EthernetServer servidor(80); //Declaracion del puerto 80

int PIN_LED=8; //Aqui establecemos la variable PIN_LED como un valor entero
String readString=String(30); //lee los caracteres de una secuencia en una cadena.
//Los strings se representan como arrays de caracteres (tipo char)
String state=String(10);

int value;
void setup() {
  Ethernet.begin(mac, ip); //Inicializamos con las direcciones asignadas 
  servidor.begin(); //inicia el servidor
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED,LOW);
  state="ESPERE";
  
    myservo.attach(6);
    pinMode(13,OUTPUT); //Establecemos los pines como salidas
    pinMode(12,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(4,OUTPUT);
    
}


void loop() {
  //EthernetClient Crea un cliente que se puede conectar a 
  //una dirección específica de Internet IP
  EthernetClient cliente= servidor.available(); 
  if(cliente) {
    boolean lineaenblanco=true; 
    while(cliente.connected()) {
      if(cliente.available()) {
        char c=cliente.read(); 
        if(readString.length()<30) {
          readString.concat(c);
          //Cliente conectado
          //Leemos petición HTTP caracter a caracter
          //Almacenar los caracteres en la variable readString
        } 
        if(c=='\n' && lineaenblanco) //Si la petición HTTP ha finalizado 
          {
          int LED = readString.indexOf("LED="); 
          if(readString.substring(LED,LED+5)=="LED=T") { //vamos
              value=1;
             //digitalWrite(pin, value);
             digitalWrite(13, value);
             delay(150);
             digitalWrite(12, value);
             delay(150);
             digitalWrite(11, value);
             delay(150);
             digitalWrite(10, value);
             delay(150);
             digitalWrite(9, value);
             delay(150);
             digitalWrite(8, value);
             delay(150);
             digitalWrite(7, value);
             delay(150);
             digitalWrite(5, value);
             delay(150);
             digitalWrite(4, value);
             delay(150);
              myservo.write(180);
              state="VAMOS";}
          else if (readString.substring(LED,LED+5)=="LED=F") {
               value=0;
               digitalWrite(4, value);
               delay(150);
               myservo.write(10);
               digitalWrite(5, value);
               delay(150);
               digitalWrite(7, value);
               delay(150);
               digitalWrite(8, value);
               delay(150);
               digitalWrite(9, value);
               delay(150);
               digitalWrite(10, value);
               delay(150);
               digitalWrite(11, value);
               delay(150);
               digitalWrite(12, value);
               delay(150);
               digitalWrite(13, value);
               delay(150);
              state="VENIMOS";
          }  else if (readString.substring(LED,LED+5)=="LED=C") {
                digitalWrite(13, 1);
                digitalWrite(7, 1);
                delay(200);
                digitalWrite(13, 0);
                delay(200);
                digitalWrite(7, 0);
                delay(200);
                digitalWrite(12,1);
                digitalWrite(8, 1);
                delay(200);
                
                digitalWrite(12,0);
                delay(250);
                digitalWrite(8,0);
                delay(250);
                digitalWrite(11,1);
                digitalWrite(9, 1);
                delay(250);
                digitalWrite(11,0);
                delay(250);
                digitalWrite(9, 0);
                delay(250);
                digitalWrite(10,1);
                delay(250);
                digitalWrite(10,0);
                delay(250);
                digitalWrite(5, 1);
                digitalWrite(4, 1);
                delay(250);
                for(int i=0;i<=180;i=i+20){
                  myservo.write(i);
                  delay(50);
                }
                for(int i=180;i>=0;i=i-20){
                  myservo.write(i);
                  delay(50);
                }
              state="CENTRO";
          }
    
//Cabecera HTTP estándar
cliente.println("HTTP/1.1 200 OK"); 
cliente.println("Content-Type: text/html"); 
cliente.println(); //Página Web en HTML 
cliente.println("<html>"); 
cliente.println("<head>"); 
cliente.println("<title>LAB3 :)</title>"); 

          cliente.println("<style>");
          cliente.println("body {background-image: url('https://images.fineartamerica.com/images-medium-large-5/tokyo-skyline-in-watercolor-background-pablo-romero.jpg');background-repeat: repeat-x;}");
          cliente.println(".button {border: none; text-align: center;font-size: 16px; margin: 4px 2px; cursor: pointer;width:150px;height:55px;border-radius: 4px;border-radius: 4px;}");
          cliente.println(".grupo{background-color: rgba(253, 235, 208, 0.8);border-style: solid;border-color: #F8C471;color: #34495E;padding: 20px;text-align: center; text-decoration: none;margin-right: 420px; margin-left: 420px; margin-top: 100px;margin-bottom: 100px;}");
          cliente.println(".button1 {background-color: #FFC300 ;}");
          cliente.println(".button2 {background-color: #C70039;}");
          cliente.println(".button3 {background-color: #7D3C98;}");
          cliente.println("</style>");

cliente.println("</head>");
cliente.println("<body width=100% height=100%>");
 
cliente.println("<center>");
cliente.println("<div class='grupo'>"); 
cliente.println("<h2>GRUPO DINAMITA</h2>");
cliente.print("<br><hr> Integrantes:[-Abigail-Teresa-Zannie-Noe]<br><hr>"); 
cliente.print("ESTADO: "); 
cliente.print(state); 
cliente.print("<br>"); 
cliente.println("<input type=submit class = 'button button1' value=VAMOS onClick=location.href='./?LED=T\'>"); 
cliente.println("<input type=submit class = 'button button2' value=VENIMOS onClick=location.href='./?LED=F\'>"); 
cliente.println("<input type=submit class = 'button button3' value=CENTRO onClick=location.href='./?LED=C\'>");
cliente.println("</div>"); 
cliente.println("</center>"); 

cliente.println("</body>"); 
cliente.println("</html>"); 
cliente.stop();
//Cierro conexión con el cliente 
readString="";
}
}
}
}
}
