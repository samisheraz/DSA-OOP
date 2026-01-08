#include <iostream>
#include <string>
#include <vector>
using namespace std;

// -----------------------------
// Classes
// -----------------------------
class TimeSlot {
private:
    int id;
    string timeRange;
public:
    TimeSlot(int i = 0, string t = "") { id = i; timeRange = t; }
    void setId(int i) { id = i; }
    void setTimeRange(string t) { timeRange = t; }
    int getId() { return id; }
    string getTimeRange() { return timeRange; }
};

class Teacher {
private:
    string name;
    string email;
public:
    Teacher(string n = "", string e = "") { name = n; email = e; }
    void setName(string n) { name = n; }
    void setEmail(string e) { email = e; }
    string getName() { return name; }
    string getEmail() { return email; }
};

class Session {
private:
    string name;
public:
    Session(string n = "") { name = n; }
    void setName(string n) { name = n; }
    string getName() { return name; }
};

class Room {
private:
    string type;
    string name;
public:
    Room(string t = "", string n = "") { type = t; name = n; }
    void setType(string t) { type = t; }
    void setName(string n) { name = n; }
    string getType() { return type; }
    string getName() { return name; }
    string display() { return name; }
};

class Course {
private:
    string name;
    string credit;
public:
    Course(string n = "", string c = "") { name = n; credit = c; }
    void setName(string n) { name = n; }
    void setCredit(string c) { credit = c; }
    string getName() { return name; }
    string getCredit() { return credit; }
};

class Lesson {
private:
    Course course;
    Teacher teacher;
    Session session;
    Room room;
    string day;
    TimeSlot slot;

public:
    void setCourse(Course c) { course = c; }
    void setTeacher(Teacher t) { teacher = t; }
    void setSession(Session s) { session = s; }
    void setRoom(Room r) { room = r; }
    void setDay(string d) { day = d; }
    void setSlot(TimeSlot s) { slot = s; }

    Course getCourse() { return course; }
    Teacher getTeacher() { return teacher; }
    Session getSession() { return session; }
    Room getRoom() { return room; }
    string getDay() { return day; }
    TimeSlot getSlot() { return slot; }

    string classRow() {
        return day + " | " + teacher.getName() + " | " +
            course.getName() + " | " + course.getCredit() + " | " +
            room.display() + " | " + slot.getTimeRange() + "\n";
    }

    string teacherRow() {
        return day + " | " + slot.getTimeRange() + " | " +
            course.getName() + " | " + course.getCredit() + " | " +
            room.display() + " | " + session.getName() + "\n";
    }

    // New method for displaying lesson with session in table
    string allLessonsRow() {
        return session.getName() + " | " + day + " | " + teacher.getName() + " | " +
            course.getName() + " | " + course.getCredit() + " | " +
            room.display() + " | " + slot.getTimeRange() + "\n";
    }
};

// -----------------------------
// Timetable System
// -----------------------------
class TimetableSystem {
private:
    string timetableName;
    int workingDays;

    vector<string> dayNames;
    vector<vector<TimeSlot>> slotsPerDay;

    vector<Teacher> teachers;
    vector<Session> sessions;
    vector<Room> rooms;
    vector<Course> courses;
    vector<Lesson> lessons;

    bool isValidDayName(const string& name) {
        if (name.empty()) {
            return false;
        }

        // Check if the name contains any digit
        for (char c : name) {
            if (isdigit(c)) {
                return false;
            }
        }
        return true;
    }
public:
    // ---------- INITIALIZE ----------
    void initialize() {
        cout << "Enter Timetable Name: ";
        while (true) {
            getline(cin, timetableName);

            // Check if the name contains any digit
            bool hasDigit = false;
            for (char c : timetableName) {
                if (isdigit(c)) {
                    hasDigit = true;
                    break;
                }
            }

            if (hasDigit) {
                cout << "Error: Timetable name cannot contain numbers. Please enter a valid name: ";
            }
            else if (timetableName.empty()) {
                cout << "Error: Timetable name cannot be empty. Please enter a valid name: ";
            }
            else {
                break; // Valid name
            }
        }

        cout << "Enter Number of Working Days: ";
        while (!(cin >> workingDays) || workingDays <= 0) {
            cout << "Please enter a valid positive integer: ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        for (int d = 0; d < workingDays; d++) {
            string day;
            while (true) {
                cout << "\nEnter Day " << d + 1 << ": ";
                getline(cin, day);

                if (!isValidDayName(day)) {
                    cout << "Error: Day name cannot contain numbers or be empty. Please enter a valid day name: ";
                }
                else {
                    dayNames.push_back(day);
                    break;
                }
            }

            int slots;
            cout << "How many slots for " << day << "? ";
            while (!(cin >> slots) || slots <= 0) {
                cout << "Please enter valid positive integer: ";
                cin.clear(); cin.ignore(10000, '\n');
            }
            cin.ignore();

            vector<TimeSlot> daySlots;
            for (int s = 0; s < slots; s++) {
                string time;
                cout << "Enter time for Slot " << s + 1 << ": ";
                getline(cin, time);
                daySlots.push_back(TimeSlot(s + 1, time));
            }
            slotsPerDay.push_back(daySlots);
        }
        cout << "\nTimetable '" << timetableName << "' initialized!\n";
    }

    // ---------- INSTITUTE DATA ----------
    void instituteDataMenu() {
        int ch;
        while (true) {
            cout << "\n--- Institute Data ---\n";
            cout << "1. Add Teacher\n2. Add Session\n3. Add Room\n4. Back\nEnter choice: ";
            while (!(cin >> ch)) {
                cout << "Error: Please enter a valid integer choice (1-4): ";
                cin.clear(); cin.ignore(10000, '\n');
            }
            cin.ignore();
            if (ch == 1) addTeacher();
            else if (ch == 2) addSession();
            else if (ch == 3) addRoom();
            else break;
        }
    }

    void addTeacher() {
        string n, e;
        cout << "Teacher Name: "; getline(cin, n);
        cout << "Email: "; getline(cin, e);
        teachers.push_back(Teacher(n, e));
        cout << "Teacher added successfully!\n";
    }

    void addSession() {
        string n;
        cout << "Session Name: "; getline(cin, n);

        // Check for duplicate session
        bool found = false;
        for (int i = 0; i < sessions.size(); i++) {
            if (sessions[i].getName() == n) {
                found = true;
                break;
            }
        }
        if (found) {
            cout << "Error: Session with this name already exists!\n";
            return;
        }

        sessions.push_back(Session(n));
        cout << "Session added successfully!\n";
    }

    void addRoom() {
        int ch;
        cout << "1. Lab\n2. Other\nEnter choice: ";
        while (!(cin >> ch) || (ch != 1 && ch != 2)) {
            cout << "Error: Please enter a valid integer choice (1 or 2): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        string name;
        if (ch == 1) {
            cout << "Enter Lab Name: ";
            getline(cin, name);
            rooms.push_back(Room("Lab", name));
        }
        else {
            cout << "Enter Room Name: ";
            getline(cin, name);
            rooms.push_back(Room("Other", name));
        }
        cout << "Room added successfully!\n";
    }

    // ---------- LESSON CONFIG ----------
    void lessonConfigMenu() {
        int ch;
        while (true) {
            cout << "\n--- Lesson Configuration ---\n";
            cout << "1. Add Course\n2. Add Lesson\n3. Back\nEnter choice: ";
            while (!(cin >> ch)) {
                cout << "Error: Please enter a valid integer choice (1-3): ";
                cin.clear(); cin.ignore(10000, '\n');
            }
            cin.ignore();
            if (ch == 1) addCourse();
            else if (ch == 2) addLesson();
            else break;
        }
    }

    void addCourse() {
        string n, c;
        cout << "Course Name: "; getline(cin, n);
        cout << "Credit Hours: "; getline(cin, c);
        courses.push_back(Course(n, c));
        cout << "Course added successfully!\n";
    }

    // ---------- ADD LESSON WITH CONFLICT CHECK ----------
    void addLesson() {
        if (teachers.empty() || sessions.empty() || rooms.empty() || courses.empty()) {
            cout << "Add Teachers, Sessions, Rooms, and Courses first!\n";
            return;
        }

        Lesson lesson;
        int choice;

        // Session
        cout << "\nSelect Session:\n";
        for (int i = 0; i < sessions.size(); i++)
            cout << i + 1 << ". " << sessions[i].getName() << endl;
        cout << "Enter choice: ";
        while (!(cin >> choice) || choice < 1 || choice > sessions.size()) {
            cout << "Enter valid choice: ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        lesson.setSession(sessions[choice - 1]);
        cin.ignore(10000, '\n');

        // Course
        cout << "\nSelect Course:\n";
        for (int i = 0; i < courses.size(); i++)
            cout << i + 1 << ". " << courses[i].getName() << " (" << courses[i].getCredit() << ")\n";
        cout << "Enter choice: ";
        while (!(cin >> choice) || choice < 1 || choice > courses.size()) {
            cout << "Enter valid choice: ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        lesson.setCourse(courses[choice - 1]);
        cin.ignore(10000, '\n');

        // Teacher
        cout << "\nSelect Teacher:\n";
        for (int i = 0; i < teachers.size(); i++)
            cout << i + 1 << ". " << teachers[i].getName() << endl;
        cout << "Enter choice: ";
        while (!(cin >> choice) || choice < 1 || choice > teachers.size()) {
            cin.clear(); cin.ignore(10000, '\n');
        }
        lesson.setTeacher(teachers[choice - 1]);
        cin.ignore(10000, '\n');

        // Room
        cout << "\nSelect Room:\n";
        for (int i = 0; i < rooms.size(); i++)
            cout << i + 1 << ". " << rooms[i].display() << endl;
        cout << "Enter choice: ";
        while (!(cin >> choice) || choice < 1 || choice > rooms.size()) {
            cin.clear(); cin.ignore(10000, '\n');
        }
        lesson.setRoom(rooms[choice - 1]);
        cin.ignore(10000, '\n');

        // Day
        cout << "\nSelect Day:\n";
        for (int i = 0; i < dayNames.size(); i++)
            cout << i + 1 << ". " << dayNames[i] << endl;
        cout << "Enter choice: ";
        while (!(cin >> choice) || choice < 1 || choice > dayNames.size()) {
            cin.clear(); cin.ignore(10000, '\n');
        }
        int dayIndex = choice - 1;
        lesson.setDay(dayNames[dayIndex]);
        cin.ignore(10000, '\n');

        // Slot
        cout << "\nSelect Slot:\n";
        for (int i = 0; i < slotsPerDay[dayIndex].size(); i++)
            cout << i + 1 << ". " << slotsPerDay[dayIndex][i].getTimeRange() << endl;
        cout << "Enter choice: ";
        while (!(cin >> choice) || choice < 1 || choice > slotsPerDay[dayIndex].size()) {
            cin.clear(); cin.ignore(10000, '\n');
        }
        lesson.setSlot(slotsPerDay[dayIndex][choice - 1]);
        cin.ignore(10000, '\n');

        // ---------- CONFLICT CHECK ----------
        for (auto& l : lessons) {
            if (l.getDay() == lesson.getDay() &&
                l.getSlot().getId() == lesson.getSlot().getId()) {

                if (l.getTeacher().getName() == lesson.getTeacher().getName()) {
                    cout << "Error: Teacher " << lesson.getTeacher().getName() << " is already assigned at this time.\n";
                    return;
                }
                if (l.getRoom().getName() == lesson.getRoom().getName()) {
                    cout << "Error: Room " << lesson.getRoom().getName() << " is already booked at this time.\n";
                    return;
                }
                if (l.getSession().getName() == lesson.getSession().getName()) {
                    cout << "Error: Session " << lesson.getSession().getName() << " already has a lesson at this time.\n";
                    return;
                }
            }
        }

        lessons.push_back(lesson);
        cout << "Lesson added successfully!\n";
    }

    // ---------- VIEW ALL LESSONS ----------
    void viewAllLessons() {
        if (lessons.empty()) {
            cout << "\nNo lessons added yet.\n";
            return;
        }

        cout << "\n";
        cout << "=============================================================================================================\n";
        cout << "                                        ALL LESSONS - COMPLETE VIEW\n";
        cout << "=============================================================================================================\n";
        cout << "SESSION | DAY       | TEACHER               | COURSE                 | CREDIT | ROOM       | TIME\n";
        cout << "=============================================================================================================\n";

        for (int i = 0; i < lessons.size(); i++) {
            string session = lessons[i].getSession().getName();
            string day = lessons[i].getDay();
            string teacher = lessons[i].getTeacher().getName();
            string course = lessons[i].getCourse().getName();
            string credit = lessons[i].getCourse().getCredit();
            string room = lessons[i].getRoom().getName();
            string time = lessons[i].getSlot().getTimeRange();

            // Format the output with proper alignment
            printf("%-7s | %-9s | %-21s | %-22s | %-6s | %-10s | %s\n",
                session.c_str(), day.c_str(), teacher.c_str(),
                course.c_str(), credit.c_str(), room.c_str(), time.c_str());
        }

        cout << "=============================================================================================================\n";
        cout << "Total Lessons: " << lessons.size() << "\n\n";
    }

    // ---------- DISPLAY CLASS TIMETABLE SESSION WISE ----------
    void displayClassTimetableBySession() {
        if (sessions.empty()) {
            cout << "No sessions available!\n";
            return;
        }

        if (lessons.empty()) {
            cout << "No lessons added yet.\n";
            return;
        }

        int ch;
        cout << "\n--- Display Class Timetable ---\n";
        cout << "1. Display Timetable for All Sessions\n";
        cout << "2. Display Timetable by Session Name\n";
        cout << "Enter choice: ";
        while (!(cin >> ch) || (ch != 1 && ch != 2)) {
            cout << "Error: Please enter a valid integer choice (1 or 2): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        if (ch == 1) {
            // Display timetable for ALL sessions
            displayAllSessionsTimetable();
        }
        else if (ch == 2) {
            // Display timetable for a specific session
            displayTimetableBySessionName();
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    void displayAllSessionsTimetable() {
        cout << "\n";
        cout << "************************************************************************\n";
        cout << "                   TIMETABLE FOR ALL SESSIONS\n";
        cout << "************************************************************************\n\n";

        int sessionCount = 0;

        // Display timetable for each session that has lessons
        for (int s = 0; s < sessions.size(); s++) {
            string sessionName = sessions[s].getName();
            bool hasLessons = false;

            // Check if this session has any lessons
            for (int i = 0; i < lessons.size(); i++) {
                if (lessons[i].getSession().getName() == sessionName) {
                    hasLessons = true;
                    break;
                }
            }

            if (hasLessons) {
                sessionCount++;
                displaySessionTimetable(sessionName);
            }
        }

        if (sessionCount == 0) {
            cout << "No sessions have any lessons scheduled.\n";
        }
        else {
            cout << "Total Sessions with Timetable: " << sessionCount << "\n";
        }
    }

    void displayTimetableBySessionName() {
        // Show available sessions
        cout << "\nAvailable Sessions:\n";
        for (int i = 0; i < sessions.size(); i++) {
            cout << i + 1 << ". " << sessions[i].getName() << endl;
        }

        int choice;
        cout << "\nSelect Session to view timetable: ";
        while (!(cin >> choice) || choice < 1 || choice > sessions.size()) {
            cout << "Error: Please enter a valid integer choice (1-" << sessions.size() << "): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        if (choice >= 1 && choice <= sessions.size()) {
            string selectedSession = sessions[choice - 1].getName();
            displaySessionTimetable(selectedSession);
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    void displaySessionTimetable(string sessionName) {
        cout << "\n";
        cout << "==========================================================\n";
        cout << "           TIMETABLE FOR SESSION: " << sessionName << "\n";
        cout << "==========================================================\n";

        bool found = false;

        // Display for each day
        for (int d = 0; d < dayNames.size(); d++) {
            string day = dayNames[d];
            bool dayHasLessons = false;

            // Check if this day has lessons for this session
            for (int i = 0; i < lessons.size(); i++) {
                if (lessons[i].getSession().getName() == sessionName &&
                    lessons[i].getDay() == day) {
                    dayHasLessons = true;
                    break;
                }
            }

            if (dayHasLessons) {
                cout << "\n" << day << ":\n";
                cout << "---------------------------------------------------------------------\n";

                // Display header
                cout << "TIME        | TEACHER                | COURSE                  | CREDIT | ROOM\n";
                cout << "---------------------------------------------------------------------\n";

                // Display lessons for this day in this session, sorted by slot
                for (int slotNum = 1; slotNum <= slotsPerDay[d].size(); slotNum++) {
                    for (int i = 0; i < lessons.size(); i++) {
                        if (lessons[i].getSession().getName() == sessionName &&
                            lessons[i].getDay() == day &&
                            lessons[i].getSlot().getId() == slotNum) {

                            // Get the data
                            string time = lessons[i].getSlot().getTimeRange();
                            string teacher = lessons[i].getTeacher().getName();
                            string course = lessons[i].getCourse().getName();
                            string credit = lessons[i].getCourse().getCredit();
                            string room = lessons[i].getRoom().getName();

                            // Display without truncation - increased column widths
                            printf("%-11s | %-22s | %-23s | %-6s | %s\n",
                                time.c_str(), teacher.c_str(), course.c_str(),
                                credit.c_str(), room.c_str());

                            found = true;
                        }
                    }
                }
            }
        }

        if (!found) {
            cout << "\nNo timetable found for Session: " << sessionName << "\n";
        }

        cout << "==========================================================\n\n";
    }

    // ---------- TEACHER TIMETABLE ----------
    void displayTeacherTimetable() {
        if (teachers.empty()) { cout << "No teachers available!\n"; return; }
        int ch;
        cout << "\n1. Display All Teachers Timetable\n2. Display by Teacher Name\nEnter choice: ";
        while (!(cin >> ch) || (ch != 1 && ch != 2)) {
            cout << "Error: Please enter a valid integer choice (1 or 2): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();
        if (ch == 1) {
            for (auto& t : teachers) {
                cout << "\nTEACHER: " << t.getName() << endl;
                for (auto& l : lessons)
                    if (l.getTeacher().getName() == t.getName())
                        cout << l.teacherRow();
            }
        }
        else if (ch == 2) {
            for (int i = 0; i < teachers.size(); i++)
                cout << i + 1 << ". " << teachers[i].getName() << endl;
            int choice; cout << "Enter choice: ";
            while (!(cin >> choice) || choice < 1 || choice > teachers.size()) {
                cout << "Error: Please enter a valid integer choice (1-" << teachers.size() << "): ";
                cin.clear(); cin.ignore(10000, '\n');
            }
            cin.ignore();
            if (choice < 1 || choice > teachers.size()) return;
            string selectedTeacher = teachers[choice - 1].getName();
            cout << "\nTEACHER: " << selectedTeacher << endl;
            for (auto& l : lessons)
                if (l.getTeacher().getName() == selectedTeacher)
                    cout << l.teacherRow();
        }
    }

    // ---------- EDIT TIMETABLE --
    void editTimetableMenu() {
        int ch;
        while (true) {
            cout << "\n--- Edit Timetable ---\n";
            cout << "1. Edit Slots\n2. Edit Institute Data\n3. Edit Lesson Configuration\n4. Back\nEnter choice: ";
            while (!(cin >> ch)) {
                cout << "Error: Please enter a valid integer choice (1-4): ";
                cin.clear(); cin.ignore(10000, '\n');
            }
            cin.ignore();
            if (ch == 1) editSlotsMenu();
            else if (ch == 2) editInstituteData();
            else if (ch == 3) editCourses();
            else break;
        }
    }

    // ---------- EDIT SLOTS MENU ----------
    void editSlotsMenu() {
        int ch;
        while (true) {
            cout << "\n--- Edit Slots ---\n";
            cout << "1. Edit Day Names\n2. Edit Time Slots\n3. Back\nEnter choice: ";
            while (!(cin >> ch)) {
                cout << "Error: Please enter a valid integer choice (1-3): ";
                cin.clear(); cin.ignore(10000, '\n');
            }
            cin.ignore();
            if (ch == 1) editDayNames();
            else if (ch == 2) editTimeSlots();
            else break;
        }
    }

    void editDayNames() {
        cout << "\nCurrent Day Names:\n";
        for (int i = 0; i < dayNames.size(); i++) {
            cout << i + 1 << ". " << dayNames[i] << endl;
        }

        int choice;
        cout << "Select day to edit (0 to cancel): ";
        while (!(cin >> choice)) {
            cout << "Error: Please enter a valid integer: ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        if (choice < 1 || choice > dayNames.size()) {
            cout << "Cancelled.\n";
            return;
        }

        string oldDayName = dayNames[choice - 1];
        string newDayName;

        while (true) {
            cout << "Current name: " << oldDayName << endl;
            cout << "Enter new name: ";
            getline(cin, newDayName);

            if (!isValidDayName(newDayName)) {
                cout << "Error: Day name cannot contain numbers or be empty. Please enter a valid day name: ";
            }
            else {
                break;
            }
        }

        // Update day name in dayNames vector
        dayNames[choice - 1] = newDayName;

        // Update day name in all lessons
        for (int i = 0; i < lessons.size(); i++) {
            if (lessons[i].getDay() == oldDayName) {
                lessons[i].setDay(newDayName);
            }
        }

        cout << "Day name updated successfully!\n";
    }

    void editTimeSlots() {
        cout << "\nSelect Day to edit its time slots:\n";
        for (int i = 0; i < dayNames.size(); i++) {
            cout << i + 1 << ". " << dayNames[i] << endl;
        }

        int dayChoice;
        cout << "Enter choice: ";
        while (!(cin >> dayChoice) || dayChoice < 1 || dayChoice > dayNames.size()) {
            cout << "Error: Please enter a valid integer choice (1-" << dayNames.size() << "): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        if (dayChoice < 1 || dayChoice > dayNames.size()) {
            cout << "Invalid choice!\n";
            return;
        }

        int dayIndex = dayChoice - 1;

        cout << "\nCurrent Time Slots for " << dayNames[dayIndex] << ":\n";
        for (int i = 0; i < slotsPerDay[dayIndex].size(); i++) {
            cout << i + 1 << ". " << slotsPerDay[dayIndex][i].getTimeRange() << endl;
        }

        int slotChoice;
        cout << "\nSelect slot to edit (0 to cancel): ";
        while (!(cin >> slotChoice)) {
            cout << "Error: Please enter a valid integer: ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        if (slotChoice < 1 || slotChoice > slotsPerDay[dayIndex].size()) {
            cout << "Cancelled.\n";
            return;
        }

        string oldTimeRange = slotsPerDay[dayIndex][slotChoice - 1].getTimeRange();
        int slotId = slotsPerDay[dayIndex][slotChoice - 1].getId();
        string newTimeRange;

        cout << "Current time: " << oldTimeRange << endl;
        cout << "Enter new time range: ";
        getline(cin, newTimeRange);

        // Update time slot
        slotsPerDay[dayIndex][slotChoice - 1].setTimeRange(newTimeRange);

        // Update time slot in all lessons
        for (int i = 0; i < lessons.size(); i++) {
            if (lessons[i].getDay() == dayNames[dayIndex]) {
                // Get the slot from lesson
                TimeSlot lessonSlot = lessons[i].getSlot();
                if (lessonSlot.getId() == slotId) {
                    // Update the time range in the slot
                    lessonSlot.setTimeRange(newTimeRange);
                    lessons[i].setSlot(lessonSlot);
                }
            }
        }

        cout << "Time slot updated successfully!\n";
    }

    void editInstituteData() {
        int ch;
        cout << "\n--- Edit Institute Data ---\n";
        cout << "1. Edit Teachers\n2. Edit Sessions\n3. Edit Rooms\n4. Back\nEnter choice: ";
        while (!(cin >> ch)) {
            cout << "Error: Please enter a valid integer choice (1-4): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();
        if (ch == 1) editTeachers();
        else if (ch == 2) editSessions();
        else if (ch == 3) editRooms();
    }

    void editTeachers() {
        for (int i = 0; i < teachers.size(); i++)
            cout << i + 1 << ". " << teachers[i].getName() << endl;
        int ch; cout << "Enter choice: ";
        while (!(cin >> ch) || ch < 1 || ch > teachers.size()) {
            cout << "Error: Please enter a valid integer choice (1-" << teachers.size() << "): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();
        string oldName = teachers[ch - 1].getName();
        string n, e;
        cout << "New Name: "; getline(cin, n);
        cout << "New Email: "; getline(cin, e);
        Teacher updated(n, e);
        teachers[ch - 1] = updated;
        for (auto& l : lessons)
            if (l.getTeacher().getName() == oldName) l.setTeacher(updated);
    }

    void editRooms() {
        for (int i = 0; i < rooms.size(); i++)
            cout << i + 1 << ". " << rooms[i].display() << endl;
        int ch; cout << "Enter choice: ";
        while (!(cin >> ch) || ch < 1 || ch > teachers.size()) {
            cout << "Error: Please enter a valid integer choice (1-" << teachers.size() << "): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();
        string oldName = rooms[ch - 1].getName();
        string type, name;
        cout << "Enter Type (Lab/Other): "; getline(cin, type);
        cout << "Enter New Name: "; getline(cin, name);
        Room updated(type, name);
        rooms[ch - 1] = updated;
        for (auto& l : lessons)
            if (l.getRoom().getName() == oldName) l.setRoom(updated);
    }

    void editSessions() {
        for (int i = 0; i < sessions.size(); i++)
            cout << i + 1 << ". " << sessions[i].getName() << endl;
        int ch; cout << "Enter choice: ";
        while (!(cin >> ch) || ch < 1 || ch > teachers.size()) {
            cout << "Error: Please enter a valid integer choice (1-" << teachers.size() << "): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();
        string oldName = sessions[ch - 1].getName();
        string n; cout << "New Session Name: "; getline(cin, n);

        // Check for duplicate session
        bool found = false;
        for (int i = 0; i < sessions.size(); i++) {
            if (sessions[i].getName() == n) {
                found = true;
                break;
            }
        }
        if (found) {
            cout << "Error: Session with this name already exists!\n";
            return;
        }

        Session updated(n);
        sessions[ch - 1] = updated;
        for (auto& l : lessons)
            if (l.getSession().getName() == oldName) l.setSession(updated);
    }

    void editCourses() {
        for (int i = 0; i < courses.size(); i++)
            cout << i + 1 << ". " << courses[i].getName() << endl;
        int ch; cout << "Enter choice: ";
        while (!(cin >> ch) || ch < 1 || ch > teachers.size()) {
            cout << "Error: Please enter a valid integer choice (1-" << teachers.size() << "): ";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();
        string oldName = courses[ch - 1].getName();
        string n, c;
        cout << "New Name: "; getline(cin, n);
        cout << "New Credit: "; getline(cin, c);
        Course updated(n, c);
        courses[ch - 1] = updated;
        for (auto& l : lessons)
            if (l.getCourse().getName() == oldName) l.setCourse(updated);
    }
};

// -----------------------------
// MAIN
// -----------------------------
int main() {
    TimetableSystem system;
    system.initialize();

    int ch;
    while (true) {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Institute Data\n";
        cout << "2. Lesson Configuration\n";
        cout << "3. View All Lessons\n";
        cout << "4. Edit Timetable\n";
        cout << "5. Display Class Timetable\n";
        cout << "6. Display Teacher Timetable\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore();

        if (ch == 1) system.instituteDataMenu();
        else if (ch == 2) system.lessonConfigMenu();
        else if (ch == 3) system.viewAllLessons();
        else if (ch == 4) system.editTimetableMenu();
        else if (ch == 5) system.displayClassTimetableBySession();
        else if (ch == 6) system.displayTeacherTimetable();
        else if (ch == 7) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}