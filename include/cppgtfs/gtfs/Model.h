//
// Created by vvesa on 18.04.2020.
//

#ifndef CPPGTFS_MODEL_H
#define CPPGTFS_MODEL_H

#include <cppgtfs/containers/Container.h>
#include <cppgtfs/containers/ContContainer.h>

#include <memory>
#include <vector>

namespace cppgtfs::gtfs
{
    /**
     * Utility class used to define common smart pointer types available for the wrapped object
     * @tparam WrappedObject - wrapped object type
     */
    template< typename WrappedObject>
    class PointerWrapper
    {
    public:
        using SharedPtr = std::shared_ptr<WrappedObject>;
        using WeakPtr = std::weak_ptr<WrappedObject>;
        using UniquePtr = std::unique_ptr<WrappedObject>;
        using RawPtr = WrappedObject*;
    };

    /**
     * Utility class used to define container type used for the wrapped object
     * @tparam WrappedObject - wrapped object type
     * @tparam ContainerType - container type used
     */
    template<
        typename WrappedObject,
        template<typename> class ContainerType
    >
    class ContainerWrapper
    {
    public:
        using Container = ContainerType<WrappedObject>;

    };

    /**
     * Model wrapper class used to wrap common model and fields for model
     * @tparam WrappedFields
     * @tparam WrappedObject
     */
    template<
        typename WrappedFields,
        typename WrappedObject
    >
    class ModelWrapper:  public WrappedObject
    {
    public:
        using Fields = WrappedFields;
        using Object = WrappedObject;


        template<class ... Types>
        static Object create(Types&&... args)
        {
            return Object{std::forward<Types>(args)...};
        }

        template<class ... Types>
        ModelWrapper(Types ... args): Object(args...) { }

        ModelWrapper(): Object() {}

        ModelWrapper(const WrappedObject& object): Object(object) { }

        ModelWrapper(const Object&& object): Object(object) { }

        const Object& object() const
        {
            return *this;
        }

        Object& object()
        {
            return *this;
        }

        static Fields& fields()
        {
            return ModelWrapper<Fields ,Object>::flds;
        }

    private:
        static Fields flds;
    };

    template<
        typename WrappedFields,
        typename WrappedObject
    >
    WrappedFields ModelWrapper<WrappedFields, WrappedObject>::flds = ModelWrapper::Fields();


    template<
        typename WrappedObject,
        template<typename> class ContainerT = Container
    >
    class Model:
        public ModelWrapper<typename WrappedObject::Fields, WrappedObject>,
        public PointerWrapper<WrappedObject>,
        public ContainerWrapper<WrappedObject, ContainerT>
    {
    public:
        template<class ... Types>
        Model(Types ... args): ModelWrapper<typename WrappedObject::Fields,WrappedObject>(args...) { }
    };

}



#endif    //CPPGTFS_MODEL_H
