#include "HttpServer.hpp"

const char* HttpServer::ssid = "Wyspa Szczura";
const char* HttpServer::password = "hejpiast";

HttpServer::HttpServer() :
    server( 80 )
{
}

void HttpServer::Initialize()
{
    //begin WiFi connection
    WiFi.begin( HttpServer::ssid, HttpServer::password );
    // Wait for connection
    while ( WiFi.status() != WL_CONNECTED )
    {
        delay( 500 );
        Serial.print( "." );
    }

    Serial.println( "" );
    Serial.print( "Connected to " );
    Serial.println( ssid );
    Serial.print( "IP address: " );
    Serial.println( WiFi.localIP() );

    SPIFFS.begin();
    File f = SPIFFS.open( "/index.html", "r" );
    if ( f )
    {
        Serial.println( "File open success" );
    }
    else
    {
        Serial.println( "File open failed" );
    }

    server.serveStatic( "/", SPIFFS, "/" );
}

void HttpServer::handleClient()
{
    server.handleClient();
}

HttpServer::~HttpServer()
{
}