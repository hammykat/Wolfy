# Conventions

## Naming

    * camelCase for variables & parameters
    * PascalCase for functions, methods, namespaces, enum names, classes, structs
    * SNAKE_CASE for constexpr, #define, enum values

    Open curly brackets '{' on the same line. i.e:   

    ```cpp           
    if (x == true) {
        // code
    }
    ```
    
## Spdlog

* spdlog::info() for giving information about intended behaviour (i.e: "Level loaded succesfully in 3.8ms")
* spdlog::warning() for things that are not bugs, but may cause trouble (i.e: "Level loaded succesfuly in 15 minutes. (Too long)")
* spdlog::error() for recoverable bugs that do not crash the game (i.e: "Failed to load localization keys, defaulting to English")
* spdlog::critical() for bugs that crash the game (i.e "Failed to create a window. Closing the application")

## Other

* When adding a to-do comment, also add WOLFYTODO so it is easier to search for in the IDE (i.e: "//todo WOLFYTODO fix")
