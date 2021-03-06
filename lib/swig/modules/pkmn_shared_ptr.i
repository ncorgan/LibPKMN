/*
 * Copyright (c) 2016,2018 Nicholas Corgan (n.corgan@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

%include <stdint.i>

namespace std
{
    template <class T> class shared_ptr
    {
        public:
            shared_ptr() {}
            shared_ptr(T* p) {}

            T* operator->() {
                return px;
            }

            %extend {
                /*
                 * This should be uintptr_t, but SWIG converts it to unsigned int,
                 * even on 64-bit platforms.
                 */
                uintmax_t __cptr() const {
                    return uintmax_t(self->get());
                }

                bool __sptr_eq(const std::shared_ptr<T> &rhs) {
                    return ((*self) == rhs);
                }
            }

    private:
        T* px;
        int pn;
    };
}
