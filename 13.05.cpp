#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void Clear(const std::string& source_str) {
  fs::path source_path = fs::absolute(source_str);
  std::ifstream source(source_path.native());
  if (!source.is_open()) {
    throw std::runtime_error("Input file cannot be opened");
  }

  auto target_path = fs::temp_directory_path() / "tmp.txt";
  std::ofstream target(target_path.native());
  if (!target.is_open()) {
    throw std::runtime_error("Cannot create temporary file");
  }

  std::string cur;
  while (std::getline(source, cur)) {
    if (cur.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
      target << cur << '\n';
    }
  }

  source.close();
  target.close();

  fs::copy_file(target_path, source_path, fs::copy_options::overwrite_existing);
  fs::remove(target_path);
}

int main() { Clear("test.txt"); }