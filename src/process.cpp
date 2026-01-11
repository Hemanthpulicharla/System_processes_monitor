#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {
  user_ = LinuxParser::User(pid_);
  command_ = LinuxParser::Command(pid_);
  ram_ = LinuxParser::Ram(pid_);
  uptime_ = LinuxParser::UpTime(pid_);
  cpuUsage_ = compute_cpu();
}

float Process::compute_cpu() {
  std::vector<float> cputime = LinuxParser::CpuUtilization(pid_);
  if (cputime.size() == 5) {
    float utime = cputime[0], stime = cputime[1], cutime = cputime[2],
          cstime = cputime[3], starttime = cputime[4];
    float uptime = LinuxParser::UpTime();
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - starttime / sysconf(_SC_CLK_TCK);

    return (total_time / sysconf(_SC_CLK_TCK)) / seconds;
  }
  return 0;
}
int Process::Pid() { return pid_; }


float Process::CpuUtilization() { return cpuUsage_; }


string Process::Command() { return command_; }

string Process::Ram() { return ram_; }

string Process::User() { return user_; }

long int Process::UpTime() { return uptime_; }


bool Process::operator<(Process& a) {

  return CpuUtilization() > a.CpuUtilization();
}