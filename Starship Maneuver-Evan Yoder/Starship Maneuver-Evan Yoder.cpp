// Starship Maneuver-Evan Yoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>

using namespace std;
using namespace sf;
using namespace sfp;

const float KB_SPEED = 0.2;

void LoadTex(Texture& tex, string filename) {
    if (!tex.loadFromFile(filename)) {
        cout << "Could not load " << filename << endl;
    }
}

void MoveRocketship(PhysicsSprite& rocketship, int elapsedMS) {
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        Vector2f newPos(rocketship.getCenter());
        newPos.x = newPos.x + (KB_SPEED * elapsedMS);
        rocketship.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        Vector2f newPos(rocketship.getCenter());
        newPos.x = newPos.x - (KB_SPEED * elapsedMS);
        rocketship.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        Vector2f newPos(rocketship.getCenter());
        newPos.y = newPos.y - (KB_SPEED * elapsedMS * 2);
        rocketship.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        Vector2f newPos(rocketship.getCenter());
        newPos.y = newPos.y + (KB_SPEED * elapsedMS);
        rocketship.setCenter(newPos);
    }
}

int main() {
    string background = "background/space_background.jpg";
    string background1 = "background/space_background.jpg";


    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(background1)) {
        cout << "Couldn't Load Image" << endl;
        exit(1);
    }
    Image backgroundImage;
    backgroundImage = backgroundTex.copyToImage();

    RenderWindow window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(800, 600, desktop.bitsPerPixel), "Starship Manuever");

    Sprite sprite1;
    Texture tex1;
    tex1.loadFromImage(backgroundImage);
    sprite1.setTexture(tex1);

    World world(Vector2f(0, 0));
    int score(0);
    int arrows(10);

    PhysicsSprite& rocketShip = *new PhysicsSprite();
    Texture rocketTex;
    LoadTex(rocketTex, "images/rocket ship.png");
    rocketShip.setTexture(rocketTex);
    Vector2f sz = rocketShip.getSize();
    rocketShip.setCenter(Vector2f(400,
        600 - (sz.y / 2)));
    world.AddPhysicsBody(rocketShip);


    PhysicsSprite arrow;
    Texture arrowTex;
    LoadTex(arrowTex, "images/arrow.png");
    arrow.setTexture(arrowTex);
    bool drawingArrow(false);

    PhysicsRectangle top;
    top.setSize(Vector2f(800, 10));
    top.setCenter(Vector2f(400, 5));
    top.setStatic(true);
    world.AddPhysicsBody(top);

    PhysicsRectangle left;
    left.setSize(Vector2f(10, 600));
    left.setCenter(Vector2f(5, 300));
    left.setStatic(true);
    world.AddPhysicsBody(left);

    PhysicsRectangle right;
    right.setSize(Vector2f(10, 600));
    right.setCenter(Vector2f(795, 300));
    right.setStatic(true);
    world.AddPhysicsBody(right);

    Texture redTex;
    LoadTex(redTex, "images/asteroid.png");
    PhysicsShapeList<PhysicsSprite> asteroids;

    



    top.onCollision = [&drawingArrow, &world, &arrow]
    (PhysicsBodyCollisionResult result) {
        drawingArrow = false;
        world.RemovePhysicsBody(arrow);
    };

    Text scoreText;
    Font font;
    if (!font.loadFromFile("fonts/Star_Shield.ttf")) {
        cout << "Couldn't load font Star Shield.ttf" << endl;
        exit(1);
    }
    scoreText.setFont(font);
    Text arrowCountText;
    arrowCountText.setFont(font);

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    Time currentTime(lastTime);
    long deltaAsteroid = (0);
    long deltaStar = (0);

    while ((arrows > 0) || drawingArrow) {
        currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        long deltaMS = deltaTime.asMilliseconds();
       
        if (deltaAsteroid > 2000) {
            deltaAsteroid = 0;
            world.UpdatePhysics(deltaAsteroid);
            PhysicsSprite& asteroid = asteroids.Create();
            PhysicsSprite& asteroid2 = asteroids.Create();
            PhysicsSprite& asteroid3 = asteroids.Create();
            asteroid.setTexture(redTex);
            asteroid2.setTexture(redTex);
            asteroid3.setTexture(redTex);
            Vector2f sz = asteroid.getSize();
            asteroid.setCenter(Vector2f(200, 100 + (sz.x / 2)));
            asteroid2.setCenter(Vector2f(400, 200 + (sz.x / 2)));
            asteroid3.setCenter(Vector2f(600, 100 + (sz.x / 2)));
            asteroid.setVelocity(Vector2f(0, 0.20));
            asteroid2.setVelocity(Vector2f(0, 0.20));
            asteroid3.setVelocity(Vector2f(0, 0.20));
            world.AddPhysicsBody(asteroid);
            world.AddPhysicsBody(asteroid2);
            world.AddPhysicsBody(asteroid3);
            asteroid.onCollision = [&drawingArrow, &world, &rocketShip, &asteroid, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == rocketShip) {
                    drawingArrow = false;
                    //world.RemovePhysicsBody(arrow);
                    world.RemovePhysicsBody(asteroid);
                    asteroids.QueueRemove(asteroid);
                    score += 10;
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid);
                    asteroids.QueueRemove(asteroid);
                }
            };
            asteroid2.onCollision = [&drawingArrow, &world, &rocketShip, &asteroid2, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == rocketShip) {
                    drawingArrow = false;
                    //world.RemovePhysicsBody(arrow);
                    world.RemovePhysicsBody(asteroid2);
                    asteroids.QueueRemove(asteroid2);
                    score += 10;
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid2);
                    asteroids.QueueRemove(asteroid2);
                }
            };
            asteroid3.onCollision = [&drawingArrow, &world, &rocketShip, &asteroid3, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == rocketShip) {
                    drawingArrow = false;
                    //world.RemovePhysicsBody(arrow);
                    world.RemovePhysicsBody(asteroid3);
                    asteroids.QueueRemove(asteroid3);
                    score += 10;
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid3);
                    asteroids.QueueRemove(asteroid3);
                }
            };
        }
        



        if (deltaMS > 9) {
            deltaAsteroid += deltaMS;
            lastTime = currentTime;
            world.UpdatePhysics(deltaMS);
            MoveRocketship(rocketShip, deltaMS);
            if (Keyboard::isKeyPressed(Keyboard::Space) &&
                !drawingArrow) {
                drawingArrow = true;
                arrow.setCenter(rocketShip.getCenter());
                arrow.setVelocity(Vector2f(0, 0));
                world.AddPhysicsBody(arrow);
                arrows -= 1;
            }

            window.clear();
            window.draw(sprite1);
            if (drawingArrow) {
                window.draw(arrow);
            }
            for (PhysicsShape& asteroid : asteroids) {
                window.draw((PhysicsSprite&)asteroid);
            }
            window.draw(rocketShip);
            scoreText.setString(to_string(score));
            FloatRect textBounds = scoreText.getGlobalBounds();
            scoreText.setPosition(
                Vector2f(790 - textBounds.width, 590 - textBounds.height));
            window.draw(scoreText);
            arrowCountText.setString(to_string(arrows));
            textBounds = arrowCountText.getGlobalBounds();
            arrowCountText.setPosition(
                Vector2f(10, 590 - textBounds.height));
            window.draw(arrowCountText);
            //world.VisualizeAllBounds(window);

            window.display();
            asteroids.DoRemovals();
        }
    }

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    FloatRect textBounds = gameOverText.getGlobalBounds();
    gameOverText.setPosition(Vector2f(
        400 - (textBounds.width / 2),
        300 - (textBounds.height / 2)
    ));
    window.draw(gameOverText);
    window.display();
    bool LeaveVar(true);
    do {
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            LeaveVar = false;
        }
    } while (LeaveVar);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
