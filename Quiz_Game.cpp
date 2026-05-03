#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<windows.h>

using namespace std;

// ================= THEME FUNCTION =================
void changeConsoleColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ================= MENU =================
void menu()
{
    cout << "1. Start Quiz\n";
    cout << "2. View High Scores\n";
    cout << "3. End Game\n";
    cout << "4. Quiz Log\n";
    cout << "5. Change Theme\n";
}

// ================= SUBJECT =================
void subject()
{
    cout << "1. Science\n2. Computer\n3. History\n4. Sports\n5. IQ/Logic\n";
}

// ================= MODE =================
void Mode()
{
    cout << "1. Easy\n2. Medium\n3. Hard\n";
}

// ================= DATE =================
string getDate()
{
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    return to_string(ltm.tm_mday) + "/" +
        to_string(ltm.tm_mon + 1) + "/" +
        to_string(1900 + ltm.tm_year);
}

// ================= HIGH SCORES =================
void viewHighScores()
{
    ifstream file("high_scores.txt");
    if (!file)
    {
        cout << "No scores found\n";
        system("pause"); return;
    }

    string line;
    while (getline(file, line))
        cout << line << endl;

    system("pause");
}

// ================= QUIZ LOG =================
void viewQuizLog()
{
    ifstream file("quiz_logs.txt");
    if (!file)
    {
        cout << "No logs found\n";
        system("pause"); return;
    }

    string line;
    while (getline(file, line))
        cout << line << endl;

    system("pause");
}

// ================= QUIZ =================
void runQuiz(string filename)
{
    string lines[1000];
    int total = 0;

    ifstream file(filename);
    if (!file)
    {
        cout << "File error\n";
        system("pause"); return;
    }

    while (getline(file, lines[total])) total++;
    file.close();

    int totalQ = total / 7;

    int score = 0, wrong = 0;
    bool used[200] = { false };

    string name;
    cout << "Enter name: ";
    cin >> name;

    srand(time(0));

    for (int i = 0; i < min(10, totalQ); i++)
    {
        int q;
        do { q = rand() % totalQ; } while (used[q]);

        int start = q * 7;

        cout << "\n" << lines[start] << endl;
        for (int j = 1; j <= 4; j++)
            cout << j << ". " << lines[start + j] << endl;

        int correct = atoi(lines[start + 5].c_str());

        int ans;
        cout << "Answer: ";
        cin >> ans;

        if (ans == correct)
        {
            cout << "Correct!\n";
            score++;
        }
        else
        {
            cout << "Wrong! Correct: " << lines[start + 6] << endl;
            wrong++;
        }

        used[q] = true;
    }

    cout << "\nFinal Score: " << score << endl;

    ofstream s("high_scores.txt", ios::app);
    s << name << " " << score << " " << getDate() << endl;
    s.close();

    ofstream l("quiz_logs.txt", ios::app);
    l << name << " Score:" << score << " Wrong:" << wrong << endl;
    l.close();

    system("pause");
}

// ================= MAIN =================
int main()
{
    int n;

    while (true)
    {
        system("cls");
        cout << "==== QUIZ MASTER ====\n";
        menu();
        cin >> n;

        if (n == 1)
        {
            int sub, mode;
            subject();
            cin >> sub;

            Mode();
            cin >> mode;

            if (sub == 1)
                runQuiz(mode == 1 ? "EasyS.txt" : mode == 2 ? "MediumS.txt" : "HardS.txt");
            else if (sub == 2)
                runQuiz(mode == 1 ? "EasyC.txt" : mode == 2 ? "MediumC.txt" : "HardC.txt");
            else if (sub == 3)
                runQuiz(mode == 1 ? "EasyH.txt" : mode == 2 ? "MediumH.txt" : "HardH.txt");
            else if (sub == 4)
                runQuiz(mode == 1 ? "EasyP.txt" : mode == 2 ? "MediumP.txt" : "HardP.txt");
            else if (sub == 5)
                runQuiz(mode == 1 ? "EasyI.txt" : mode == 2 ? "MediumI.txt" : "HardI.txt");
        }
        else if (n == 2)
            viewHighScores();

        else if (n == 3)
            break;

        else if (n == 4)
            viewQuizLog();

        else if (n == 5)
        {
            int t;
            cout << "1.Default 2.Green 3.Red 4.Blue 5.Yellow\n";
            cin >> t;

            if (t == 1) changeConsoleColor(7);
            else if (t == 2) changeConsoleColor(10);
            else if (t == 3) changeConsoleColor(12);
            else if (t == 4) changeConsoleColor(9);
            else if (t == 5) changeConsoleColor(14);
        }
    }

    return 0;
}