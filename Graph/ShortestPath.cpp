#include "../Defines.h"

typedef pair<ll, int> pli;
typedef vector<pli> vpli;
typedef vector<vpli> vvpli;

/* START SOLUTION */

// O(|V|^2)
// Can't handle negative edges.
// el    : an edge list of the form {weight, to}
// dads  : init with (|V|, -1), to be filled
// dists : init with (|V|, LLONG_MAX/2), to be filled
//         can use a vis array instead if dists arent needed
// start : starting node
// returns the weight of the minimum spanning tree or -1 if 
//         not connected
void dijkstras(vvpli& el, vll& dists, vi& dads, int start) {
  set<pli> pq; // weight, node

  dists[start] = 0;
  pq.insert({0, start});
  while (!pq.empty()) {
    ll w = pq.begin()->first;
    int n = pq.begin()->second;
    pq.erase(pq.begin());
    if (w > dists[n]) continue;

    for (auto& e : el[n]) { // {weight, to}
      ll d = dists[n] + e.first;
      if (d < dists[e.second]) {
        dists[e.second] = d;
        dads[e.second] = n;
        pq.insert({d, e.second});
      }
    }
  }
}

// O(|V|*|E|)
// el    : an edge list of the form {weight, to}
// dists : init with (|V|, LLONG_MAX/2)
// dads  : init with (|V|, -1)
void bellman_ford(vvpli& el, vll& dists, vi& dads, int s) {
  int N = el.size();
  dists[s] = 0;
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (auto& e : el[i]) {
        ll w = e.first;
        int j = e.second;
        if (dists[i] + w < dists[j]) {
          dists[j] = dists[i] + w;
          dads[j] = i;
        }
      }
    }
  }
}

/* END SOLUTION */

// http://uva.onlinejudge.org/external/3/341.html
int main() {
  int caze = 1;
  while (true) {
    int N;
    cin >> N;
    if (N == 0) break;

    vvpli el(N, vpli()); // to, weight
    for (int i = 0; i < N; i++) {
      int M; cin >> M;
      for (int j = 0; j < M; j++) {
        int to, w;
        cin >> to >> w;
        el[i].push_back({w, to-1});
      }
    }

    int start, end;
    cin >> start >> end;
    --start;
    --end;

    cout << "Case " << caze++ << ": ";
    vi dads(N, -1);
    vll dists(N, LLONG_MAX/2);
    bellman_ford(el, dists, dads, start);

    stack<ll> ans;
    int n = end;
    while (n != start) {
      ans.push(n);
      n = dads[n];
    }
    ans.push(start);

    cout << "Path =";
    while (!ans.empty()) {
      cout << " " << (ans.top() + 1);
      ans.pop();
    }
    cout << "; " << dists[end] << " second delay" << endl;
  }
}