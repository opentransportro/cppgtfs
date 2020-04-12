// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_CONTCONTAINER_H_
#define AD_CPPGTFS_GTFS_CONTCONTAINER_H_

#include <algorithm>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace ad::cppgtfs::gtfs
{
    template<typename T>
    class ContContainer
    {
    public:
        ContContainer() :
            _final(false){};

        T* add(const T& obj);

        bool remove(const std::string& id);

        const T* get(const std::string& id) const;

        T* get(const std::string& id);

        const T* getRef(const std::string& id) const;

        T* getRef(const std::string& id);

        size_t size() const;

        void finalize();

        typename std::vector<T>::const_iterator begin() const;

        typename std::vector<T>::iterator begin();

        typename std::vector<T>::const_iterator end() const;

        typename std::vector<T>::iterator end();

    private:
        std::vector<T> _vec;
        bool _final;
    };

    template<typename T>
    struct ContCompCmp
    {
        bool operator()(const T& lh, const T& rh) const
        {
            return lh.getId() < rh.getId();
        }
    };

    template<typename T>
    struct ContCompCmp2
    {
        bool operator()(const T& lh, const std::string& rh) const
        {
            return lh.getId() < rh;
        }
    };
#include "ContContainer.tpp"
}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_CONTCONTAINER_H_
