# DoorDarshan

A small C++17 movie and series recommender for the age-old question: **what should I watch tonight?**

DoorDarshan asks about mood, genre, day, format, language, and available time. It uses a transparent scoring system to suggest up to three titles from a hand-curated list.

## Run on Windows

1. Open this folder in VS Code.
2. Select **Terminal → New Terminal**.
3. Run:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o screenpick.exe
.\screenpick.exe
```

Make sure the terminal is open in the same folder as `main.cpp`.

## Run on macOS / Linux

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o screenpick
./screenpick
```

## What it considers

- Mood: happy, low, stressed, romantic, curious, motivated, bored, adventurous
- Genre: comedy, drama, romance, mystery/crime, sci-fi/fantasy, adventure, family, thriller
- Day: weekday, Friday, Saturday, Sunday
- Movie or series
- Hindi or English
- Available time

## How recommendations work

Format, language, and runtime are filters. Matching mood and genre earn points, and the day adds a small bonus for relevant viewing styles. The highest-scoring matches appear first. If several titles tie, their order is shuffled.

This is deliberately a rule-based project, not a machine-learning model. The logic is readable and easy to extend.

## Current limitations

- The catalogue is small and stored in `main.cpp`.
- Streaming-platform availability is not checked.
- Series runtime means approximate episode length.
- Recommendations do not use viewing history or ratings.

## Suggested future improvements

- Load titles from CSV.
- Add age ratings and streaming services.
- Let users save a favourites list.
- Add a desktop interface with Qt.

## Files

- `main.cpp` — complete program
- `README.md` — setup and project documentation
- `.gitignore` — excludes generated executables
- `LICENSE` — MIT license
