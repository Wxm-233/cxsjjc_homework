#include <iostream>
#include <string>
#include <list>
#include <set>
using namespace std;

class file {
private:
    string name_;
public:
    file(string name) : name_(name) {}
    const string& name() {
        return name_;
    }
    class less {
    public:
        bool operator() (const file* f1, const file* f2) const {
            return f1->name_ < f2->name_;
        }
    };
};

class dir {
private:
    string name_;
    int level;
    list<dir*> dirs;
    set<file*, file::less> files;
    dir* father_;
public:
    dir(string name, int level, dir* father = nullptr) : name_(name), level(level), father_(father) {}
    const string& name() {
        return name_;
    }
    dir* addDir(string name) {
        dir* newDir = new dir(name, level+1, this);
        dirs.push_back(newDir);
        return newDir;
    }
    void addFile(string name) {
        files.insert(new file(name));
    }
    dir* father() {
        return father_;
    }
    void clear() {
        for (auto &i : files) {
            delete i;
        }
        for (auto &i : dirs) {
            i->clear();
            delete i;
        }
        files.clear();
        dirs.clear();
    }
    void printPrefix() {
        for (int i = 0; i < level; ++i) {
            cout << "|     ";
        }
    }
    void output() {
        printPrefix();
        cout << name_ << endl;
        for (auto& i : dirs) {
            i->output();
        }
        for (auto& i : files) {
            printPrefix();
            cout << i->name() << endl;
        }
    }
};

int main() {
    dir* ROOT = new dir("ROOT", 0);
    dir* currentDir = ROOT;
    int dataSet = 1;
    while (cin.peek() != '#') {
        if (cin.peek() == '*') {
            cin.get(), cin.get();
            currentDir = ROOT;
            printf("DATA SET %d:\n", dataSet++);
            ROOT->output();
            cout << endl;
            ROOT->clear();
        }
        else if (cin.peek() == ']') {
            cin.get(), cin.get();
            currentDir = currentDir->father();
        }
        else {
            string name;
            cin >> name, cin.get();
            switch (name[0]) {
                case 'f':
                    currentDir->addFile(name);
                    break;
                case 'd':
                    currentDir = currentDir->addDir(name);
                    break;
                default:
                    clog << "error" << endl;
            }
        }
    }
    return 0;
}