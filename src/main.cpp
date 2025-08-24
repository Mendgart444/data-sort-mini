#include <iostream>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: please provide a path";
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "-v") {
        std::cout << "version 0.0.0\n";
    } else {
        std::string path = arg;
        std::map<std::string, std::string> category = {
            {".jpg", "Pictures"},
            {".png", "Pictures"},
            {".pdf", "Documents"},
            {".txt", "Texts"},
            {".mp3", "Music"},
            {".gif", "GIFs"},
            {".docx", "Word"},
            {".pptx", "Powerpoint"},
            {".xlsx", "Outlook"},
            {".one", "Onenote"},
        };

        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()){
                std::string end = entry.path().extension().string();

                if (category.count(end)) {
                    std::string targetFolder = path + "/" + category[end];
                    fs::create_directories(targetFolder);
                    
                    fs::path zielPfad = targetFolder+ "/" + entry.path().filename().string();
                    fs::rename(entry.path(), zielPfad);

                    std::cout << "[INFO] Move: " << entry.path().filename() 
                              << " → " << targetFolder << std::endl;
                }
            }
        }
    }

    return 0;
}