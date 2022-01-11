#include <bits/stdc++.h>

using namespace std;

// gets the membership result for each value in the project fund set
vector<double> fundMembership(int x) {
    vector<double> res(4); // will hold the membership values
    for (int i = 0; i < 4; i++) {
        if (i == 0) { // Very Low
            if (x >= 0 && x <= 30) {
                if (x >= 0 && x <= 10) { // slope is 0
                    res[i] = 1;
                } else {
                    double slp = -1 / 20.0; // ((0-1)/(30-10)
                    double b = 1.5; // 0 = 30 * slp + b
                    res[i] = slp * x + b; // the membership value of Very Low
                }
            }
        } else if (i == 1) { // Low
            if (x >= 10 && x <= 60) {
                if (x >= 30 && x <= 40) {
                    res[i] = 1;
                } else {
                    if (x >= 10 && x <= 30) {
                        double slp = 1 / 20.0;
                        double b = -0.5;
                        res[i] = slp * x + b;
                    } else if (x >= 40 && x <= 60) {
                        double slp = -1 / 20.0;
                        double b = 3;
                        res[i] = slp * x + b;
                    }
                }
            }
        } else if (i == 2) { // Medium
            if (x >= 40 && x <= 90) {
                if (x >= 60 && x <= 70) {
                    res[i] = 1;
                } else {
                    if (x >= 40 && x <= 60) {
                        double slp = 1 / 20.0;
                        double b = -2.0;
                        res[i] = slp * x + b;
                    } else if (x >= 40 && x <= 60) {
                        double slp = -1 / 20.0;
                        double b = 4.5;
                        res[i] = slp * x + b;
                    }
                }
            }
        } else if (i == 3) { // High
            if (x >= 70 && x <= 100) {
                if (x >= 90 && x <= 100) {
                    res[i] = 1;
                } else {
                    double slp = 1 / 20.0;
                    double b = -3.5;
                    res[i] = slp * x + b;
                }
            }
        }
    }
    return res;
}

// gets the membership result for each value in the experience level set
vector<double> expMembership(int x) {
    vector<double> res(3); // will hold the membership values
    for (int i = 0; i < 3; i++) {
        if (i == 0) { // Beginner
            if (x >= 0 && x <= 30) {
                if (x >= 0 && x <= 15) {
                    double slp = 1 / 15.0;
                    double b = 0;
                    res[i] = slp * x + b;
                } else {
                    double slp = -1 / 15.0;
                    double b = 2;
                    res[i] = slp * x + b;
                }
            }
        } else if (i == 1) { // Intermediate
            if (x >= 15 && x <= 45) {
                if (x >= 15 && x <= 30) {
                    double slp = 1 / 15.0;
                    double b = -1;
                    res[i] = slp * x + b;
                } else {
                    double slp = -1 / 15.0;
                    double b = 3;
                    res[i] = slp * x + b;
                }
            }
        } else if (i == 2) { // Expert
            if (x >= 30 && x <= 60) {
                double slp = 1 / 30.0;
                double b = -1;
                res[i] = slp * x + b;
            }
        }
    }
    return res;
}

// gets the predicted risk class based on the risk membership value
int getRisk(double x) {
    vector<double> res(3); // will hold the membership values
    for (int i = 0; i < 3; i++) {
        if (i == 0) { // Low
            if (x >= 0 && x <= 50) {
                if (x >= 0 && x <= 25) {
                    double slp = 1 / 25.0;
                    double b = 0;
                    res[i] = slp * x + b;
                } else {
                    double slp = -1 / 25.0;
                    double b = 2;
                    res[i] = slp * x + b;
                }
            }
        } else if (i == 1) { // Normal
            if (x >= 25 && x <= 75) {
                if (x >= 25 && x <= 50) {
                    double slp = 1 / 25.0;
                    double b = -1;
                    res[i] = slp * x + b;
                } else {
                    double slp = -1 / 25.0;
                    double b = 3;
                    res[i] = slp * x + b;
                }
            }
        } else if (i == 2) { // High
            if (x >= 50 && x <= 100) {
                double slp = 1 / 50.0;
                double b = 0;
                res[i] = slp * x + b;
            }
        }
    }
    if (res[0] > res[1] && res[0] > res[2]) return 0; // Then Risk is Low
    else if (res[1] >= res[0] && res[1] > res[2]) return 1; // Then Risk is Medium
    else return 2; // Then Risk is High
}

int main() {
    cout << "Variables: ";
    int variables;
    cin >> variables;
    cout << "Project Fund: ";
    int projectFund;
    cin >> projectFund;
    cout << "Experience Level: ";
    int expLevel;
    cin >> expLevel;

    vector<double> fundMembershipRes = fundMembership(projectFund);
    vector<double> expMembershipRes = expMembership(expLevel);

    vector<double> R(3); // Inference Rules
    R[0] = max(fundMembershipRes[3], expMembershipRes[2]);
    R[1] = max(min(fundMembershipRes[2], expMembershipRes[1]), expMembershipRes[0]);
    R[2] = max(fundMembershipRes[0], min(fundMembershipRes[1], expMembershipRes[0]));

    double res = 0; // mean weighted average
    res += R[0] * 25 + R[1] * 50 + R[3] * 83.333333; // sum of R * centroids / sum of R
    res /= R[0] + R[1] + R[3];
    cout << "Predicted Value (Risk): " << res << "\n";
    int risk = getRisk(res); // expected Risk class
    if (risk == 0) cout << "Risk will be Low\n";
    else if (risk == 1) cout << "Risk will be Normal\n";
    else cout << "Risk will be High\n";
}