//
// Created by judelhuu on 7/7/25.
//

#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <utility>
#include <memory>


template<typename T>
class Vector2 {
public:
    Vector2(){}
    Vector2(T x, T y) {
        this->x = x;
        this->y = y;
    }
    T x, y;

    //  https://stackoverflow.com/questions/21916578/overloaded-and-comparison-with-nullptr
    bool operator==(const Vector2 &other) const {
        return (*this == other);
    }
    bool operator==(std::nullptr_t null) const {
        return (*this == nullptr);
    }
};


template<typename First, typename Second>
class Vector2D_util {
    Vector2D_util();
    Vector2D_util(First first, Second second)
    {
        container = std::make_shared<std::pair<First, Second>>(first, second);
        x = std::make_shared<First>(first);
        y = std::make_shared<Second>(second);
    }
    ~Vector2D_util()=default;


    std::shared_ptr<First> x;  std::shared_ptr<Second> y;
    std::shared_ptr<std::pair<First, Second>> container = nullptr;
};





#endif //VECTOR2D_H
