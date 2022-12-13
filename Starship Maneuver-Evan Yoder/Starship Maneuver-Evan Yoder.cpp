// Starship Maneuver-Evan Yoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>
#include <SFML/Audio.hpp>



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

    RenderWindow window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(800, 600, desktop.bitsPerPixel), "Starship Manuever");

    Text scoreText;
    Font font;

    string background = "background/space_background.jpg";
    string background1 = "background/space_background.jpg";


    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(background1)) {
        cout << "Couldn't Load Image" << endl;
        exit(1);
    }
    Image backgroundImage;
    backgroundImage = backgroundTex.copyToImage();

    SoundBuffer Buffer;
    if (!Buffer.loadFromFile("sound/rock_music.wav")) {
        cout << "coul not load spaceship_crusing.mp3" << endl;
        exit(5);
    }
    Sound shipSound;
    shipSound.setBuffer(Buffer);

    Music music;
    if (!music.openFromFile("sound/rock_music.wav")) {
        cout << "Failed to load spaceship_crusing.mp3 ";
        exit(6);
    }
    music.play();

    Sprite sprite1;
    Texture tex1;
    tex1.loadFromImage(backgroundImage);
    sprite1.setTexture(tex1);

    World world(Vector2f(0, 0));
    int score(0);
    int bolts(15);
  

    PhysicsSprite& rocketShip = *new PhysicsSprite();
    Texture rocketTex;
    LoadTex(rocketTex, "images/rocket ship.png");
    rocketShip.setTexture(rocketTex);
    Vector2f sz = rocketShip.getSize();
    rocketShip.setCenter(Vector2f(400,
        600 - (sz.y / 2)));
    world.AddPhysicsBody(rocketShip);


    PhysicsSprite bolt;
    Texture boltTex;
    LoadTex(boltTex, "images/bolt.png");
    bolt.setTexture(boltTex);
    bool drawingbolt(false);

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





    top.onCollision = [&drawingbolt, &world, &bolt]
    (PhysicsBodyCollisionResult result) {
        drawingbolt = false;
        world.RemovePhysicsBody(bolt);
    };

    if (!font.loadFromFile("fonts/Star_Shield.ttf")) {
        cout << "Couldn't load font Star Shield.ttf" << endl;
        exit(1);
    }
    scoreText.setFont(font);
    Text boltCountText;
    boltCountText.setFont(font);

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    Time currentTime(lastTime);
    long deltaAsteroid = (0);


    while ((bolts > 0) || drawingbolt) {
        currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        long deltaMS = deltaTime.asMilliseconds();

        if (deltaAsteroid > 1500) {
            deltaAsteroid = 0;
            world.UpdatePhysics(deltaAsteroid);
            PhysicsSprite& asteroid = asteroids.Create();
            PhysicsSprite& asteroid2 = asteroids.Create();
            PhysicsSprite& asteroid3 = asteroids.Create();
            PhysicsSprite& asteroid4 = asteroids.Create();
            PhysicsSprite& asteroid5 = asteroids.Create();
            asteroid.setTexture(redTex);
            asteroid2.setTexture(redTex);
            asteroid3.setTexture(redTex);
            asteroid4.setTexture(redTex);
            asteroid5.setTexture(redTex);
            Vector2f sz = asteroid.getSize();
            asteroid.setCenter(Vector2f(250, 50 + (sz.x / 2)));
            asteroid2.setCenter(Vector2f(400, 100 + (sz.x / 2)));
            asteroid3.setCenter(Vector2f(550, 50 + (sz.x / 2)));
            asteroid4.setCenter(Vector2f(700, 100 + (sz.x / 2)));
            asteroid5.setCenter(Vector2f(100, 100 + (sz.x / 2)));
            asteroid.setVelocity(Vector2f(0, 0.20));
            asteroid2.setVelocity(Vector2f(0, 0.20));
            asteroid3.setVelocity(Vector2f(0, 0.20));
            asteroid4.setVelocity(Vector2f(0, 0.20));
            asteroid5.setVelocity(Vector2f(0, 0.20));

            world.AddPhysicsBody(asteroid);
            world.AddPhysicsBody(asteroid2);
            world.AddPhysicsBody(asteroid3);
            world.AddPhysicsBody(asteroid4);
            world.AddPhysicsBody(asteroid5);
            asteroid.onCollision = [&drawingbolt, &world, &rocketShip, &bolt, &bolts, &asteroid, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == bolt) {
                    drawingbolt = false;
                    world.RemovePhysicsBody(bolt);
                    world.RemovePhysicsBody(asteroid);
                    asteroids.QueueRemove(asteroid);
                    score += 10;
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid);
                    asteroids.QueueRemove(asteroid);
                }
            };
            asteroid.onCollision = [&drawingbolt, &world, &rocketShip, &bolt, &bolts, &asteroid, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == bolt) {
                    drawingbolt = false;
                    world.RemovePhysicsBody(bolt);
                    world.RemovePhysicsBody(asteroid);
                    asteroids.QueueRemove(asteroid);
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid);
                    asteroids.QueueRemove(asteroid);
                }
            };
            asteroid2.onCollision = [&drawingbolt, &world, &rocketShip, &bolt, &asteroid2, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == bolt) {
                    drawingbolt = false;
                    world.RemovePhysicsBody(bolt);
                    world.RemovePhysicsBody(asteroid2);
                    asteroids.QueueRemove(asteroid2);
                    score += 10;
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid2);
                    asteroids.QueueRemove(asteroid2);
                }
            };
            asteroid3.onCollision = [&drawingbolt, &world, &rocketShip, &bolt, &asteroid3, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == bolt) {
                    drawingbolt = false;
                    world.RemovePhysicsBody(bolt);
                    world.RemovePhysicsBody(asteroid3);
                    asteroids.QueueRemove(asteroid3);
                    score += 10;
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid3);
                    asteroids.QueueRemove(asteroid3);
                }
            };
            asteroid4.onCollision = [&drawingbolt, &world, &rocketShip, &bolt, &asteroid4, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == bolt) {
                    drawingbolt = false;
                    world.RemovePhysicsBody(bolt);
                    world.RemovePhysicsBody(asteroid4);
                    asteroids.QueueRemove(asteroid4);
                    score += 10;
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid4);
                    asteroids.QueueRemove(asteroid4);
                }

            };
            asteroid5.onCollision = [&drawingbolt, &world, &rocketShip, &bolt, &asteroid5, &asteroids, &score, &right]
            (PhysicsBodyCollisionResult result) {
                if (result.object2 == bolt) {
                    drawingbolt = false;
                    world.RemovePhysicsBody(bolt);
                    world.RemovePhysicsBody(asteroid5);
                    asteroids.QueueRemove(asteroid5);
                    score += 10;
                }
                if (result.object2 == right) {
                    world.RemovePhysicsBody(asteroid5);
                    asteroids.QueueRemove(asteroid5);
                }
            };
        }




        if (deltaMS > 9) {
            deltaAsteroid += deltaMS;
            lastTime = currentTime;
            world.UpdatePhysics(deltaMS);
            MoveRocketship(rocketShip, deltaMS);
            if (Keyboard::isKeyPressed(Keyboard::Space) &&
                !drawingbolt) {
                drawingbolt = true;
                bolt.setCenter(rocketShip.getCenter());
                bolt.setVelocity(Vector2f(0, -1));
                world.AddPhysicsBody(bolt);
                bolts -= 1;

                SoundBuffer Buffer;
                if (!Buffer.loadFromFile("sound/blaster.wav")) {
                    cout << "coul not load spaceship_crusing.mp3" << endl;
                    exit(5);
                }
                Sound shipSound;
                shipSound.setBuffer(Buffer);

                Music music;
                if (!music.openFromFile("sound/blaster.wav")) {
                    cout << "Failed to load spaceship_crusing.mp3 ";
                    exit(6);
                }
                music.play();
            }


            window.clear();
            window.draw(sprite1);
            if (drawingbolt) {
                window.draw(bolt);
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
            boltCountText.setString(to_string(bolts));
            textBounds = boltCountText.getGlobalBounds();
            boltCountText.setPosition(
                Vector2f(10, 590 - textBounds.height));
            window.draw(boltCountText);
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
