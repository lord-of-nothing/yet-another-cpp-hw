#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void CAPITALIZE_FOLDER(const fs::path& directory_path) {
  if (!fs::is_directory(directory_path)) {
    throw "Path should lead to a directory";
  }

  for (const auto& file : fs::directory_iterator(directory_path)) {
    std::string new_filename = file.path().filename().string();
    std::transform(new_filename.begin(), new_filename.end(),
                   new_filename.begin(), ::toupper);

    fs::path new_path = file.path();
    new_path.replace_filename(new_filename);

    if (file.path() != new_path) {
      try {
        fs::rename(file.path(), new_path);
      } catch (const std::exception& e) {
        std::cout << "Error renaming file: " << e.what() << std::endl;
      }
    }
  }
}

int main() {
  fs::path directory_path = "../test_folder";

  CAPITALIZE_FOLDER(fs::current_path() / directory_path);
}