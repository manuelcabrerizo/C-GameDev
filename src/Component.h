#ifndef COMPONNENT_H
#define COMPONNENT_H

class Entity;

class Component {
    public:
        const char* name;
        Entity* owner;
        virtual ~Component() {}
        virtual void Initialize() {}
        virtual void Update(float deltaTime) {}
        virtual void Render() {}

};

#endif