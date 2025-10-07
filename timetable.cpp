 #include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// 🎨 ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

// --------------------------- Class Definition ---------------------------
class TimeTableEntry {
private:
    string day;
    string subject;
    string startTime;
    string endTime;

public:
    TimeTableEntry(string d, string s, string start, string end)
        : day(d), subject(s), startTime(start), endTime(end) {}

    void display() const {
        cout << left << setw(10) << day
             << setw(15) << subject
             << setw(15) << startTime
             << setw(15) << endTime << endl;
    }

    string getDay() const { return day; }
    string getSubject() const { return subject; }

    void update(string s, string start, string end) {
        subject = s;
        startTime = start;
        endTime = end;
    }
};

// --------------------------- Manager Class ---------------------------
class TimeTableManager {
private:
    vector<TimeTableEntry> entries;

public:
    void addEntry() {
        string day, subject, startTime, endTime;
        cout << YELLOW << "Enter Day (e.g., Monday): " << RESET;
        cin >> day;
        cout << YELLOW << "Enter Subject: " << RESET;
        cin.ignore();
        getline(cin, subject);
        cout << YELLOW << "Enter Start Time (e.g., 10:00 AM): " << RESET;
        getline(cin, startTime);
        cout << YELLOW << "Enter End Time (e.g., 11:00 AM): " << RESET;
        getline(cin, endTime);

        entries.emplace_back(day, subject, startTime, endTime);
        cout << GREEN << "\n✅ Entry added successfully!\n" << RESET;
    }

    void viewAll() {
        if (entries.empty()) {
            cout << RED << "\n❌ No entries available!\n" << RESET;
            return;
        }

        cout << CYAN << "\n----------- TIME TABLE -----------\n" << RESET;
        cout << BOLD << left << setw(10) << "DAY"
             << setw(15) << "SUBJECT"
             << setw(15) << "START TIME"
             << setw(15) << "END TIME" << RESET << endl;
        cout << BLUE << "-----------------------------------------------\n" << RESET;

        for (const auto &entry : entries)
            entry.display();
    }

    void deleteEntry() {
        string day, subject;
        cout << YELLOW << "Enter Day of entry to delete: " << RESET;
        cin >> day;
        cout << YELLOW << "Enter Subject name: " << RESET;
        cin.ignore();
        getline(cin, subject);

        for (auto it = entries.begin(); it != entries.end(); ++it) {
            if (it->getDay() == day && it->getSubject() == subject) {
                entries.erase(it);
                cout << GREEN << "\n🗑️ Entry deleted successfully!\n" << RESET;
                return;
            }
        }
        cout << RED << "\n❌ Entry not found!\n" << RESET;
    }

    void updateEntry() {
        string day, subject;
        cout << YELLOW << "Enter Day of entry to update: " << RESET;
        cin >> day;
        cout << YELLOW << "Enter Subject name: " << RESET;
        cin.ignore();
        getline(cin, subject);

        for (auto &entry : entries) {
            if (entry.getDay() == day && entry.getSubject() == subject) {
                string newSubject, newStart, newEnd;
                cout << YELLOW << "Enter New Subject: " << RESET;
                getline(cin, newSubject);
                cout << YELLOW << "Enter New Start Time: " << RESET;
                getline(cin, newStart);
                cout << YELLOW << "Enter New End Time: " << RESET;
                getline(cin, newEnd);

                entry.update(newSubject, newStart, newEnd);
                cout << GREEN << "\n✏️ Entry updated successfully!\n" << RESET;
                return;
            }
        }
        cout << RED << "\n❌ Entry not found!\n" << RESET;
    }
};

// --------------------------- Main Function ---------------------------
int main() {
    TimeTableManager manager;
    int choice;

    do {
        cout << CYAN << "\n========= TIME TABLE MANAGEMENT SYSTEM =========\n" << RESET;
        cout << BLUE << "1. Add Entry\n";
        cout << "2. View All Entries\n";
        cout << "3. Delete Entry\n";
        cout << "4. Update Entry\n";
        cout << "5. Exit\n" << RESET;
        cout << YELLOW << "Enter your choice: " << RESET;
        cin >> choice;

        switch (choice) {
        case 1:
            manager.addEntry();
            break;
        case 2:
            manager.viewAll();
            break;
        case 3:
            manager.deleteEntry();
            break;
        case 4:
            manager.updateEntry();
            break;
        case 5:
            cout << MAGENTA << "\n👋 Exiting... Have a productive day!\n" << RESET;
            break;
        default:
            cout << RED << "\n❌ Invalid choice! Try again.\n" << RESET;
        }
    } while (choice != 5);

    return 0;
}
