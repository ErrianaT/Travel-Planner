#include <iostream>
#include <SFML/Graphics.hpp>
#include "uiRenderer.h"
using namespace std;



int main() {
    //create window
    sf::RenderWindow welcomewindow(sf::VideoMode(800,700), "Travel Planner");

    //load fonts
    sf:: Font bold;
    sf:: Font bolditalic;
    sf:: Font regular;
    if(!bold.loadFromFile("/Users/angelacruz/CLionProjects/travel_planner/resources/NotoSans-Bold.ttf")
    || !bolditalic.loadFromFile("/Users/angelacruz/CLionProjects/travel_planner/resources/NotoSans-BoldItalic.ttf")
    || !regular.loadFromFile("/Users/angelacruz/CLionProjects/travel_planner/resources/NotoSans-Regular.ttf")){
        cerr<< "Error loading font" << endl;
        return -1;
    }

    // make all welcome texts
    sf::Text welcometext = createText(bold, "Welcome to ", 35, sf::Color::White, 176, 100);
    sf::Text boldwelc = createText(bolditalic, "Travel Planner", 35, sf::Color::Black, 392, 100);
    sf::Text exclamation = createText(bolditalic, "!", 35, sf::Color::White, 635, 100);
    sf::Text whenvisit = createText(regular, "When are you planning your visit?", 28, sf::Color::White, 99, 170 );
    sf::Text month = createText(regular, "Month: ", 23, sf::Color::White, 120, 230 );
    sf::Text Day = createText(regular, "Day: ", 23, sf::Color::White, 395, 230 );
    sf::Text wherego = createText(regular, "Where would you like to go?", 28, sf::Color::White, 99, 280 );
    sf::Text city = createText(regular, "Enter a City:", 23, sf::Color::White, 120, 340 );

    // output texts
    sf::Text packbags = createText(regular, "Prepare for these conditions! ", 28, sf::Color::White, 99, 480);
    sf::Text temp = createText(regular, "Average Temp: ", 23, sf::Color::White, 120, 530);
    sf::Text precipitation = createText(regular, "Precipitation: ", 23, sf::Color::White, 120, 565);
    sf::Text  windspeed = createText(regular, "Wind Speed: ", 23, sf::Color::White, 120, 595);

    //create dropdown
    dropdown months(200, 225, 150, 30, regular,
                    {"January", "February", "March", "April", "May", "June", "July",
                     "August", "September", "October", "November", "December"}, 18);
    //dropdown weeks(470, 225, 100, 30, regular,
                  //  {"1st", "2nd", "3rd", "4th", "5th"}, 18);

    // make textboxs
    textbox day(470, 225, 100, 30, regular, 20);
    textbox citybox(250, 335, 400, 35, regular, 20);

    // make button
    clickbutton enterbutton(300, 400, 200, 50, regular, "Search", 24);

    // make output values text
    sf::Text tempresult = createText(regular, " ", 23, sf::Color::White, 250, 530);
    sf::Text precresult = createText(regular, " ", 23, sf::Color::White, 250, 565);
    sf::Text wsresult = createText(regular, " ", 23, sf::Color::White, 250, 595);


    while(welcomewindow.isOpen()){
        sf::Event event;
        while(welcomewindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                welcomewindow.close();
            }
            enterbutton.onEvent(event, welcomewindow);
            months.onEvent(event);
            day.onEvent(event);
            citybox.onEvent(event);
        }
        if(enterbutton.isclicked()){
            // output results on button click
            tempresult.setString(" degrees");
            precresult.setString(" inches");
            wsresult.setString(" mph");
            //reset
            enterbutton.resetbutton();

        }

        //draw window and welcome texts
        welcomewindow.clear(sf::Color(130, 220, 155));
        welcomewindow.draw(welcometext); welcomewindow.draw(boldwelc);
        welcomewindow.draw(exclamation); welcomewindow.draw(whenvisit);
        welcomewindow.draw(month); welcomewindow.draw(Day);
        welcomewindow.draw(wherego); welcomewindow.draw(city);

        //draw result texts
        welcomewindow.draw(packbags);
        welcomewindow.draw(precipitation);
        welcomewindow.draw(windspeed);
        welcomewindow.draw(temp);

        //draw textbox
        citybox.draw(welcomewindow);
        day.draw(welcomewindow);

        //draw dropdown
        months.draw(welcomewindow);

        //drawbutton
        enterbutton.draw(welcomewindow);

        if(enterbutton.isclicked()){
            welcomewindow.draw(tempresult);
            welcomewindow.draw(precresult);
            welcomewindow.draw(wsresult);
        }

        welcomewindow.display();
    }

    return 0;
}
