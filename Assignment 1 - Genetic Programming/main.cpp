#include <bits/stdc++.h>

using namespace std;

#define chrom vector<bool>

int N; // Number of items
int P = 20; // Number of chromosomes
int W; // Knapsack weight
vector<int> weights; // Weights of items
vector<int> values; // Values of items
vector<chrom> population; // Population of chromosomes
int Pc = 80; // Crossover prob
int Pm = 5; // Mutation prob

void generatePopulation(); // Generates random population of P chromosomes
bool isValid(chrom &); // checks whether a chromosome is valid (total weights <= knapsack weight)
int fitness(chrom &); // returns the fitness of a chromosome (total values)
pair<int, int> select(); // selects two chromosomes to generate a new generation
pair<chrom, chrom> crossover(pair<int, int> &); // creates the new generation from parents
void mutation(pair<chrom, chrom> &); // mutates the new generation with probability of Pm
void replace(pair<chrom, chrom> &); // replaces the new generation with the least fitness chromosomes
pair<int, int> getBestResult(); // gets the best chromosome fitness
bool solution(); // checks if we've got a solution (same best result keeps occurring)

int main() {
    int t;
    cin >> t;
    int cnt = 1;
    while (t--) {
        cin >> N;
        cin >> W;
        weights.resize(N);
        values.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> weights[i];
            cin >> values[i];
        }
        generatePopulation();
        while (!solution()) {
            auto parents = select();
            auto newG = crossover(parents);
            mutation(newG);
            replace(newG);
        }
        auto bestResult = getBestResult();
        chrom bestChrom = population[bestResult.second];
        cout << "Case: " << cnt++ << " " << bestResult.first << "\n";
        int numItems = count(bestChrom.begin(), bestChrom.end(), true);
        cout << numItems << "\n";
        for (int i = 0; i < N; i++) {
            if (bestChrom[i]) {
                cout << weights[i] << " " << values[i] << "\n";
            }
        }
    }
}

bool randomBool() {
    return rand() % 2 == 0;
}

int randomInt(int min, int max) {
    return min + (rand() % (max - min + 1));
}

void generatePopulation() {
    population.clear();
    while (population.size() < P) {
        chrom v(N);
        int totalWeight = 0;
        for (int i = 0; i < N; i++) {
            if (randomBool()) {
                if (totalWeight + weights[i] <= W) {
                    v[i] = true;
                    totalWeight += weights[i];
                }
            }
        }
        population.push_back(v);
    }
}

bool isValid(chrom &v) {
    int totalWeight = 0;
    for (int i = 0; i < N; i++) {
        totalWeight += weights[i] * v[i];
    }
    return totalWeight <= W;
}

int fitness(chrom &v) {
    int totalVal = 0;
    for (int i = 0; i < N; i++) {
        totalVal += values[i] * v[i];
    }
    return totalVal;
}

// Roulette Wheel
pair<int, int> select() {
    vector<int> cum(P);
    cum[0] = fitness(population[0]);
    for (int i = 1; i < P; i++) {
        cum[i] = cum[i - 1] + fitness(population[i]);
    }
    int num1, num2;
    int selected1 = -1, selected2 = -1;
    while (selected1 == -1) {
        num1 = randomInt(0, cum.back() - 1);
        if (num1 < cum[0]) {
            selected1 = 0;
            break;
        }
        for (int i = 1; i < P; i++) {
            if (num1 >= cum[i - 1] && num1 < cum[i]) {
                selected1 = i;
                break;
            }
        }
    }
    while (selected2 == -1) {
        num2 = randomInt(0, cum.back() - 1);
        if (num2 < cum[0] && selected1 != 0) {
            selected2 = 0;
            break;
        }
        for (int i = 1; i < P; i++) {
            if (num2 >= cum[i - 1] && num2 < cum[i] && selected1 != i) {
                selected2 = i;
                break;
            }
        }
    }
    return make_pair(selected1, selected2);
}

pair<chrom, chrom> crossover(pair<int, int> &selected) {
    bool Rc = randomInt(0, 100);
    if (Rc <= Pc) {
        int Xc = randomInt(1, N - 1);
        chrom p1 = population[selected.first];
        chrom p2 = population[selected.second];
        chrom new1(N), new2(N);
        for (int i = 0; i < Xc; i++) {
            new1[i] = p1[i];
            new2[i] = p2[i];
        }
        for (int i = Xc; i < N; i++) {
            new1[i] = p2[i];
            new2[i] = p1[i];
        }
        return make_pair(new1, new2);
    }
}

void mutation(pair<chrom, chrom> &p) {
    for (int i = 0; i < N; i++) {
        if (randomInt(0, 100) <= Pm) {
            p.first[i] = !p.first[i];
        }
    }
    for (int i = 0; i < N; i++) {
        if (randomInt(0, 100) <= Pm) {
            p.second[i] = !p.second[i];
        }
    }
}

void replace(pair<chrom, chrom> &p) {
    if (isValid(p.first)) {
        int mn = 1e9;
        int mnIdx;
        for (int i = 0; i < P; i++) {
            if (fitness(population[i]) < mn) {
                mn = fitness(population[i]);
                mnIdx = i;
            }
        }
        if (fitness(p.first) > mn) {
            population[mnIdx] = p.first;
        }
    }
    if (isValid(p.second)) {
        int mn = 1e9;
        int mnIdx;
        for (int i = 0; i < P; i++) {
            if (fitness(population[i]) < mn) {
                mn = fitness(population[i]);
                mnIdx = i;
            }
        }
        if (fitness(p.second) > mn) {
            population[mnIdx] = p.second;
        }
    }
}

pair<int, int> getBestResult() {
    int mx = 0;
    int mxIdx = -1;
    for (int i = 0; i < P; i++) {
        if (fitness(population[i]) > mx) {
            mx = fitness(population[i]);
            mxIdx = i;
        }
    }
    return make_pair(mx, mxIdx);
}

bool solution() {
    static int mx = 0;
    static int occ = 0;
    if (getBestResult().first == mx) {
        occ++;
        if (occ == 1000) return true;
    } else {
        mx = getBestResult().first;
        occ = 1;
    }
    return false;
}