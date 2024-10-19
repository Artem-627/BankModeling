#include <SFML/Graphics.hpp>
#include <iostream>

#include <crow.h>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return 5;
    });


    app.port(6277).multithreaded().run();

    return 0;
}
