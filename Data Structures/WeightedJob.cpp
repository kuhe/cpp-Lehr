#include "WeightedJob.h"

WeightedJob::WeightedJob() {

}
WeightedJob::WeightedJob(double weight, double length) : weight(weight), length(length) {};
WeightedJob::WeightedJob(string weight, string length) {
    this->weight = stod(weight); this->length = stod(length);
}
bool WeightedJob::higherPriorityRatio(const WeightedJob& self, const WeightedJob& other) {
    double ownPriority, otherPriority;
    ownPriority = self.weight / self.length;
    otherPriority = other.weight / other.length;
    return ownPriority > otherPriority;
};
bool WeightedJob::operator > (const WeightedJob& other) const {
    double ownPriority = getPriority();
    double otherPriority = other.getPriority();
    bool comparison = ownPriority > otherPriority;
    if (comparison) {
        return true;
    }
    if (ownPriority == otherPriority) {
        return weight > other.weight;
    }
    return false;
};
bool WeightedJob::operator == (const WeightedJob& other) const {
    return weight == other.weight && length == other.length;
};
bool WeightedJob::operator < (const WeightedJob& other) const {
    return !(operator == (other)) && !(operator > (other));
};
double WeightedJob::getPriority() const {
    return weight - length;
}