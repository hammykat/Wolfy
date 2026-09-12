//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_PROJECTMANAGER_HPP
#define WOLFY_PROJECTMANAGER_HPP

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace ProjectManager {

    // Returns the current user's home folder.
    // On Windows this usually comes from the USERPROFILE environment variable.
    // Example:
    // C:\Users\berke
    fs::path GetUserHomeDirectory();

    // Returns Wolfy Engine's user data folder inside Documents\WolfyEngine.
    // This is the parent folder of the Projects folder.
    // Use this for launcher-wide files such as Launcher.wolfy.
    // Example:
    // C:\Users\x\Documents\Wolfy Engine
    fs::path GetEngineFolder();

    void CreateEngineFolder();

    // Returns the file the code is being executed. Such as  C:\Users\x\Cpp Projects\Wolfy\cmake-build-debug
    std::filesystem::path GetContentRootPath();
}

#endif //WOLFY_PROJECTMANAGER_HPP