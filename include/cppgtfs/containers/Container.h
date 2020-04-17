// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_CONTAINER_H_
#define AD_CPPGTFS_GTFS_CONTAINER_H_

#include <string>
#include <unordered_map>

namespace cppgtfs::gtfs
{
    template<typename T>
    class Container
    {
    public:
        Container() = default;
        ~Container();

        /**
         * Adds a object of type T into the container and returns a reference to it
         * @param ent - entity to be inserted into container
         * @return pointer to inserted object
         */
        [[maybe_unused]] T* add(const T& ent);
        bool remove(const std::string& id);

        const T* get(const std::string& id) const;
        T* get(const std::string& id);

        const T* getRef(const std::string& id) const { return get(id); }
        T* getRef(const std::string& id) { return get(id); }
        [[nodiscard]] size_t size() const;

        void finalize(){}

        typename std::unordered_map<std::string, T*>::const_iterator begin() const;
        typename std::unordered_map<std::string, T*>::iterator begin();

        typename std::unordered_map<std::string, T*>::const_iterator end() const;
        typename std::unordered_map<std::string, T*>::iterator end();

    private:
        std::unordered_map<std::string, T*> _map {};
    };

    // ____________________________________________________________________________
    template<typename T>
    Container<T>::~Container()
    {
        for (auto i : _map) {
            delete i.second;
        }
    }

    // ____________________________________________________________________________
    template<typename T>
    T* Container<T>::add(const T& ent)
    {
        T* c = new T(ent);
        if (_map.insert(std::pair<std::string, T*>(T::getId(c), c)).second) {
            return c;
        }
        return 0;
    }

    // ____________________________________________________________________________
    template<typename T>
    bool Container<T>::remove(const std::string& id)
    {
        return _map.erase(id);
    }

    // ____________________________________________________________________________
    template<typename T>
    T* Container<T>::get(const std::string& id)
    {
        if (_map.find(id) != _map.end()) {
            return _map.find(id)->second;
        }
        return 0;
    }

    // ____________________________________________________________________________
    template<typename T>
    const T* Container<T>::get(const std::string& id) const
    {
        if (_map.find(id) != _map.end()) {
            return _map.find(id)->second;
        }
        return 0;
    }

    // ____________________________________________________________________________
    template<typename T>
    size_t Container<T>::size() const
    {
        return _map.size();
    }

    // ____________________________________________________________________________
    template<typename T>
    typename std::unordered_map<std::string, T*>::const_iterator
    Container<T>::begin() const
    {
        return _map.begin();
    }

    // ____________________________________________________________________________
    template<typename T>
    typename std::unordered_map<std::string, T*>::iterator Container<T>::begin()
    {
        return _map.begin();
    }

    // ____________________________________________________________________________
    template<typename T>
    typename std::unordered_map<std::string, T*>::const_iterator Container<T>::end()
    const
    {
        return _map.end();
    }

    // ____________________________________________________________________________
    template<typename T>
    typename std::unordered_map<std::string, T*>::iterator Container<T>::end()
    {
        return _map.end();
    }

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_CONTAINER_H_
