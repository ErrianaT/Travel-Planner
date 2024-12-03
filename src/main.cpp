#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "B-Tree.h"
#include <SFML/Graphics.hpp>
#include "TempMap.h"
#include "uiRenderer.h"
using namespace std;
using namespace sf;

void readFile(const string& filename, BTree& tree) {
   ifstream file(filename);
   if (!file.is_open()) {
       cerr << "Error: Could not open file " << filename << endl;
       return;
   }


   string line;
   // skipping the header line
   getline(file, line);


   while (getline(file, line)) {
       stringstream ss(line);

       // declaring variables for all columns
       string precipitationStr, dateFull, dateMonth, dateWeek, dateYear;
       string city, stationCode, stationLocation, state;
       string avgTemp, maxTemp, minTemp, windDirection, temp, windSpeedStr;


       // reading each value into corresponding variable
       getline(ss, precipitationStr, ',');  // Data.Precipitation
       getline(ss, dateFull, ',');          // Date.Full
       getline(ss, dateMonth, ',');         // Date.Month
       getline(ss, dateWeek, ',');          // Date.Week
       getline(ss, dateYear, ',');          // Date.Year
       getline(ss, city, ',');              // Station.City
       getline(ss, stationCode, ',');       // Station.Code
       getline(ss, stationLocation, ',');   // Station.Location
       getline(ss, temp, ',');              // placeholder
       getline(ss, state, ',');             // Station.State
       getline(ss, avgTemp, ',');           // Data.Temperature.Avg Temp
       getline(ss, maxTemp, ',');           // Data.Temperature.Max Temp
       getline(ss, minTemp, ',');           // Data.Temperature.Min Temp
       getline(ss, windDirection, ',');     // Data.Wind.Direction
       getline(ss, windSpeedStr, ',');      // Data.Wind.Speed


       // removing quotation marks
       city.erase(remove(city.begin(), city.end(), '"'), city.end());
       state.erase(remove(state.begin(), state.end(), '"'), state.end());
       precipitationStr.erase(remove(precipitationStr.begin(), precipitationStr.end(), '"'), precipitationStr.end());
       avgTemp.erase(remove(avgTemp.begin(), avgTemp.end(), '"'), avgTemp.end());
       windSpeedStr.erase(remove(windSpeedStr.begin(), windSpeedStr.end(), '"'), windSpeedStr.end());

       // converting precipitation and windspeed to floats
       float precipitation = (stof(precipitationStr));
       int avgtemp = (stoi(avgTemp));
       float windSpeed = (stof(windSpeedStr));

       // inserting into B tree
       tree.insert(city, state, precipitation, windSpeed, avgtemp);
   }


   file.close();
}

void readFileMap(const std::string& filename, TempsMap& tempMap) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    // skipping the header line
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);

        // declaring variables for all columns
        string precipitationStr, dateFull, dateMonth, dateWeek, dateYear;
        string city, stationCode, stationLocation, state;
        string avgTemp, maxTemp, minTemp, windDirection, temp, windSpeedStr;

        // reading each value into corresponding variable
        getline(ss, precipitationStr, ',');  // Data.Precipitation
        getline(ss, dateFull, ',');          // Date.Full
        getline(ss, dateMonth, ',');         // Date.Month
        getline(ss, dateWeek, ',');          // Date.Week of
        getline(ss, dateYear, ',');          // Date.Year
        getline(ss, city, ',');              // Station.City
        getline(ss, stationCode, ',');       // Station.Code
        getline(ss, stationLocation, ',');   // Station.Location
        getline(ss, state, ',');             // Station.State
        getline(ss, avgTemp, ',');           // Data.Temperature.Avg Temp
        getline(ss, maxTemp, ',');           // Data.Temperature.Max Temp
        getline(ss, minTemp, ',');           // Data.Temperature.Min Temp
        getline(ss, windDirection, ',');     // Data.Wind.Direction
        getline(ss, temp, ',');               // placeholder
        getline(ss, windSpeedStr, ',');      // Data.Wind.Speed

        // removing quotation marks
        city.erase(remove(city.begin(), city.end(), '"'), city.end());
        dateWeek.erase(remove(city.begin(), city.end(), '"'), city.end());
        dateMonth.erase(remove(city.begin(), city.end(), '"'), city.end());
        state.erase(remove(state.begin(), state.end(), '"'), state.end());
        precipitationStr.erase(remove(precipitationStr.begin(), precipitationStr.end(), '"'), precipitationStr.end());
        avgTemp.erase(remove(avgTemp.begin(), avgTemp.end(), '"'), avgTemp.end());
        windSpeedStr.erase(remove(windSpeedStr.begin(), windSpeedStr.end(), '"'), windSpeedStr.end());

        int day = stoi(dateWeek);
        int month = stoi(dateMonth);
        int averageTemp = stoi(avgTemp);


        tempMap.insert(city, vector<tuple<int, int, int>>{make_tuple(day, month, averageTemp)});


    }
    file.close();
}
void readFileMap(const string& filename, TempsMap& tempMap) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    // skipping the header line
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);

        // declaring variables for all columns
        string precipitationStr, dateFull, dateMonth, dateWeek, dateYear;
        string city, stationCode, stationLocation, state;
        string avgTemp, maxTemp, minTemp, windDirection, temp, windSpeedStr;

        // reading each value into corresponding variable
        getline(ss, precipitationStr, ',');  // Data.Precipitation
        getline(ss, dateFull, ',');          // Date.Full
        getline(ss, dateMonth, ',');         // Date.Month
        getline(ss, dateWeek, ',');          // Date.Week of
        getline(ss, dateYear, ',');          // Date.Year
        getline(ss, city, ',');              // Station.City
        getline(ss, stationCode, ',');       // Station.Code
        getline(ss, stationLocation, ',');   // Station.Location
        getline(ss, state, ',');             // Station.State
        getline(ss, avgTemp, ',');           // Data.Temperature.Avg Temp
        getline(ss, maxTemp, ',');           // Data.Temperature.Max Temp
        getline(ss, minTemp, ',');           // Data.Temperature.Min Temp
        getline(ss, windDirection, ',');     // Data.Wind.Direction
        getline(ss, temp, ',');               // placeholder
        getline(ss, windSpeedStr, ',');      // Data.Wind.Speed

        // removing quotation marks
        city.erase(remove(city.begin(), city.end(), '"'), city.end());
        state.erase(remove(state.begin(), state.end(), '"'), state.end());
        precipitationStr.erase(remove(precipitationStr.begin(), precipitationStr.end(), '"'), precipitationStr.end());
        windSpeedStr.erase(remove(windSpeedStr.begin(), windSpeedStr.end(), '"'), windSpeedStr.end());

        int day = stoi(dateWeek);
        int month = stoi(dateMonth);
        int averageTemp = stoi(avgTemp);

        tempMap.insert(city, tuple(day,month,averageTemp));

    }
    file.close();
}

int main() {
    sf::RenderWindow welcomewindow(sf::VideoMode(800, 700), "Travel Planner");

    // Load fonts
    sf::Font bold, bolditalic, regular;
    if (!bold.loadFromFile("../src/NotoSans-Bold.ttf") ||
        !bolditalic.loadFromFile("../src/NotoSans-BoldItalic.ttf") ||
        !regular.loadFromFile("../src/NotoSans-Regular.ttf")) {
        cerr << "Error loading font" << endl;
        return -1;
    }

    // Create welcome texts
    sf::Text welcometext = createText(bold, "Welcome to ", 48, sf::Color::White, 80, 100);
    sf::Text boldwelc = createText(bolditalic, "Travel Planner", 48, sf::Color::Black, 375, 100);
    sf::Text exclamation = createText(bolditalic, "!", 48, sf::Color::White, 710, 102);
    sf::Text whenvisit = createText(regular, "When are you planning your visit?", 28, sf::Color::White, 180, 170);
    sf::Text month = createText(regular, "Month: ", 23, sf::Color::White, 160, 230);
    sf::Text day = createText(regular, "Day: ", 23, sf::Color::White, 430, 230);
    sf::Text wherego = createText(regular, "Where would you like to go?", 28, sf::Color::White, 210, 300);
    sf::Text city = createText(regular, "Enter a City:", 23, sf::Color::White, 120, 360);

    // Creating textboxes
    textbox citybox(260, 355, 400, 35, regular, 20);
    textbox daybox(495, 228, 100, 30, regular, 20);

    // Creating buttons
    clickbutton startButton(300, 450, 200, 80, bold, "Start Planning", 20);
    clickbutton returnButton(450, 450, 200, 80, bold, "Return to Start", 20); // Add the "Return to Start" button

    // Dropdown for months
    dropdown months(250, 228, 150, 30, regular,
        {"January", "February", "March", "April", "May", "June", "July",
         "August", "September", "October", "November", "December"}, 18);

    bool navigateToNextPage = false;

    while (welcomewindow.isOpen()) {
    sf::Event event;
    while (welcomewindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            welcomewindow.close();
        }

        if (navigateToNextPage) {
            // Handle returnButton interaction
            if (returnButton.onEvent(event, welcomewindow)) {
                navigateToNextPage = false; // Return to the welcome page
                break; // Exit the event loop to redraw the welcome page
            }
        } else {
            // Handle interactions on the welcome page
            months.onEvent(event);
            daybox.onEvent(event);
            citybox.onEvent(event);

            if (startButton.onEvent(event, welcomewindow)) {
                navigateToNextPage = true;
            }
        }
    }

    // Rendering logic
    if (navigateToNextPage) {
        // Draw the second page
        welcomewindow.clear(sf::Color(50, 50, 50));

        // Background
        Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("../src/ResultsPage.png")) {
            std::cerr << "Error loading background image" << std::endl;
            return -1;
        }
        Sprite backgroundSprite(backgroundTexture);
        FloatRect textureRect = backgroundSprite.getLocalBounds();
        backgroundSprite.setScale(
            welcomewindow.getSize().x / textureRect.width,
            welcomewindow.getSize().y / textureRect.height
        );
        welcomewindow.draw(backgroundSprite);

        // Getting user input
        string chosenCity = citybox.getInput();

        // Initializing B Tree and attempting to read data file
        BTree btree(3);
        try {
            readFile("../data/weather.csv", btree);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        string resultData = btree.searchCity(chosenCity);

        // Draw results text
        Text resultsPageText = createText(bold, "Prepare for these conditions", 36, sf::Color::Black, 160, 80);
        Text data = createText(regular, resultData, 32, sf::Color::White, 280, 180);
        welcomewindow.draw(resultsPageText);
        welcomewindow.draw(data);

        // Draw return button
        returnButton.draw(welcomewindow);
        welcomewindow.display();
    } else {
        // Draw the welcome page
        welcomewindow.clear(sf::Color(130, 220, 155));
        welcomewindow.draw(welcometext);
        welcomewindow.draw(boldwelc);
        welcomewindow.draw(exclamation);
        welcomewindow.draw(whenvisit);
        welcomewindow.draw(month);
        welcomewindow.draw(day);
        welcomewindow.draw(wherego);
        welcomewindow.draw(city);

        // Draw textboxes
        citybox.draw(welcomewindow);
        daybox.draw(welcomewindow);

        // Draw buttons
        startButton.draw(welcomewindow);

        // Draw dropdown
        months.draw(welcomewindow);

        welcomewindow.display();
    }
}


    return 0;
}
