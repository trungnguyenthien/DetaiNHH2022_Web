#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <String>

/// Refer: https://randomnerdtutorials.com/esp8266-nodemcu-client-server-wi-fi/
class Esp8266_HTTPS
{
public:
    void setup(String ssid, String password)
    {
        Serial.print("Connecting to: (WIFI) ");
        Serial.println(ssid);
        // Connect to the wifi
        WiFi.begin(ssid.c_str(), password.c_str());
        WiFi.mode(WIFI_STA);

        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            delay(200);
        }

        Serial.println("");
        Serial.printf_P(PSTR("\n%lu: Connected. My IP: %s\r\n"), millis(), WiFi.localIP().toString().c_str());
    }

    String get(bool isHttps, const char *host, const char *path)
    {
        if (WiFiMulti.run() != WL_CONNECTED)
        {
            Serial.println("WiFiMulti.run() != WL_CONNECTED");
            Serial.println("WiFi Disconnected");
            return "--";
        }

        WiFiClient client = makeClient(isHttps, host);
        HTTPClient http;
        String payload = "--";

        String endpoint = makeEndpoint(host, path);

        // Your IP address with path or Domain name with URL path
        if (http.begin(client, endpoint))
        {
            Serial.println("Start Request ....");
            Serial.println(endpoint);
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

    String makeEndpoint(const char *host, const char *path)
    {
        char *output = new char[9999];
        strcpy(output, host);
        strcat(output, path);
        return output;
    }

    WiFiClient makeClient(bool isSecure, const char *host)
    {
        if (isSecure)
        {
            WiFiClientSecure clientX;
            clientX.setInsecure();
            clientX.connect(host, 443);
            return clientX;
        }
        else
        {
            WiFiClient client;
            return client;
        }
    }
};