#include <iostream>
#include <filesystem>
#include <map>
#include <algorithm>
#include <set>

// often used values
#define ver "0.0.2\n"
//colors
#define red "\e[0;31m"
#define green "\e[0;32m"
#define yellow "\e[0;33m"
#define blue "\e[0;34m"
// color reset
#define reset "\e[0m"

namespace fs = std::filesystem;

// This function sorts the files in folders. It uses the file extension like main.cpp to sort them.
//                                                                                ~~~
int sort(std::map<std::string, std::string> file_extension_category, std::string path_to_sort) {
    try {
        for (const auto& current_dir : fs::directory_iterator(path_to_sort)) {
            if (current_dir.is_regular_file()) {
                std::string file_extension = current_dir.path().extension().string();

                std::transform(file_extension.begin(), file_extension.end(), file_extension.begin(), ::tolower);

                if (file_extension_category.count(file_extension)) {
                    std::string target_folder = path_to_sort + "/" + file_extension_category[file_extension];
                    fs::create_directories(target_folder);

                    fs::path target_path = target_folder + "/" + current_dir.path().filename().string();
                    fs::rename(current_dir.path(), target_path);

                    std::cout << blue << "[INFO] " << reset << "Move: " << current_dir.path().filename() << blue
                        << " -> " << reset << target_folder << "\n";
                }
            }
        }
    } catch (std::exception& e) {
        std::cerr << red << "Error: " << e.what() << reset << "\n";
        return 1;
    }

    return 0;
}

int main(int argc, char** argv) {
    // little welcome text.
    std::cout << blue << "Data Sort Mini Tool " << reset << ver;

    // Error if no arguments delivered.
    if (argc < 2) {
        std::cerr << "Error: please provide a path";
        return 1;
    }
    // take first argument.
    std::string arg1 = argv[1];
    // parse arg1.
    if (arg1 == "-v") {
        std::cout << "version: " << ver;
    } else if (arg1 == "-h") {
        std::cout << "data-sort-mini tool version: " << ver << "Usage: data-sort-mini <DIR> --exclude* .cpp .pdf\n\n";
        
        std::cout << "commands:\n";
        std::cout << "-v: display version\n";
        std::cout << "-h: display help text\n\n";

        std::cout << "* = optional\n";
    } else {
        std::string arg2 = argv[2];
        // this variabel is needed for the sort() function.
        std::map<std::string, std::string> file_extension_category = {
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
            {".exe", "Software-Windows"},
            {" ", "Software-Linux"},
            {".log", "Logs"},
            {".cat", "Catalogs"},
            {".dll", "Software Extensions"},
        };
        // When the user is using the --exclude argument.
        std::set<std::string> exclude;
        // detect if the user uses the exclude argument and handle it.
        if (arg2 == "--exclude") {
            for (int i = 3; i < argc; i++) {
                exclude.insert(argv[i]);
            }

            for (const auto& key : exclude) {
                file_extension_category.erase(key);
            }
        }
        // catch the exit code.
        int result_of_sort = sort(file_extension_category, arg1);
        // parse the exit code.
        if (result_of_sort == 0) {
            std::cout << green << "Sucess!\n" << reset;
            return 0;
        } else {
            return result_of_sort;
        }
    }
}