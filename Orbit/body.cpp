#include "body.h"

body::body(float _mass, point_2d _location, vector_2d _velocity, color _colour)
{
    mass = _mass;
    location = _location;
    velocity = _velocity;
    colour = _colour;
    radius = sqrt(mass/3.14);
}

point_2d body::getLocation()
{
    return location;
}

float body::getMass()
{
    return mass;
}

void body::update(vector<body *> objects)
{
    return;
}

void body::draw()
{
    location.x = location.x + velocity.x;
    location.y = location.y + velocity.y;
    fill_circle(colour, circle_at(location, radius));
}

staticObj::staticObj(float _mass, point_2d _location, vector_2d _velocity, color _colour) : body(_mass, _location, _velocity, _colour) {}

void staticObj::update(vector<body *> objects)
{
    return;
}

dynamic::dynamic(float _mass, point_2d _location, vector_2d _velocity, color _colour) : body(_mass, _location, _velocity, _colour) {}

void dynamic::update(vector<body*> objects)
{
    for (int i = 0; i < size(objects); i++)
    {
        if ((location.x == (*objects[i]).getLocation().x && location.y == (*objects[i]).getLocation().y))
        {
        }
        else 
        {
            velocity = vector_add(velocity, gravity((*objects[i])));
        }
    }
    return;
}

vector_2d dynamic::gravity(body obj)
{
    float angle = point_point_angle(location, obj.getLocation());

    //float cogX = ((location.x * mass) + (obj.getLocation().x * obj.getMass())) / (mass + obj.getMass());
    //float cogY = ((location.y * mass) + (obj.getLocation().y * obj.getMass())) / (mass + obj.getMass());

    //float dist = point_point_distance(location, point_at(cogX, cogY));

    //calculations based upon the inverse square law
    float dist = point_point_distance(location, obj.getLocation());
    float gravForce = GRAV_CONST * ((obj.getMass())/(dist * dist));

    return vector_from_angle(angle, gravForce/mass);
}