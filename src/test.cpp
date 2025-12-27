#include <iostream>

int main()
{
    for (int i{}; i < 10; i++)
    {
        std::cout << i << '\n';
    }
    return 0;
}

class Animal
{
    public:
        Animal(int legs, int arms);
        ~Animal() = default;

    private:
        int legs;
        int arms;
};