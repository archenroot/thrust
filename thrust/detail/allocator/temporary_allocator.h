/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <thrust/detail/config.h>
#include <thrust/detail/allocator/tagged_allocator.h>
#include <thrust/detail/allocator/allocator_traits.h>
#include <thrust/pair.h>
//#include <thrust/detail/pointer.h>
//#include <thrust/detail/reference.h>
#include <thrust/memory.h>
#include <thrust/detail/dispatchable.h>

namespace thrust
{
namespace detail
{


// XXX the pointer parameter given to tagged_allocator should be related to
//     the type of the expression get_temporary_buffer(system, n).first
//     without decltype, compromise on pointer<T,System>
template<typename T, typename System>
  class temporary_allocator
    : public thrust::detail::tagged_allocator<
               T, System, thrust::pointer<T,System>
             >
{
  private:
    typedef thrust::detail::tagged_allocator<
      T, System, thrust::pointer<T,System>
    > super_t;

    System &m_system;

  public:
    typedef typename super_t::pointer   pointer;
    typedef typename super_t::size_type size_type;

    inline explicit temporary_allocator(thrust::dispatchable<System> &system) :
      super_t(),
      m_system(system.derived())
    {}

    pointer allocate(size_type cnt);

    void deallocate(pointer p, size_type n);

    inline System &system()
    {
      return m_system;
    } // end system()

  private:
    typedef thrust::pair<pointer, size_type> pointer_and_size;
}; // end temporary_allocator


} // end detail
} // end thrust

#include <thrust/detail/allocator/temporary_allocator.inl>

