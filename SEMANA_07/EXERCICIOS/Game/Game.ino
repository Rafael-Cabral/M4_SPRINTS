#include <WiFi.h>
#define led1 15
#define led2 18
#define led3 46
#define led4 11
#define buzzer 2

const char *ssid = "Inteli-COLLEGE";
const char *password = "QazWsx@123";

WiFiServer server(80);

void relay_wifi();

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT);


  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(741);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  while (WiFi.status() != WL_CONNECTED)  //aguarda conexão (WL_CONNECTED é uma constante que indica sucesso na conexão)
  {
    WiFi.begin(ssid, password);  //inicializa WiFi, passando o nome da rede e a senha
    Serial.print(".");           //vai imprimindo pontos até realizar a conexão...

    delay(741);  //741ms
  }

  relay_wifi();  //chama função para controle dos relés por wifi



}  //end loop


// ============================================================================
// --- relay_wifi ---
void relay_wifi() {

  WiFiClient client = server.available();  //verifica se existe um cliente conectado com dados a serem transmitidos

  if (client)                                 //existe um cliente?
  {                                           //sim
    Serial.println("Novo Cliente Definido");  //informa por serial
    String currentLine = "";                  //string para armazenar a mensagem do cliente

    while (client.connected())  //repete enquanto o cliente estiver conectado
    {

      if (client.available())    //existem dados a serem lidos?
      {                          //sim
        char c = client.read();  //salva em c
        Serial.write(c);         //mostra na Serial

        if (c == '\n')                    //é um caractere de nova linha?
        {                                 //sim
          if (currentLine.length() == 0)  //a mensagem terminou?
          {                               //sim
            //gera a página HTML
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            
            client.println();
            client.println("<h1>Selecione um botao e o seu colega outro. Quem fizer o Buzzer tocar perde!</h1>");
            client.print("<h2> <a href=\"/H1\"><button>SORTE</button></a> </h2><br>");
            client.print("<h2> <a href=\"/H5\"><button>SORTE</button></a> </h2><br>");
            client.print("<h2> <a href=\"/H4\"><button>SORTE</button></a> </h2><br>");
            client.print("<h2> <a href=\"/H3\"><button>SORTE</button></a> </h2><br>");
            client.print("<h2> <a href=\"/H2\"><button>SORTE</button></a> </h2><br>");

            client.println();
            break;  //encerra o laço

          }

          else
            currentLine = "";

        }

        else if (c != '\r')
          currentLine += c;

        if (currentLine.endsWith("GET /H1")) digitalWrite(led1, HIGH);
        if (currentLine.endsWith("GET /H2")) digitalWrite(led2, HIGH);
        if (currentLine.endsWith("GET /H3")) digitalWrite(led3, HIGH);
        if (currentLine.endsWith("GET /H4")) digitalWrite(led4, HIGH);
        if (currentLine.endsWith("GET /H5")) tone(buzzer, 1500, 2000);
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}









/* ========================================================   
 
                                                              
======================================================== */
/* --- Final do Programa --- */
