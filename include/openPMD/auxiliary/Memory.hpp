#pragma once

#include "openPMD/Dataset.hpp"
#include "openPMD/Datatype.hpp"

#include <functional>
#include <memory>
#include <utility>


namespace openPMD
{
namespace auxiliary
{
std::unique_ptr< void, std::function< void(void*) > >
allocatePtr(Datatype dtype, Extent const& e);

std::unique_ptr< void, std::function< void(void*) > >
allocatePtr(Datatype dtype, size_t numPoints);

inline std::unique_ptr< void, std::function< void(void*) > >
allocatePtr(Datatype dtype, Extent const& e)
{
  size_t numPoints = 1;
  for( auto const& dimensionSize : e )
    numPoints *= dimensionSize;
  return allocatePtr(dtype, numPoints);
}

inline std::unique_ptr< void, std::function< void(void*) > >
allocatePtr(Datatype dtype, size_t numPoints)
{
    void* data = nullptr;
    std::function< void(void*) > del = [](void*){};
    switch( dtype )
    {
        using DT = Datatype;
        case DT::VEC_STRING:
            data = new char*[numPoints];
            del = [](void* p){ delete[] static_cast< char** >(p); };
            break;
        case DT::VEC_LONG_DOUBLE:
        case DT::LONG_DOUBLE:
            data = new long double[numPoints];
            del = [](void* p){ delete[] static_cast< long double* >(p); };
            break;
        case DT::ARR_DBL_7:
        case DT::VEC_DOUBLE:
        case DT::DOUBLE:
            data = new double[numPoints];
            del = [](void* p){ delete[] static_cast< double* >(p); };
            break;
        case DT::VEC_FLOAT:
        case DT::FLOAT:
            data = new float[numPoints];
            del = [](void* p){ delete[] static_cast< float* >(p); };
            break;
        case DT::VEC_INT16:
        case DT::INT16:
            data = new int16_t[numPoints];
            del = [](void* p){ delete[] static_cast< int16_t* >(p); };
            break;
        case DT::VEC_INT32:
        case DT::INT32:
            data = new int32_t[numPoints];
            del = [](void* p){ delete[] static_cast< int32_t* >(p); };
            break;
        case DT::VEC_INT64:
        case DT::INT64:
            data = new int64_t[numPoints];
            del = [](void* p){ delete[] static_cast< int64_t* >(p); };
            break;
        case DT::VEC_UINT16:
        case DT::UINT16:
            data = new uint16_t[numPoints];
            del = [](void* p){ delete[] static_cast< uint16_t* >(p); };
            break;
        case DT::VEC_UINT32:
        case DT::UINT32:
            data = new uint32_t[numPoints];
            del = [](void* p){ delete[] static_cast< uint32_t* >(p); };
            break;
        case DT::VEC_UINT64:
        case DT::UINT64:
            data = new uint64_t[numPoints];
            del = [](void* p){ delete[] static_cast< uint64_t* >(p); };
            break;
        case DT::VEC_CHAR:
        case DT::CHAR:
            data = new char[numPoints];
            del = [](void* p){ delete[] static_cast< char* >(p); };
            break;
        case DT::VEC_UCHAR:
        case DT::UCHAR:
            data = new unsigned char[numPoints];
            del = [](void* p){ delete[] static_cast< unsigned char* >(p); };
            break;
        case DT::BOOL:
            data = new bool[numPoints];
            del = [](void* p){ delete[] static_cast< bool* >(p); };
            break;
        case DT::STRING:
            /* user assigns c_str pointer */
            break;
        case DT::UNDEFINED:
        default:
            throw std::runtime_error("Unknown Attribute datatype");
    }

    return std::unique_ptr< void, std::function< void(void*) > >(data, del);
}
} // auxiliary
} // openPMD
