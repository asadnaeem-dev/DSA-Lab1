// Lab 9 - Task 3: Weighted M-ary Tree - Galaxy Representation Problem
// Asad Naeem - 541495 - BSDS 3A
//
// Each StarSystem is a node of an M-ary tree. Each edge from a parent to a
// child is a TravelRoute carrying a travel cost. The Galaxy class owns the
// tree and provides:
//   * is_balanced(x)  - for every node, the sizes of all M child subtrees
//                       differ by at most 1 (an empty child slot has size 0)
//   * count_leaves(x) - number of leaf systems in the subtree rooted at x

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class StarSystem;

// ---------------- TravelRoute ----------------
class TravelRoute {
public:
    float travel_cost;
    StarSystem* destination;

    TravelRoute(float cost = 0.0f, StarSystem* dest = nullptr)
        : travel_cost(cost), destination(dest) {}
};

// ---------------- StarSystem ----------------
class StarSystem {
public:
    int system_id;
    string name;
    int num_planets;
    float x, y, z;
    bool is_habitable;
    vector<TravelRoute> routes;   // outgoing edges to children (at most M)

    StarSystem(int id, const string& n, int planets,
               float px, float py, float pz, bool habitable)
        : system_id(id), name(n), num_planets(planets),
          x(px), y(py), z(pz), is_habitable(habitable) {}
};

// ---------------- Galaxy ----------------
class Galaxy {
private:
    int M;
    StarSystem* root;

    StarSystem* find(StarSystem* node, int id) const {
        if (node == nullptr) return nullptr;
        if (node->system_id == id) return node;
        for (const TravelRoute& r : node->routes) {
            StarSystem* res = find(r.destination, id);
            if (res) return res;
        }
        return nullptr;
    }

    // Returns the size of the subtree at `node`, or -1 if any node inside
    // it is unbalanced. One post-order pass -> O(n).
    int balancedSize(StarSystem* node) const {
        if (node == nullptr) return 0;

        int total = 1;
        int minSize = -1, maxSize = -1;
        for (const TravelRoute& r : node->routes) {
            int s = balancedSize(r.destination);
            if (s == -1) return -1;                // imbalance found below
            total += s;
            if (minSize == -1 || s < minSize) minSize = s;
            if (s > maxSize) maxSize = s;
        }
        // Unused child slots of an M-ary node are empty subtrees of size 0
        if ((int)node->routes.size() < M) minSize = 0;
        if (maxSize == -1) maxSize = 0;

        if (maxSize - minSize > 1) return -1;
        return total;
    }

    void print(StarSystem* node, const string& prefix, float costSoFar) const {
        for (size_t i = 0; i < node->routes.size(); i++) {
            const TravelRoute& r = node->routes[i];
            bool last = (i == node->routes.size() - 1);
            StarSystem* c = r.destination;
            cout << prefix << (last ? "`-- " : "|-- ")
                 << "(" << fixed << setprecision(1) << r.travel_cost << ") "
                 << c->name << " [id " << c->system_id << ", "
                 << c->num_planets << " planets"
                 << (c->is_habitable ? ", habitable" : "")
                 << ", total cost " << costSoFar + r.travel_cost << "]" << endl;
            print(c, prefix + (last ? "    " : "|   "), costSoFar + r.travel_cost);
        }
    }

    void destroy(StarSystem* node) {
        if (node == nullptr) return;
        for (TravelRoute& r : node->routes) destroy(r.destination);
        delete node;
    }

public:
    // Overloaded constructors
    Galaxy() : M(2), root(nullptr) {}
    Galaxy(int m, StarSystem* rootNode = nullptr) : M(m), root(rootNode) {}
    ~Galaxy() { destroy(root); }

    StarSystem* getRoot() const { return root; }
    int getM() const { return M; }

    // Adds `child` under the system with id `parent_id` with the given cost.
    bool add_system(int parent_id, StarSystem* child, float cost) {
        if (root == nullptr) {
            root = child;
            return true;
        }
        StarSystem* parent = find(root, parent_id);
        if (parent == nullptr) {
            cout << "  ! Parent " << parent_id << " not found, "
                 << child->name << " not added." << endl;
            delete child;
            return false;
        }
        if ((int)parent->routes.size() >= M) {
            cout << "  ! " << parent->name << " already has " << M
                 << " routes, " << child->name << " not added." << endl;
            delete child;
            return false;
        }
        parent->routes.push_back(TravelRoute(cost, child));
        return true;
    }

    bool is_balanced(StarSystem* x) const {
        return balancedSize(x) != -1;
    }

    int count_leaves(StarSystem* x) const {
        if (x == nullptr) return 0;
        if (x->routes.empty()) return 1;
        int leaves = 0;
        for (const TravelRoute& r : x->routes) leaves += count_leaves(r.destination);
        return leaves;
    }

    StarSystem* find(int id) const { return find(root, id); }

    void display() const {
        if (root == nullptr) {
            cout << "(empty galaxy)" << endl;
            return;
        }
        cout << root->name << " [id " << root->system_id << ", "
             << root->num_planets << " planets"
             << (root->is_habitable ? ", habitable" : "") << "]  (root)" << endl;
        print(root, "", 0.0f);
    }
};

void report(const Galaxy& g, StarSystem* x) {
    cout << "  is_balanced(" << x->name << ")  : "
         << (g.is_balanced(x) ? "true" : "false") << endl;
    cout << "  count_leaves(" << x->name << ") : " << g.count_leaves(x) << endl;
}

int main() {
    cout << "===== Task 3: Weighted M-ary Tree - Galaxy =====" << endl << endl;

    // a) Construct the data structures (M = 3, root given to the constructor)
    StarSystem* sol = new StarSystem(1, "Sol", 8, 0, 0, 0, true);
    Galaxy galaxy(3, sol);
    cout << "Galaxy created with M = " << galaxy.getM()
         << ", root = " << galaxy.getRoot()->name << endl << endl;

    galaxy.add_system(1, new StarSystem(2, "AlphaCentauri", 3, 4.3f, 1.1f, 0.2f, false), 4.3f);
    galaxy.add_system(1, new StarSystem(3, "Sirius", 2, 8.6f, -2.0f, 1.5f, false), 8.6f);
    galaxy.add_system(1, new StarSystem(4, "Vega", 5, 25.0f, 3.2f, -4.1f, true), 25.0f);
    galaxy.add_system(2, new StarSystem(5, "Proxima", 1, 4.2f, 1.0f, 0.3f, true), 0.5f);
    galaxy.add_system(3, new StarSystem(6, "SiriusB", 0, 8.7f, -2.1f, 1.4f, false), 1.2f);
    galaxy.add_system(4, new StarSystem(7, "Lyra", 4, 26.5f, 3.0f, -4.4f, true), 2.8f);

    cout << "--- Galaxy 1 (route costs in brackets) ---" << endl;
    galaxy.display();
    cout << endl;
    report(galaxy, galaxy.getRoot());
    report(galaxy, galaxy.find(2));
    cout << endl;

    // Trying to exceed M routes from one system
    cout << "Adding a 4th route from Sol (M = 3):" << endl;
    galaxy.add_system(1, new StarSystem(99, "Betelgeuse", 6, 600, 10, 10, false), 640.0f);
    cout << endl;

    // b) Make it unbalanced: grow the AlphaCentauri branch deeper
    galaxy.add_system(5, new StarSystem(8, "Kepler", 7, 4.0f, 1.3f, 0.6f, true), 3.1f);
    galaxy.add_system(8, new StarSystem(9, "Gliese", 2, 3.8f, 1.6f, 0.9f, false), 2.2f);

    cout << "--- Galaxy 2 (after adding Kepler and Gliese) ---" << endl;
    galaxy.display();
    cout << endl;
    report(galaxy, galaxy.getRoot());
    report(galaxy, galaxy.find(3));
    cout << endl;

    // c) Fill out branches so leaves increase and subtree sizes even out
    galaxy.add_system(2, new StarSystem(10, "Ross128", 1, 4.9f, 1.4f, 0.1f, false), 1.9f);
    galaxy.add_system(3, new StarSystem(11, "Procyon", 2, 9.1f, -1.8f, 1.7f, false), 2.4f);
    galaxy.add_system(3, new StarSystem(12, "Luyten", 1, 9.3f, -2.4f, 1.2f, true), 1.6f);
    galaxy.add_system(4, new StarSystem(13, "Altair", 3, 26.0f, 2.5f, -3.9f, false), 3.5f);
    galaxy.add_system(4, new StarSystem(14, "Deneb", 0, 27.2f, 4.1f, -5.0f, false), 4.0f);

    cout << "--- Galaxy 3 (more systems added) ---" << endl;
    galaxy.display();
    cout << endl;
    report(galaxy, galaxy.getRoot());
    report(galaxy, galaxy.find(4));

    return 0;
}
