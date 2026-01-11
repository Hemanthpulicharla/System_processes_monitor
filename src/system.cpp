#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System() : cpu_(Processor()) { Read(); }


void System::Read() {
  std::vector<Process> processes;
  std::vector<int> pids = LinuxParser::Pids();
  for (int pid : pids) {
    Process process(pid);
    if (std::stoi(process.Ram()) > 0) {
      processes.push_back(process);
    }
  }
  std::sort(processes.begin(), processes.end());
  std::sort(pids.begin(), pids.end());
  processes_ = processes;
  pids_ = pids;
}


void System::Update() {
  std::vector<int> pids = LinuxParser::Pids();
  std::sort(pids.begin(), pids.end());
  if (pids != pids_) {
    Read();
  }
}


Processor& System::Cpu() { return cpu_; }


vector<Process>& System::Processes() {
  Update();
  return processes_;
}


std::string System::Kernel() { return LinuxParser::Kernel(); }


float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }


int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }


long int System::UpTime() { return LinuxParser::UpTime(); }