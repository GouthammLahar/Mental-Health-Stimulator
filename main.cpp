#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;

const int RECENT_MOODS_SIZE = 5;

struct UserProfile {
    string username;
    int age;
    string gender;
};

queue<string> recentMoods;
map<string, vector<string>> moodSuggestions = {
    {"happy", {"Keep smiling!", "Share your joy with others", "Do something creative"}},
    {"sad", {"Talk to a friend", "Watch your favorite movie", "Write down your thoughts"}},
    {"anxious", {"Practice deep breathing", "Try grounding techniques", "Make a to-do list"}},
    {"angry", {"Count to ten", "Go for a walk", "Practice mindfulness"}},
    {"tired", {"Take a power nap", "Drink some water", "Stretch your body"}},
    {"stressed", {"Prioritize your tasks", "Listen to calming music", "Do some light exercise"}}
};

vector<string> quotes = {
"Believe in yourself and all that you are. Know that there is something inside you that is greater than any obstacle.",
"In the middle of every difficulty lies opportunity.",
"Small steps every day lead to big changes over time.",
"You don not have to control your thoughts. You just have to stop letting them control you.",
"Self-care is how you take your power back.",
"Be gentle with yourself, you're doing the best you can.",
"Every step forward, no matter how small, is progress.",
"Strength grows in the moments when you think you can not go on but you keep going anyway.",
"Rest and self-care are so important. When you take time to replenish your spirit, it allows you to serve others from the overflow.",
"You are worthy of all the good things life has to offer, exactly as you are."
};

void saveUserProfile(const UserProfile& user) {
    ofstream file("user_profile.txt");
    if (file.is_open()) {
        file << user.username << endl;
        file << user.age << endl;
        file << user.gender << endl;
        file.close();
        cout << "Profile saved successfully!" << endl;
    } else {
        cerr << "Error: Unable to save profile." << endl;
    }
}

UserProfile loadUserProfile() {
    UserProfile user;
    ifstream file("user_profile.txt");
    if (file.is_open()) {
        getline(file, user.username);
        string ageStr;
        getline(file, ageStr);
        user.age = stoi(ageStr);
        getline(file, user.gender);
        file.close();
        cout << "Profile loaded successfully!" << endl;
    } else {
        cout << "No existing profile found. Starting fresh." << endl;
    }
    return user;
}

void logMood(const string& mood) {
    if (recentMoods.size() >= RECENT_MOODS_SIZE) {
        recentMoods.pop();
    }
    recentMoods.push(mood);
    
    ofstream file("mood_log.txt", ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        file << mood << "," << now << endl;
        file.close();
    } else {
        cerr << "Error: Unable to save mood log." << endl;
    }
}

void showRecentMoods() {
    if (recentMoods.empty()) {
        cout << "No moods logged yet." << endl;
        return;
    }
    
    cout << "Recent moods:" << endl;
    queue<string> temp = recentMoods;
    int count = 1;
    while (!temp.empty()) {
        cout << count++ << ". " << temp.front() << endl;
        temp.pop();
    }
}

map<string, int> getMoodFrequency() {
    map<string, int> frequency;
    ifstream file("mood_log.txt");
    string line;
    
    while (getline(file, line)) {
        string mood = line.substr(0, line.find(','));
        frequency[mood]++;
    }
    
    return frequency;
}

void showMoodSuggestions(const string& mood) {
    if (moodSuggestions.find(mood) != moodSuggestions.end()) {
        cout << "Suggestions for " << mood << " mood:" << endl;
        for (const string& suggestion : moodSuggestions[mood]) {
            cout << " " << suggestion << endl;
        }
    } else {
        cout << "No suggestions available for this mood." << endl;
    }
}

string getRandomQuote() {
    srand(time(0));
    return quotes[rand() % quotes.size()];
}

void conductBreathingExercise() {
    cout << "\n=== Guided Breathing Exercise ===\n";
    cout << "Let's do a simple breathing exercise together.\n";
    cout << "Follow the instructions and breathe naturally.\n\n";
    
    for (int cycle = 1; cycle <= 3; cycle++) {
        cout << "Cycle " << cycle << " of 3:\n";
        cout << "Breathe in slowly through your nose... ";
        this_thread::sleep_for(chrono::seconds(3));
        cout << "Good!\n";
        cout << "Hold your breath gently... ";
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Perfect!\n";
        cout << "Breathe out slowly through your mouth... ";
        this_thread::sleep_for(chrono::seconds(3));
        cout << "Excellent!\n\n";
    }
    
    cout << "Great job! You've completed the breathing exercise.\n";
    cout << "Take a moment to notice how you feel now.\n\n";
}

void addGratitudeEntry() {
    cout << "What are you grateful for today?" << endl;
    string entry;
    cin.ignore();
    getline(cin, entry);
    
    ofstream file("gratitude_journal.txt", ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        file << ctime(&now) << entry << endl << endl;
        file.close();
        cout << "Gratitude entry saved." << endl;
    } else {
        cerr << "Error saving gratitude entry." << endl;
    }
}

void showGratitudeJournal() {
    ifstream file("gratitude_journal.txt");
    if (file.is_open()) {
        cout << "Your Gratitude Journal:" << endl;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
    } else {
        cout << "Your gratitude journal is empty." << endl;
    }
}

void showMainMenu(UserProfile& user) {
    while (true) {
        cout << "\n\n= Mental Health Companion =" << endl;
        cout << "User: " << user.username << endl;
        cout << "1. Log mood" << endl;
        cout << "2. View recent moods" << endl;
        cout << "3. See mood suggestions" << endl;
        cout << "4. View mood trends" << endl;
        cout << "5. Get motivational quote" << endl;
        cout << "6. Do breathing exercise" << endl; 
        cout << "7. Gratitude journal" << endl;
        cout << "8. Edit profile" << endl;
        cout << "9. Exit" << endl;
        cout << "Choose an option: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "How are you feeling? (happy, sad, anxious, angry, tired, stressed): ";
                string mood;
                cin >> mood;
                logMood(mood);
                showMoodSuggestions(mood);
                break;
            }
            case 2:
                showRecentMoods();
                break;
            case 3: {
                cout << "Enter mood to get suggestions (happy, sad, anxious, angry, tired, stressed): ";
                string mood;
                cin >> mood;
                showMoodSuggestions(mood);
                break;
            }
            case 4: {
                map<string, int> freq = getMoodFrequency();
                cout << "Your mood frequency:" << endl;
                for (const auto& pair : freq) {
                    cout << pair.first << ": " << pair.second << " times" << endl;
                }
                break;
            }
            case 5:
                cout << "Motivational quote: " << getRandomQuote() << endl;
                break;
            case 6:
                conductBreathingExercise();
                break;
            case 7: {
                cout << "1. Add entry\n2. View journal\nChoice: ";
                int journalChoice;
                cin >> journalChoice;
                if (journalChoice == 1) {
                    addGratitudeEntry();
                } else {
                    showGratitudeJournal();
                }
                break;
            }
            case 8: {
                cout << "New username: ";
                cin >> user.username;
                cout << "Age: ";
                cin >> user.age;
                cout << "Gender: ";
                cin >> user.gender;
                saveUserProfile(user);
                break;
            }
            case 9:
                cout << "Goodbye! Take care of yourself." << endl;
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

int main() {
    cout << "= Mental Health Companion =" << endl;
    
    UserProfile user = loadUserProfile();
    if (user.username.empty()) {
        cout << "Let's create your profile:" << endl;
        cout << "Username: ";
        cin >> user.username;
        cout << "Age: ";
        cin >> user.age;
        cout << "Gender: ";
        cin >> user.gender;
        saveUserProfile(user);
    }
    
    showMainMenu(user);
    
    return 0;
}
