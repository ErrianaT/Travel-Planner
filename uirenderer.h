#ifndef TRAVEL_PLANNER_UIRENDERER_H
#define TRAVEL_PLANNER_UIRENDERER_H
#endif //TRAVEL_PLANNER_UIRENDERER_H

#include <iostream>
using namespace std;



// text renderer function
sf::Text createText(const sf::Font&font, const std::string& str, unsigned int size, const sf::Color& color, float x, float y){
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    return text;
}

//text box renderer
class textbox{
    // make private objects
private:
    sf::RectangleShape box;
    sf::Text text;
    string input;
    bool typing;
public:
    textbox(float x, float y, float width, float height, sf::Font& font, unsigned int charSize){
        //make box
        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color(255, 255, 255));
        box.setOutlineThickness(2);
        box.setPosition(x, y);
        //make text specs
        text.setFont(font);
        text.setCharacterSize(charSize);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x+5, y+(height-charSize)/2);

        typing = false;
    }
    void draw(sf::RenderWindow& window){
        window.draw(box);
        window.draw(text);
    }
    // make function for box being used
    void onEvent(const sf::Event& event){
        if(event.type == sf::Event::MouseButtonPressed){
            //checks if clicked
            if(box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                typing = true;
                box.setOutlineColor(sf::Color::Blue);
            }
            else{
                typing = false;
                box.setOutlineColor(sf::Color::Black);
            }
        }
        // get text input if theyre typing
        if(typing && event.type ==sf::Event::TextEntered){
            //backspace
            if(event.text.unicode == '\b'){
                if(!input.empty()){
                    input.pop_back();
                }
            }
                // non letters/numbers ignored
            else if(event.text.unicode < 128 && event.text.unicode > 31){
                input += static_cast<char>(event.text.unicode);
            }
            text.setString(input);
        }
    }
    const string& getInput() const{return input;}
};

class dropdown{
private:
    sf::RectangleShape button;
    sf::Text buttonText;
    std::vector<sf::Text> list;
    sf::RectangleShape optionbox;
    bool listed;

public:
    dropdown(float x, float y, float width, float height, sf::Font & font,
             const vector<string>& options, unsigned int charSize){
        button.setSize(sf::Vector2f(width, height));
        button.setFillColor(sf::Color(255, 255, 255));
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color::Black);
        button.setPosition(x, y);
        buttonText.setFont(font);
        buttonText.setCharacterSize(charSize);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setString(options[0]);
        buttonText.setPosition(x+10, y+(height - charSize)/2);

        for(size_t i = 0; i< options.size(); ++i){
            sf::Text option;
            option.setFont(font);
            option.setCharacterSize(charSize);
            option.setString(options[i]);
            option.setPosition(x+10, y+height + (i*height));
            list.push_back(option);
        }
        optionbox.setSize(sf::Vector2f (width, height * options.size()));
        optionbox.setFillColor(sf::Color(200, 200, 200));
        optionbox.setPosition(x, y+height);
    }
    void draw(sf::RenderWindow& window){
        window.draw(button);
        window.draw(buttonText);

        if(listed){
            window.draw(optionbox);
            for(const auto& option : list){
                window.draw(option);
            }
        }
    }
    // handle dropdown being used
    void onEvent(const sf::Event& event){
        if(event.type == sf::Event::MouseButtonPressed){
            // if clicked
            if(button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                listed = !listed;
            }
            else if(listed){
                for(size_t i = 0; i<list.size(); ++i){
                    if(list[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                        buttonText.setString(list[i].getString());
                        listed = false;
                        break;
                    }
                }
            }
            else{
                listed = false;
            };
        }
    }
    const string picked() const{
        return buttonText.getString();
    }
};

//button renderer class
class clickbutton{
private:
    sf::RectangleShape button;
    sf::Text buttontext;
    bool clicked;

public:
    // constructor
    clickbutton(float x, float y, float width, float height, const sf::Font& font,
           const string& text, unsigned int charSize){
        button.setSize(sf::Vector2f(width, height));
        button.setFillColor(sf::Color::Blue);
        button.setPosition(x, y);
        buttontext.setFont(font);
        buttontext.setString(text);
        buttontext.setCharacterSize(charSize);
        buttontext.setFillColor(sf::Color::White);
        buttontext.setPosition(x +(width - buttontext.getGlobalBounds().width)/2,
                               y+(height - buttontext.getGlobalBounds().height)/2);
        clicked = false;
    }
    //draw actual button
    void draw(sf::RenderWindow& window){
        window.draw(button);
        window.draw(buttontext);
    }
    //handle if its clicked
    void onEvent(const sf::Event& event){
        if(event.type == sf::Event::MouseButtonPressed){
            if(button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){

            }
        }
    }

};
