#include "Button.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::String& text, const sf::Font& font) {
    button.setSize(size);
    button.setPosition(position);
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setFillColor(sf::Color::White);

    // Centrowanie tekstu na przycisku
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2 - textBounds.top
    );

    normalColor = sf::Color::Blue;
    hoverColor = sf::Color::Red;
    button.setFillColor(normalColor);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonSprite); // Rysowanie sprite
    window.draw(buttonText);
}

void Button::update(const sf::Vector2i& mousePos) {
    if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        button.setFillColor(hoverColor); // Zmiana koloru na hover
    } else {
        button.setFillColor(normalColor); // Powrót do normalnego koloru
    }
}

bool Button::isClicked(const sf::Vector2i& mousePos, const sf::Event::MouseButtonEvent& mouseEvent) const {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) &&
           mouseEvent.button == sf::Mouse::Left;
}

std::string Button::getText() const {
    return buttonText.getString(); // Zwraca tekst przycisku jako std::string
}

void Button::setTexture(const std::string& textureFile) {
    if (buttonTexture.loadFromFile(textureFile)) {
        buttonSprite.setTexture(buttonTexture);
        buttonSprite.setPosition(button.getPosition());
        buttonSprite.setScale(
            button.getSize().x / buttonTexture.getSize().x,
            button.getSize().y / buttonTexture.getSize().y
        );
    }
};