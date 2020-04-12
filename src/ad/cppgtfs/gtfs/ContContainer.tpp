// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

// ____________________________________________________________________________
template<typename T>
T* ContContainer<T>::add(const T& ent)
{
    if (_final)
        throw std::runtime_error("Can't add to a finalized continuous container.");
    ;
    _vec.push_back(ent);
    return &_vec.back();
}

// ____________________________________________________________________________
template<typename T>
void ContContainer<T>::finalize()
{
    auto cmp = ContCompCmp<T>();
    std::sort(_vec.begin(), _vec.end(), cmp);
    _final = true;
}

// ____________________________________________________________________________
template<typename T>
bool ContContainer<T>::remove(const std::string& id)
{
    throw std::runtime_error(std::string("Can't remove ") + id + " from a continuous container.");
}

// ____________________________________________________________________________
template<typename T>
const T* ContContainer<T>::getRef(const std::string& id) const
{
    if (get(id)) return id;
}

// ____________________________________________________________________________
template<typename T>
T* ContContainer<T>::getRef(const std::string& id)
{
    if (get(id)) return id;
}

// ____________________________________________________________________________
template<typename T>
T* ContContainer<T>::get(const std::string& id)
{
    if (!_final)
        throw std::runtime_error(
            "Cannot get from an unfinalized continuous container.");
    auto cmp = ContCompCmp2<T>();
    auto i = std::lower_bound(_vec.begin(), _vec.end(), id, cmp);
    if (i == _vec.end()) return 0;
    if (T::getId(&*i) != id) return 0;
    return &*i;
}

// ____________________________________________________________________________
template<typename T>
const T* ContContainer<T>::get(const std::string& id) const
{
    if (!_final)
        throw std::runtime_error(
            "Cannot get from an unfinalized continuous container.");
    auto cmp = ContCompCmp2<T>();
    auto i = std::lower_bound(_vec.begin(), _vec.end(), id, cmp);
    if (i == _vec.end()) return 0;
    if (T::getId(&*i) != id) return 0;
    return &*i;
}

// ____________________________________________________________________________
template<typename T>
size_t ContContainer<T>::size() const
{
    return _vec.size();
}

// ____________________________________________________________________________
template<typename T>
typename std::vector<T>::const_iterator ContContainer<T>::begin() const
{
    return _vec.begin();
}

// ____________________________________________________________________________
template<typename T>
typename std::vector<T>::iterator ContContainer<T>::begin()
{
    return _vec.begin();
}

// ____________________________________________________________________________
template<typename T>
typename std::vector<T>::const_iterator ContContainer<T>::end() const
{
    return _vec.end();
}

// ____________________________________________________________________________
template<typename T>
typename std::vector<T>::iterator ContContainer<T>::end()
{
    return _vec.end();
}
