#ifndef _SWAPSORT_
#define _SWAPSORT_
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
using namespace std;
using State = vector<int>;
class SwapSort
{
private:
    set<list<State>> _paths;
    set<list<State>> _solutions;
    set<State> _explored;
public:
    SwapSort(State init)
    {
        list<State> ls;
        ls.push_back(init);
        _paths.insert(ls);
    }

    void show_solutions()
    {
        if (_solutions.size()==0) {
            cout << "No solution.\n";
        } else {
            for (auto p : _solutions) {
                for (auto s : p) {
                    for (auto i : s) {
                        cout << i << " ";
                    }
                    cout << "-> ";
                }
                cout << ".\n";
            }
        }
    }

    set<State> extend(State s); /// ( the first with the second )|| ( the first with the last )
    void solve(int steps);
};
bool isSorted(State s) {
    int before = s.front();
    for(int i : s)
        if(before > i)
            return false;
        else
        	before = i;
    return true;
}

set<State>
SwapSort::extend(State s) {
    set<State> extended;
    State second = s;

    second[0] = second[0] + second[1];
    second[1] = second[0] - second[1];
    second[0] = second[0] - second[1];

    s.front() = s.front() + s.back();
    s.back() = s.front() - s.back();
    s.front() = s.front() - s.back();

    extended.insert(second);
    extended.insert(s);

    return extended;
}

void
SwapSort::solve(int steps) {
    while (steps--) {
        set<list<State>> newPaths;
        set<list<State>> oldPaths;

        for (list<State> now_path : _paths) {
            _explored.insert(now_path.back());

            set<State> nextStates = extend(now_path.back());
            for (State extended_state : nextStates) {
                    if (isSorted(extended_state)) {
                        list<State> new_path = now_path;
                        new_path.push_back(extended_state);
                        _solutions.insert(new_path);
                    }
                    else {
                        auto search = _explored.find(extended_state);  ///Duplicate check
                        if (search == _explored.cend()) {               ///search is the latest one >>> did not appear before
                            list<State> new_path = now_path;
                            new_path.push_back(extended_state);
                            newPaths.insert(new_path);
                        }
                    }
                }
                oldPaths.insert(now_path);
            }

        for (list<State> p : oldPaths)
            _paths.erase(p);
        for (list<State> p : newPaths)
            _paths.insert(p);
    }
}
#endif
