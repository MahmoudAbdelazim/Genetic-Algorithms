#include <bits/stdc++.h>

using namespace std;

#define point pair<double, double>
#define chrom vector<double>
#define inverse(x) 1.0 / x

int N; // Number of items
int D; // Polynomial degree
int P; // Number of chromosomes
int Pc = 90; // Crossover prob
int Pm = 2; // Mutation prob
int t = 0; // current generation
int T = 10000; // Maximum number of generations
int b = 2; // dependency factor

vector<point > points; // the points of the curve
vector<chrom > population; // Population of chromosomes

void generatePopulation(); // Generates random population of P chromosomes
double error(chrom &v);
double fitness(chrom &); // returns the fitness of a chromosome (total values)
pair<chrom, chrom > select(); // selects two chromosomes to generate a new generation
pair<chrom, chrom > crossover(pair<chrom, chrom > &); // creates the new generation from parents
void mutation(pair<chrom, chrom > &); // mutates the new generation with probability of Pm
void mutate(chrom &c);
void replace(pair<chrom, chrom > &); // replaces the new generation with the least fitness chromosomes
pair<double, int> getBestResult(); // gets the best chromosome fitness

int main() {
    ifstream input;
    input.open("input.txt");
    ofstream output;
    output.open("output.txt");
//    srand(time(0));
    int testCases;
    input >> testCases;
    while (testCases--) {
        input >> N;
        input >> D;
        D++;
        P = max(3, N / 2);
        points.clear();
        points.resize(N);
        for (int i = 0; i < N; i++) {
            input >> points[i].first >> points[i].second;
        }
        generatePopulation();
        auto bestResult = getBestResult();
        while (t <= T) {
            auto parents = select();
            auto newG = crossover(parents);
            mutation(newG);
            replace(newG);
            auto curBestResult = getBestResult();
            if (curBestResult.first > bestResult.first) {
                bestResult = curBestResult;
            }
            t++;
        }
        chrom bestChrom = population[bestResult.second];
        for (double i: bestChrom) {
            output << fixed << setprecision(3) << i << " ";
        }
        output << "\nError = " << fixed << setprecision(3) << inverse(bestResult.first) << "\n";
    }
}

int randomInt(int min, int max) {
    return min + (rand() % (max - min + 1));
}

double randomDouble(double min, double max) {
    return min + (double) (rand()) / ((double) (RAND_MAX / (max - min)));
}

void generatePopulation() {
    population.clear();
    while (population.size() < P) {
        chrom v(D);
        for (int i = 0; i < D; i++) {
            v[i] = randomDouble(-10, 10);
        }
        population.push_back(v);
    }
}

double error(chrom &v) {
    double totalSum = 0;
    for (point p: points) {
        double x = p.first;
        double y = p.second;
        double sum = 0;
        for (int i = 0; i < D; i++) {
            sum += v[i] * pow(x, i);
        }
        sum -= y;
        sum *= sum;
        totalSum += sum;
    }
    totalSum /= N;
    return totalSum;
}

double fitness(chrom &v) {
    return inverse(error(v));
}

// Tournament selection
pair<chrom, chrom > select() {
    vector<chrom > matingPool(P);
    for (int i = 0; i < P; i++) {
        chrom c1 = population[randomInt(0, P - 1)];
        chrom c2 = population[randomInt(0, P - 1)];
        if (fitness(c1) > fitness(c2)) {
            matingPool[i] = c1;
        } else {
            matingPool[i] = c2;
        }
    }
    chrom c1 = matingPool[randomInt(0, P - 1)];
    chrom c2 = matingPool[randomInt(0, P - 1)];
    return make_pair(c1, c2);
}

// 2-point Crossover
pair<chrom, chrom > crossover(pair<chrom, chrom > &selected) {
    int Rc = randomInt(0, 100);
    if (Rc <= Pc) {
        int Xc1 = randomInt(1, D - 1);
        int Xc2 = randomInt(1, D - 1);
        if (Xc1 > Xc2) swap(Xc1, Xc2);
        chrom p1 = selected.first;
        chrom p2 = selected.second;
        chrom new1(D), new2(D);
        for (int i = 0; i < Xc1; i++) {
            new1[i] = p1[i];
            new2[i] = p2[i];
        }
        for (int i = Xc1; i < Xc2; i++) {
            new1[i] = p2[i];
            new2[i] = p1[i];
        }
        for (int i = Xc2; i < D; i++) {
            new1[i] = p1[i];
            new2[i] = p2[i];
        }
        return make_pair(new1, new2);
    } else {
        return selected;
    }
}

// Non-uniform mutation
void mutation(pair<chrom, chrom > &p) {
    mutate(p.first);
    mutate(p.second);
}

void mutate(chrom &c) {
    for (int i = 0; i < D; i++) {
        int Rm = randomInt(0, 100);
        if (Rm <= Pm) {
            double Lx = c[i] - (-10);
            double Ux = 10 - c[i];
            double r1 = randomDouble(0, 1);
            double y;
            if (r1 <= 0.5) {
                y = Lx;
            } else {
                y = Ux;
            }
            double r = randomDouble(0, 1);
            double delta = y * (1 - pow(r, (pow(1 - (double) t / T, (double) b))));
            if (y == Lx) {
                c[i] -= delta;
            } else {
                c[i] += delta;
            }
        }
    }
}

void replace(pair<chrom, chrom > &p) {
    int c1 = randomInt(0, P - 1);
    int c2 = randomInt(0, P - 1);
    population[c1] = p.first;
    population[c2] = p.second;
}

pair<double, int> getBestResult() {
    double mx = fitness(population[0]);
    int mxIdx = 0;
    for (int i = 1; i < P; i++) {
        if (fitness(population[i]) > mx) {
            mx = fitness(population[i]);
            mxIdx = i;
        }
    }
    return make_pair(mx, mxIdx);
}