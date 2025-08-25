#include <iostream>
#include <filesystem>
#include <map>
#include <algorithm>

#define ver "0.0.1\n"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    std::cout << "Data Sort Mini Tool " << ver;

    if (argc < 2) {
        std::cerr << "Error: please provide a path";
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "-v") {
        std::cout << "version: " << ver;
    } else if (arg == "-h") {
        std::cout << "data-sort-mini tool version: " << ver << "Usage: data-sort-mini <DIR>\n\n";
        std::cout << "commands:\n";
        std::cout << "-v: display version\n";
        std::cout << "-h: display help text\n";
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
            {".cpp", "Programming/C++"},
            {".c", "Programming/C"},
            {".rs", "Programming/Rust"},
            {".py", "Programming/Python"},
            {".html", "Programming/Web/html"},
            {".js", "Programming/Web/Javascript"},
            {".ts", "Programming/Web/Typescript"},
            {".json", "Programming/Web/json"},
            {".css", "Programming/Web/css"},
            {".mp4", "Videos"},
            {".bat", "Shellscripts/cmd"},
            {".sh", "Shellscripts/sh"},
            {".ps1", "Shellscripts/powershell"},
        };

        try {
            for (const auto& entry : fs::directory_iterator(path)) {
                if (entry.is_regular_file()){
                    std::string end = entry.path().extension().string();

                    std::transform(end.begin(), end.end(), end.begin(), ::tolower);

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
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }

    return 0;
}