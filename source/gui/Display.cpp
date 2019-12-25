#include <iostream>

#include "gui/Display.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"

#include <iostream>
#include <termios.h>
#include <unistd.h>

std::string Display::getCommandFromUser() {
  std::string str;
  std::cout << std::endl << "Enter your command: ";
  str = getText();
  return str;
}
void Display::printText(std::string body) {
  std::cout << body;
}

void Display::printError(std::string body) {
  std::cout << "Error: " << body << std::endl;
}

void Display::printTask(std::shared_ptr<Task> task) {
  std::cout << "Task \"" << task->getName() << "\" ID=" << task->getId() << std::endl
            << "Description: " << task->getDescription() << std::endl
            << "Creator id: " << task->getCreatorId() << std::endl
            << "Project id: " << task->getProjectId() << std::endl;
}

void Display::printUser(std::shared_ptr<User> user) {
  std::cout << "User \"" << user->getName() << "\" ID=" << user->getId() << std::endl
            << "Email: " << user->getEmail() << std::endl;
}

void Display::printProject(std::shared_ptr<Project> project) {
  std::cout << "Project \"" << project->getName() << "\" ID=" << project->getId() << std::endl
            << "Description: " << project->getDescription() << std::endl;
}

std::string Display::getText() {
  std::string str;
  do {
    getline(std::cin, str);
  } while (StrFunc::isEmpty(str));
  return str;
}

long Display::getLong() {
  long num;
  while (true) {
    try {
      num = std::stol(getText());
      break;
    }
    catch (const std::exception &ex) {
      std::cout << "You must enter an integer: ";
    }
  }
  return num;
}

void Display::getInformationTaskSave(std::shared_ptr<Task> task) {
  printText("Project ID to which task will belong: ");
  task->setProjectId(getLong());
  printText("Name of a task: ");
  task->setName(getText());
  printText("Description: ");
  task->setDescription(getText());
}

void Display::getInformationTaskUpdate(std::shared_ptr<Task> task) {
  printText("New name of a task: ");
  task->setName(getText());
  printText("New description: ");
  task->setDescription(getText());
}

void Display::getInformationUserSave(std::shared_ptr<User> user) {
  printText("User name: ");
  user->setName(getText());
  printText("Email: ");
  user->setEmail(getText());
  printText("Password: ");
  user->setPassword(getText());
  user->setStatus("user");
}

void Display::getInformationUserUpdate(std::shared_ptr<User> user) {
  printText("New password: ");
  user->setPassword(getText());
  printText("New email: ");
  user->setEmail(getText());
}

void Display::getInformationProjectSave(std::shared_ptr<Project> project) {
  printText("Name: ");
  project->setName(getText());
  printText("Description: ");
  project->setDescription(getText());
}

void Display::getInformationProjectUpdate(std::shared_ptr<Project> project) {
  printText("New description: ");
  project->setDescription(getText());
}

void Display::getPasswordAndNameForNewUser(std::shared_ptr<User> user) {
  printText("User name: ");
  user->setName(getText());
  std::string pas;
  bool isEqual = false;
  while (!isEqual) {
    printText("Password: ");
    pas = getPassword();
    printText("Password again: ");
    std::string pas2 = getPassword();
    if (pas != pas2) std::cout << "Passwords are not equal, try again" << std::endl;
    else isEqual = true;
  }
  user->setPassword(pas);
  user->setStatus("user");
}

void Display::getPasswordAndName(std::shared_ptr<User> user) {
  printText("\n   Sign in\n");
  printText("User name: ");
  user->setName(getText());
  std::string pas;
  printText("Password: ");
  pas = getPassword();
  user->setPassword(pas);
}

std::string Display::getPassword() {
  const char BACKSPACE = 127;
  const char RETURN = 10;

  bool show_asterisk = true;

  std::string password;
  unsigned char ch = 0;

  while ((ch = getChar()) != RETURN) {
    if (ch == BACKSPACE) {
      if (password.length() != 0) {
        if (show_asterisk)
          std::cout << "\b \b";
        password.resize(password.length() - 1);
      }
    } else {
      password += ch;
      if (show_asterisk) std::cout << '*';
    }
  }
  std::cout << std::endl;
  return password;
}

char Display::getChar() {
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}



