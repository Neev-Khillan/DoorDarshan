#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

using namespace std;

struct Pick {
    string title, type, genre, language, mood, vibe, description;
    int minutes;
};

const vector<Pick> films = {
    {"3 Idiots", "Movie", "Comedy / Drama", "Hindi", "happy stressed motivated", "funny inspiring", "Three friends, campus chaos, and a reminder to enjoy the process.", 170},
    {"Queen", "Movie", "Comedy / Drama", "Hindi", "low motivated adventurous", "feel-good empowering", "A young woman takes a solo trip and finds her own confidence.", 146},
    {"Drishyam", "Movie", "Crime / Thriller", "Hindi", "curious focused stressed", "tense twisty", "A family man tries to stay one step ahead of a criminal investigation.", 163},
    {"Zindagi Na Milegi Dobara", "Movie", "Adventure / Drama", "Hindi", "sad stressed adventurous", "friendship scenic feel-good", "Three friends go on a road trip that changes how they see life.", 153},
    {"Panchayat", "Series", "Comedy / Drama", "Hindi", "low stressed happy", "warm funny comfort", "A city graduate adjusts to life in a quiet village.", 35},
    {"Kota Factory", "Series", "Drama", "Hindi", "stressed motivated low", "friendship thoughtful", "Student life, expectations, and the people who help you through them.", 45},
    {"Aspirants", "Series", "Drama", "Hindi", "motivated stressed focused", "ambition friendship", "Friendship and ambition collide in the world of competitive exams.", 45},
    {"Andhadhun", "Movie", "Crime / Thriller", "Hindi", "curious bored adventurous", "dark twisty", "A pianist gets caught in a crime story full of unexpected turns.", 139},
    {"The Intern", "Movie", "Comedy / Drama", "English", "tired stressed low", "warm comfort funny", "A gentle story about friendship, work, and starting over.", 121},
    {"The Pursuit of Happyness", "Movie", "Drama", "English", "sad motivated low", "inspiring emotional", "A father keeps going when life gives him very little room to breathe.", 117},
    {"About Time", "Movie", "Romance / Fantasy", "English", "romantic low happy", "warm emotional dreamy", "A romantic story that makes ordinary moments feel important.", 123},
    {"Knives Out", "Movie", "Mystery / Comedy", "English", "curious bored focused", "clever twisty funny", "A modern whodunit with a house full of suspicious people.", 130},
    {"Interstellar", "Movie", "Sci-fi / Drama", "English", "curious dreamy adventurous", "epic emotional thoughtful", "A space mission becomes a story about time, distance, and love.", 169},
    {"The Martian", "Movie", "Sci-fi / Adventure", "English", "motivated curious adventurous", "clever hopeful funny", "One astronaut, a lot of problems, and an impressive amount of science.", 144},
    {"The Secret Life of Walter Mitty", "Movie", "Adventure / Comedy", "English", "dreamy low adventurous", "uplifting scenic", "A daydreamer finally steps outside the life he imagined.", 114},
    {"Paddington 2", "Movie", "Family / Comedy", "English", "low happy stressed", "comfort wholesome funny", "A kind-hearted bear makes a strong case for being decent.", 103},
    {"Brooklyn Nine-Nine", "Series", "Comedy", "English", "happy stressed low bored", "funny comfort quick", "A fast-moving workplace comedy with lovable detectives.", 22},
    {"The Good Place", "Series", "Comedy / Fantasy", "English", "curious low happy", "clever funny thoughtful", "A funny afterlife mystery with surprisingly big questions.", 22},
    {"Modern Family", "Series", "Comedy", "English", "tired stressed happy low", "comfort funny family", "A familiar family sitcom for an easy, low-effort watch.", 22},
    {"Stranger Things", "Series", "Sci-fi / Mystery", "English", "curious adventurous focused", "suspenseful nostalgic", "A small town, strange events, and a close group of friends.", 50}
};

string lower(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return s;
}

int menu(const string& question, const vector<string>& options) {
    while (true) {
        cout << "\n" << question << "\n";
        for (size_t i = 0; i < options.size(); ++i)
            cout << "  " << i + 1 << ") " << options[i] << "\n";
        cout << "Your choice: ";

        int choice;
        if (cin >> choice && choice >= 1 && choice <= static_cast<int>(options.size())) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice - 1;
        }
        cout << "Please enter a number from 1 to " << options.size() << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool contains(const string& list, const string& word) {
    return lower(list).find(lower(word)) != string::npos;
}

int main() {
    mt19937 randomEngine(random_device{}());

    cout << "\n";
    cout << "  =========================================\n";
    cout << "                 SCREENPICK\n";
    cout << "          find something for tonight\n";
    cout << "  =========================================\n";
    cout << "\nNo endless scrolling. Just a few quick questions.\n";

    bool repeat = true;
    while (repeat) {
        int moodChoice = menu("How are you feeling?", {
            "Happy / upbeat", "Low / need a lift", "Stressed / tired",
            "Romantic / dreamy", "Curious / want a puzzle",
            "Motivated / need a push", "Bored / want something different",
            "Adventurous / want a thrill"
        });
        const vector<string> moods = {"happy", "low", "stressed", "romantic", "curious", "motivated", "bored", "adventurous"};
        string mood = moods[moodChoice];

        int genreChoice = menu("What sounds good?", {
            "surprise me", "Comedy", "Drama", "Romance",
            "Mystery / crime", "Sci-fi / fantasy", "Action / adventure",
            "Family", "Thriller"
        });
        const vector<string> genres = {"any", "comedy", "drama", "romance", "crime", "sci-fi", "adventure", "family", "thriller"};
        string genre = genres[genreChoice];

        int dayChoice = menu("What kind of watch-day is it?", {
            "Weekday, keep it short", "Friday, switch my brain off",
            "Saturday, full movie-night energy", "Sunday, cosy and easy"
        });

        int formatChoice = menu("Movie or series?", {"Movie", "Series", "Either"});
        int languageChoice = menu("Language?", {"Any language", "Hindi", "English"});
        int timeChoice = menu("How much time do you have?", {"Under 30 minutes", "About 1 to2 hours", "No time limit"});

        vector<pair<int, int>> results;
        for (size_t i = 0; i < films.size(); ++i) {
            const Pick& p = films[i];

            if (formatChoice == 0 && p.type != "Movie") continue;
            if (formatChoice == 1 && p.type != "Series") continue;
            if (languageChoice == 1 && p.language != "Hindi") continue;
            if (languageChoice == 2 && p.language != "English") continue;
            if (timeChoice == 0 && p.minutes > 30) continue;
            if (timeChoice == 1 && (p.minutes < 60 || p.minutes > 150)) continue;

            int score = 0;
            if (contains(p.mood, mood)) score += 5;
            if (genre != "any" && contains(p.genre, genre)) score += 4;
            if (dayChoice == 0 && p.minutes <= 30) score += 2;
            if (dayChoice == 1 && contains(p.vibe, "funny")) score += 2;
            if (dayChoice == 3 && contains(p.vibe, "comfort")) score += 2;
            if (dayChoice == 2 && p.minutes >= 120) score += 1;

            if (score > 0) results.push_back({score, static_cast<int>(i)});
        }

        sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        cout << "\n  -----------------------------------------\n";
        cout << "                 YOUR SHORTLIST\n";
        cout << "  -----------------------------------------\n";

        if (results.empty()) {
            cout << "Nothing fits all those choices in this small collection.\n";
            cout << "Try 'Either', 'Any language', or 'No time limit'.\n";
        } else {
            size_t tied = 1;
            while (tied < results.size() && results[tied].first == results[0].first) ++tied;
            shuffle(results.begin(), results.begin() + static_cast<long>(tied), randomEngine);

            int count = min(3, static_cast<int>(results.size()));
            for (int i = 0; i < count; ++i) {
                const Pick& p = films[results[i].second];
                cout << "\n  " << i + 1 << ". " << p.title << " (" << p.type << ")\n";
                cout << "     " << p.genre << " | " << p.language << " | ";
                cout << p.minutes << (p.type == "Series" ? " min per episode" : " min") << "\n";
                cout << "     " << p.description << "\n";
            }
            cout << "\nSuggestions are hand-picked; streaming availability is not checked.\n";
        }

        int again = menu("Want another set of suggestions?", {"Yes, start again", "No, I'm sorted"});
        repeat = (again == 0);
    }

    cout << "\nThanks for using ScreenPick. Enjoy the watch.\n\n";
    return 0;
}
