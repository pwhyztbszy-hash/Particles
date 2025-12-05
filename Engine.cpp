#include "Engine.h"

Engine::Engine()
{
    VideoMode vm = VideoMode::getDesktopMode();
    m_Window.create(vm, "Particles", Style::Default);

    // limit FPS to 60
    m_Window.setFramerateLimit(60);
}

void Engine::run()
{
    Clock clock;

    cout << "Starting Particle unit tests..." << endl;

    Particle p(m_Window, 4,{ (int)m_Window.getSize().x / 2,(int)m_Window.getSize().y / 2 });

    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen())
    {
        // Restart the clock
        sf::Time elapsed = clock.restart();

        // Convert time to secondods
        float dtAsSeconds = elapsed.asSeconds();
        
        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        // Close window
        if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
        {
            m_Window.close();
        }

        // checks for left click
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            Vector2i mousePos = Mouse::getPosition(m_Window);

            for (int i = 0; i < 5; i++)
            {
                int numPts = rand() % 26 + 25; // 25-50 vertices
                // creat and store new particles 
                Particle newParticle(m_Window, numPts, mousePos);
                m_particles.push_back(newParticle);
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    for (size_t i = 0; i < m_particles.size(); )
    {
        if (m_particles[i].getTTL() > 0.0)
        {
            m_particles[i].update(dtAsSeconds);
            ++i;
        }
        else
        {
            m_particles.erase(m_particles.begin() + i);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    for (size_t i = 0; i < m_particles.size(); i++)
    {
        m_Window.draw(m_particles[i]);
    }

    m_Window.display();
}
