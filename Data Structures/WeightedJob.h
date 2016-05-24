#ifndef CPPREF_WEIGHTEDJOB_H
#define CPPREF_WEIGHTEDJOB_H

#include <string>

using std::string;

/**
 * Basic example of an order-able type.
 */
class WeightedJob {
public:
    double weight;
    double length;
    WeightedJob();
    WeightedJob(double weight, double length);
    WeightedJob(string weight, string length);
    static bool higherPriorityRatio(const WeightedJob& self, const WeightedJob& other);
    bool operator > (const WeightedJob& other) const;
    bool operator == (const WeightedJob& other) const;
    bool operator < (const WeightedJob& other) const;
    double getPriority() const;
};

#endif //CPPREF_WEIGHTEDJOB_H
