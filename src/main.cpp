#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "B-Tree.h"
#include <algorithm>
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
        windSpeedStr.erase(remove(windSpeedStr.begin(), windSpeedStr.end(), '"'), windSpeedStr.end());

        // converting precipitation and windspeed to floats
        float precipitation = (stof(precipitationStr));
        float windSpeed = (stof(windSpeedStr));

        // inserting into B tree
        tree.insert(city, state, precipitation, windSpeed);
    }

    file.close();
}

int main() {
    int width = 800, height = 600;
    RenderWindow window(VideoMode(width, height), "Travel Planner");

    // Loading the background image as a texture
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../src/travelImage.png")) {  // Replace with the path to your image
        std::cerr << "Error loading background image" << std::endl;
        return -1;
    }

    Sprite backgroundSprite(backgroundTexture);
    FloatRect textureRect = backgroundSprite.getLocalBounds();
    backgroundSprite.setScale(
        window.getSize().x / textureRect.width, // scale based on window width
        window.getSize().y / textureRect.height // scale based on window height
    );

    // Loading font
    Font font, inputFont;
    if (!font.loadFromFile("../src/BRLNSB.TTF")) {
        std::cerr << "Error loading BRLNSB font." << std::endl;
        return -1;
    }

    if (!inputFont.loadFromFile("../src/BELL.TTF")) {
        std::cerr << "Error loading BELL.ttf" << std::endl;
        return -1;
    }

    // Creating labels for the text boxes
    Text titleLabel("Travel Planner", font, 48);
    titleLabel.setPosition(250, 100);
    Text cityLabel("Enter City:", font, 24);
    cityLabel.setFillColor(Color::White);
    cityLabel.setPosition(200, 220);

    Text dateLabel("Enter Date:", font, 24);
    dateLabel.setFillColor(Color::White);
    dateLabel.setPosition(200, 320);

    // Text boxes
    RectangleShape cityBox(Vector2f(300, 40));
    cityBox.setFillColor(Color::White);
    cityBox.setPosition(350, 220);

    RectangleShape dateBox(Vector2f(300, 40));
    dateBox.setFillColor(Color::White);
    dateBox.setPosition(350, 320);

    // Text to display user input
    Text cityInputText("", inputFont, 24);
    cityInputText.setFillColor(Color::Black);
    cityInputText.setPosition(360, 225);

    Text dateInputText("MM/DD", inputFont, 24);  // Set default text "Month/Year"
    Color grey = Color(192, 192, 192);
    dateInputText.setFillColor(grey);
    dateInputText.setPosition(360, 325);

    // Variables to track which box is active
    bool cityActive = false;
    bool dateActive = false;

    // Storing user input
    string cityInput;
    string dateInput = "MM/DD";  // Initializing with the default text

    // Blinking cursor
    bool showCursor = true;
    Clock cursorClock;
    float cursorBlinkInterval = 0.5f;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed) {
                // Check if city box is clicked
                if (cityBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    cityActive = true;
                    dateActive = false;
                }
                // Check if date box is clicked
                else if (dateBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    dateActive = true;
                    cityActive = false;
                    if (dateInput == "MM/DD") {
                        dateInput = "";  // Clear default text when user clicks into the date box
                    }
                } else {
                    cityActive = false;
                    dateActive = false;
                }
            }

            if (event.type == Event::TextEntered) {
                if (cityActive) {
                    if (event.text.unicode == '\b' && !cityInput.empty()) { // Handle backspace
                        cityInput.pop_back();
                    } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                        cityInput += static_cast<char>(event.text.unicode);
                    }
                } else if (dateActive) {
                    if (event.text.unicode == '\b' && !dateInput.empty()) { // Handle backspace
                        dateInput.pop_back();
                    } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                        dateInput += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }

    // Updating text
    cityInputText.setString(cityInput);
    dateInputText.setString(dateInput);  // Update the date input text

        // Cursor blinking
        if (cursorClock.getElapsedTime().asSeconds() >= cursorBlinkInterval) {
            showCursor = !showCursor;
            cursorClock.restart();
        }

        // Clear the window
        window.clear();
        // Draw Background
        window.draw(backgroundSprite);

        // Draw the UI elements
        window.draw(titleLabel);
        window.draw(cityLabel);
        window.draw(dateLabel);
        window.draw(cityBox);
        window.draw(dateBox);
        window.draw(cityInputText);
        window.draw(dateInputText);

        // Draw the flashing cursor if active
        if (cityActive && showCursor) {
            RectangleShape cursor(Vector2f(2, 30));  // Cursor width and height
            cursor.setFillColor(Color::Black);
            cursor.setPosition(cityInputText.getPosition().x + cityInputText.getGlobalBounds().width, cityInputText.getPosition().y);
            window.draw(cursor);
        }
        if (dateActive && showCursor) {
            RectangleShape cursor(Vector2f(2, 30));  // Cursor width and height
            cursor.setFillColor(Color::Black);
            cursor.setPosition(dateInputText.getPosition().x + dateInputText.getGlobalBounds().width, dateInputText.getPosition().y);
            window.draw(cursor);
        }

        // Display everything
        window.display();
    }
    return 0;
}
