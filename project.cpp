#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// player class
class Player {
protected:
    string name;
public:
    Player(string n) : name(n) {}
    string getName() const { return name; }
};

//batsmen class
class Batsman : public Player {
private:
    int runs, balls, fours, sixes;
public:
    Batsman(string n) : Player(n), runs(0), balls(0), fours(0), sixes(0) {}

    void addRuns(int r) {
        runs += r;
        balls++;
        if (r == 4) fours++;
        if (r == 6) sixes++;
    }
    
    // for wide or extra 
    void addExtra(int r) { runs += r; } 

    int getRuns() const { return runs; }
    int getBalls() const { return balls; }
    int getFours() const { return fours; }
    int getSixes() const { return sixes; }

    void printStats() const {
        float sr = (balls > 0) ? (runs * 100.0 / balls) : 0.0;
        cout << left << setw(10) << name
             << setw(5) << runs
             << setw(5) << balls
             << setw(5) << fours
             << setw(5) << sixes
             << setw(7) << fixed << setprecision(1) << sr << endl;
    }
};

//bowler class
class Bowler : public Player {
private:
    int ballsBowled, runsGiven, wickets;
public:
    Bowler(string n) : Player(n), ballsBowled(0), runsGiven(0), wickets(0) {}

    void bowlBall(int runs, bool wicket = false, bool extra = false) {
        if (!extra) ballsBowled++;  // wide/no-ball does NOT count as ball
        runsGiven += runs;
        if (wicket) wickets++;
    }

    void printStats() const {
        int overs = ballsBowled / 6;
        int balls = ballsBowled % 6;
        float econ = (ballsBowled > 0) ? (runsGiven * 6.0 / ballsBowled) : 0.0;

        cout << left << setw(10) << name
             << "Overs: " << overs << "." << balls
             << "  Runs: " << runsGiven
             << "  Wkts: " << wickets
             << "  Econ: " << fixed << setprecision(1) << econ
             << endl;
    }
};

//match class
class Match {
private:
    vector<Batsman> batsmen;
    vector<string> fallOfWickets;
    vector<Bowler> bowlers;

    int striker, nonStriker;
    int totalRuns, wickets, balls;
    int oversLimit;

public:
    int currentBowler;

   Match(vector<string> batNames, vector<string> bowlerNames, int overs)
    : totalRuns(0), wickets(0), balls(0), oversLimit(overs), currentBowler(0){
    for (auto &n : batNames)
        batsmen.emplace_back(n);

    for (auto &bn : bowlerNames)
        bowlers.emplace_back(bn);

    striker = 0;
    nonStriker = 1;
    }

    
    void playBall(int runs, bool wicket = false, bool extra = false) {

        if (balls / 6 >= oversLimit) {
            cout << "\n--- Innings Over (20 overs completed) ---\n";
            return;
        }

        if (extra) {
            totalRuns += runs;
            //batsmen[striker].addExtra(runs);
            bowlers[currentBowler].bowlBall(runs, wicket, extra);
            return;
        }

        balls++;

        if (wicket) {
            wickets++;
            bowlers[currentBowler].bowlBall(0, true);

            fallOfWickets.push_back(
                batsmen[striker].getName() + " - " + to_string(totalRuns)
            );

            cout << "Wicket! " << batsmen[striker].getName() << " is out.\n";

            strikeNewBatsman();
            return;
        }

        
        totalRuns += runs;
        batsmen[striker].addRuns(runs);
        bowlers[currentBowler].bowlBall(runs, false, false);

        
        if (runs % 2 == 1) {
            swap(striker, nonStriker);
      }

        
        if (balls % 6 == 0) {
            swap(striker, nonStriker);
      }

        if (balls % 6 == 0 && !extra) {
            currentBowler = (currentBowler + 1) % bowlers.size();
            cout << "\n--- New Bowler: " << bowlers[currentBowler].getName() << " ---\n";
}

    }

    void strikeNewBatsman() {
        if (striker < batsmen.size() - 1){
            striker = max(striker, nonStriker) + 1;
        }
        if (striker >= batsmen.size()) {
            cout << "\nAll Out!\n";
        }
    }

   
    void printScorecard() const {
        cout << "\n========== SCORECARD ==========\n";
        cout << "Total: " << totalRuns << "/" << wickets
             << "  Overs: " << balls / 6 << "." << balls % 6 << "\n\n";

        cout << "Batsman     R    B    4s   6s   SR\n";
        for (int i = 0; i < batsmen.size(); i++) {
            batsmen[i].printStats();
        }

        cout << "\nBowler Stats:\n";
        for (auto &b : bowlers)
            b.printStats();


        cout << "\nFall of Wickets:\n";
        for (auto &f : fallOfWickets) cout << f << endl;

        cout << "================================\n";
    }
};


int main() {

    vector<string> bats = {"Rohit", "Gill", "Kohli", "Shreyas", "Rahul",
                           "Hardik", "Jadeja", "Shami", "Kuldeep", "Siraj", "Bumrah"};

    vector<string> bowls = {"Starc", "Hazlewood", "Cummins"};

    Match m(bats, bowls, 4);

    while (true) {
        cout << "\nEnter ball result:\n";
        cout << "Runs (0-6 or 7 for wide/no-ball): ";
        int runs; cin >> runs;

        bool wicket = false, extra = false;

        if (runs == 7) { extra = true; runs = 1; }

        cout << "Wicket? (1/0): ";
        int w; cin >> w;
        wicket = (w == 1);

        m.playBall(runs, wicket, extra);
        m.printScorecard();

        char cont;
        cout << "\nNext ball? (y/n): ";
        cin >> cont;
        if (cont != 'y' && cont != 'Y'){
            break;
        }
    }
}