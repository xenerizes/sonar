add_library(sonar
    Parser.cpp
    Json.cpp
    Token.cpp
    Scanner.cpp
    StateImpl.cpp
    Source.cpp
    )

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/include)
