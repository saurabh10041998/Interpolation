#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
// lets just stick to quadratic interpolation then we do generic..

struct data {
    double time;
    double x;
};

#define data struct data
vector<data> samples;


//Main solution


//function which calculates the coefficient of newtons divided diff polynomial..
vector<double> calculateCoefficient(vector<double> &dp, int k, vector<data> dsamples) {
    int n = dp.size();
    vector<double>b(k+1);
    cout<<"b0 "<<dp[0]<<endl;
    b[0] = dp[0];
    for(int i = 1; i <= (k); i++) {
        for(int j = 0; j < n - i; j++) {
            dp[j] = (dp[j + 1] - dp[j]) / (dsamples[j+i].time - dsamples[j].time);
        }
        cout<<"b"<<i<<" "<<dp[0]<<endl;
        b[i] = dp[0];
    }
    return b;

}

double NDDP(vector<double>b, vector<data>dsamples, int t) {
    double ans = 0;
    for(int i = 0; i < b.size(); i++) {
        double term = b[i];
        for(int j = 0; j < i; j++) {
            term *= (t - dsamples[j].time);
        }
        ans += term;
    }
    return ans;
}

void solve(double t) {
    //choose the points..
    int k = 2;          //quadratic interpolation..
    //choosing points..
    vector<data>dsamples(3);        // dsamples --> drawn samples.. and 3 = 2 + 1 (k + 1)
    
    //TODO: logic to choose sample points depending on t.
    int startindex = 1;

    int j = 0;
    for(int i = startindex; i <= startindex + k; i++) {
        dsamples[j++] = samples[i];
    }    
    vector<double> dp;
    for(int i = 0; i < dsamples.size(); i++) {
        dp.push_back(dsamples[i].x);
    }

    //calculating the coefficients..
    vector<double> b = calculateCoefficient(dp, k, dsamples);

    double ans = NDDP(b, dsamples, t);

    cout<<ans<<endl;
    
}

int main() {
    // Input the data..
    double time, x;

    // Number of sample..
    int n = 6;
    

    samples.resize(n+1);
    for(int i = 0; i < n; i++) {
        cin>>time>>x;
        samples[i] = {time, x};
    }

    //finding the approx value of the x at t = 16..
    double t = 16;

    solve(t);
    return 0;
}
