#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    float center_offset_x = window.getSize().x / 2;
    float center_offset_y = window.getSize().y / 2;

    // declaring shapes
    sf::RectangleShape rectangle(sf::Vector2f(500, 350));
    float rectangle_center_x = rectangle.getSize().x /2;
    float rectangle_center_y = rectangle.getSize().y /2;
    rectangle.setFillColor(sf::Color::Cyan);
    rectangle.setOutlineThickness(10.f);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));

    rectangle.setOrigin(rectangle_center_x, rectangle_center_y);
    rectangle.setPosition(center_offset_x, center_offset_y);
    sf::FloatRect boundries = rectangle.getLocalBounds();

    float boundries_offset_x = center_offset_x - rectangle_center_x;
    float boundries_offset_y = center_offset_y - rectangle_center_y;
    
    sf::CircleShape ball(20);
    ball.setOrigin(10, 10);
    ball.setPosition(center_offset_x, center_offset_y);
    ball.setFillColor(sf::Color::Magenta);
    float ball_x_adv = 1;
    float ball_y_adv = 1;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // move ball
        sf::Vector2f ball_pos = ball.getPosition();
        if(boundries.width + boundries_offset_x <= ball_pos.x or ball_pos.x <= boundries.left + boundries_offset_x)
        {
            ball_x_adv *= -1;
        }
        if(boundries.height + boundries_offset_y <= ball_pos.y or ball_pos.y <= boundries.top + boundries_offset_y)
        {
            ball_y_adv *= -1;
        }
        ball.move(ball_x_adv, ball_y_adv);

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(rectangle);
        window.draw(ball);

        // end the current frame
        window.display();
    }

    return 0;
}
