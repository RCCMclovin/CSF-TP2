/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char cert_DigiCert_Global_Root_CA [] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
MIIEyDCCA7CgAwIBAgIQDPW9BitWAvR6uFAsI8zwZjANBgkqhkiG9w0BAQsFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH
MjAeFw0yMTAzMzAwMDAwMDBaFw0zMTAzMjkyMzU5NTlaMFkxCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxMzAxBgNVBAMTKkRpZ2lDZXJ0IEdsb2Jh
bCBHMiBUTFMgUlNBIFNIQTI1NiAyMDIwIENBMTCCASIwDQYJKoZIhvcNAQEBBQAD
ggEPADCCAQoCggEBAMz3EGJPprtjb+2QUlbFbSd7ehJWivH0+dbn4Y+9lavyYEEV
cNsSAPonCrVXOFt9slGTcZUOakGUWzUb+nv6u8W+JDD+Vu/E832X4xT1FE3LpxDy
FuqrIvAxIhFhaZAmunjZlx/jfWardUSVc8is/+9dCopZQ+GssjoP80j812s3wWPc
3kbW20X+fSP9kOhRBx5Ro1/tSUZUfyyIxfQTnJcVPAPooTncaQwywa8WV0yUR0J8
osicfebUTVSvQpmowQTCd5zWSOTOEeAqgJnwQ3DPP3Zr0UxJqyRewg2C/Uaoq2yT
zGJSQnWS+Jr6Xl6ysGHlHx+5fwmY6D36g39HaaECAwEAAaOCAYIwggF+MBIGA1Ud
EwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFHSFgMBmx9833s+9KTeqAx2+7c0XMB8G
A1UdIwQYMBaAFE4iVCAYlebjbuYP+vq5Eu0GF485MA4GA1UdDwEB/wQEAwIBhjAd
BgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwdgYIKwYBBQUHAQEEajBoMCQG
CCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2VydC5jb20wQAYIKwYBBQUHMAKG
NGh0dHA6Ly9jYWNlcnRzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RH
Mi5jcnQwQgYDVR0fBDswOTA3oDWgM4YxaHR0cDovL2NybDMuZGlnaWNlcnQuY29t
L0RpZ2lDZXJ0R2xvYmFsUm9vdEcyLmNybDA9BgNVHSAENjA0MAsGCWCGSAGG/WwC
ATAHBgVngQwBATAIBgZngQwBAgEwCAYGZ4EMAQICMAgGBmeBDAECAzANBgkqhkiG
9w0BAQsFAAOCAQEAkPFwyyiXaZd8dP3A+iZ7U6utzWX9upwGnIrXWkOH7U1MVl+t
wcW1BSAuWdH/SvWgKtiwla3JLko716f2b4gp/DA/JIS7w7d7kwcsr4drdjPtAFVS
slme5LnQ89/nD/7d+MS5EHKBCQRfz5eeLjJ1js+aWNJXMX43AYGyZm0pGrFmCW3R
bpD0ufovARTFXFZkAdl9h6g4U5+LXUZtXMYnhIHUfoyMo5tS58aI7Dd8KvvwVVo4
chDYABPPTHPbqjc1qCmBaZx2vN4Ye5DUys/vZwP9BFohFrH/6j/f3IL16/RZkiMN
JCqVJUzKoZHm1Lesh3Sz8W2jmdv51b2EQJ8HmA==
-----END CERTIFICATE-----
)CERT";

WiFiMulti WiFiMulti;
//X509List cert(cert_DigiCert_Global_Root_CA);

void setup()
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  //WiFiMulti.addAP("wifi-zone-ufam");
  WiFiMulti.addAP("ICOMP_1A", "****");
  WiFiMulti.addAP("wifi-zone-ufam-1");

  Serial.println();
  Serial.println();
  Serial.print("Waiting for WiFi... ");

  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}


void loop()
{
  //added support para reconectar
  int connected = 1;
  while(WiFiMulti.run() != WL_CONNECTED) {
    if(connected){
      Serial.println("WiFi not connected!");
      connected &=0;
    }
    Serial.print(".");
    delay(500);
  }
  connected |= 1;

  Serial.println("Tentando requisicao a uma página de XMB");

  //faz o http request
  WiFiClientSecure *client = new WiFiClientSecure;
  if(client) client->setCACert(cert_DigiCert_Global_Root_CA);
  else Serial.println("Erro ao setar o certificado");

  HTTPClient http;
  unsigned long startTime = millis();

  /*
   * Mude aqui o arquivo a ser baixado, apenas github allowed
   */
  // https://raw.githubusercontent.com/diogosm/tp2_CsF_2024-1/master/output/file_5000.txt
  //http.begin("https://raw.githubusercontent.com/diogosm/tp2_CsF_2024-1/master/output/file_500.txt"); // Mude para um link de tamanho fixo
  //http.begin("https://raw.githubusercontent.com/diogosm/tp2_CsF_2024-1/master/output/file_5000.txt"); 
  http.begin(*client, "https://raw.githubusercontent.com/diogosm/tp2_CsF_2024-1/master/output/file_5000.txt"); 
  int httpCode = http.GET();

  if (httpCode > 0) {
    //String payload = http.getString();
    //Serial.println(http.getString());
    
    // calcula o quanto foi baixado
    int responseSizeInBytes = 0; //http.getString().length();
    Serial.print("Tamanho do response: ");
    Serial.print(http.getSize()); //nova forma de pegar o tamanho do payload: https://links2004.github.io/Arduino/dd/d8d/class_h_t_t_p_client.html#aa15267cd69b0b03da7f5ccbc3424c04a
    Serial.println(" bytes");
  } else {
    Serial.println("Error on HTTP request");
  }

  unsigned long endTime = millis();
  unsigned long timeTaken = endTime - startTime;
  Serial.print("Tempo total: ");
  Serial.print(timeTaken);
  Serial.println(" ms");

  http.end();
  delay(20000);
}

