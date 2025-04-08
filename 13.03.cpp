#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

enum class proc_status { R, S, T, Z };

struct process {
  size_t id;
  std::string name;
  proc_status status;
  std::string owner;
};

namespace proc {
std::vector<process> proc_list;
}

std::string status_to_string(proc_status status) {
  if (status == proc_status::R) {
    return "Running";
  }
  if (status == proc_status::S) {
    return "Sleeping";
  }
  if (status == proc_status::T) {
    return "Stopped";
  }
  return "Zombie";
}

void ListProc() {
  const std::vector<std::string> columns = {"PID", "Name", "Status", "Owner"};
  const std::vector<int> col_widths = {8, 25, 10, 15};
  const std::string div = " | ";

  for (size_t i = 0; i < columns.size(); ++i) {
    std::cout << std::left << std::setw(col_widths[i]) << columns[i];
    if (i != columns.size() - 1) {
      std::cout << div;
    } else {
      std::cout << std::endl;
    }
  }

  size_t width = 3 * (col_widths.size() - 1);
  for (const auto& elem : col_widths) {
    width += elem;
  }
  std::cout << std::string(width, '-') << std::endl;

  for (const auto& pr : proc::proc_list) {
    std::cout << std::setw(col_widths[0]) << pr.id << div
              << std::setw(col_widths[1]) << pr.name << div
              << std::setw(col_widths[2]) << status_to_string(pr.status) << div
              << std::setw(col_widths[3]) << pr.owner << std::endl;
  }
}

int main() {
  proc::proc_list.emplace_back(769, "systemd-journald", proc_status::S, "root");
  proc::proc_list.emplace_back(8588, "gnome-shell", proc_status::S, "user");
  proc::proc_list.emplace_back(82576, "htop", proc_status::R, "user");

  ListProc();
}