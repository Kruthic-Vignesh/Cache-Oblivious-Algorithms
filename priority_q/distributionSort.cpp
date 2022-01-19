#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

//#include <MedianFind.h>

#define N 1000000000

using namespace std;

typedef long long ll;


//Non cache-oblivious median find
float findMedian(std::vector<ll> a)
{
    ll n = a.size();
    if (n % 2 == 0) {
        nth_element(a.begin(), a.begin() + n / 2, a.end());
        nth_element(a.begin(), a.begin() + (n - 1) / 2, a.end());
        return (float)(a[(n - 1) / 2] + a[n / 2]) / 2;
    }
    else {
        nth_element(a.begin(), a.begin() + n / 2, a.end());
        return (float)a[n / 2];
    }
}



void distributionSort(ll arr[], ll size);

class bucket {
public:
    float pivot;
    vector<ll> bckt;

    bucket() {
        pivot = N;
    }
};

void distributeBckts(vector<bucket>& bckts, ll arr[], ll& size, ll& rootSize, ll nextSubarr[], ll bnums[], ll& noSubarr, ll i, ll j, ll m) {
    if (m == 1) {
        if (bnums[i] != j)
            return;

        vector<bucket> tempExt;
        while (bckts.size() > j + 1) {
            tempExt.push_back(bckts[bckts.size() - 1]);
            bckts.pop_back();
        }

        bucket tempBkt;
        if (bckts.size() > j) {
            tempBkt = bckts[j];
            bckts.pop_back();
        }

        while (nextSubarr[i] - i * rootSize < rootSize && nextSubarr[i] < size) {
            if (arr[nextSubarr[i]] < tempBkt.pivot) {
                tempBkt.bckt.push_back(arr[nextSubarr[i]]);
                nextSubarr[i]++;
            }
            else {
                bnums[i]++;
                break;
            }
        }

        if (tempBkt.bckt.size() > 2 * rootSize || tempBkt.bckt.size() == size) {
            for (ll p = 0; p < noSubarr; p++)
                if (bnums[p] > j)
                    bnums[p]++;

            bucket tempBkt2;
            tempBkt2.pivot = tempBkt.pivot;
            tempBkt.pivot = findMedian(tempBkt.bckt);

            ll size1 = tempBkt.bckt.size() / 2;
            ll size2 = tempBkt.bckt.size() - size1;

            ll temp1[size1];
            ll temp2[size2];

            ll x = 0, y = 0;

            for (ll p = 0; p < tempBkt.bckt.size(); p++)
                if (tempBkt.bckt[p] < tempBkt.pivot) {
                    temp1[x] = tempBkt.bckt[p];
                    x++;
                }
                else {
                    temp2[y] = tempBkt.bckt[p];
                    y++;
                }


            distributionSort(temp1, size1);
            distributionSort(temp2, size2);

            tempBkt.bckt.clear();

            for (ll p = 0; p < size1; p++)
                tempBkt.bckt.push_back(temp1[p]);

            for (ll p = 0; p < size2; p++)
                tempBkt2.bckt.push_back(temp2[p]);

            bckts.push_back(tempBkt);
            bckts.push_back(tempBkt2);


        }
        else {
            ll temp[tempBkt.bckt.size()];
            for (ll p = 0; p < tempBkt.bckt.size(); p++)
                temp[p] = tempBkt.bckt[p];

            distributionSort(temp, tempBkt.bckt.size());
            for (ll p = 0; p < tempBkt.bckt.size(); p++)
                tempBkt.bckt[p] = temp[p];

            bckts.push_back(tempBkt);
        }

        while (tempExt.size()) {
            bckts.push_back(tempExt[tempExt.size() - 1]);
            tempExt.pop_back();
        }

    }
    else if (m) {
        if (m % 2 == 0) {
            distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, i, j, m / 2);
            distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, i + m / 2, j, m / 2);
            distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, i, j + m / 2, m / 2);
            distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, i + m / 2, j + m / 2, m / 2);
        }
        else {
            distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, i, j, m / 2);
            distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, i + m / 2, j, m / 2 + 1);
            distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, i, j + m / 2, m / 2 + 1);
            distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, i + m / 2, j + m / 2, m / 2 + 1);
        }
    }
}

void distributionSort(ll arr[], ll size) {
    if (size == 1)
        return;

    ll rootSize = sqrt(size);
    ll extra = size % rootSize;
    ll noSubarr = extra ? size / rootSize + 1 : size / rootSize;

    for (ll i = 0; i < size / rootSize; i++)
        distributionSort(&arr[i * rootSize], rootSize);
    if (extra)
        distributionSort(arr + size - extra, extra);

    ll nextSubarr[noSubarr];
    for (ll i = 0; i < size; i += rootSize)
        nextSubarr[i / rootSize] = i;

    ll bnums[noSubarr];
    for (ll i = 0; i < noSubarr; i++)
        bnums[i] = 0;

    vector<bucket> bckts;

    distributeBckts(bckts, arr, size, rootSize, nextSubarr, bnums, noSubarr, 0, 0, noSubarr);

    ll temp = 0;
    for (ll i = 0; i < bckts.size(); i++)
        for (ll j = 0; j < bckts[i].bckt.size(); j++) {
            arr[temp] = bckts[i].bckt[j];
            temp++;
        }

}

int main() {
    ll size;
    cin >> size;

    ll arr[size];
    for (ll i = 0; i < size; i++)
        cin >> arr[i];

    distributionSort(arr, size);

    for (ll i = 0; i < size; i++)
        cout << arr[i] << " ";

    cout << std::endl;
}