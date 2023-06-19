// Name : Aaqib Ahmed Nazir
// Roll No: 22I-1920
//  Section: DS-D
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

// function prototypes
void getStudentCourses(string _courses[11]);
void getTeacherCourses(string _courses[11]);
string stuID, teacherID;
// user class
class User
{
private:
    string name;
    string password;
    string id;
    string user_type; // teacher or student
public:
    // default constructor
    User()
    {
        this->name = "";
        this->password = "";
        this->id = "";
        this->user_type = "";
    }

    // parameterized constructor
    User(string n, string p, string i)
    {
        this->name = n;
        this->password = p;
        this->id = i;
        this->user_type = "None";
    }

    // getters
    string getName()
    {
        return this->name;
    }

    string getPassword()
    {
        return this->password;
    }

    string getId()
    {
        return this->id;
    }

    string getUserType()
    {
        return this->user_type;
    }

    // setters
    void setName(string n)
    {
        this->name = n;
    }

    void setPassword(string p)
    {
        this->password = p;
    }

    void setId(string i)
    {
        this->id = i;
    }

    void setUserType(string u)
    {
        this->user_type = u;
    }

    // login menu function prototype
    void loginMenu();

    // function to check if the given id is in correct format or not eg. 22I-2841
    bool checkID(string _id)
    {
        int length = 0;
        // should be 8 characters long
        for (int i = 0; _id[i] != '\0'; i++)
        {
            length++;
        }

        if (length == 8)
        {
            // the first 2 characters must be digits the third character must be a letter,4th character should be a - and  the last 4 characters must be digits
            if (_id[0] >= '0' && _id[0] <= '9' && _id[1] >= '0' && _id[1] <= '9' && _id[2] >= 'A' && _id[2] <= 'Z' && _id[3] == '-' && _id[4] >= '0' && _id[4] <= '9' && _id[5] >= '0' && _id[5] <= '9' && _id[6] >= '0' && _id[6] <= '9' && _id[7] >= '0' && _id[7] <= '9')
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        else
        {
            return false;
        }
    }

    // function that checks if the password is correct or not The password provided must have minimum of 6 length. The password must contain uppercase, lowercase, numeric digit, and special characters.
    bool checkPassword(string _password)
    {
        bool hasUpper = false;
        bool hasLower = false;
        bool hasDigit = false;
        bool hasSpecial = false;
        int length = 0;

        // calculate the length of the password
        for (int i = 0; _password[i] != '\0'; i++)
        {
            length++;
        }

        if (length >= 6 && length <= 50) // if password is 6 or more characters
        {
            for (int i = 0; i <= length; i++)
            {
                if (_password[i] >= 'A' && _password[i] <= 'Z') // condtion to check if password conatins uppercase letter
                {
                    hasUpper = true;
                }

                if (_password[i] >= 'a' && _password[i] <= 'z') // condtion to check if password conatins lowercase letter
                {
                    hasLower = true;
                }

                if (_password[i] >= '0' && _password[i] <= '9') // condtion to check if password conatins digit
                {
                    hasDigit = true;
                }

                else if (_password[i] == '!' || _password[i] == '@' || _password[i] == '#' || _password[i] == '$' || _password[i] == '%' || _password[i] == '^' || _password[i] == '&' || _password[i] == '*' || _password[i] == '(' || _password[i] == ')' || _password[i] == '-' || _password[i] == '_' || _password[i] == '+' || _password[i] == '=' || _password[i] == '{' || _password[i] == '}' || _password[i] == '[' || _password[i] == ']' || _password[i] == '|' || _password[i] == '\\' || _password[i] == ':' || _password[i] == ';' || _password[i] == '"' || _password[i] == '\'' || _password[i] == '<' || _password[i] == '>' || _password[i] == ',' || _password[i] == '.' || _password[i] == '?' || _password[i] == '/')
                {
                    hasSpecial = true;
                }
            }
        }

        if (hasUpper && hasLower && hasDigit && hasSpecial) // if password meets the requirements
        {
            return true;
        }

        else if (!(hasUpper && hasLower && hasDigit && hasSpecial)) // if password does not meet the requirements
        {
            return false;
        }

        return false;
    }

    // function to display the profile
    void displayProfile()
    {
        // function displays the profile of the user
        cout << "\n\t\t\t\t\t\t  ***Profile***" << endl;
        cout << "Name: " << this->name << endl;
        cout << "ID: " << this->id << endl;
        cout << "Password: " << this->password << endl;
        cout << "User Type: " << this->user_type << endl;
        cout << "Press E to go back: " << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'E' || choice == 'e')
        {

            return;
        }
        else
        {
            cout << "Invalid choice!" << endl;
            displayProfile();
        }
    }

    // function to change the password
    void changePassword()
    {
        // function changes the password and also from the file
        string newPassword;
        cout << "Enter your new password: ";
        getline(cin, newPassword);
        cout << "Press Y to confrim or E to go back: ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'Y' || choice == 'y')
        {
            if (checkPassword(newPassword))
            {
                // updating the password in the file
                fstream file;
                if (user_type == "Student")
                {
                    file.open("studentspasswords.txt", ios::in); // opening the file in read mode for student
                }
                else if (user_type == "Teacher")
                {
                    file.open("Teacherpasswords.txt", ios::in); // opening the file in read mode for teacher
                }

                string line;
                string temp;
                while (getline(file, line))
                {
                    if (line == this->password) // if the line is the old password
                    {
                        line = newPassword;           // replace it with the new password
                        this->password = newPassword; // update the password in the object
                    }
                    temp += line + "\n"; // add the line to the temp string
                }
                cout << "\nPassword changed successfully!" << endl;
            }
            else
            {
                cout << "\nPassword must have minimum of 6 length. The password must contain uppercase, lowercase, numeric digit, and special characters." << endl;
                changePassword();
            }
        }
        else if (choice == 'E' || choice == 'e')
        {
            return;
        }
        else
        {
            cout << "\nInvalid choice!" << endl;
            changePassword();
        }
    }

    // function to calculate the string length
    int Len(string str)
    {
        int length = 0;
        for (int i = 0; str[i] != '\0'; i++)
        {
            length++;
        }
        return length;
    }
};

// student class
class Student : public User // inheriting the User class
{
private:
    string courses[11]; // array of courses
public:
    // default constructor
    Student() : User()
    {
    }

    // parameterized constructor
    Student(string _name, string _password, string _id) : User(_name, _password, _id)
    {
    }

    // setter
    void setCourses(string _courses, int index)
    {
        courses[index] = _courses;
    }
    // getter
    string getCourses(int index)
    {
        return courses[index];
    }

    // studnet login function
    void StudentLogin()
    {
        string _name;
        string _id;
        string _password;
        cout << "\t\t\t\t\t\t  ***Student Login***" << endl;
        cout << "Enter your name: ";
        getline(cin, _name);
        cout << "Enter your Student ID: ";
        getline(cin, _id);
        stuID = _id;
        // checking if the id is valid or not
        if (!checkID(_id))
        {
            cout << "\nID is incorrect" << endl;
            cout << "Make sure your ID is in correct format eg. 22I-2841" << endl;
            // calling the login function again
            StudentLogin();
        }

        cout << "Enter your password: ";
        // getline(cin, _password);
        cin >> _password;
        // password asterisks
        for (int i = 0; i < Len(_password); i++)
        {
            cout << "*";
        }
        // checking if the password is valid or not
        if (!checkPassword(_password))
        {
            cout << "\nPassword is incorrect" << endl;
            cout << "Make sure your password has minimum of 6 length. \nThe password must contain uppercase, lowercase, numeric digit, and special characters." << endl;
            // calling the login function again
            StudentLogin();
        }
        // Asking user to press Y to continue or E to go back to the login menu
        cout << "\nPress \'Y\' to login or \'E\' to go back: ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'Y' || choice == 'y')
        {
            // checking if the user exist or not( reading the name from the csv file)
            setName(_name);
            setId(_id);
            setPassword(_password);
            cout << "\t\t\t\t\t\t     loading..." << endl;
            if (!StudentAuthentication())
            {
                cout << "\nUser does not exist" << endl;
                cout << "Make sure you have entered the correct Name, ID and password" << endl;
                // calling the login function again
                StudentLogin();
            }
            else if (StudentAuthentication())
            {
                cout << "\n\t\t\t\t\t\t     Login Successful!" << endl;
                // calling the student menu function
                StudentMenu();
            }
        }
        else if (choice == 'E' || choice == 'e')
        {
            loginMenu(); // returning to the login menu
        }
        else
        {
            cout << "Invalid input" << endl;
            // calling the login function again
            StudentLogin();
        }
    }

    // function that reads the csv file and checks if the NU ID is in the csv file or not and if exist then its a student otherwise its a teacher csv file name: Course Registration Data - Sheet1.csv
    bool StudentAuthentication()
    {
        bool foundUser = false, passwordFound = false;
        ifstream file("Course Registration.csv"); // opening the csv file
        if (file.is_open())
        {
            string line;
            getline(file, line); // Skip the header line

            while (getline(file, line))
            {
                // Split the line into a stringstream
                stringstream ss(line); // using string stream to split the line
                string roll_no, id, name;
                getline(ss, roll_no, ','); // getting the roll no
                getline(ss, id, ',');
                getline(ss, name, ',');

                // Compare the id and name
                if (id == getId() && name == getName()) // if the id and name matches then the user is a student
                {
                    foundUser = true;
                    break;
                }
            }

            file.close();
        }

        ifstream file2("Studentpassword.txt"); // opening the student password file

        if (file2.is_open())
        {
            string line;
            getline(file, line);
            while (getline(file2, line)) // reading the file line by line
            {
                stringstream ss(line); // using string stream to split the line
                string name, _password;
                getline(ss, name, ','); // getting the name
                getline(ss, _password, ',');

                // Print the retrieved name and password for debugging
                /*cout << "Retrieved name: " << name << endl;
                cout << "Retrieved password: " << _password << endl;
                cout << "Entered name: " << getName() << endl;
                cout << "Entered password: " << getPassword() << endl;*/

                // Compare the name and password
                if (name == getName() && _password == getPassword()) // if the name and password matches then the user is a student
                {
                    passwordFound = true;
                    break;
                }
            }
            file2.close();
        }

        if (foundUser && passwordFound)
        {
            setUserType("Student");
            return true;
        }

        else if (foundUser == false && passwordFound == false)
        {
            return false;
        }

        return false;
    }

    // displaying the student menu
    void StudentMenu(); // function prototype

    // function to display the enrolled courses
    void viewEnrolledCourses()
    {
        // saving the courses in a string array
        getStudentCourses(courses);
        cout << "\n\t\t\t\t\t\t  ***Enrolled Courses***" << endl;
        cout << "Your enrolled courses are: " << endl;
        // displaying the courses that are enrolled
        if (courses[0] == "1")
        {
            cout << ">CS 101-Programming Fundamentals" << endl;
        }

        if (courses[1] == "1")
        {
            cout << ">CS 201-Object Oriented Programming" << endl;
        }

        if (courses[3] == "1")
        {
            cout << ">CS 301-Data Structures" << endl;
        }

        if (courses[4] == "1")
        {
            cout << ">CS 302-Analysis of Algorithms" << endl;
        }

        if (courses[5] == "1")
        {
            cout << ">SE 301-Software Requirements Engineering" << endl;
        }

        if (courses[6] == "1")
        {
            cout << ">CS 501-Research Methodology" << endl;
        }

        if (courses[7] == "1")
        {
            cout << ">CS 407-Big Data Analytics" << endl;
        }

        if (courses[8] == "1")
        {
            cout << ">CS 307-Artificial Intelligence" << endl;
        }

        if (courses[9] == "1")
        {
            cout << ">CS 601-Deep Learning" << endl;
        }

        if (courses[10] == "1")
        {
            cout << ">CS 409-Digital Image Processing" << endl;
        }

        else if (courses[0] == "0" && courses[1] == "0" && courses[2] == "0" && courses[3] == "0" && courses[4] == "0" && courses[5] == "0" && courses[6] == "0" && courses[7] == "0" && courses[8] == "0" && courses[9] == "0" && courses[10] == "0")
        {
            cout << "You are not enrolled in any course" << endl;
        }

        cout << "\nPress E to go back to the student menu" << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'E' || choice == 'e')
        {
            StudentMenu();
        }
        else
        {
            cout << "Invalid input" << endl;
            viewEnrolledCourses();
        }
    }
};

// teacher class
class Teacher : public User // inheriting the User class
{
private:
    string course[11];
    string assignedCourse; // course assigned to the teacher

public:
    // default constructor
    Teacher() : User()
    {
        this->assignedCourse = "";
    }

    // parameterized constructor
    Teacher(string _name, string _id, string _password, string _course, int _num_of_students) : User(_name, _id, _password)
    {
        this->assignedCourse = _course;
    }

    // setter function
    void setCourse(string _course, int index)
    {
        this->course[index] = _course;
    }
    void setassignedCourse(string _course)
    {
        this->assignedCourse = _course;
    }

    // getter function
    string getCourse(int i)
    {
        return this->course[i];
    }
    string getassignedCourse()
    {
        return this->assignedCourse;
    }

    // login menu for teacher
    void TeacherLogin()
    {
        cout << "\n\t\t\t\t\t\t  ***Teacher Login***" << endl;
        cout << "Enter your name: ";
        string _name;
        getline(cin, _name);
        cout << "Enter your ID: ";
        string _id;
        getline(cin, _id);
        teacherID = _id;
        // checking if id is valid or not
        if (!checkID(_id))
        {
            cout << "Invalid ID" << endl;
            cout << "Make sure your ID is in correct format eg. 22I-2841" << endl;
            TeacherLogin(); // calling the login function again
        }

        cout << "Enter your password: ";
        string _password;
        getline(cin, _password);
        // displaying password in *
        for (int i = 0; i < Len(_password); i++)
        {
            cout << "*";
        }
        cout << endl;
        // checking if the password is in correct format or not
        if (!checkPassword(_password))
        {
            cout << "Invalid password" << endl;
            cout << "Make sure your password has minimum of 6 length. \nThe password must contain uppercase, lowercase, numeric digit, and special characters." << endl;
            TeacherLogin(); // calling the login function again
        }

        // Asking user to press Y to continue or E to go back to the login menu
        cout << "\nPress \'Y\' to login or \'E\' to go back: ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'Y' || choice == 'y')
        {
            // checking if the user exist or not( reading the name from the csv file)
            setName(_name);
            setId(_id);
            setPassword(_password);
            cout << "\t\t\t\t\t\t     loading..." << endl;
            if (!TeacherAuthentication())
            {
                cout << "\nUser does not exist" << endl;
                cout << "Make sure you have entered the correct Name, ID and password" << endl;
                // calling the login function again
                TeacherLogin();
            }
            else if (TeacherAuthentication())
            {
                cout << "\n\t\t\t\t\t\t     Login Successful!" << endl;
                // calling the teacher menu function
                TeacherMenu();
            }
        }
        else if (choice == 'E' || choice == 'e')
        {
            // calling the login function again
            loginMenu();
        }
        else
        {
            cout << "Invalid input" << endl;
            TeacherLogin(); // calling the login function again
        }
    }

    // menu for teacher prototype
    void TeacherMenu();

    // function that verify if the teacher id is valid or not by checking the name and id from the csv file
    bool TeacherAuthentication()
    {
        bool foundUser = false;
        fstream file("Teachers data.csv");
        if (file.is_open())
        {
            string line;
            getline(file, line); // Skip the header line
            while (getline(file, line))
            {
                // Parse the line
                stringstream ss(line);
                string roll_no, id, name;
                getline(ss, roll_no, ',');
                getline(ss, id, ',');
                getline(ss, name, ',');

                // Compare the id and name
                if (id == getId() && name == getName())
                {
                    foundUser = true;
                    break;
                }
            }
            file.close();
        }

        bool passwordFound = false;
        ifstream file2("Teacherpassword.txt");

        if (file2.is_open())
        {
            string line;
            getline(file, line);
            while (getline(file2, line))
            {
                stringstream ss(line);
                string name, _password;
                getline(ss, name, ',');
                getline(ss, _password, ',');

                if (name == getName() && _password == getPassword())
                {
                    passwordFound = true;
                    break;
                }
            }
            file2.close();
        }

        if (foundUser && passwordFound)
        {
            this->setUserType("Teacher");
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }

    // function that displays the assigned courses to the teacher
    void ViewAssignedCourses()
    {
        cout << "\n\t\t\t\t\t\t  ***Assigned Courses***" << endl;
        cout << "Courses: " << endl;
        // calling AssigningCourses function
        getTeacherCourses(course);

        // checking which courses are assigned to the teacher
        if (course[0] == "1")
        {
            assignedCourse = "CS 101-Programming Fundamentals";
            cout << ">CS 101-Programming Fundamentals" << endl;
        }

        else if (course[1] == "1")
        {
            assignedCourse = "CS 201-Object Oriented Programming";
            cout << ">CS 201-Object Oriented Programming" << endl;
        }

        else if (course[3] == "1")
        {
            assignedCourse = "CS 301-Data Structures";
            cout << ">CS 301-Data Structures" << endl;
        }

        else if (course[4] == "1")
        {
            assignedCourse = "CS 302-Analysis of Algorithms";
            cout << ">CS 302-Analysis of Algorithms" << endl;
        }

        else if (course[5] == "1")
        {
            assignedCourse = "SE 301-Software Requirements Engineering";
            cout << ">SE 301-Software Requirements Engineering" << endl;
        }

        else if (course[6] == "1")
        {
            assignedCourse = "CS 501-Research Methodology";
            cout << ">CS 501-Research Methodology" << endl;
        }

        else if (course[7] == "1")
        {
            assignedCourse = "CS 407-Big Data Analytics";
            cout << ">CS 407-Big Data Analytics" << endl;
        }

        else if (course[8] == "1")
        {
            assignedCourse = "CS 307-Artificial Intelligence";
            cout << ">CS 307-Artificial Intelligence" << endl;
        }

        else if (course[9] == "1")
        {
            assignedCourse = "CS 601-Deep Learning";
            cout << ">CS 601-Deep Learning" << endl;
        }

        else if (course[10] == "1")
        {
            assignedCourse = "CS 409-Digital Image Processing";
            cout << ">CS 409-Digital Image Processing" << endl;
        }

        else if (course[0] == "0" && course[1] == "0" && course[2] == "0" && course[3] == "0" && course[4] == "0" && course[5] == "0" && course[6] == "0" && course[7] == "0" && course[8] == "0" && course[9] == "0" && course[10] == "0")
        {
            cout << "You are not assigned with any course" << endl;
        }

        cout << "\nPress E to go back to the teachet menu" << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'E' || choice == 'e')
        {
            TeacherMenu(); // calling the teacher menu function
        }

        else
        {
            cout << "Invalid input" << endl;
            ViewAssignedCourses();
        }
    }
};

// QuestionBank class to store from csv into array and also create questions
class QuestionBank // composition of teacher class
{
private:
    int num_qs;
    string MCQs[100][6];
    string TrueFalse[100][2];
    string textQs[100];

public:
    // default constructor
    QuestionBank()
    {
        num_qs = 0;
    }

    // function that allows the teacher to create Qs and also store them in the csv file
    void createQs()
    {
        // menu for creating Qs
        cout << "\n\t\t\t\t\t\t  ***Create Questions***" << endl;
        cout << "Press 1 to create MCQs" << endl;
        cout << "Press 2 to create True/False" << endl;
        cout << "Press 3 to create Descriptive Questions" << endl;
        cout << "Press 4 to test the questions" << endl;
        cout << "Press E to go back to the teacher menu" << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == '1')
        {
            createMCQS(); // calling the createMCQS function
        }

        else if (choice == '2')
        {
            createTrueFalse(); // calling the createTrueFalse function
        }

        else if (choice == '3')
        {
            createTextQs(); // calling the createTextQs function
        }

        else if (choice == '4')
        {
            inputQs(); // calling the inputQs function
        }

        else if (choice == 'E' || choice == 'e')
        {
            Teacher t1; // compostion of teacher class
            t1.TeacherMenu(); // calling the teacher menu function
        }

        else
        {
            cout << "Invalid input" << endl;
            createQs();
        }
    }

    // function that lets the teacher input the questions from the txt file
    void createMCQS()
    {
        string courses[11];         // array to store the courses
        getTeacherCourses(courses); // calling function to get thr courses assigned to the teacher
        ofstream file;
        // checking which courses are assigned to the teacher
        if (courses[0] == "1")
        {

            file.open("Programming_Fundamentals_Bank.txt", ios::app); // opening the file in append mode
        }

        else if (courses[1] == "1")
        {
            file.open("Object_Oriented_Programming_Bank.txt", ios::app);
        }

        else if (courses[3] == "1")
        {
            file.open("Data_Structures_Bank.txt", ios::app);
        }

        else if (courses[4] == "1")
        {
            file.open("Analysis_of_Algorithms_Bank.txt", ios::app);
        }

        else if (courses[5] == "1")
        {
            file.open("Software_Requirements_Engineering_Bank.txt", ios::app);
        }

        else if (courses[6] == "1", ios::in)
        {
            file.open("Research_Methodology_Bank.txt", ios::app);
        }

        else if (courses[7] == "1")
        {
            file.open("Big_Data_Analytics_Bank.txt", ios::app);
        }

        else if (courses[8] == "1")
        {
            file.open("Artificial_Intelligence_Bank.txt", ios::app);
        }

        else if (courses[9] == "1")
        {
            file.open("Deep_Learning_Bank.txt", ios::app);
        }

        else if (courses[10] == "1")
        {
            file.open("Digital_Image_Processing_Bank.txt", ios::app);
        }

        string line;
        string options[4];
        int optionIndex = 0;
        bool isCorrectOption = false;

        string question;

        // Take input from the user for the question
        cout << "Enter the MCQ question: ";
        getline(cin, question);

        if (file)
        {
            // Write the question to the file
            file << endl;
            file << "2efcde9" << endl;
            file << question << endl;

            // Take input for options and write to the file
            for (int i = 1; i <= 4; i++)
            {
                cout << "Enter option " << i << ": ";
                getline(cin, options[optionIndex]);
                optionIndex++;
            }

            string correctOption;

            // Take input for the correct option and write to the file
            cout << "Enter the correct option: ";
            getline(cin, correctOption);

            file << "Option: " << options[0] << endl;
            file << "Option: " << options[1] << endl;
            file << "Option dabfac4: " << correctOption << endl;
            file << "Option: " << options[3] << endl;

            // asking user if they want to add more questions
            cout << "Do you want to add more questions? (Y/N): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'Y' || choice == 'y')
            {
                createMCQS(); // calling the createMCQS function
            }

            else if (choice == 'N' || choice == 'n')
            {
                // close the file
                file.close();
                createQs(); // calling the createQs function
            }

            else
            {
                // close the file
                file.close();
                cout << "Invalid input" << endl;
                createQs();
            }
        }
    }

    // function that lets the teacher input the questions from the txt file
    void createTrueFalse()
    {
        string courses[11];         // array to store the courses
        getTeacherCourses(courses); // calling function to get thr courses assigned to the teacher
        ofstream file;
        // will open the file based on the course assigned to the teacher
        // checking which courses are assigned to the teacher
        // displaying the courses assigned to the teacher
        if (courses[0] == "1")
        {

            file.open("Programming_Fundamentals_Bank.txt", ios::app); // opening the file in append mode
        }

        else if (courses[1] == "1")
        {
            file.open("Object_Oriented_Programming_Bank.txt", ios::app);
        }

        else if (courses[3] == "1")
        {
            file.open("Data_Structures_Bank.txt", ios::app);
        }

        else if (courses[4] == "1")
        {
            file.open("Analysis_of_Algorithms_Bank.txt", ios::app);
        }

        else if (courses[5] == "1")
        {
            file.open("Software_Requirements_Engineering_Bank.txt", ios::app);
        }

        else if (courses[6] == "1", ios::in)
        {
            file.open("Research_Methodology_Bank.txt", ios::app);
        }

        else if (courses[7] == "1")
        {
            file.open("Big_Data_Analytics_Bank.txt", ios::app);
        }

        else if (courses[8] == "1")
        {
            file.open("Artificial_Intelligence_Bank.txt", ios::app);
        }

        else if (courses[9] == "1")
        {
            file.open("Deep_Learning_Bank.txt", ios::app);
        }

        else if (courses[10] == "1")
        {
            file.open("Digital_Image_Processing_Bank.txt", ios::app);
        }

        string question;

        // Take input from the user for the question
        cout << "Enter the True False question: ";
        getline(cin, question);

        while (file)
        {
            // writing data in file
            file << endl;
            file << "b94d27b" << endl;
            file << question << endl;

            string option[2];
            option[0] = "True";
            option[1] = "False";

            string correctOption;

            // Take input for the correct option and write to the file
            cout << "Enter the correct option: ";
            getline(cin, correctOption);
            if (correctOption == "True")
            {
                file << "Option dabfac4: " << correctOption << endl;
                file << "Option: " << option[1] << endl;
            }
            else if (correctOption == "False")
            {
                file << "Option: " << option[0] << endl;
                file << "Option dabfac4: " << correctOption << endl;
            }

            // asking user if they want to add more questions
            cout << "Do you want to add more questions? (Y/N): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'Y' || choice == 'y')
            {
                createTrueFalse(); // calling the createMCQS function
            }

            else if (choice == 'N' || choice == 'n')
            {
                // close the file
                file.close();
                createQs(); // calling the createQs function
            }

            else
            {
                // close the file
                file.close();
                cout << "Invalid input" << endl;
                createQs();
            }
        }
    }

    // function that lets the teacher input the questions from the txt file
    void createTextQs()
    {
        string courses[11];         // array to store the courses
        getTeacherCourses(courses); // calling function to get thr courses assigned to the teacher
        ofstream file;
        // will open thw file based on the course assigned to the teacher
        // checking which courses are assigned to the teacher
        // displaying the courses assigned to the teacher

        if (courses[0] == "1")
        {

            file.open("Programming_Fundamentals_Bank.txt", ios::app); // opening the file in append mode
        }

        else if (courses[1] == "1")
        {
            file.open("Object_Oriented_Programming_Bank.txt", ios::app);
        }

        else if (courses[3] == "1")
        {
            file.open("Data_Structures_Bank.txt", ios::app);
        }

        else if (courses[4] == "1")
        {
            file.open("Analysis_of_Algorithms_Bank.txt", ios::app);
        }

        else if (courses[5] == "1")
        {
            file.open("Software_Requirements_Engineering_Bank.txt", ios::app);
        }

        else if (courses[6] == "1", ios::in)
        {
            file.open("Research_Methodology_Bank.txt", ios::app);
        }

        else if (courses[7] == "1")
        {
            file.open("Big_Data_Analytics_Bank.txt", ios::app);
        }

        else if (courses[8] == "1")
        {
            file.open("Artificial_Intelligence_Bank.txt", ios::app);
        }

        else if (courses[9] == "1")
        {
            file.open("Deep_Learning_Bank.txt", ios::app);
        }

        else if (courses[10] == "1")
        {
            file.open("Digital_Image_Processing_Bank.txt", ios::app);
        }

        string question;

        // Take input from the user for the question
        cout << "Enter the Descriptive question: ";
        getline(cin, question);

        if (file)
        {
            file << endl;
            file << "88f7ace" << endl;
            file << question << endl;

            // asking user if they want to add more questions
            cout << "Do you want to add more questions? (Y/N): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'Y' || choice == 'y')
            {
                createTextQs(); // calling the createMCQS function
            }

            else if (choice == 'N' || choice == 'n')
            {
                // close the file
                file.close();
                createQs(); // calling the createQs function
            }

            else
            {
                // close the file
                file.close();
                cout << "Invalid input" << endl;
                createQs();
            }
        }
    }

    //  This function inputs the questions from the txt file in the arrays based on the type of question
    void inputQs()
    {
        string courses[11]; // array to store the courses
        const int MAX_MCQS = 5;
        const int MAX_TRUE_FALSE = 5;
        const int MAX_TEXT_QS = 2;
        const int MAX_OPTIONS = 4;
        const int MAX_ANSWER_LENGTH = 100;
        getTeacherCourses(courses); // calling function to get thr courses assigned to the teacher
        ifstream file;
        // will open thw file based on the course assigned to the teacher
        // checking which courses are assigned to the teacher
        // displaying the courses assigned to the teacher

        if (courses[0] == "1")
        {

            file.open("Programming_Fundamentals_Bank.txt", ios::in); // opening the file in append mode
        }

        else if (courses[1] == "1")
        {
            file.open("Object_Oriented_Programming_Bank.txt", ios::in);
        }

        else if (courses[3] == "1")
        {
            file.open("Data_Structures_Bank.txt", ios::in);
        }

        else if (courses[4] == "1")
        {
            file.open("Analysis_of_Algorithms_Bank.txt", ios::in);
        }

        else if (courses[5] == "1")
        {
            file.open("Software_Requirements_Engineering_Bank.txt", ios::in);
        }

        else if (courses[6] == "1", ios::in)
        {
            file.open("Research_Methodology_Bank.txt", ios::in);
        }

        else if (courses[7] == "1")
        {
            file.open("Big_Data_Analytics_Bank.txt", ios::in);
        }

        else if (courses[8] == "1")
        {
            file.open("Artificial_Intelligence_Bank.txt", ios::in);
        }

        else if (courses[9] == "1")
        {
            file.open("Deep_Learning_Bank.txt", ios::in);
        }

        else if (courses[10] == "1")
        {
            file.open("Digital_Image_Processing_Bank.txt", ios::in);
        }

        string line;
        string currentTopic;
        string currentType;
        int mcqIndex = 0;
        int trueFalseIndex = 0;
        int textQsIndex = 0;

        while (getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }

            if (line == "a5380ee")
            {
                // Read the topic title
                getline(file, currentTopic);
            }
            else if (line == "2efcde9")
            { // MCQs
                currentType = "MCQ";
                string question;
                string options[MAX_OPTIONS];
                string answerMarker;

                // Read the question
                getline(file, question);

                // Read the options
                string answer;
                int count = 0;
                for (int i = 0; i < MAX_OPTIONS; i++)
                {
                    getline(file, line);
                    if (line.find("dabfac4") != string::npos)
                    {
                        line.erase(7, 8); // Erase the answer marker
                        // Store the answer
                        if (count == 0)
                        {
                            answer = "A";
                        }
                        else if (count == 1)
                        {
                            answer = "B";
                        }
                        else if (count == 2)
                        {
                            answer = "C";
                        }
                        else if (count == 3)
                        {
                            answer = "D";
                        }
                    }
                    options[count] = line;
                    count++;
                }

                // Store the question, options, and answer in the MCQs array
                MCQs[mcqIndex][0] = question;
                for (int i = 0; i < MAX_OPTIONS; i++)
                {
                    MCQs[mcqIndex][i + 1] = options[i];
                }
                MCQs[mcqIndex][5] = answer;
                mcqIndex++;
            }

            else if (line == "b94d27b")
            { // True/False Questions
                currentType = "True/False";
                string question;
                string answerMarker;

                // Read the question
                getline(file, question);
                TrueFalse[trueFalseIndex][0] = question;

                // Read the answer marker
                getline(file, line);
                int count = 0;
                for (int i = 0; i < 2; i++)
                {
                    if (line.find("dabfac4") != string::npos)
                    {
                        // Found the answer marker
                        answerMarker = line;
                        line.erase(line.find("dabfac4"));
                        // Store the answer
                        if (count == 0)
                        {
                            TrueFalse[trueFalseIndex][3] = "True";
                        }
                        else if (count == 1)
                        {
                            TrueFalse[trueFalseIndex][3] = "False";
                        }
                    }
                    count++;
                }

                // Store the question and answer in the TrueFalse array
                TrueFalse[trueFalseIndex][1] = "True";
                TrueFalse[trueFalseIndex][2] = "False";
                trueFalseIndex++;
            }

            else if (line == "88f7ace")
            { // Descriptive Questions
                currentType = "Descriptive";
                string question;

                // Read the question
                getline(file, question);

                // Store the question in the textQs array
                textQs[textQsIndex] = question;

                textQsIndex++;
            }
        }

        file.close();

        // Testing
        /* cout << "MCQs:" << endl;
          for (int i = 0; i < MAX_MCQS; i++)
          {
              cout << i + 1 << "Q:" << MCQs[i][0] << endl;
              for (int j = 1; j <= 4; j++)
              {
                  cout << j << ": " << MCQs[i][j] << endl;
              }
              cout << "Answer: " << MCQs[i][5] << endl;
              cout << endl;
          }

          // Display the True/False questions
          cout << "True/False Questions:" << endl;
          for (int i = 0; i < MAX_TRUE_FALSE; i++)
          {
              cout << "Question " << i + 1 << ":" << TrueFalse[i][0] << endl;
              cout << TrueFalse[i][1] << endl;
              cout << TrueFalse[i][2] << endl;
              cout << "Answer: " << TrueFalse[i][3] << endl;
              cout << endl;
          }

          // Display the Descriptive questions
          cout << "Descriptive Questions:" << endl;
          for (int i = 0; i < 6; i++)
          {
              cout << "Question " << i + 1 << ":" << textQs[i] << endl;
          }*/
    }

    // getter method
    string getMCQs(int row, int col)
    {
        inputQs(); // calling the inputQs function to get the MCQs from the file,
        return MCQs[row][col];
    }

    string getTrueFalse(int row, int col)
    {
        inputQs(); // calling the inputQs function to get the TrueFalse Qs from the file,
        return TrueFalse[row][col];
    }

    string getTextQs(int row)
    {
        inputQs(); // calling the inputQs function to get the Descriptive Qs from the file,
        return textQs[row];
    }
};

// SetQuiz class where teacher can set the quiz with number of Qs, date n time and total marks
class SetQuiz // composition of the QuestionBank class
{
private:
    int totalQs;
    int totalMarks;
    string startDate;
    string quizQs[100][6];
    string quizAns[100];
    int startTime;
    string endDate;
    int endTime;
    string Qtype;

public:
    // default constructor
    SetQuiz()
    {
        totalQs = 0;
        totalMarks = 0;
        startDate = "0";
        startTime = 0;
        endDate = "0";
        endTime = 0;
    }

    // function that sets the MCQs quiz
    void setMCQs()
    {

        // copying the fromm the MCQ array in the Question Bank Class to the quizQs array
        QuestionBank QB1; // compostion of the QuestionBank class
        // storing the total number of MCQS and there options
        for (int i = 0; i < totalQs; i++)
        {
            quizQs[i][0] = QB1.getMCQs(i, 0);
            quizQs[i][1] = QB1.getMCQs(i, 1);
            quizQs[i][2] = QB1.getMCQs(i, 2);
            quizQs[i][3] = QB1.getMCQs(i, 3);
            quizQs[i][4] = QB1.getMCQs(i, 4);
        }

        // storing the answers of the MCQs in the quizAns array
        for (int i = 0; i < totalQs; i++)
        {
            quizAns[i] = QB1.getMCQs(i, 5);
        }

        // testing thd code displaying the Qs and the options and the answers
        /* for (int i = 0; i < totalQs; i++)
         {
             cout << "Question" << i << ": " << quizQs[i][0] << endl;
             cout << "1: " << quizQs[i][1] << endl;
             cout << "2: " << quizQs[i][2] << endl;
             cout << "3: " << quizQs[i][3] << endl;
             cout << "4: " << quizQs[i][4] << endl;
         }

         for (int i = 0; i < totalQs; i++)
         {
             cout << "Answer: " << quizAns[i] << endl;
         }*/
    }

    // function that sets the True/False quiz
    void setTrueFalse()
    {

        // storing True False Qs and options from the Question Bank Class to the quizQs array
        QuestionBank QB1; // compostion of the QuestionBank class
        for (int i = 0; i < totalQs; i++)
        {
            quizQs[i][0] = QB1.getTrueFalse(i, 0); // stores Q
            quizQs[i][1] = QB1.getTrueFalse(i, 1); // stores true
            quizQs[i][2] = QB1.getTrueFalse(i, 2); // stores false
        }

        // storing the answers of the True False Qs in the quizAns array
        for (int i = 0; i < totalQs; i++)
        {
            quizAns[i] = QB1.getTrueFalse(i, 3); // stoes answer
        }

        // testing the code displaying the quizQs there options and quizAns
        /*for (int i = 0; i < totalQs; i++)
        {
            cout << "Question" << i << ": " << quizQs[i][0] << endl;
            cout << "1.True" << endl;
            cout << "2.False" << endl;
        }

        // displays the answers
        for (int i = 0; i < totalQs; i++)
        {
            cout << "Answer: " << quizAns[i] << endl;
        }*/
    }

    // function that sets the Text Qs quiz
    void setTextQs()
    {

        // storing the textQs in the quizQs array
        QuestionBank QB1; // compostion of the QuestionBank class
        for (int i = 0; i < totalQs; i++)
        {
            quizQs[i][0] = QB1.getTextQs(i); // stores the textQs
        }

        // no need to store the answers of the textQs as they are descriptive

        // Displaying
        /*for (int i = 0; i < totalQs; i++)
        {
            cout << "Question" << i << ": " << quizQs[i][0] << endl;
        }*/
    }

    // function that allows the teacher to set the quiz start date and time plus the end date and time
    bool quizDuration()
    {
        getData();
        // Get the current time
        time_t currentTime = time(nullptr);
        tm *currentTm = localtime(&currentTime);

        // convert the current time to string
        tm quizStartTm{};                                      // Initialize all members to 0
        strptime(startDate.c_str(), "%d %b %Y", &quizStartTm); // convert string to time
        quizStartTm.tm_hour = startTime / 100;                 // convert the start time to hours
        quizStartTm.tm_min = startTime % 100;                  // convert the start time to minutes
        time_t quizStartTime = mktime(&quizStartTm);           // convert the start time to time_t

        // convert the end time to string
        tm quizEndTm{};                                    // Initialize all members to 0
        strptime(endDate.c_str(), "%d %b %Y", &quizEndTm); // convert string to time
        quizEndTm.tm_hour = endTime / 100;                 // convert the end time to hours
        quizEndTm.tm_min = endTime % 100;                  // convert the end time to minutes
        time_t quizEndTime = mktime(&quizEndTm);           // convert the end time to time_t

        // Check if the current time is within the quiz time window
        /*cout << "Current time: " << ctime(&currentTime) << endl;
        cout << "Quiz start time: " << ctime(&quizStartTime) << endl;
        cout << "Quiz end time: " << ctime(&quizEndTime) << endl;*/
        if (currentTime >= quizStartTime && currentTime <= quizEndTime)
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    // function that allow the teacher to chose from different options to set the quiz(menu)
    void quizMenu()
    {
        Teacher t1;
        cout << "\n\t\t\t\t\t\t  ***Set Quiz***" << endl;
        cout << "Press 1 to set the type of questions" << endl;
        cout << "Press E to go back to the teacher menu" << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        ofstream file("data.txt");
        if (choice == '1')
        {
            cout << "Press 1 to set MCQs" << endl;
            cout << "Press 2 to set True/False" << endl;
            cout << "Press 3 to set Text Questions" << endl;
            cout << "Press E to go back " << endl;
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == '1')
            {
                Qtype = "MCQ";
                file << "MCQ";
                file << endl;
            }

            else if (choice == '2')
            {
                Qtype = "TrueFalse";
                file << "TrueFalse";
                file << endl;
            }

            else if (choice == '3')
            {
                Qtype = "TextQs";
                file << "TextQs";
                file << endl;
            }

            else if (choice == 'E' || choice == 'e')
            {
                quizMenu(); // calling the quiz menu function
            }

            else
            {
                cout << "Invalid input" << endl;
                quizMenu();
            }
        }
        cout << "Enter the total number of questions: ";
        cin >> totalQs;
        file << to_string(totalQs);
        file << endl;

        cout << "Enter the total marks: ";
        cin >> totalMarks;
        file << to_string(totalMarks);
        file << endl;

        if (totalMarks <= 0)
        {
            cout << "Invalid input" << endl;
            cout << "Total Marks must be greater than 0" << endl;
            cout << "Press E to go back" << endl;
            cin >> choice;
            cin.ignore();
            if (choice == 'E' || choice == 'e')
            {
                quizMenu(); // calling the quiz menu function
            }

            else
            {
                cout << "Invalid input" << endl;
                quizMenu();
            }
        }

        cin.ignore();
        cout << "Set the start date of the quiz(eg.29 Apr 2023): ";
        getline(cin, startDate);
        // if user inputs in the wrong format then will ask user to input the information again
        while (startDate.length() != 11)
        {
            cout << "Invalid input" << endl;
            cout << "Set the start date of the quiz(eg.29 Apr 2023): ";
            getline(cin, startDate);
        }
        file << startDate;
        file << endl;

        cout << endl;
        cout << "Set the start time of the quiz(eg.1600): ";
        cin >> startTime;
        cin.ignore();
        // if user inputs in the wrong format then will ask user to input the information again
        while (startTime < 0 || startTime > 2359)
        {
            cout << "Invalid input" << endl;
            cout << "Set the start time of the quiz(eg.1600): ";
            cin >> startTime;
        }
        file << to_string(startTime);
        file << endl;
        cout << endl;

        cout << "Set the end date of the quiz(eg.29 Apr 2023): ";
        getline(cin, endDate);
        // if user inputs in the wrong format then will ask user to input the information again
        while (endDate.length() != 11)
        {
            cout << "Invalid input" << endl;
            cout << "Set the end date of the quiz(eg.29 Apr 2023): ";
            getline(cin, endDate);
        }
        file << endDate;
        file << endl;

        cout << endl;
        cout << "Set the end time of the quiz(eg.1700): ";
        cin >> endTime;
        cin.ignore();
        // if user inputs in the wrong format then will ask user to input the information again
        while (endTime < 0 || endTime > 2359)
        {
            cout << "Invalid input" << endl;
            cout << "Set the end time of the quiz(eg.1700): ";
            cin >> endTime;
        }
        file << to_string(endTime);
        file << endl;
        cout << endl;

        file.close(); // closing the file

        // testing
        if (quizDuration() == true)
        {
            if (Qtype == "MCQ")
            {
                setMCQs(); // calling the setMCQs function
            }

            else if (Qtype == "TrueFalse")
            {
                setTrueFalse(); // calling the setTrueFalse function
            }

            else if (Qtype == "TextQs")
            {
                setTextQs(); // calling the setTextQs function
            }
            cout << "\n\t\t\t\t\t\t***Quiz has been uploaded!***" << endl;
            file.close();
            getData();
        }

        else if (quizDuration() == false)
        {
            cout << "Error Quiz is not uploaded!" << endl;
            cout << "Kindly check if the start and end date/time you have entered are valid" << endl;
            cout << "Press E to go back" << endl;
            cin >> choice;
            cin.ignore();
            if (choice == 'E' || choice == 'e')
            {
                quizMenu(); // calling the quiz menu function
            }

            else
            {
                cout << "Invalid input" << endl;
                quizMenu();
            }
        }

        cout << "Press E to go back" << endl;
        cin >> choice;
        cin.ignore();
        if (choice == 'E' || choice == 'e')
        {
            t1.TeacherMenu(); // calling the quiz menu function
        }

        else
        {
            cout << "Invalid input" << endl;
            t1.TeacherMenu();
        }
    }

    // function that reads te data(start date ],start time, totalQs, totalMarks) that teacher input in the file
    void getData()
    {
        // will read data from the file
        fstream file("data.txt");

        string line, tq, tm, st, et;
        // read data from file in this format MCQ,3,33,9 May 2023,0,10 May 2023,2000, and save it into tq,tm,startDate,st,endDate,et
        stringstream ss(line);
        char comma;
        if (getline(file, Qtype))
        {
            getline(file, tq);
            getline(file, tm);
            getline(file, startDate);
            getline(file, st);
            getline(file, endDate);
            getline(file, et);
        }
        file.close();
        totalQs = stoi(tq); // converting string to int
        totalMarks = stoi(tm);
        startTime = stoi(st);
        endTime = stoi(et);
    }
    // getters
    string getstartDate()
    {
        return startDate;
    }

    string getendDate()
    {
        return endDate;
    }

    string getQuizQs(int row, int col)
    {
        return quizQs[row][col];
    }

    string getQuizAns(int row)
    {
        return quizAns[row];
    }

    string getQtype()
    {
        return Qtype;
    }

    int getStartTime()
    {
        return startTime;
    }

    int getendTime()
    {
        return endTime;
    }

    int gettotalMarks()
    {
        return totalMarks;
    }

    int gettotalQs()
    {
        return totalQs;
    }
};

// ConductQuiz class which allows the student to attempt the quiz also marks the students attendnace
class ConductQuiz : public SetQuiz // inheriting the set quiz class
{
private:
    bool attendance = false;
    double obtainedMarks;
    double marksPer_Q[100];
    bool quizAttempted = false;

public:
    // default constructor
    ConductQuiz()
    {
        attendance = false;
        obtainedMarks = 0;
    }

    // quiz menu
    void QuizMenu()
    {
        getData(); // calling the getData function
        // getting the courses of the students and teacher to check if the student is enrolled in the course for which the quiz is uplaoded
        string Tcourse[11], Scourse[11], c1 = "\0", c2 = "\0", c3 = "\0", c4 = "\0", c5 = "\0", c6 = "\0", c7 = "\0", c8 = "\0", c9 = "\0", c10 = "\0", c11 = "\0";
        Student stu; // object of student class
        getTeacherCourses(Tcourse);
        getStudentCourses(Scourse);
        // checking if the student is enrolled in taht course for which the teacher has uplaoded the quiz
        if ((Tcourse[0] == "1") && (Scourse[0] == "1"))
        {
            c1 = "Programming Fundamentals";
        }

        if ((Tcourse[1] == "1") && (Scourse[1] == "1"))
        {
            c2 = "Object Oriented Programming";
        }

        if ((Tcourse[2] == "1") && (Scourse[2] == "1"))
        {
            c3 = "Introduction To Computing";
        }

        if ((Tcourse[3] == "1") && (Scourse[3] == "1"))
        {
            c4 = "Data Structures";
        }

        if ((Tcourse[4] == "1") && (Scourse[4] == "1"))
        {
            c5 = "Analysis of Algorithms";
        }

        if ((Tcourse[5] == "1") && (Scourse[5] == "1"))
        {
            c6 = "Software Requirements Engineering";
        }

        if ((Tcourse[6] == "1") && (Scourse[6] == "1"))
        {
            c7 = "Research Methodology";
        }

        if ((Tcourse[7] == "1") && (Scourse[7] == "1"))
        {
            c8 = "Big Data Analytics";
        }

        if ((Tcourse[8] == "1") && (Scourse[8] == "1"))
        {
            c9 = "Artificial Intelligence";
        }

        if ((Tcourse[9] == "1") && (Scourse[9] == "1"))
        {
            c10 = "Deep Learning";
        }

        if ((Tcourse[10] == "1") && (Scourse[10] == "1"))
        {
            c11 = "Digital Image Processing";
        }

        // Displayinng the menu
        cout << "\n\t\t\t\t\t\t  ***Quiz Menu***" << endl;
        if (getStartTime() < 0)
        {
            cout << "No Quiz currently Available!" << endl;
        }

        else
        {
            cout << "Available Quizzes: " << endl;
            if (c1 != "\0")
            {
                cout << "> " << c1 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c2 != "\0")
            {
                cout << "> " << c2 << ", Start date: " << getstartDate() << " Time: " << getStartTime() << " End date: " << getendDate() << " Time: " << getendTime() << endl;
            }

            if (c3 != "\0")
            {
                cout << "> " << c3 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c4 != "\0")
            {
                cout << "> " << c4 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c5 != "\0")
            {
                cout << "> " << c5 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c6 != "\0")
            {
                cout << "> " << c6 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c7 != "\0")
            {
                cout << "> " << c7 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c8 != "\0")
            {
                cout << "> " << c8 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c9 != "\0")
            {
                cout << "> " << c9 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c10 != "\0")
            {
                cout << "> " << c10 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            if (c11 != "\0")
            {
                cout << "> " << c11 << ", Start date: " << getstartDate() << " Start Time: " << getStartTime() << " End date: " << getendDate() << " End Time: " << getendTime() << endl;
            }

            cout << "\nPress 1 to attempt the quiz" << endl;
            cout << "Press R to view the quiz result" << endl;
            cout << "Press E to go back to the student menu" << endl;
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == '1')
            {
                cout << "\nAre you sure you want to attempt the Quiz?" << endl;
                cout << "Note: once you start the quiz you \"cannot\" go back and the timer will automatic start" << endl;
                cout << "Press 'Y' for Yes" << endl;
                cout << "Press E to go back" << endl;
                char choice;
                cin >> choice;
                cin.ignore();
                if (choice == 'Y' || choice == 'y')
                {
                    attemptQuiz();
                }

                else if (choice == 'E' || choice == 'e')
                {
                    QuizMenu(); // calling the quiz menu function
                }

                else
                {
                    cout << "Invalid input" << endl;
                    QuizMenu();
                }
            }

            else if (choice == 'r' || choice == 'r')
            {
                viewResult(); // calling the view result function
            }

            else if (choice == 'E' || choice == 'e')
            {
                stu.StudentMenu(); // calling the student menu function
            }

            else
            {
                cout << "Invalid input" << endl;
                QuizMenu();
            }
        }
    }

    // function that allows the student to attempt quiz
    void attemptQuiz()
    {
        getData();
        bool flagTime = false; // flag to check if the quiz is available
        flagTime = quizDuration();
        if (flagTime == true)
        {
            quizAttempted = true;
            // marking students attendance
            markAttendance();

            cout << "\n\t\t\t\t\t\t  ***Attempt Quiz***" << endl;
            cout << "Total Marks : " << gettotalMarks() << endl;
            cout << "End Date: " << getendDate() << " , End Time: " << getendTime() << endl;
            cout << "\n\n";
            // checking if the quiz is MCQ or True False or Descriptive
            if (getQtype() == "MCQ")
            {
                // displaying the MCQs and options to the student
                setMCQs();
                string choice;
                double marksPerQ = gettotalMarks() / gettotalQs(); // calculating the marks per question

                cout << "\n\t\t\t\t\t\t Instructions: " << endl;
                cout << "For each question, enter the option of the correct answer(A,B,C or D)" << endl;
                cout << "Note: Inputing the wrong input will result in 0 marks for that question" << endl;
                cout << endl;

                // display Qs in Random order
                for (int i = 0; i < gettotalQs() && (flagTime == true); i++)
                {
                    // checkinh if time is over or not
                    flagTime = quizDuration();
                    if (flagTime == true)
                    {

                        int random = rand() % gettotalQs();                               // generating a random number
                        cout << "\nQuestion" << i + 1 << ": " << getQuizQs(i, 0) << endl; // displaying the question
                        cout << "A: " << getQuizQs(i, 1) << endl;                         // displaying the options
                        cout << "B: " << getQuizQs(i, 2) << endl;
                        cout << "C: " << getQuizQs(i, 3) << endl;
                        cout << "D: " << getQuizQs(i, 4) << endl;
                        // taking the input from the student
                        cout << "Enter your answer: ";
                        cin >> choice;
                        cin.ignore();

                        // checking if the answer is correct or not
                        if (choice == getQuizAns(i)) // if the answer is correct
                        {
                            obtainedMarks += marksPerQ; // adding the marks to the obtained marks
                            marksPer_Q[i] = marksPerQ;  // adding the marks per question to the array
                        }

                        else // if the answer is wrong
                        {
                            marksPer_Q[i] = 0; // adding the marks per question to the array
                        }
                    }
                }

                if (flagTime == true)
                {
                    cout << "\nTotal Marks: " << gettotalMarks() << endl;
                    cout << "Your obtained marks are: " << obtainedMarks << endl;
                }
            }

            else if (getQtype() == "TrueFalse")
            {
                // displaying the true false questions and options to the student
                setTrueFalse();

                string choice;
                double marksPerQ = gettotalMarks() / gettotalQs(); // calculating the marks per question
                cout << "\n\t\t\t\t\t\t Instructions: " << endl;
                cout << "For each question, enter the option of the correct answer(True or False)" << endl;
                cout << "Note: Inputing the wrong input will result in 0 marks for that question" << endl;
                cout << endl;

                // Displaying the Qs in random order
                for (int i = 0; i < gettotalQs() && (flagTime == true); i++)
                {
                    // checkinh if time is over or not
                    flagTime = quizDuration();
                    if (flagTime == true)
                    {
                        int randomIndex = rand() % gettotalQs(); // generating random index
                        cout << "\nQuestion" << i + 1 << ": " << getQuizQs(i, 0) << endl;
                        cout << "True" << endl;
                        cout << "False" << endl;
                        // taking the input from the student
                        cout << "Enter your answer: ";
                        cin >> choice;
                        cin.ignore();

                        // checking if the answer is correct or not
                        if (choice == getQuizAns(i)) // if the answer is correct
                        {
                            obtainedMarks += marksPerQ; // adding the marks to the obtained marks
                            marksPer_Q[i] = marksPerQ;  // adding the marks per question to the array
                        }

                        else
                        {
                            marksPer_Q[i] = 0;
                        }
                    }
                }

                if (flagTime == true)
                {
                    cout << "\nTotal Marks: " << gettotalMarks() << endl;
                    cout << "Your obtained marks are: " << obtainedMarks << endl;
                }
            }

            else if (getQtype() == "TextQs")
            {
                // displaying the descriptive questions to the student
                setTextQs();
                string choice;
                double marksPerQ = gettotalMarks() / gettotalQs(); // calculating the marks per question
                cout << "\n\t\t\t\t\t\t Instructions: " << endl;
                cout << "For each question, enter the answer" << endl;
                cout << "Note: Inputing the wrong input will result in 0 marks for that question" << endl;
                cout << endl;

                // Displaying the Qs in random order
                double marksPerQs; // 0.01 marks per character
                for (int i = 0; i < gettotalQs() && (flagTime == true); i++)
                {
                    // checkinh if time is over or not
                    flagTime = quizDuration();
                    if (flagTime == true)
                    {
                        int randomIndex = rand() % gettotalQs();                           // generating random index
                        cout << "\nQuestion " << i + 1 << ": " << getQuizQs(i, 0) << endl; // displaying the question
                                                                                           // taking the input from the student
                        cout << "Enter your answer: ";
                        getline(cin, choice);

                        // 0.01 marks per character
                        marksPerQs = 0;
                        marksPerQs += choice.length() * 0.01; // 0.01 marks per character
                        marksPer_Q[i] = marksPerQs;           // adding the marks per question to the array
                        obtainedMarks += marksPerQs;          // adding the marks to the obtained marks
                    }
                }

                if (flagTime == true)
                {
                    cout << "\nTotal Marks: " << gettotalMarks() << endl;
                    cout << "Your obtained marks are: " << obtainedMarks << endl;
                }
            }
        }

        if (flagTime == true)
        {
            // writing the marks into the file
            writeMarks();

            // asking student if want to view the result or go back
            Student stu; // composition
            cout << "\nDo you want to view the result? (Y/N): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'Y' || choice == 'y')
            {
                viewResult();
            }

            else if (choice == 'N' || choice == 'n')
            {
                cout << "You can view the result later" << endl;
                stu.StudentMenu();
            }

            else
            {
                cout << "Invalid input" << endl;
            }
        }

        // if the quiz time is up
        else if (flagTime == false)
        {
            cout << "\nQuiz time is up!" << endl;
            cout << "You cannot attempt the quiz now" << endl;
            cout << "Press E to go back to Student Menu: " << endl;
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice == 'E' || choice == 'e')
            {
                Student stu; // composition
                stu.StudentMenu();
            }

            else
            {
                Student stu; // composition
                cout << "Invalid input" << endl;
                stu.StudentMenu();
            }
        }
    }

    // function that allows the student to view the quiz result
    void viewResult()
    {
        cout << "\n\t\t\t\t\t\t  ***View Result***" << endl;
        cout << "Total Marks: " << gettotalMarks() << endl;
        cout << "Your obtained marks are: " << obtainedMarks << endl;
        cout << "Percentage: " << (obtainedMarks / gettotalMarks()) * 100 << "%" << endl;
        cout << "Total Questions: " << gettotalQs() << endl;
        cout << "Total Correct Answers: " << obtainedMarks / marksPer_Q[0] << endl;
        cout << "Total Incorrect Answers: " << gettotalQs() - (obtainedMarks / marksPer_Q[0]) << endl;
        // Marks of each question
        cout << "Marks of each question: " << endl;
        for (int i = 0; i < gettotalQs(); i++)
        {
            cout << "Question " << i + 1 << ": " << marksPer_Q[i] << endl;
        }

        cout << "Press E key to go back" << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'E' || choice == 'e')
        {
            QuizMenu();
        }

        else
        {
            cout << "Invalid input" << endl;
            QuizMenu();
        }
    }

    // function that marks the attendance and writes in file
    void markAttendance()
    {
        // writes the students ID in file and marks attendance
        if (quizAttempted)
        {
            // writing the student ID in file
            ofstream file;
            file.open("ClassAttendance.txt", ios::app);
            file << stuID << ": Present" << endl;
            file.close();
        }
    }

    // function that writes the marks of the student in file
    void writeMarks()
    {
        if (quizAttempted)
        {
            // writing the total Marks, obtained marks and marks per question in file
            ofstream file;
            file.open("StudentMarks.txt", ios::app);
            file << stuID << ": " << obtainedMarks << "/" << gettotalMarks() << endl;
            file << "Marks per question: " << endl;
            for (int i = 0; i < gettotalQs(); i++)
            {
                file << "Question " << i + 1 << ": " << marksPer_Q[i] << endl;
            }
        }
    }
    // getters
    bool getQuizAttemted()
    {
        return quizAttempted;
    }

    // get marks of each question
    double getMarksPerQ(int i)
    {
        return marksPer_Q[i];
    }
};

// Analytics class which allows the teacher to view the quiz analytics of the students
class Analytics : public ConductQuiz // inheriting the conduct quiz class
{
private:
    double classMarks[300];
    string classAttendance[300] = {"Absent"};

public:
    // default constructor
    Analytics()
    {
        classMarks[300] = {0};
        classAttendance[300] = {"Absent"};
    }

    // menu
    void analyticsMenu()
    {
        Teacher t1; // object of teacher class
        cout << "\n\t\t\t\t\t\t  ***Analytics Menu***" << endl;
        cout << "Press 1 to view the class attendance" << endl;
        cout << "Press 2 to view the class statistics" << endl;
        cout << "Press 3 to view the Qs difficulty level" << endl;
        cout << "Press E to go back to the teacher menu" << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == '1')
        {
            totalClassAttendance(); // calling the total class attendance function
        }

        else if (choice == '2')
        {
            classStats(); // calling the class stats function
        }

        else if (choice == '3')
        {
            QsDifficultyLvl(); // calling the Qs difficulty level function
        }

        else if (choice == 'E' || choice == 'e')
        {
            t1.TeacherMenu(); // calling the teacher menu function
        }

        else
        {
            cout << "Invalid input" << endl;
            analyticsMenu();
        }
    }

    // function that allows the teacher to view the class attendance
    void totalClassAttendance()
    {
        // displays the attendance of the students(the attendance is marks if a student has attempted the quiz)
        cout << "\n\t\t\t\t\t\t  ***Class Attendance***" << endl;

        cout << "ID:       Att:" << endl;
        // reading the student ID from file
        ifstream file;
        file.open("ClassAttendance.txt");
        string line;
        while (getline(file, line))
        {
            cout << line << endl; // displaying the student attendance
        }
        file.close();

        cout << "\nPress E to go back" << endl; // E for to go back to the analytics menu
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'E' || choice == 'e')
        {
            analyticsMenu();
        }

        else
        {
            cout << "Invalid input" << endl;
            analyticsMenu();
        }
    }

    // function that allows the teacher to view the class statistics
    void classStats()
    {
        cout << "\n\t\t\t\t\t\t  ***Class Statistics***" << endl;
        double classMarks[300];
        ifstream file("StudentMarks.txt");
        string line;
        double highestMarks = 0;
        double lowestMarks = 0;
        double totalMarks = 0;
        int count = 0;

        while (getline(file, line))
        {
            // Check if the line contains student marks
            if (line.find("/") != string::npos)
            {
                cout << line << endl;

                // Extract the substring containing the marks and remove whitespace
                string marksStr = line.substr(line.find(":") + 1, line.find("/") - line.find(":") - 1); // Extract the substring containing the marks
                size_t startPos = marksStr.find_first_not_of(" \t");                                    // Remove whitespace from the start of the substring
                size_t endPos = marksStr.find_last_not_of(" \t");                                       // Remove whitespace from the end of the substring
                marksStr = marksStr.substr(startPos, endPos - startPos + 1);                            // Extract the substring containing the marks

                // Convert the substring to double
                classMarks[count] = stod(marksStr);

                // Update total marks
                totalMarks += classMarks[count];

                // Update highest and lowest marks
                if (count == 0)
                {
                    highestMarks = classMarks[count];
                    lowestMarks = classMarks[count];
                }
                else
                {
                    if (classMarks[count] > highestMarks)
                    {
                        highestMarks = classMarks[count];
                    }
                    if (classMarks[count] < lowestMarks)
                    {
                        lowestMarks = classMarks[count];
                    }
                }

                count++; // Increment the count
            }
        }

        file.close();

        // displaying the highest, lowest and average marks
        cout << "\nHighest Marks: " << highestMarks << endl;
        cout << "Lowest Marks: " << lowestMarks << endl;
        cout << "Average Marks: " << totalMarks / count << endl;

        cout << "\nPress E key to go back" << endl;
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'E' || choice == 'e')
        {
            analyticsMenu();
        }

        else
        {
            cout << "Invalid input" << endl;
            analyticsMenu();
        }
    }

    // function that allows the teacher to view the Qs difficulty level
    void QsDifficultyLvl()
    {
        // shows the difficulty level of each Qs by checking the marks of each Qs
        cout << "\n\t\t\t\t\t\t  ***Qs Difficulty Level***" << endl;
        for (int i = 0; i < gettotalQs(); i++)
        {
            if (getMarksPerQ(i) >= 0 && getMarksPerQ(i) <= 2)
            {
                cout << "Question " << i + 1 << ": Easy" << endl;
            }

            else if (getMarksPerQ(i) >= 3 && getMarksPerQ(i) <= 5)
            {
                cout << "Question " << i + 1 << ": Medium" << endl;
            }

            else if (getMarksPerQ(i) >= 6 && getMarksPerQ(i) <= 10)
            {
                cout << "Question " << i + 1 << ": Hard" << endl;
            }
        }
    }
};

// main
int main()
{
    User u1;
    u1.loginMenu(); // calling the login menu function

    return 0;
}

// login menu function definition(user class)
void User::loginMenu()
{
    // Login menu
    cout << "\t\t\t\t\t***Welcome to FAST Examination System***" << endl;
    cout << "Press 1 for Student Login" << endl;
    cout << "Press 2 for Teacher Login" << endl;
    cout << "Press E to Exit the Program" << endl;
    char choice;
    cin >> choice;
    cin.ignore();
    if (choice == '1')
    {
        // Display the student login menu
        Student student; // creating the student object
        student.StudentLogin();
    }

    if (choice == '2')
    {
        // Display the teacher login menu
        Teacher teacher; // creating the teacher object
        teacher.TeacherLogin();
    }

    if (choice == 'E' || choice == 'e')
    {
        cout << "\t\t\t\t\t\tExiting the program..." << endl;
        exit(0);
    }

    else
    {
        cout << "Invalid Input!" << endl;
        loginMenu();
    }
}

// student menu function definition(user class)
void Student::StudentMenu()
{
    cout << "\n\t\t\t\t\t\t  ***Student Menu***" << endl;
    cout << "Press 1 to view your profile" << endl;
    cout << "Press 2 to attempt a quiz" << endl;
    cout << "Press 3 to view your enrolled courses" << endl;
    cout << "Press 4 to change your password" << endl;
    cout << "Press E to logout" << endl;
    char choice;
    cin >> choice;
    cin.ignore();
    if (choice == '1')
    {
        displayProfile(); // displaying the student profile
    }
    else if (choice == '2')
    {
        ConductQuiz quiz; // compostion
        quiz.QuizMenu(); 
    }
    else if (choice == '3')
    {
        viewEnrolledCourses(); // viewing the enrolled courses
    }
    else if (choice == '4')
    {
        changePassword(); // changing the password
    }

    else if (choice == 'E' || choice == 'e')
    {
        loginMenu(); // returning to the login menu
    }

    else
    {
        cout << "Invalid input" << endl;
        StudentMenu();
    }
}

// teacher menu function definition(user class)
void Teacher::TeacherMenu()
{
    cout << "\n\t\t\t\t\t\t  ***Teacher Menu***" << endl;
    cout << "Press 1 to view your profile" << endl;
    cout << "Press 2 to check your assigned courses" << endl;
    cout << "Press 3 to add questions to the questions bank" << endl;
    cout << "Press 4 to set a quiz" << endl;
    cout << "Press 5 to check class analytics" << endl;
    cout << "Press 6 to change your password" << endl;
    cout << "Press E to logout" << endl;
    char choice;
    cin >> choice;
    cin.ignore();

    if (choice == '1')
    {
        // calling the view profile function
        displayProfile();
    }

    if (choice == '2')
    {
        // calling the check assigned courses function
        ViewAssignedCourses();
    }

    if (choice == '3')
    {
        // calling the add questions function
        QuestionBank qb1; // compostion
        qb1.createQs();
    }

    if (choice == '4')
    {
        SetQuiz sq1; // compostion
        sq1.quizMenu();
    }

    if (choice == '5')
    {
        Analytics a1; // compostion
        a1.analyticsMenu();
    }

    if (choice == '6')
    {
        // calling the change password function
        changePassword();
    }

    if (choice == 'E' || choice == 'e')
    {
        // calling the login menu function
        loginMenu();
    }

    else
    {
        cout << "Invalid input" << endl;
        TeacherMenu();
    }
}

// function input the data of cousres from the csv file to the array(so we know which cousres are assigned the student)
void getStudentCourses(string _courses[11])
{
    // copying the student object
    ifstream file("Course Registration.csv"); // opening the csv file
    if (file.is_open())
    {
        string line;
        getline(file, line); // Skip the header line

        bool foundUser = false;

        while (getline(file, line))
        {
            // Parse the line
            stringstream ss(line); // used to split the string
            string sr, _id, name, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11;
            getline(ss, sr, ',');   // saves the sr#
            getline(ss, _id, ',');  // saves the student ID
            getline(ss, name, ','); // saves the student name
            getline(ss, c1, ',');   // saves the course 1
            getline(ss, c2, ',');   // saves the course 2
            getline(ss, c3, ',');
            getline(ss, c4, ',');
            getline(ss, c5, ',');
            getline(ss, c6, ',');
            getline(ss, c7, ',');
            getline(ss, c8, ',');
            getline(ss, c9, ',');
            getline(ss, c10, ',');
            getline(ss, c11, ',');

            bool idFound = false; // flag to check if the student ID has been found
            if (_id == stuID)     // checking if the student ID is found
            {
                idFound = true;
                // inputing the course data into the array courses
                _courses[0] = c1;
                _courses[1] = c2;
                _courses[2] = c3;
                _courses[3] = c4;
                _courses[4] = c5;
                _courses[5] = c6;
                _courses[6] = c7;
                _courses[7] = c8;
                _courses[8] = c9;
                _courses[9] = c10;
                _courses[10] = c11;
                break;
            }
        }
    }
}

// function input the data of cousres from the csv file to the array(so we know which cousres are assigned the teacher)
void getTeacherCourses(string _courses[11])
{
    ifstream file("Teachers data.csv"); // opening the csv file
    if (file.is_open())
    {
        string line;
        getline(file, line); // Skip the header line

        bool foundUser = false;

        while (getline(file, line))
        {
            // Parse the line
            stringstream ss(line); // used to split the string
            string sr, id, name, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11;
            getline(ss, sr, ',');   // saves the sr#
            getline(ss, id, ',');   // saves the student ID
            getline(ss, name, ','); // saves the student name
            getline(ss, c1, ',');   // saves the course 1
            getline(ss, c2, ',');   // saves the course 2
            getline(ss, c3, ',');
            getline(ss, c4, ',');
            getline(ss, c5, ',');
            getline(ss, c6, ',');
            getline(ss, c7, ',');
            getline(ss, c8, ',');
            getline(ss, c9, ',');
            getline(ss, c10, ',');
            getline(ss, c11, ',');

            bool idFound = false; // flag to check if the teacher ID has been found

            if (id == teacherID) // checking if the teacher ID is found
            {
                idFound = true;
                // inputing the courses in the array
                _courses[0] = c1;
                _courses[1] = c2;
                _courses[2] = c3;
                _courses[3] = c4;
                _courses[4] = c5;
                _courses[5] = c6;
                _courses[6] = c7;
                _courses[7] = c8;
                _courses[8] = c9;
                _courses[9] = c10;
                _courses[10] = c11;
                break;
            }
        }
    }
}
