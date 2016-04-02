/**
* \file datamanager.hpp
*
* \author Sarah Scheffler and /TODO add yourselves
*
* \brief Data manager header file
*/

#ifndef DATAMANAGER_HPP_INCLUDED
#define DATAMANAGER_HPP_INCLUDED 1

#include <set>
#include <vector>

/**
* \class DataManager
*
* \brief A class for managing CSV-stored data.  For now, assumes all data are homogeneous
* and stored in a CSV
*/
template <class T>
class DataManager {

    /// A point is defined to be a vector of T's
	typedef vector<T> point;

    /// Number of means
	int k_;

	/// The csv file containing the data
	char* dataFile_;

	/// The current best guess at the means
	std::set<point> means_;

	/// Lower bounds
	std::set<point> lowerBounds_;

	/// Upper bounds
	std::set<point> upperBounds_;

	bool stoppingCriterion_ ( bool (*f)(/*what as inputs to this?*/) );

public: 

    /// Operators to check if two DataManagers have the same Agreement - same k, T, and bounds
	bool operator==(const DataManager &other) const;
    bool operator!=(const DataManager &other) const;

    /// Getter for means
	std::set<point> getMeans();

	/// Get sum of all points closest to the given mean
	point sumPointsInCluster(point mean);

    /// Get random means within the bounds
	set<point> getRandomMeans();

private:

    /// returns the mean the point is closest to
	point getClosestMean(point dataPoint); 

    /// Calculate new k means based on distance (only done by server)
	std::set<point> getNewMeans(int k, char* dataFile);


}