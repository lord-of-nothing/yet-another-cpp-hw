#include <chrono>
#include <filesystem>
#include <format>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

//////////////////////////////////////////////////////////////////////////////////////

auto type(const std::filesystem::file_status& status) {
  if (std::filesystem::is_block_file(status)) {
    return 'b';
  }

  if (std::filesystem::is_character_file(status)) {
    return 'c';
  }

  if (std::filesystem::is_directory(status)) {
    return 'd';
  }

  if (std::filesystem::is_fifo(status)) {
    return 'p';
  }

  if (std::filesystem::is_other(status)) {
    return 'o';
  }

  if (std::filesystem::is_regular_file(status)) {
    return 'f';
  }

  if (std::filesystem::is_socket(status)) {
    return 's';
  }

  if (std::filesystem::is_symlink(status)) {
    return 'l';
  }

  //  ---------------------------------------------------------------

  return '?';
}

//////////////////////////////////////////////////////////////////////////////////////

auto permissions(std::filesystem::perms permissions) -> std::string {
  auto lambda = [permissions](auto x, auto y) {
    return (permissions & x) == std::filesystem::perms::none ? '-' : y;
  };

  return {lambda(std::filesystem::perms::owner_read, 'r'),

          lambda(std::filesystem::perms::owner_write, 'w'),

          lambda(std::filesystem::perms::owner_exec, 'x')};
}

//////////////////////////////////////////////////////////////////////////////////////

auto size(const std::filesystem::path& path) {
  auto size = 0uz;

  if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
    for (const auto& entry :
         std::filesystem::recursive_directory_iterator(path)) {
      if (!std::filesystem::is_directory(entry.status())) {
        size += std::filesystem::file_size(entry);
      }
    }
  }

  return size;
}

//////////////////////////////////////////////////////////////////////////////////////

auto size(const std::filesystem::directory_entry& entry) {
  auto size = 0uz;

  if (std::filesystem::is_regular_file(entry.status())) {
    size = std::filesystem::file_size(entry);
  } else {
    size = ::size(entry.path());
  }

  char array[4]{'B', 'K', 'M', 'G'};

  auto index = 0uz;

  while (index < 3 && size >= 1'024) {
    size /= 1'024;

    ++index;
  }

  return (std::stringstream() << std::format("{: >4}", size) << array[index])
      .str();
}

//////////////////////////////////////////////////////////////////////////////////////

void view(const std::filesystem::path& path, const std::regex& reg) {
  if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
      std::string filename = entry.path().filename().string();
      if (!std::regex_match(filename, reg)) {
        continue;
      }

      std::cout << "view : " << type(entry.status()) << " | ";

      std::cout << permissions(entry.status().permissions()) << " | ";

      std::cout << size(entry) << " | ";

      auto time = std::chrono::file_clock::to_sys(entry.last_write_time());

      std::cout << std::chrono::floor<std::chrono::seconds>(time) << " | ";

      std::cout << filename << '\n';
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////

int main() {
  std::regex reg("^c.*");  // файлы, имена которых начинаются на c
  view(std::filesystem::current_path(), reg);
}