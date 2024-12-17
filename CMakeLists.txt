cmake_minimum_required(VERSION 3.29)
project(FirstTry)

set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "D:\\Apps\\CLion\\CLion 2024.2.1\\bin\\SFML-2.6.2\\lib\\cmake\\SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

add_executable(FirstTry main.cpp
        chosePlayerWindow.cpp
        choosePlayerWindow.h
        fileModule.h
        fileModule.cpp
        newPlayerWindowUnit.h
        newPlayerWindowUnit.cpp
        DropBox.h
        DropBox.cpp
        gameWindowUnit.h
        gameWindowUnit.cpp
        RocketClass.h
        RocketClass.cpp
        CannonClass.h
        CannonClass.cpp
        AlienClass.h
        AlienClass.cpp
        TextureManagerClass.h
        gameOverWindowUnit.h
        gameOverWindowUnit.cpp
        scoreBoardWindowUnit.h
        scoreBoardWindowUnit.cpp
        pauseWindowUnit.h
        pauseWindowUnit.cpp)
target_link_libraries(FirstTry sfml-graphics sfml-window sfml-system)