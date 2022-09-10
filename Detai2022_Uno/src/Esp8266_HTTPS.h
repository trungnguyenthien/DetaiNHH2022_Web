#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

/// Refer: https://randomnerdtutorials.com/esp8266-nodemcu-client-server-wi-fi/
class Esp8266_HTTPS
{
public:
    void setup(char *ssid, char *password)
    {
        Serial.print("Connecting to ");

        WiFi.begin(ssid, password);
        // Connect to the wifi
        WiFi.mode(WIFI_STA);
        // WiFiMulti.addAP(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            delay(500);
        }

        Serial.println("");
        Serial.printf_P(PSTR("\n%lu: Connected. My IP: %s\r\n"), millis(), WiFi.localIP().toString().c_str());
    }

    String httpGet(const char *host, const char *path)
    {
        if (WiFiMulti.run() != WL_CONNECTED)
        {
            Serial.println("WiFiMulti.run() != WL_CONNECTED");
            Serial.println("WiFi Disconnected");
            return "--";
        }

        WiFiClient client;
        // WiFiClient client;
        HTTPClient http;
        String payload = "--";

        char serverName[512];
        strcpy(serverName, host);
        strcat(serverName, path);

        // Your IP address with path or Domain name with URL path
        if (http.begin(client, serverName))
        {
            Serial.println("Start Request ....");
            Serial.println(serverName);
            int httpResponseCode = http.GET();

            if (httpResponseCode > 0)
            {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);
                payload = http.getString();
            }
            else
            {
                Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
                payload = "--";
            }

            Serial.print("HTTP Response payload: ");
            Serial.println(payload);
            // Free resources
            http.end();
        }

        return payload;
    }

    String httpsGet(const char *host, const char *path)
    {
        if (WiFiMulti.run() != WL_CONNECTED)
        {
            Serial.println("WiFiMulti.run() != WL_CONNECTED");
            Serial.println("WiFi Disconnected");
            return "--";
        }

        WiFiClientSecure client;
        client.setInsecure(); // the magic line, use with caution
        client.connect(host, 443);

        // WiFiClient client;
        HTTPClient http;
        String payload = "--";

        char serverName[512];
        strcpy(serverName, host);
        strcat(serverName, path);

        // Your IP address with path or Domain name with URL path
        if (http.begin(client, serverName))
        {
            Serial.println("Start Request ....");
            Serial.println(serverName);
            int httpResponseCode = http.GET();

            if (httpResponseCode > 0)
            {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);
                payload = http.getString();
            }
            else
            {
                Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
                payload = "--";
            }

            Serial.print("HTTP Response payload: ");
            Serial.println(payload);
            // Free resources
            http.end();
        }

        return payload;
    }

private:
    ESP8266WiFiMulti WiFiMulti;
};