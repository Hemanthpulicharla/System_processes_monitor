  #include "ncurses_display.h"
   #include <ncurses.h>
#include <chrono>
    #include <string>
     #include <thread>
      #include <vector>
     
     #include "format.h"
     #include "process.h"
     #include "system.h"
    
     using std::string;
     using std::to_string;
    
     std::string NCursesDisplay::ProgressBar(float percent) {
       std::string result{"0%"};
       int size{50};
       float bars{percent * size};
    
       for (int i{0}; i < size; ++i) {
         result += i <= bars ? '|' : ' ';
       }
    
       string display{to_string(percent * 100).substr(0, 4)};
       if (percent < 0.1 || percent == 1.0)
         display = " " + to_string(percent * 100).substr(0, 3);
       return result + " " + display + "/100%";
     }
    
     void NCursesDisplay::DisplaySystem(System& system, WINDOW* window) {
       int row{0};
       mvwprintw(window, ++row, 2, "OS: %s", system.OperatingSystem().c_str());
      mvwprintw(window, ++row, 2, "Kernel: %s", system.Kernel().c_str());
       mvwprintw(window, ++row, 2, "CPU: ");
       wattron(window, COLOR_PAIR(1));
       mvwprintw(window, row, 10, "");
       wprintw(window, ProgressBar(system.Cpu().Utilization()).c_str());
       wattroff(window, COLOR_PAIR(1));
       mvwprintw(window, ++row, 2, "Memory: ");
       wattron(window, COLOR_PAIR(1));
       mvwprintw(window, row, 10, "");
       wprintw(window, ProgressBar(system.MemoryUtilization()).c_str());
       wattroff(window, COLOR_PAIR(1));
       mvwprintw(window, ++row, 2, "Total Processes: %d", system.TotalProcesses());
       mvwprintw(window, ++row, 2, "Running Processes: %d", system.RunningProcesses());
       mvwprintw(window, ++row, 2, "Up Time: %s", Format::ElapsedTime(system.UpTime()).c_str());
       wrefresh(window);
     }
    
     void NCursesDisplay::DisplayProcesses(std::vector<Process>& processes,
                                           WINDOW* window, int n) {
       int row{0};
       int const pid_column{2};
       int const user_column{9};
       int const cpu_column{18};
       int const ram_column{25};
       int const time_column{35};
       int const command_column{46};
      wattron(window, COLOR_PAIR(2));
       mvwprintw(window, ++row, pid_column, "PID");
       mvwprintw(window, row, user_column, "USER");
       mvwprintw(window, row, cpu_column, "CPU[%%]");
       mvwprintw(window, row, ram_column, "RAM[MB]");
       mvwprintw(window, row, time_column, "TIME+");
       mvwprintw(window, row, command_column, "COMMAND");
       wattroff(window, COLOR_PAIR(2));
       int max_processes = processes.size() < n ? processes.size() : n;
       for (int i = 0; i < max_processes; ++i) {
         mvwprintw(window, ++row, pid_column, "%s", Format::NormalizeString(to_string(processes[i].
       Pid()), 6).c_str());
         mvwprintw(window, row, user_column, "%s", Format::NormalizeString(processes[i].User(), 8).
       c_str());
         float cpu = processes[i].CpuUtilization() * 100;
         mvwprintw(window, row, cpu_column, "%s", Format::NormalizeString(to_string(cpu).substr(0,
       4), 6).c_str());
         mvwprintw(window, row, ram_column, "%s", Format::NormalizeString(processes[i].Ram(), 7).
       c_str());
         mvwprintw(window, row, time_column, "%s", Format::ElapsedTime(processes[i].UpTime()).c_str
       ());
         mvwprintw(window, row, command_column, "%s", Format::NormalizeString(processes[i].Command
       (), getmaxx(window) - 46).c_str());
       }
     }
    
     void NCursesDisplay::Display(System& system, int n) {
       initscr();      
       noecho();       
       cbreak();       
       start_color();  
    
       int x_max = getmaxx(stdscr);
       WINDOW* system_window = newwin(9, x_max - 1, 0, 0);
       WINDOW* process_window = newwin(3 + n, x_max - 1, getmaxy(system_window) + 1, 0);
    
      while (1) {
         init_pair(1, COLOR_BLUE, COLOR_BLACK);
         init_pair(2, COLOR_GREEN, COLOR_BLACK);
         box(system_window, 0, 0);
         box(process_window, 0, 0);
         werase(system_window); 
         werase(process_window);
        DisplaySystem(system, system_window);
        DisplayProcesses(system.Processes(), process_window, n);
        wrefresh(system_window);
        wrefresh(process_window);
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      endwin();
    }