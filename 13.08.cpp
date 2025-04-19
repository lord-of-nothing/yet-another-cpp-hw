#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

void RemoveOldFiles(const fs::path& directory_path,
                    const std::string& str_time_target) {
  if (!fs::is_directory(directory_path)) {
    throw std::invalid_argument("Path should lead to a directory");
  }

  std::chrono::local_time<std::chrono::seconds> local_time_target;
  std::istringstream iss(str_time_target);
  iss >> std::chrono::parse("%F %T", local_time_target);
  if (iss.fail()) {
    throw std::invalid_argument("Incorrect datetime target");
  }

  auto sys_time_target = std::chrono::current_zone()->to_sys(local_time_target);

  for (const auto& file : fs::recursive_directory_iterator(directory_path)) {
    if (std::chrono::file_clock::to_sys(file.last_write_time()) <
        sys_time_target) {
      bool is_deleted = fs::remove(file);
      if (!is_deleted) {
        std::cout << file.path() << " could not be deleted" << std::endl;
      }
    }
  }
}

int main() {
  std::filesystem::path directory_path = "test_folder";
  std::string time_target = "2025-04-19 14:35:00";

  RemoveOldFiles(fs::current_path() / directory_path, time_target);
}